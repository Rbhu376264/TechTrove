#include "user.h"
#include "tweet.h"
#include <algorithm>


User::User(std::string name)
{
    name_ = name;
}
User::~User()
{
    for(std::list<Tweet*>::iterator it = tweets_.begin(); it != tweets_.end(); ++it)
    {
        delete (*it);
    }

}
std::string User::name() const
{
    return name_;
}

std::set<User*> User::followers() const
{
    return followers_;
}

std::set<User*> User::following() const
{
    return following_;
}
std::list<Tweet*> User::tweets() const
{
    return tweets_;
}
void User::addFollower(User* u)
{
    std::set<User*>::iterator it = followers_.find(u);

    if(it == followers_.end())
    {
        followers_.insert(u);
    }
}

void User::addFollowing(User* u)
{
    
    std::set<User*>::iterator it = following_.find(u);

    if(it == following_.end())
    {
        following_.insert(u);
    }
}

void User::addTweet(Tweet* t)
{
    tweets_.push_back(t);
}

std::vector<Tweet*>User:: getFeed()
{
    std::vector<Tweet*> myVector;
    std::list<Tweet*>::iterator it_;
    std::set<User*>::iterator it_1;


    for(it_ = tweets_.begin(); it_ != tweets_.end(); ++it_)
    {
        myVector.push_back(*it_);
    }

    for(it_1 = following_.begin(); it_1 !=following_.end(); ++it_1)
    {
        std::list<Tweet*> list_copy = (*it_1)->tweets_;
        for(it_ = list_copy.begin(); it_ != list_copy.end(); ++it_)
        {
            myVector.push_back(*it_);
        }

    }

    sort(myVector.begin(), myVector.end(), TweetComp());

    return myVector;
}