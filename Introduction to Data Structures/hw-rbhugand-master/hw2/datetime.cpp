#include "datetime.h"
#include <ctime>
#include <cstring>
#include <sstream>


DateTime::DateTime()
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    year = timeinfo->tm_year + 1900;
    month = timeinfo->tm_mon + 1;
    day = timeinfo->tm_mday;
    hour = timeinfo->tm_hour;
    min = timeinfo->tm_min;
    sec = timeinfo->tm_sec;
}

DateTime::DateTime(int hh, int mm, int ss, int year, int month, int day)
{
    this->year = year;
    this->month = month;
    this->day = day;
    hour = hh;
    min = mm;
    sec = ss;
}

bool DateTime::operator<(const DateTime& other) const
{
    if(this->year < other.year)
    {
        return true;
    }
    if(this->month < other.month)
    {
        return true;
    }
    if(this->day < other.day)
    {
        return true;
    }
    if(this->hour < other.hour)
    {
        return true;
    }
    if(this->min < other.min)
    {
        return true;
    }
    if(this->sec < other.sec)
    {
        return true;
    }

    return false;
    
    
}

std::ostream& operator<<(std::ostream& os, const DateTime& other)
{
    os<<other.year<<'-';
    if(other.month<10)
    {
        os<<'0';
    }
    os<<other.month<<'-';
    if(other.day<10)
    {
        os<<'0';
    }
    os<<other.day<<" ";
    if(other.hour<10)
    {
        os<<'0';
    }
    os<<other.hour<<':';
    if(other.min<10)
    {
        os<<'0';
    }
    os<<other.min<<':';
    if(other.sec<10)
    {
        os<<'0';
    }
    os<<other.sec;

    // os<<other.month<<'-'<<other.day<<" "<<other.hour<<':'<<other.min<<':'<<other.sec;

    return os;
}

std::istream& operator>>(std::istream& is, DateTime& dt)
{
    std::string word;
    std::stringstream ss;
    
    getline(is,word,'-');

    // std::cout<<word<<std::endl;

    ss.str(word);

    ss>>dt.year;
    // std::cout<<dt.year<<std::endl;

    if(ss.fail() || is.eof())
    {
        dt = DateTime();
        return is;
    }
    ss.clear();

    getline(is,word,'-');

    ss.str(word);

    ss>>dt.month;

    //  std::cout<<dt.month<<std::endl;

    if(ss.fail() || is.eof())
    {
        dt = DateTime();
        return is;
    }
    ss.clear();

    getline(is,word,' ');

    // std::cout<<word<<std::endl;

    ss.str(word);

    ss>>dt.day;

    //  std::cout<<dt.day<<std::endl;

    if(ss.fail()||is.eof())
    {
        dt = DateTime();
        return is;
    }
    ss.clear();

    getline(is,word,':');

    // std::cout<<word<<std::endl;

    ss.str(word);

    ss>>dt.hour;

    //  std::cout<<dt.hour<<std::endl;

    if(ss.fail()||is.eof())
    {
        dt = DateTime();
        return is;
    }
    ss.clear();

    getline(is,word,':');

    // std::cout<<"line 169 : "<<word<<std::endl;

    ss.str(word);

    ss>>dt.min;

    //  std::cout<<dt.min<<std::endl;

    if(ss.fail()||is.eof())
    {
        std::cout<<"line 179"<<std::endl;
        dt = DateTime();
        return is;
    }
    ss.clear();

    getline(is,word,' ');

    // std::cout<<word<<std::endl;

    ss.str(word);

    ss>>dt.sec;

    //  std::cout<<dt.sec<<std::endl;

    if(ss.fail())
    {
        dt = DateTime();
        return is;
    }
    ss.clear();

    return is;
     
}
