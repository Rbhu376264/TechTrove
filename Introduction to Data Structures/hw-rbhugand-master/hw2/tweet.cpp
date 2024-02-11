#include "tweet.h"
#include "user.h"
#include "util.h"
#include <cstring>
#include <sstream>

Tweet::Tweet()
{

}
Tweet::Tweet(User* user, const DateTime& time, const std::string& text)
{
    u = user;
    time_ = time;
    text_ = text;
    // std::cout<<"line 16"<<std::endl;
    // std::cout<<text_<<std::endl;
    // std::cout<<"line 18"<<std::endl;
    std::stringstream ss(text_);
    std::string word;

    while(ss>>word)
    {
        if(word[0] == '#')
        {
            word = word.substr(1);
            convLower(word);
            hashTags_.insert(word);
            // std::cout<<word<<std::endl;
            // std::cout<<"line 29"<<std::endl;
            // // std::cout<<hashTags_.size()<<std::endl;
            
        }
    }

}

DateTime const & Tweet::time() const
{
    return time_;
}

std::string const & Tweet::text() const
{
    return text_;
}

std::set<std::string> Tweet::hashTags() const
{
    return hashTags_; 
}
bool Tweet:: operator<(const Tweet& other) const
{
    return this->time_< other.time_;
}

std::ostream& operator<<(std::ostream& os, const Tweet& t)
{
    os<<t.time_<<' '<<t.u->name()<<' '<<t.text();

    return os;
}



User*Tweet:: user() const
{
    return u;
}