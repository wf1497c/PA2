//
//  AutoWordProvider.cpp
//  Assigment2
//
//  Created by rick gessner on 10/17/20.
//

#include "AutoWordProvider.hpp"

namespace ECE17 {

  AutoWordProvider::AutoWordProvider() : WordProvider() {
    // initialize dict
    dict[WordType::adjective] = {"good", "bad", "funny", "sad", "strange", 
                                 "tasty", "stupid", "normal", "curious", "random"};
    dict[WordType::adverb] =  {"quickly", "pretty", "locally", "briefly", "regularly", 
                               "solidly", "heavily", "loudly", "potentially", "undoubtedly"};
    dict[WordType::animal] =  {"mouse", "cow", "tiger", "rabbit", "dragon", 
                               "snake", "horse", "goat", "monkey", "dog"};
    dict[WordType::color] = {"red", "orange", "yellow", "green", "blue", 
                              "purple", "brown", "black", "white", "pink"};
    dict[WordType::fruit] = {"apple", "banana", "pineapple", "watermelon", "orange", 
                             "strawberry", "lemon", "papaya", "guava", "mango"};
    dict[WordType::name] = {"Louis", "Abigail", "Emily", "John", "Amber", 
                            "Josh", "Andy", "Scott", "Jenny", "Cindy"};
    dict[WordType::noun] = {"pen", "pencil", "liver", "watch", "butter", 
                            "ear", "iphone", "trash", "ball", "pants"};
    dict[WordType::number] = {"ten", "nine", "eight", "seven", "six", 
                              "five", "four", "three", "two", "one"};
    dict[WordType::place] = {"UCSD", "CMU", "Library", "IKEA", "church",
                             "kitchen", "street", "gym", "supermarket", "airport"};
    dict[WordType::pluralnoun] = {"children", "cats", "women", "people", "feet",
                                  "teeth", "mice", "knives", "lives", "data"};
    dict[WordType::verb] = {"say", "kick", "climb", "copy", "paste",
                            "love", "like", "hear", "see", "learn"};
    dict[WordType::year] = {"2022"}; //"1991", "1992", "1993", "1994", "1995", "1996", "1997", "1998", "1999", 
  }
  
  //get a word of the given type from your robot!...
  std::string AutoWordProvider::getWord(WordType aType) {
    int ind = rand() % dict[aType].size(); 
    std::string tmp = dict[aType][ind];
    return dict[aType][ind]; //STUDENT this is clearly wrong!
  }

}
