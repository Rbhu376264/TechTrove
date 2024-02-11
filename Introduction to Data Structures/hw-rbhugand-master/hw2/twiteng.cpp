#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "twiteng.h"
// Add other header files
#include "tweet.h"
#include "util.h"
#include "user.h"


using namespace std;


// Update as needed
TwitEng::TwitEng()
{

}

// Update as needed
TwitEng::~TwitEng()
{
  for(std::map<std::string ,User*> ::iterator it = myMap.begin(); it!= myMap.end(); ++it)
  {
    delete it->second;
    
  }

}

// Complete this function
bool TwitEng::parse(char* filename)
{
  ifstream ifile(filename);
  if (ifile.fail()) {
    cerr << "Unable to open " << filename << endl;
    return true;
  }
  int numUsers;
  ifile >> numUsers;
  if (ifile.fail()) {
    cerr << "Unable to read number of users " << endl;
    ifile.close();
    return true;
  }
  // Finish the parsing of the input file. Return false if successful,
  // true otherwise.
  string empty;
  getline(ifile,empty);
  int inc = 0;
  while(inc != numUsers)
  {
    string line, word;
    getline(ifile,line);
    // cout<<line<<endl;
    if(ifile.fail())
    {
      cerr << "Unable to users " << endl;
      ifile.close();
      return true;

    }
    stringstream ss(line);
    ss>>word;
    // cout<<word<<endl;
    User* x;
    std::map<string ,User*>::iterator it = myMap.find(word);
    if(it == myMap.end())
    {
      x = new User(word);
      myMap.insert(make_pair(word,x));
    }
    else
    {
      x = it->second;
    }
    
    while(ss>>word)
    {
      // cout<<word<<endl;
      User * y; 
      it = myMap.find(word);
      if(it == myMap.end())
      {

        y = new User(word);
        myMap.insert(make_pair(word,y));
        
      }
      else
      {  
        y = it->second;
      }
      x->addFollowing(y);
      y->addFollower(x);
    }
    inc++;
  }

  // int counter = 0;

  while(true)
  {
    string line, word, tweet_text;
    DateTime t;
    getline(ifile,line);
    if(ifile.fail())
    {
      break;
      ifile.close();
      
      

    }
    stringstream ss(line);
    // cout<<line<<endl;
    ss>>t;
    // cout<<t<<endl;
    DateTime curr = DateTime();
    if(!(t<curr) && !(curr<t))
    {
      // cout<<t<<endl;
      return true;
    }
    // cout<<t<<endl;

    
    // cout << "SS now has: " << ss.str() << " " << ss.tellg() << endl;
    // stringstream ss(line);
    ss>>word;
    // cout<<word<<endl;
    if(validUser(word) == false)
    {
      return true;
    }
    

    User* x;
    std::map<string ,User*>::iterator it = myMap.find(word);
    if(it == myMap.end())
    {
      x = new User(word);
      myMap.insert(make_pair(word,x));
    }
    else
    {
      x = it->second;
    }

    getline(ss, tweet_text);
    tweet_text = trim(tweet_text);
    // cout<<tweet_text<<endl;


    Tweet* twe = new Tweet(x,t,tweet_text); 
    x->addTweet(twe);
    std::set<std::string> tweet_Set = twe->hashTags();
    // cout<<tweet_Set.size()<<endl;
    // for(std::set<std::string>::iterator it_3 = tweet_Set.begin(); it_3 != tweet_Set.end(); ++it_3)
    // {
    //   cout<<(*it_3)<<endl;
    // }

    for(std::set<std::string>::iterator it = tweet_Set.begin(); it!= tweet_Set.end(); ++it)
    {
      std::map<string, std::set<Tweet*> >::iterator it_3 = hashtagMap.find(*it);

      if(it_3 == hashtagMap.end())
      {
        std::set<Tweet*> newSet;

        newSet.insert(twe);

        hashtagMap.insert(make_pair(*it,newSet));

      }
      else
      {
        it_3->second.insert(twe);
      }

    }

    
  
  }

  // for(std::map<string, std::set<Tweet*> >::iterator it_3 = hashtagMap.begin(); it_3 != hashtagMap.end(); ++it_3)
  // {
  //   cout<<it_3->first<<endl;
  // }
  

  return false;
}





// Implement other member functions below

void TwitEng::addTweet(const std::string& username, const DateTime& time, const std::string& text)
{
  User* x;
  std::map<string ,User*>::iterator it = myMap.find(username);
  if(it == myMap.end())
  {
    x = new User(username);
    myMap.insert(make_pair(username,x));
  }
  else
  {
    x = it->second;
  }

  Tweet* twe = new Tweet(x,time,text);
  std::set<std::string> tweet_Set = twe->hashTags();
  x->addTweet(twe);
  for(std::set<std::string>::iterator it = tweet_Set.begin(); it!= tweet_Set.end(); ++it)
  {
    std::map<string, std::set<Tweet*> >::iterator it_3 = hashtagMap.find(*it);

    if(it_3 == hashtagMap.end())
    {
      std::set<Tweet*> newSet;

      newSet.insert(twe);

      hashtagMap.insert(make_pair(*it,newSet));

    }
    else
    {
      it_3->second.insert(twe);
    }

  }

  


}

std::vector<Tweet*> TwitEng::search(std::vector<std::string>& terms, int strategy)
{
  std::vector<Tweet*> vec_tweets;
  std::set<Tweet*> output_set;
  if(terms.size() == 0)
  {
    return vec_tweets;

  }
  if(terms.size() == 1)
  {
    convLower(terms[0]);
    std::map<std::string, std::set<Tweet*> >::iterator it_set1 = hashtagMap.find(terms[0]);
    // for(std::map<string, std::set<Tweet*> >::iterator it_3 = hashtagMap.begin(); it_3 != hashtagMap.end(); ++it_3)
    // {
    //   cout<<it_3->first<<endl;
    // }
    if(it_set1 == hashtagMap.end())
    {
      // cout<<"line 235"<<endl;
      return vec_tweets;
      
    }
    output_set = it_set1->second;
    for(std::set<Tweet*>::iterator it = output_set.begin(); it != output_set.end(); ++it)
    {
      // cout<<*it<<endl;
      vec_tweets.push_back(*it);
    }
    return vec_tweets;
  }
  if(terms.size() >= 2)
  {
    convLower(terms[0]);
    convLower(terms[1]);
    // std::vector<Tweet*> vec_tweets;
    
    std::map<std::string, std::set<Tweet*> >::iterator it_set1 = hashtagMap.find(terms[0]);
    std::map<std::string, std::set<Tweet*> >::iterator it_set2 = hashtagMap.find(terms[1]);

    // if(terms.size() == 2)
    // {
    //   if(strategy == 0)
    //   {
  
    //     output_set = Intersections(it_set1->second,it_set2->second);
    //     for(std::set<Tweet*>::iterator it = output_set.begin(); it != output_set.end(); ++it)
    //     {
    //       vec_tweets.push_back(*it);
    //     }

    //     return vec_tweets;
    //   }
    //   if(strategy == 1)
    //   {
    //     output_set = Unions(it_set1->second,it_set2->second);
    //     for(std::set<Tweet*>::iterator it = output_set.begin(); it != output_set.end(); ++it)
    //     {
    //       vec_tweets.push_back(*it);
    //     }
    //     return vec_tweets;

    //   }
    // }


    if(strategy == 0)
    { 
      // cout<<"line 251"<<endl;
      output_set = Intersections(it_set1->second,it_set2->second);
      for(unsigned int i = 2; i<terms.size(); i++)
      {
        convLower(terms[i]);
        std::map<std::string, std::set<Tweet*> >::iterator it_and = hashtagMap.find(terms[i]);
        output_set = Intersections(output_set,it_and->second);
      }
    }
    if(strategy == 1)
    {
      output_set = Unions(it_set1->second,it_set2->second);
      for(unsigned int i = 2; i<terms.size(); i++)
      {
        convLower(terms[i]);
        std::map<std::string, std::set<Tweet*> >::iterator it_or = hashtagMap.find(terms[i]);
        output_set = Unions(output_set,it_or->second);
      }
    }

    for(std::set<Tweet*>::iterator it = output_set.begin(); it != output_set.end(); ++it)
    {
      vec_tweets.push_back(*it);
    }


    
  }
  
  return vec_tweets;

}

std::set<Tweet*> TwitEng::Unions(std::set<Tweet*>Set1,std::set<Tweet*>Set2)
{
  std::set<Tweet*> outSet;
  std::set<Tweet*>::iterator it2 = Set2.begin();

  outSet = Set1;

  while(it2 != Set2.end())
  {
    std::set<Tweet*>::iterator it3 = outSet.find(*it2);

    if(it3 == outSet.end())
    {
      outSet.insert(*it2);
    }
    ++it2;

  }

  return outSet;
  

}

std::set<Tweet*> TwitEng::Intersections(std::set<Tweet*> Set1,std::set<Tweet*>Set2)
{
  // cout<<"In insertion"<<endl;
  std::set<Tweet*> outSet;
  std::set<Tweet*>::iterator it1 = Set1.begin();

  while(it1 != Set1.end())
  {
    // cout<<"going for insertion"<<endl;
    std::set<Tweet*>::iterator it2 = Set2.find(*it1);
    if(it2 != Set2.end())
    {
      outSet.insert(*it1);
    }
    ++it1;
  }
  return outSet;

}

void TwitEng::dumpFeeds()
{
  std::map<std::string ,User*>::iterator u_it = myMap.begin();

  while(u_it != myMap.end())
  {
    User* u = u_it->second;
    std::string name = u_it->first;
    std::vector<Tweet*> usr_vec = u->getFeed();
    std::string file_name = name + ".feed";
    ofstream ofile(file_name);

    ofile<<name<<endl;
    std::vector<Tweet*>::iterator it_vec = usr_vec.begin();

    while(it_vec != usr_vec.end())
    {
      // cout<<(*it_vec)->time()<<(*it_vec)->user()->name()<<(*it_vec)->text()<<endl;
      ofile<<(*it_vec)->time()<<(*it_vec)->user()->name()<<(*it_vec)->text()<<endl;

      ++it_vec;
    }
    ++u_it;


  } 
}

bool TwitEng::validUser(const std::string& name) const
{
  
  std::map<string,User*>::const_iterator it = myMap.find(name);

  if(it != myMap.end())
  {
    return true;
  }
  return false;

  

}