#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include "DictionaryTrie.h"
#include "util.h"
#include <iostream>
#include <sstream>
#include <fstream>

int main(int argc, char*argv[]){
	if(argc!=5){
		std::cout<<"It should take four arguments as input:  ./benchdict min_size step_size num_iterations dictfile\n";
		return 0;
	}
	int min_size = std::stoi(argv[1]);
	int step_size = std::stoi(argv[2]);
	int num_iter = std::stoi(argv[3]);
	std::string dictFile = argv[4];
	//Checking
	/* it has been done on UTIL.cpp
	std::ifstream checkFile;
	int count = 0;
	std::string checkLine;
	checkFile.open(dictFile,std::ios::binary);
	while(std::getline(checkFile,checkLine))
		count++;
	if(count<min_size + i * step_size)
		std::cout<<"ERROR, Not enough lines in the given file for testing!!!"<<std::endl;
	*/

	//BST test
	std::cout<<"DictionaryBST:"<<std::endl;
	for(int i = 0; i<num_iter; i++){
		/*step one*/
		DictionaryBST*bst =new DictionaryBST();
		std::ifstream infile;
		infile.open(dictFile, std::ios::binary);
		Utils::load_dict(*bst, infile, min_size + i * step_size);
		/*step two*/
		std::vector<std::string> words;
	/*	std::string line;
		for(int j = 0; j<100; j++){
			infile.getline(line);
			words.push_back(line);
		}//loading 100 words	
		*/
		Utils::load_vector(words, infile,100);	
		std::vector<std::string>::iterator it;
		long long totalTime = 0, duration = 0;	
		Timer t;
		for(int a = 0; a<100; a++){
			for(it = words.begin();	it!=words.end(); ++it){
				t.begin_timer();//void
				bst->find(*it);
				totalTime+=t.end_timer();
			}
		}//after 10000 times of finding the same 100 words;
		duration = totalTime/100.0;
		/*step three*/
		std::cout<<min_size + i * step_size<<"\t"<<duration<<std::endl;
		delete bst;
	}
	//HashTable test
	std::cout<<"DictionaryHashTable:"<<std::endl;
	for(int i = 0; i<num_iter; i++){
		/*step one*/
		DictionaryHashtable *ht = new DictionaryHashtable();
		std::ifstream infile;
		infile.open(dictFile, std::ios::binary);
		Utils::load_dict(*ht, infile, min_size + i * step_size);
		/*step two*/
		std::vector<std::string> words;
    Utils::load_vector(words, infile,100); 
    std::vector<std::string>::iterator it;
    long long totalTime = 0, duration = 0;  
    Timer t;
    for(int a = 0; a<100; a++){
      for(it = words.begin(); it!=words.end(); ++it){
        t.begin_timer();//void
        ht->find(*it);
        totalTime+=t.end_timer();
      }
    }//after 10000 times of finding the same 100 words;
    duration = totalTime/100.0;
    /*step three*/
    std::cout<<min_size + i * step_size<<"\t"<<duration<<std::endl;
    delete ht;
	}
	//Trie test
	std::cout<<"DictionaryTrie:"<<std::endl;
	for(int i = 0; i<num_iter; i++){
		/*step one*/	
		DictionaryTrie* dt = new DictionaryTrie();
		std::ifstream infile;
		infile.open(dictFile, std::ios::binary);
		Utils::load_dict(*dt, infile, min_size + i * step_size);
		/*step two*/
		std::vector<std::string> words;
    Utils::load_vector(words, infile,100); 
    std::vector<std::string>::iterator it;
    long long totalTime = 0, duration = 0;  
    Timer t;
    for(int a = 0; a<100; a++){
      for(it = words.begin(); it!=words.end(); ++it){
        t.begin_timer();//void
        dt->find(*it);
        totalTime+=t.end_timer();
      }
    }//after 10000 times of finding the same 100 words;
    duration = totalTime/100.0;
    /*step three*/
    std::cout<<min_size + i * step_size<<"\t"<<duration<<std::endl;
    delete dt;
	}
}
