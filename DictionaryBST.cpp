#include "util.h"
#include "DictionaryBST.h"

/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST()
{

}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{ 
//  std::cout<<"In BST insert"<<std::endl;
  if(word.size() == 0)
    return false;
  return dict.insert(word).second; //check if inserted, second for bool value
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  return dict.find(word)!=dict.end(); // cant find till the end
  
}

/* Destructor */
DictionaryBST::~DictionaryBST(){}
