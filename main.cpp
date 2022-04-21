//
//  main.cpp
//  Assigment2
//
//  Created by rick gessner on 10/17/20.
//

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "UserWordProvider.hpp"
#include "AutoWordProvider.hpp"
#include "UserWordProvider.hpp"
#include "Madlib.hpp"
#include "AboutMe.hpp"
#include <sstream>
#include <regex>
#include <set>

static std::string theTerms =
  "(NOUN|PLURALNOUN|NAME|VERB|ADJECTIVE|ADVERB|NUMBER|COLOR|FRUIT|ANIMAL|PLACE|YEAR)";

//------------------------------------------------------------------

//Path YOUR LOCAL project folder where text files are.
//Add an extra path seperator to end of the string...
const char* getFolderPath() {
  return "/Users/rickg/Code/ECE17/SP22/rickg/RG_PA2/RG_PA2/";
}

//--------------------------------------------------------

//this is where we actually run each madlib...
bool runTest(const std::string &aFilePath, ECE17::WordProvider &aDelegate,
             const char* aTestName="basic") {
  ECE17::Madlib theStory;
  int theState=theStory.readStoryFile(aFilePath);
  bool theResult{false};
  
  if(!theState) {
    std::stringstream temp;
    theStory.getSubstitutes(aDelegate).showBlendedStory(temp);
    std::string theBuf=temp.str();
  
    theResult=std::regex_search(theBuf, std::regex(theTerms));
    static const char* theStates[]={"FAIL","PASS"};
    std::cout << aTestName << " test " << theStates[!theResult] << "\n";
    std::cout << theBuf << "LEN: " << theBuf.size() << "\n";
  }
  return theResult;
}

bool testWords(ECE17::WordProvider &aDelegate) {

  std::cout << "words test ";
  std::string tmp = aDelegate.getWord(ECE17::WordType::year);
  if(aDelegate.getWord(ECE17::WordType::year)!="2022") {
    std::cout << "FAIL\n";
    return true;
  }
  
  static const ECE17::WordType theTypes[] {
    ECE17::WordType::noun, ECE17::WordType::pluralnoun,
    ECE17::WordType::name, ECE17::WordType::verb,
    ECE17::WordType::adjective, ECE17::WordType::adverb,
    ECE17::WordType::number, ECE17::WordType::color,
    ECE17::WordType::fruit, ECE17::WordType::animal,
    ECE17::WordType::place
  };
  
  std::stringstream theOutput;
  size_t theCount{0};
  for(auto theType: theTypes) {
    std::set<std::string> theWords;
    for(int i=0;i<20;i++) {
      theWords.insert(aDelegate.getWord(theType));
    }
    for(auto &theWord : theWords) {
      theOutput << theWord << "\n";
    }

    theCount+=theWords.size();
  }

  if(theCount<90) {
    std::cout << "FAIL\n";
    return false;
  }
  std::cout << "PASS\n";
  std::cout << theOutput.str() << "\n";

  return true;
}


int runAutoGraderTest(const char* aMode, const std::string &aPath) {
  std::string theMode(aMode);
  
  if("compile"==theMode) {
    ECE17::AboutMe theStudent;
    std::cout << aMode << " test ";
    if(theStudent.getPID()!="Your PID") {
      if(theStudent.getName()!="Your name") {
        std::cout << "PASS\n";
        return 0;
      }
    }
    else std::cout << "FAIL\n";
  }
  else if("user"==theMode) {
    ECE17::UserWordProvider theProvider;
    runTest(aPath, theProvider, aMode);
  }
  else if("words"==theMode) {
    ECE17::AutoWordProvider theProvider;
    testWords(theProvider);
  }
  else if("auto"==theMode) {
    ECE17::AutoWordProvider theProvider;
    runTest(aPath, theProvider, aMode);
  }
  return 0;
}

//--------------------------------------------------------

int main(int argc, const char * argv[]) {

  //STUDENT: DO NOT CHANGE THIS WITHOUT PERMISSION---

  std::srand((unsigned int)time(nullptr));//random # seed...
  if(argc>2) {
    //arg1 is the testname; arg2 is test file name...
    std::string thePath(getFolderPath());
    if(4==argc) thePath=argv[3];
    std::string theFullPath=thePath+argv[2];
    return runAutoGraderTest(argv[1], theFullPath); //used by auto-grader
  }
  
  //----------------------------------------------------------------
  //STUDENT -- You can change code below this line for custom tests...
  
  ECE17::AutoWordProvider theProvider; //use this one....
  //ECE17::AutoWordProvider theProvider; //or use this one...
  std::string theFullPath(getFolderPath());

  if(testWords(theProvider)) std::cout << "---------PASS--------\n";
  else std::cout << "---------FAIL--------\n";
  //return runTest(theFullPath+"simplemadlib.txt", theProvider);
  //return runTest("/home/wf1497c/cpp_design/oop_basic/ECE-17/Madlibs/simplemadlib.txt", theProvider);
  //return runTest("/home/wf1497c/cpp_design/oop_basic/ECE-17/Madlibs/test.txt", theProvider);
  
  return 0;
}
