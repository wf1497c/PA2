# SP22-PA2
Let's practice using strings and streams

## Due Wednesday, April 20, 2022 at 11:30pm (PST)

Let's start putting our objects to good use. In this assignment, we're going to start using object-oriented principles to build a simple word game.  This is the first time you're expected to build a collection of objects that work together to solve a problem using "delegation". 

Before the Internet and smart-phones, entertainment was much simpler. Trying to be entertained in the back of the family car on drive to Grandma's house was essential. In the good old days, the family played a word game called, "Madlibs".  In this game, one player reads a story, in which words have been intentionally left out. As they encounter the missing word, they ask the other players for subtitute words of a given type, including _nouns_, _verbs_, _names_, _colors_ and more.  The other players offer random silly words, and the story gets filled in with their suggestions. At the end, the story is ready aloud with the suggested words, and it can be pretty fun (to little kids, especially).

![Image](madlibs.jpg)

## Overview 

This assignment will be the first time that you meaningfully work on classes that incorporate the basics of Object-Oriented programming.   Take a look at the source files in assignment folder:

```
Mablibs.hpp/.cpp		
WordProvider.hpp		
AutoWordProvider.hpp/.cpp
UserWordProvider.hpp/.cpp	
main.cpp
(and a few madlibs text files for testing)
```

When you run your program, your `main()` function calls the logic found in `runTest()` function. Below is a snipped from that function. Notice how readable the code is, in terms of clearly identifying the steps that are going to occur. You might also notice that there are two objects working together here: `Madlib` and `WordProvider`. 

```
1. int runTest(const std::string &aFilePath, ECE17::WordProvider &aProvider) {
2.   ECE17::Madlib theStory;
3.   int theResult=theStory.readStoryFile(aFilePath);
4.   if(!theResult) {
5.      theStory.getSubstitutes(aDelegate).showBlendedStory(std::cout);
6.   }
7.   return theResult;
8. }
```

The `runTest()` method creates a `MadLib` object and sends the following messages:

1. `readStoryFile` to open and read the specified text file containing the madlib story (on line 3 above)
2. `theStory.getSubstitutes()` (line 5) to gather word substitutions to complete the story
3. `theStory.showBlendedStory()` (line 5) to show the final results

As we discussed in lecture, the `MadLib` class relies on a delegate named `WordProvider` to provide each substitute word.  This base class has two subclasses: 1) `UserWordProvider`, and 2) `AutoWordProvider`.  If your program asks the `UserWordProvider` for words, it responds by asking the human user who ran the program for input using std::cin on the console. A typical exchange might look like this:

```
Enter an adjective:  fuzzy   <----  user entered the word 'fuzzy' and pressed return
Enter a noun:  <await user input>...  
(etc.)
```

The other subclass, `AutoWordProvider`, may also be used as the WordProvider (delegate) in a call to `runTest()`.  When used, the `AutoWordProvider` returns a word based on an internal dictionary of words that it maintains for each word type (e.g. noun, verb, adjective, name...etc.).  Think of the `AutoWordProvider` as a little chatbot who can return words of a given word-category.  Below, is a list of the known word-types your code needs to support:

```
 enum class WordType {noun, pluralnoun, name, verb, adjective, adverb, number, color, fruit, animal, place, year};
```

> NOTE: If we ask you for a YEAR, it means we want you to return the current calendar year. 


## Encapsulation 

By encapsulating our classes, we gain the ability to think about what they do and how they work, without worrying that users of our class can unintentionally depend on our implementation details. All of your classes encapsulate their member data. Only an instance of each class can directly access it's members. Each class offers a very small interface (set of public methods) to control the object. 

## Inheritance 

We use `inheritance` in this solution to provide a multiple types of `WordProvider` sub-classes. The first sub-class, `UserWordProvider` will ask the human user for a word of a given type via console input.  The `Madlibs` class will store each of the words provided, and substitute the provided words into the madlib template for everyone to read and enjoy.  

The second sub-class of `WordProvider` is the `AutoWordProvider` class. Instead of asking the user for a word, objects of this class will automatically choose a word of the given type at random.  (Like a chatbot).  To do so, they need to contain a dictionary of words (by word-type) to choose from.  Building that word list is your responsibility. 

## Polymorphism

Polymorphism is used in this assignment when different types of `WordProvider` objects are asked for a substitute word. Your `UserWordProvider` will respond much differently (by asking a user) than will your `AutoWordProvider` (which automatically makes a suggestion). In either case, the `Madlib` class will call your method, `getSubstitudeWord(type)`, and the given word-provider object will figure out how to respond.  This is an example of polymorophism (many forms). Each `WordProvider` sub-class responds in its own way.

## Part 1 -- `Madlib` class

The main logic for your code lives in the `main.cpp` method, `runTest()`.  The process begins by reading a given madlibs template text-file (via `Madlib::readStoryFile()`. Then we call the `MadLib::getSubstitutes()` method that scans the word list looking for CAPITALIZED words. For each CAPITALIZED word it finds, it will send the message, `getWord` to a given `WordProvider` delegate object. That object will get a substitute word, and return it to the `controller`. After all the words in the madlibs file have been processed, the `MadLib::showBlendedStory()` to reveal the resulting madlib.  

### Reading a madlibs file

As we said above, your `Madlib` object reads the given madlibs template file. Take a look at the madlibs1.txt file to see how it is formatted. You'll notice that some words are CAPITALIZED.  These words need to be substituted to complete the game.  We have provided a simple, stream-oriented algorithm that reads these words, so you have a starting point (see `MadLib::readStoryFile()`). 

> NOTE:  To setup your code properly, you have to manually enter the path to your project folder on your computer. Do that in `main.cpp`, in the function called, `getFolderPath()`. 

#### Task 1A -- Improving how we read madlib files

Consider this example madlib file: 

```
The nasal hyperdrive was invented by NAME. 
```

Our current implementation sees the words:  `The`, `nasal`, `hyperdrive`, `was`, `invented`, `by`, `NAME.`.   Notice that the last word isn't `NAME` (no period), but `NAME.` -- with a period at the end. The problem is that the `WordProvider` class doesn't understand the `NAME.` word-type (it only knows the `NAME` word-type). 

The flaw in our default implementation of `Madlib::readStoryFile()` is caused by how it handles "delimiters" that separate words in out input file.   The current version uses whitespace delimiters (newlines, tabs, spaces).  That's a good start. But the problem with this approach is that is misses cases where punctuation is attached to a word (e.g. `NAME.`) as shown in the example above.

For this task, you need to find a way to improve the "edge cases" where the tokenizer in `Madlib::readStoryFile()` returns a word with punctation attached.  You're free to do this in any way you like.  You could preprocess each word as you read them in `Madlib::readStoryFile()`, or do it later when you try to get word substitutes from  your `WordProvider` delegate.  You could also improve the `readStoryFile` method, and fix the tokenization issue right there. You're also free to add additional data members or methods to the `Madlib` class to help you solve this problem.
 
To complete this task, improve the `MadLib::readStoryFile()` method found in `MadLib.cpp`.  

#### Task 1B - Getting Substitute Words

After reading all the words from the given madlib text-file, we need to get word substitutions from our `WordProvider` delegate. That's what makes this game fun!

In the `Madlib::getSubstitutes()` method, we iterate over all the words from the given madlibs text-file (stored internally as storywords), to find any that are CAPITALIZED.  In each case, the code calls `getWord(WordType)` method of the given `WordProvider` delegate.

To complete this task, you'll need to find a way to cache (save) these word suggestions for use in the final step: generating your final story. There are many ways to do this, but an easy way to add another data member to the `Madlib` class to hold the ordered list of word substitutions.  You might consider adding a data structure (or use another mechanism) to store the words the your `WordProvider` delegate returns to you. We'll need to access the `WordProvider` provided words so that in the final step (showing the finished story), we can substitute the CAPITALIZED words in our original story with words that were gathered during this step.

To complete this task, implement the `MadLib::getSubstitutes()` method, found in `MadLib.cpp`. 

## Part 2 - Implement the `WordProvider` classes

`WordProviders` are simple objects. They offer one main method, `getWord(WordType)`, which accepts a word-type, and returns a word of that type back to the caller. Each of the `WordProvider` classes does this job a little differently. You have to write the logic for these objects yourself.

### 2a -- Getting substitute words from the user

As the `Madlibs` class finds CAPTITALIZED words in the madlibs template, it will call an available `WordProvider` class, and send it the message, `getWord(WordType)`.  In the case of the `UserWordProvider` class -- it should display a prompt to the user on the command line, asking for a word of the given type:

```
Please enter a/an noun: 
```

It will wait for the user to input a string (and press return), then capture their input using `std::cin`, and return the user-provided word from the method. 

To complete this step, implement the `UserWordProvider::getWord(WordType)` method found in `UserWordProvider.cpp`. 

#### A Helpful Dictionary

When your `UserWordProvider` class is asked to provide a word, it needs to print out a request to the user (e.g. 'Please enter a verb'). We've provided a helpful **dictionary** called `gLabelForType` that can found in the `WordProvider.hpp` file.  This dictionary is built upon an STL map container, and relates a given enum `WordType` with a `std::string` that holds a readable version of that type. For example, the string associated with `WordType::verb` is "verb".  You might find it helpful to use this dictionary when constructing your user prompt when gathering user input. 

### 2b -- Getting substitute words from the Chatbot (`AutoWordProvider` class) 

Next you will implement the class `AutoWordProvider` found in your project folder. This class is also a subclass of the `WordProvider` class, also found in your project. Rather than asking the user for input, your bot will select a word at random, based on the type of word being requested. The controller will ask your bot for words using the `getWord(WordType)` method. 

Your bot should be clever, and offer at least 10 words of each type, just in case.  If you want your solution to be flexible, you can (optionally) read in a list of words we provide in the the `wordlist.json` file.  Otherwise, manually create your own word lists for each word-type (noun, verb,...).

To complete this step, implement the `AutoWordProvider::getWord(WordType)` method found in `AutoWordProvider.cpp`. 


## Part 3 -- Showing the finished story

When the `Madlib` class has gathered all the required word substitutions, it's ready to print the final story to the terminal. It does so by calling the method, `showBlendedStory(std::ostream &anOutput)'. You must implement this method yourself. Again, you'll iterate all the storywords, and replace the CAPITALIZED words with substitute words you gathered above. Format your output as you would if you were typing a sentence, with proper spacing and punctuation.

To complete this task, implement the `MadLib::showBlendedStory()` method, found in `MadLib.cpp`. 


## Part 4 -- Testing

There are two ways to test out your work: manually, and using our auto-grader.  Here is the implementation of our main function from `main.cpp':

```
int main(int argc, const char * argv[]) {
  //STUDENT: DO NOT CHANGE THIS WITHOUT PERMISSION---
  if(argc>2) {
    return runAutoGraderTest(argv[1], argv[2]); //called if we cmd-line arguments (used by auto-grader)
  }

  //STUDENT -- Change anything below this line for your own tests...
  ECE17::UserWordProvider theProvider;
  std::string theFullPath(getFolderPath());
  return runTest(theFullPath+"madlibs1.txt", theProvider);
}
```

As you can see, when our autograder uses your main fuction -- it passes two command-line arguments. The first argument (user|robot) indiciates which type of `WordProvider` it is testing. The second argument is the name of the madlib text-file it wants to use for testing.  You'll notice we've provided you several test files.

If you don't pass any command-line arguments, the code at the bottom of the `main()` function will run. This is the code path that you'll generally use (at first) for your own testing and you build and debug your code.  It simply creates a `MadLib` class, chooses a `WordProvider` and asks it to read a specified test file.  You may freely change any code in this part of the main.  

DO NOT change code at the top part of the main function that the auto-grader uses.

Make sure you build and run sufficient tests to ensure that `MadLib`, `UserWordProvider` and `AutoWordProvider` classes work correctly.  The results can be pretty amusing.

## Part 5 -- Manual Testing -- Updating Your Engineering Notebook

(comments here...)

### Submitting Your Work
#### Due Wednesday April 20, 2022 at 11:30pm (PST)

Don't forget to update your `AboutMe.*` files!

```
Compile test: 20pts
Words-test (validating AutoWordProvider::getWord): 20pts
User-Test: 30pts [will be manually graded]
Auto-test: 30pts
```

As always, please turn your work in by commiting your working files back into github. Don't forget to update the `AboutMe.*` files with your personal information.  You might just copy those files over from PA1. Vlad-the-compiler is eagerly awating your code! 
