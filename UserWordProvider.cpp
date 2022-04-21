//
//  UserWordProvider.cpp
//  Assigment2
//
//  Created by rick gessner on 10/17/20.
//

#include "UserWordProvider.hpp"
#include <iostream>


namespace ECE17 {

  UserWordProvider::UserWordProvider() : WordProvider() {
    //nothing much to do here...
  }
  
  //Ask the user for word of the given type...
  std::string UserWordProvider::getWord(WordType aType) {
    std::string givenWord;
    std::cout << "Please enter a/an " << gLabelForType[aType] << ": ";
    std::cin >> givenWord;
    std::cout << givenWord << "\n";
    return givenWord; //STUDENT: fix this method!
  }

}
