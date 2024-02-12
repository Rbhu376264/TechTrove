#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout<<"\033[1;41m----Missing an argument----\033[0m"<<endl;
	  cout << "Usage: ./decipher <file>"<<endl;
	  cout << "Examples:" << endl;
	  cout << "\t./decipher secret/message1.txt \033[1;90m//to decipher message 1\033[0m" << endl;
	  cout << "\t./decipher secret/message2.txt \033[1;90m//to decipher message 2\033[0m"<<endl;
		return -1;
	}

	/************* You complete *************/

	try
	{
		ifstream ifile(argv[1]);
		int base;
		string privateKey;
		string mod;
		string private_message;
		string deciphered_message = "";

		ifile>>base>>privateKey>>mod;

		BigInt val1(privateKey,base);
		BigInt val2(mod,base);



		while(!ifile.fail())
		{
			ifile>>private_message;
			BigInt private_1(private_message,base);
			private_1.modulusExp(val1,val2);
			deciphered_message += (char)private_1.to_int();

		}

		deciphered_message.pop_back();

		cout<<deciphered_message<<endl;


	}

	catch(const exception& e){
    cout<<e.what()<<endl;//print the message of the exception defined in its "what" function.
    return -1;//end the program and return status != 0 to indicate that there is an error.
	}
 
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
	return 0;
}
