#include "util.h"
#include "DictionaryTrie.h"
TstNode::TstNode(){};
TstNode::TstNode(char a)
{ 
  this-> val = a;
  this->end = false;
  this->left = NULL;
  this->mid = NULL;
  this->right = NULL;
  this->fn = INT_MIN;
  this->ans= "";
}
/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){ 
  //  this->root = new TstNode(NULL);
  root = 0;
}
/*
   void DictionaryTrie::help(TstNode* pt, std::string word, int index)
   {
   if(pt==NULL)
   {
   TstNode* temp = new TstNode(word[index]);
   pt = temp;

   }
   if(pt->val > word[index])
   help(pt->left, word,index);
   else if(pt->val < word[index])
   help(pt->right, word,index);
   else
   {
   if(index+1 == word.length()
   pt->end = true;
   else
   add(pt->mid, word, index+1);
   }

   }*/

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  if(word.size()==0)
    return false;
  TstNode* pt;
  if(!root){
    // 	std::cerr<<"new word\n";   
    root = new TstNode(word[0]); 
    pt = root;
    for(unsigned int i = 1; i<word.size(); i++)
    {
      pt->mid = new TstNode(word[i]);
      pt = pt->mid;
    }
    // if(pt->end) return false;
    pt->end = true;
		pt->fn = freq;
		pt->ans = word;
		return true;
  }//end not root
  else{ 
    pt = root;
    while(true){
      if(pt->val > word[0]){
				if(pt->left!=NULL)
	  			pt = pt->left;
				else{
	  			pt->left = new TstNode(word[0]);
	 				pt = pt->left;
	  			break;
				}	
      }
      else if( pt->val <word[0]){
				if(pt->right!=NULL)
	  		pt = pt->right;
				else{
	  			pt->right = new TstNode(word[0]);
	  			pt = pt->right;
	  			break;
				}
      }
      else{
				break;
      } 
    }   
    //    std::cerr<<"str[1:]\n";
    for(unsigned int i = 1; i<word.length(); i++){
			if(!pt->mid){
							//	std::cerr<<"mid is null\n";
				pt->mid = new TstNode(word[i]);
				pt = pt->mid;
      }
      else if (pt->mid->val == word[i]){
				pt = pt->mid;
      }
      else{
				pt = pt->mid;
				while(true){
					//	std::cerr<<"Current:"<<pt->val<<word[i];
					if(pt->val >word[i]){
					
						if(pt->left!=NULL)
							pt = pt->left;
						else{
							pt->left = new TstNode(word[i]);
							pt = pt->left;
					//std::cerr<<pt->val;
						}
					}
					else if(pt->val < word[i]){
						if(pt->right!=NULL)
							pt = pt->right;
						else{
							pt->right = new TstNode(word[i]);
							pt = pt->right;
						//	break;
						}
					}
					else{
						break;
					}     

				}
			}
    }   // for loop for str[1:] 
    if(pt->end) 
      return false; 
    pt->end = true;
		
    pt->fn = freq;
		pt->ans = word;
		
//	std::cerr<<pt->val<<pt->fn<<pt->ans<<"\n";
  } // root not null

  return pt->end;

}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  if(word.size()==0)
    return false;
	if(!root)
		return false;
	TstNode *pt = root;
	for(unsigned int i = 0; i<word.length(); i++){
		while(true){
		//	std::cerr<<pt->val<<word[i]<<": current\n";
			if(pt->val >word[i]){
				if(pt->left!=NULL){
					pt=pt->left;
	//		std::cerr<<word[i]<<":going left\n";
				}
				else{	
			//		std::cerr<<pt->val<<word[i]<<":returned\n";
					return pt->end;
			
				}
			}
			else if(pt->val <word[i]){
				if(pt->right!=NULL){
					pt= pt->right;
		//	std::cerr<<word[i]<<":going right\n";
					
								}
								else{

			//		std::cerr<<pt->val<<word[i]<<":returned\n";
									return pt->end;
								
								}
							}
							else{
								if(pt->mid == NULL||i+1==word.length()){
								//	std::cerr<<"mid is null\n";
									return pt->end;	
								}								
								else{
		//		std::cerr<<word[i]<<":going mid\n";
									pt=pt->mid;
								break;
								}
							}					
			}
						}
					return pt->end;
}
void DictionaryTrie::traversalHelp(TstNode* current,std::set< std::pair<unsigned int, std::string> > & a){
	if(current->end){
		std::pair<int,std::string> p(current->fn,current->ans);

//	std::cerr<<current->val<<current->fn<<current->ans<<"\n";
		a.insert(p);
	}
	if(current->left!=NULL)
		traversalHelp(current->left, a);
	if(current->right!=NULL)
		traversalHelp(current->right,a);
	if(current->mid!=NULL)
		traversalHelp(current->mid,a);
} 
/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  std::set<std::pair<unsigned int, std::string> > all; //store all if true the word, recursively traverse all the node, pass by reference.
	unsigned int count = 0;
	for(unsigned int i = 0; i<prefix.length(); i++){
		if(!std::islower(prefix[i])){
			std::cerr<<"Invalid Input. Please retry with correct input"<<std::endl;
			return words;
		}
	
	}
	if(!root){
	//	std::cerr<<"return no root\n";
		return words;
	}
	if(num_completions <=0 || prefix.length()==0){
	//	std::cerr<<"return small word or small num_completion\n";
		return words;
		
	}
//	std::cerr<<"set pt to root, traverse to prefix first\n";
	TstNode*pt = root;		
	//go to prefix first
	for(unsigned int i = 0; i<prefix.length();i++){			
		while(true){
			if(pt->val >prefix[i]){
				if(pt->left!=NULL){
					pt=pt->left;
	//				std::cerr<<"going left\n";
				}
				else{
		//			std::cerr<<"nonexisten word at line 237\n";	
					return words;	
				}
			}
			else if(pt->val < prefix[i]){
				if(pt->right!=NULL){
					pt= pt->right;
							
				//	std::cerr<<"going right\n";
				}
				else{
			//		std::cerr<<"nonexisten word at line 248\n";
					return words;
					
				}
			}
			else{
				if(pt->mid == NULL||i==prefix.length()){
				//	std::cerr<<"nonexisten word at line 255\n";
					return words;	
				}								
				else{
				//	if(i+1!=prefix.length())
					pt=pt->mid;
					
				//	std::cerr<<pt->val<<"going mid\n";
					break;
				}
			}					
		}//while
	}//for
//	std::cout<<pt->val<<"\n";
	traversalHelp(pt,all);
	std::set< std::pair<unsigned int, std::string> >::reverse_iterator rit;
	for(rit = all.rbegin(); rit!=all.rend();++rit){
		words.push_back((*rit).second);
		count++;
		if(count==num_completions)
			break;
	}
	return words;
	
}
/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  delete this->root;

}
