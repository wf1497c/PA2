//
//  madlib.hpp
//  Assigment2
//
//  Created by rick gessner on 10/17/20.
//

#ifndef madlib_hpp
#define madlib_hpp

#include <stdio.h>
#include <vector>
#include <fstream>
#include "WordProvider.hpp"
#include <string>
#include <set> // for checking keys
#include <iostream>

namespace ECE17 {

  class Madlib {
  public:
    Madlib();
    Madlib(const Madlib &aCopy);
    ~Madlib();
    Madlib& operator=(const Madlib &aCopy);
    
    //read words in a file and store them internally...
    int       readStoryFile(const std::string &aPath);
    Madlib&   getSubstitutes(WordProvider &aDelegate);
    Madlib&   showBlendedStory(std::ostream &anOutput);
    bool      isKeytoChange(std::string aWord); // to check whether the word is a key to call wordProvider
    
  protected:
    WordType  getTypeForLabel(std::string &aWord);

    std::vector<std::string> storywords; //collected from users...
    std::set<std::string> keys; // for checking keys
    //STUDENT: You'll need another collection of user-words
    std::vector<std::string> userWords;
  };

}

#endif /* madlib_hpp */
