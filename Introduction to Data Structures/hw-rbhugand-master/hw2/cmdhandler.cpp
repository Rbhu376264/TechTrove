#include "cmdhandler.h"
#include "util.h"
using namespace std;

QuitHandler::QuitHandler()
{

}

QuitHandler::QuitHandler(Handler* next)
  : Handler(next)
{

}

bool QuitHandler::canHandle(const std::string& cmd) const
{
	return cmd == "QUIT";

}

Handler::HANDLER_STATUS_T QuitHandler::process(TwitEng* eng, std::istream& instr) const
{
	eng->dumpFeeds();
	return HANDLER_QUIT;
}


AndHandler::AndHandler()
{

}

AndHandler::AndHandler(Handler* next)
  : Handler(next)
{

}

bool AndHandler::canHandle(const std::string& cmd) const
{
	return cmd == "AND";

}

Handler::HANDLER_STATUS_T AndHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::vector<std::string> newVec;
	std::string line;
	// std::string empty;
	// getline(instr,empty);
	// getline(instr,line,' ');
	
	while(instr>>line)
	{
		newVec.push_back(line);
		// getline(instr,line,' ');

	}
	std::vector<Tweet*> twit_vec = eng->search(newVec,0);
	displayHits(twit_vec);
	return HANDLER_OK;
}

OrHandler::OrHandler()
{

}

OrHandler::OrHandler(Handler* next)
  : Handler(next)
{

}

bool OrHandler::canHandle(const std::string& cmd) const
{
	return cmd == "OR";

}

Handler::HANDLER_STATUS_T OrHandler::process(TwitEng* eng, std::istream& instr) const
{
	std::vector<std::string> newVec;
	std::string line;
	while(instr>>line)
	{
		// cout<<line<<endl;
		newVec.push_back(line);

	}
	std::vector<Tweet*> twit_vec = eng->search(newVec,1);
	displayHits(twit_vec);
	return HANDLER_OK;
}

TweetHandler::TweetHandler()
{

}

TweetHandler::TweetHandler(Handler* next)
  : Handler(next)
{

}

bool TweetHandler::canHandle(const std::string& cmd) const
{
	return cmd == "TWEET";

}

Handler::HANDLER_STATUS_T TweetHandler::process(TwitEng* eng, std::istream& instr) const
{
	DateTime t;
	std::string u_name;
	std::string tweet_text;
	t = DateTime();
	instr>>u_name;
	getline(instr,tweet_text);
	if(instr.fail())
	{
		return HANDLER_ERROR;
	}
	if(eng->validUser(u_name) == false)
	{
		// cout<<"line 126"<<endl;
		return HANDLER_ERROR;
	}
	eng->addTweet(u_name,t,tweet_text);
	// cout<<u_name<<endl;
	// cout<<tweet_text<<endl;

	// return HANDLER_QUIT;
	return HANDLER_OK;
}
