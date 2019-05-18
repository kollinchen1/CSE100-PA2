#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<cstdlib>
#include<fstream>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"

#define LETTERS 26
using namespace std;


int main(int argc, char** argv)
{

  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("a");
  words.push_back("app");
  words.push_back("gugglebee");
  words.push_back("waldos");
  words.push_back("are you not entertained");
  words.push_back("never gonna give you up");  
  
  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
 // cout <<"HI"<<endl;
  wen = words.end();
// cout<<words.size()<<endl;
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);

      tt = dt.insert(*wit, 1);
     // cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

  
  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(!t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(!t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(t_bst && t_ht && tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  cout << endl;

	/*You are supposed to add more test cases in this file */
	
	cout << "test finding non existing words"<<endl;
	tt = dt.find("we are here");
	if(tt)
		cout<<"Finding:"<<"we are here..."<<"failed"<<endl;
	else 
		cout<<"Finding:"<<"we are here..."<<"passed"<<endl;
	DictionaryTrie dict;
	ifstream infile;
	infile.open("shuffled_unique_freq_dict.txt");
	Utils::load_dict(dict, infile);
	infile.close();
//	cout<<"LOADED\n";
	vector<string> word = dict.predictCompletions("ste", 4);

	for(unsigned int i = 0; i < word.size(); i++)
		cout<<word[i]<<endl; 
	return 0;
}
