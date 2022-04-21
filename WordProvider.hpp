//
//  WordProvider.hpp
//  RGAssigment2
//
//  Created by rick gessner on 10/17/20.
//

#ifndef WordProvider_hpp
#define WordProvider_hpp

#include <stdio.h>
#include <string>
#include <map>
#include <algorithm>

namespace ECE17 {

  enum class WordType {noun, pluralnoun, name, verb, adjective,
    adverb, number, color, fruit, animal, place, year};

  class WordProvider {
  public:
    virtual ~WordProvider() {}
    virtual std::string getWord(WordType aType)=0;
  };

  //A helpful dictionary...
  static std::map<WordType, std::string> gLabelForType = {
    std::make_pair(WordType::noun, "noun"),
    std::make_pair(WordType::pluralnoun, "pluralnoun"),
    std::make_pair(WordType::name, "name"),
    std::make_pair(WordType::verb, "verb"),
    std::make_pair(WordType::adjective, "adjective"),
    std::make_pair(WordType::adverb, "adverb"),
    std::make_pair(WordType::number, "number"),
    std::make_pair(WordType::color, "color"),
    std::make_pair(WordType::fruit, "fruit"),
    std::make_pair(WordType::animal, "animal"),
    std::make_pair(WordType::place, "place"),
    std::make_pair(WordType::year, "year")
  };

}
  
#endif /* WordProvider_hpp */
