#include "util.h"
#include "DictionaryHashtable.h"
#include <fstream>
#include <iostream>


int main(int argc, char*argv[]){
	if(argc!=3){
		std::cout<<"Your benchhash function should take two arguments as input:";
		std::cout<<"  ./benchhash dictfile num_words"<<std::endl;
		return 0;
	}
	std::cout<<"#hits\t#slots receiving the #hits\n";
	Timer t;	
	int size = std::stoi(argv[2]);
	std::string dictFile = argv[1];
	int hSize = size*2;
	std::ifstream infile;
	infile.open(dictFile, std::ios::binary);
	std::vector<std::string>words;
	Utils::load_vector(words,infile,size);//words now have size of words
  int maxStep = 0;	
	std::string arr; //hashword
	std::vector<unsigned int>prob(hSize,0);
	std::vector<unsigned int>prob1(hSize,0);
	std::vector<unsigned int>prob2(hSize); //Brute force algorthim
  double average=0; 
	std::vector<unsigned int>prob3(hSize); //Brute force algorthim
	for(int i = 0; i<size; i++){
		//hash Function one
		arr = words[i];
		unsigned int hashVal = 0;
		for(unsigned int j = 0; j<arr.length();j++){
			int letter = arr[j];
			hashVal = (hashVal * 27 + letter) % hSize;
		}//27 for 26 letters and a empty space
		prob[hashVal]++;	
	}	
	//print
//	for(int b = 0; b<hSize; b++)
//		std::cout<<prob[b]<<"\n";
	unsigned int totalHits = hSize;
	for(auto it = prob.begin(); it!=prob.end(); ++it){
		prob2[*it]++;	
	}
	totalHits-=prob2[0];
	for(unsigned int count = 0;count<prob2.size(); count++){
			if(prob2[count]!=0){
				std::cout<<count<<"\t"<<prob2[count]<<"\n";
				average+= totalHits* count;
				if(count>0)
				totalHits = totalHits - prob2[count];
				maxStep=count;		
			}
		
	}
	std::cout<<"From that information, we would then calculate that the average number of steps in a search would be about " << average/size<<std::endl;
	std::cout<<"The worst case steps that would be needed to find a word is "<<maxStep<<std::endl;
	std::cout<<"\n#hits\t#slots receiving the #hits\n";
//	int off;
	maxStep = 0;
	std::string val;
	unsigned int hashVal1;
	for(int a = 0; a<size; a++){
	//	off = 0;	
		val = words[a];
	//	std::cout<<a<<" "<<size<<std::endl;
//	std::cout<<"DONE 49\n";
		for(unsigned int i = 0; i<words[a].length()-1; i++){
			hashVal1= (31*hashVal1+ val[i])%hSize;
		
		}
	//	std::cout<<h<<std::endl;
	//	hashVal1 =h%hSize;
		prob1[hashVal1]++;
	
	//	std::cout<<hashVal1<<"\n";
	}
//	std::cout<<"DONE 62\n";
//	prob3.clear();
	totalHits = hSize;	
	average = 0;
	for(auto it = prob1.begin(); it!=prob1.end(); ++it){
	//	std::cout<<*it<<std::endl;
		prob3[*it]++;
	}
	totalHits-=prob3[0];
	for(unsigned int count = 0;count<prob3.size(); count++){
			if(prob3[count]!=0){
				std::cout<<count<<"\t"<<prob3[count]<<"\n";
				average+= totalHits* count;
        if(count>0)
        totalHits = totalHits - prob3[count];		
				maxStep=count;
			}
	}

	std::cout<<"From that information, we would then calculate that the average number of steps in a search would be about " << average/size<<std::endl;
	std::cout<<"The worst case steps that would be needed to find a word is "<<maxStep<<std::endl; 
	/* 
	//from stepik hash function two
	for(int j = 0; j<size; j++){
		unsigned int val = 0;
  	for(int i = 0; i < key.length(); i++) {
    	val += (unsigned int)(key[i]); // cast each character of key to unsigned int
    }
		
	}*/

}
