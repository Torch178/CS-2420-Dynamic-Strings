#include "../build/Challenge Activity 1 - Dynamic Strings/Url.h"
#include "../inc/DynamicString.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>

using std::cout;
using std::endl;
using std::invalid_argument;
using std::strcmp;
using std::string;

template <typename T>
void test(int testNum, int& correct, T actual, T expected){

   if(actual == expected){
      correct++;
      cout << "Passed Test " << testNum << endl;
   }
   else{
      cout << "***Failed Test " << testNum << "***" << endl;
      cout << "Actual: " << actual << " Expected: " << expected << endl;
   }
}

void testString(int testNum, int& correct, const char* actual, const char* expected){

   if(actual && expected && strcmp(actual, expected) == 0){
      correct++;
      cout << "Passed Test " << testNum << endl;
   }
   else{
      cout << "***Failed Test " << testNum << "***" << endl;
      if(actual && expected){
         cout << "Actual: " << actual << " Expected: " << expected << endl;
      }
   }
}

int main(){

   int testNum  = 1;
   int correct = 0;

   cout << "---------------Memory Management Tests--------------" << endl;
   DynamicString s1("abc");
   DynamicString* s2 = new DynamicString(s1);
   s2->operator[](0) = 'b';
   test(testNum++, correct, s2->operator[](0), 'b');
   test(testNum++, correct, s1[0], 'a');
   DynamicString* s3 = new DynamicString(*s2);
   DynamicString s4("baa baa");
   *s3 = s4;
   s3->operator[](0) = 'a';
   test(testNum++, correct, s3->operator[](0), 'a');
   test(testNum++, correct, s4[0], 'b');
   delete s3;
   delete s2;

   cout << "--------URL Parsing Tests--------" << endl;
   /*Scheme and Host*/
   Url u1("http://www.icarus.cs.weber.edu");
   Url u2("https://icarus.cs.weber.edu");
   Url u3("smb://kfeuz@athena.cs.weber.edu");
   Url u4("file:///home/cs2420/assignment3/");
   Url u5("http://icarus.cs.weber.edu/~kfeuz/index.html");
   Url u6("https://weber.edu/index.html?lang=en");
   Url u7("http://cplusplus.com/index.html?version=c++11#Reference");
   Url u8("https://wikipedia.org/index.html#Help");

   cout << "--------Compare--------" << endl;
   /*Compare*/
   test(testNum++, correct, u1.compare(u2)<0, true);
   test(testNum++, correct, u3.compare(u4)>0, true);
   test(testNum++, correct, u6.compare(u7)>0, true);
   test(testNum++, correct, u8.compare(u8), 0);
   Url u9("HTTP://cplusplus.com/index.html?version=c++11#Reference");
   test(testNum++, correct, u7.compare(u9), 0);
   Url u10("http://CPLUSPLUS.COM/index.html?version=c++11#Reference");
   test(testNum++, correct, u10.compare(u7), 0);
   Url u11("http://cplusplus.com/INDEX.html?version=c++11#Reference");
   test(testNum++, correct, u7.compare(u11)>0, true);
   Url u12("https://WEBER.edu/index.html?lang=en");
   //test(testNum++, correct, u6.compareIgnoreFrag(u12), 0);
   Url u13("HTTPS://weber.edu/INDEX.html?lang=en");
   //test(testNum++, correct, u6.compareIgnoreFrag(u13)>0, true);


   cout << "--------Error Checking--------" << endl;
   try{
      Url u21("google.com");//invalid argument(no scheme)
      test(testNum++, correct, 0, 1);
   }
   catch(invalid_argument){
      test(testNum++, correct, 0, 0);
   }
   try{
      Url u30("/index.html");//invalid argument (relative url)
      test(testNum++, correct, 0, 1);
   }
   catch(invalid_argument){
      test(testNum++, correct, 0, 0);
   }
   try{
      Url u27("://weber.edu");//invalid argument(no scheme)
      test(testNum++, correct, 0, 1);
   }
   catch(invalid_argument){
      test(testNum++, correct, 0, 0);
   }


   cout << endl << "----------Results----------" << endl;
   cout << "Passed " << correct << "/" << --testNum << " tests" << endl;

}
