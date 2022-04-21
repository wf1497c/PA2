//
//  madlib_hpp.cpp
//  Assigment2
//
//  Created by rick gessner on 10/17/20.
//

#include "Madlib.hpp"
#include "AutoWordProvider.hpp"

namespace ECE17 {
  Madlib::Madlib() : storywords() {
    std::vector<std::string> ks = {"NOUN", "PLURALNOUN", "NAME", "VERB", "ADJECTIVE",
                             "ADVERB", "NUMBER", "COLOR", "FRUIT", "ANIMAL",
                             "PLACE", "YEAR"};
    for(std::string k:ks) keys.insert(k);
  }

  Madlib::Madlib(const Madlib &aCopy) {
    (*this)=aCopy;
  }

  Madlib::~Madlib() {}
  
  Madlib& Madlib::operator=(const Madlib &aCopy) {
    storywords=aCopy.storywords;
    return *this;
  }

  //given a word-type, find the associated wordtype enum... (reverse lookup)
  WordType Madlib::getTypeForLabel(std::string &aWord) {
    std::transform(aWord.begin(), aWord.end(), aWord.begin(), ::tolower); //lowercase
    for(auto thePair : gLabelForType) {
      if(thePair.second==aWord) {
        return thePair.first;
      }
    }
    return WordType::noun;
  }

  bool isPunct(char aChar) {
    static std::string punct(".;?!:,'");
    return std::string::npos==punct.find(aChar) ? false : true ;
  }

  //read words in a file and store them internally...
  int Madlib::readStoryFile(const std::string &aPath) {
    std::ifstream theStream(aPath);

    if(theStream.is_open()) {
      std::string theWord;
      while (theStream >> theWord) {
        //STUDENT: This really needs to be improved to deal
        // with breaking up input into words more effectively.

        std::string tmp;
        for(char c:theWord){
          if(isalpha(c) || isdigit(c)){
            tmp += c;
          }
        }
        storywords.push_back(tmp);
        if(isPunct(theWord.back())){
          std::string punc = {theWord.back()};
          storywords.push_back(punc);
        }
      }
    }

    return 0;
  }
  
  Madlib& Madlib::showBlendedStory(std::ostream &anOutput) {
    //STUDENT: implement me!
    anOutput << storywords[0];
    for(int i = 1; i < storywords.size(); i++){
      if(isPunct(storywords[i][0])) anOutput << storywords[i];
      else anOutput << " " << storywords[i];
    }
    anOutput << "\n";
    return *this;
  }

  Madlib& Madlib::getSubstitutes(WordProvider &aDelegate) {
    for(std::string &theWord : storywords) {
      if(isKeytoChange(theWord)){
        std::string subWord = aDelegate.getWord(getTypeForLabel(theWord));
        userWords.push_back(subWord);
        theWord = subWord;
      }
      //STUDENT: Finish this method.
      //if theWord is all caps, then convert it to a WordType (enum)
      //Then call the delegate to get a substitute word.
      //e.g.  aDelgate.getWord(WordTypes::noun);
      //Finally, decide how to save the returned substitute words.
    }
    return *this;
  }

  bool Madlib::isKeytoChange(std::string aWord){
    if(!isPunct(aWord[0])) std::transform(aWord.begin(), aWord.end(), aWord.begin(), ::toupper);
    if(keys.count(aWord)) return true;
    return false;
  }

}
