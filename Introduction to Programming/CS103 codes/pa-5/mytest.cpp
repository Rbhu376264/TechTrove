#include "bigint.h"
#include <iostream>
#include <fstream>
using namespace std;


int main() {
    //Add your own code
    //You may comment out the example code snippets below
  
    //First example

    /*
    BigInt mytest("DADCAFE", 16);
    cout<<mytest.to_string()<<endl;//should print DADCAFE
    BigInt mytest2("1010",2);
    cout<<mytest2.to_string()<<endl;//should print 1010
    BigInt mytest3("1010",2);
    cout<<mytest3.to_int()<<endl;//should print 10

    //Second example
    BigInt first("DADCAFE", 16);
    BigInt second("BEEF", 16);
    BigInt sum = first + second;
    first += second;
    cout<<boolalpha<<(first >= second)<<endl;//should print true
    cout<<sum.to_string()<<endl;//should print DAE89ED
    cout<<first.to_string()<<endl;//should print DAE89ED
    
    //Third example
    BigInt var1(496,10);
    BigInt var2(249,10);
    BigInt var3(1189,10);
    // BigInt val1(5,2);
    // BigInt val2(3,2);
    // val1*=val2;
    // cout<<val1.to_int()<<endl;*/
    BigInt val1(4,10);
    BigInt val2(13,10);
    BigInt val3(445,10);
    val1.modulusExp(val2,val3);
    cout<<val1.to_int()<<endl;
  /*
    BigInt var4 = modPow(var1,var2,var3);
    cout<<var4.to_int()<<endl;//should print 72
    cout<<(char)var4.to_int()<<endl;//should print "H"*/
    
    
	return 0;
}
