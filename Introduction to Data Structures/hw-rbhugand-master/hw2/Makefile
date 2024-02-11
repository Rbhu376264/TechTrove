CXX=g++
CXXFLAGS=-g -Wall -std=c++11

all: twitter

# Finish this target by adding other dependencies and 
# the action to compile the final twitter executable
twitter: twitter.o user.o twiteng.o cmdhandler.o datetime.o handler.o tweet.o util.o
	$(CXX) $(CXXFLAGS) twitter.o user.o twiteng.o cmdhandler.o datetime.o handler.o tweet.o util.o -o $@

# Complete	
twitter.o: twitter.cpp twiteng.h cmdhandler.h util.h
	$(CXX) $(CXXFLAGS) -c twitter.cpp -o twitter.o

# Add other rules/targets
user.o: user.cpp user.h tweet.h
	$(CXX) $(CXXFLAGS) -c user.cpp -o user.o
twiteng.o: twiteng.cpp twiteng.h tweet.h util.h user.h
	$(CXX) $(CXXFLAGS) -c twiteng.cpp -o twiteng.o
cmdhandler.o: cmdhandler.cpp cmdhandler.h util.h
	$(CXX) $(CXXFLAGS) -c cmdhandler.cpp -o cmdhandler.o
datetime.o: datetime.cpp datetime.h 
	$(CXX) $(CXXFLAGS) -c datetime.cpp -o datetime.o
handler.o: handler.cpp handler.h twiteng.h
	$(CXX) $(CXXFLAGS) -c handler.cpp -o handler.o
tweet.o: tweet.cpp tweet.h datetime.h user.h
	$(CXX) $(CXXFLAGS) -c tweet.cpp -o tweet.o
util.o: util.cpp util.h 
	$(CXX) $(CXXFLAGS) -c util.cpp -o util.o
clean:
	rm -f *.o twitter *.feed
