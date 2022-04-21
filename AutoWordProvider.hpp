//
//  AutoWordProvider.hpp
//  Assigment2 
//
//  Created by rick gessner on 10/17/20.
//

#ifndef AutoWordProvider_hpp
#define AutoWordProvider_hpp

#include <stdio.h>
#include "WordProvider.hpp"
#include <map>
#include <vector>

namespace ECE17 {
  
  class AutoWordProvider : public WordProvider {
  public:
                        AutoWordProvider(); //ctor
    virtual             ~AutoWordProvider() {}
    virtual std::string getWord(WordType aType);
  private:
    std::map<WordType, std::vector<std::string>> dict; // store words for each type
  };
}

#endif /* AutoWordProvider_hpp */
