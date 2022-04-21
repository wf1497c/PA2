//
//  UserWordProvider.hpp
//  Assigment2
//
//  Created by rick gessner on 10/17/20.
//

#ifndef UserWordProvider_hpp
#define UserWordProvider_hpp

#include <stdio.h>
#include "WordProvider.hpp"

namespace ECE17 {

  class UserWordProvider : public WordProvider {
  public:
                        UserWordProvider(); //ctor
    virtual             ~UserWordProvider() {}
    virtual std::string getWord(WordType aType);
  };

}
#endif /* UserWordProvider_hpp */
