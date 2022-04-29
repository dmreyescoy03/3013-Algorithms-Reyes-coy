/*****************************************************************************
*                    
*  Author:           David Reyes-coy
*  Email:            dmreyescoy0318@my.msutexas.edu
*  Label:            PO3
*  Title:            Trie Tree Search
*  Course:           CMPS 3013
*  Semester:         Spring 2022
* 
*  Description:
*        This program contains a Trie tree data structure
*        that reads word from a .txt file and allows the 
*        user to search for words.
*        
*  Usage: 
*       Start typing one lowercase letter at a time. 
*       
*  Files:            
*       main.cpp    : driver program 
*       mygetch.hpp : header file with getch() definition
*       timer.hpp   : timer implementation
*       dictionary.txt : huge word file
*****************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "mygetch.hpp"
#include <cstring>
#include "timer.hpp"

using namespace std;

/**
 * struct Node
 * 
 *     This node class is to store the letters, other nodes, and 
 *     a boolean.
 * 
 * Public Methods:
 *    
 *     Node(char x)                               
 * 
 * Usage: 
 * 
 *     Node name = new Node(x); 
 *      
 */
struct Node{
    Node* character[26];
    bool isLeaf;
    char letter;
  
    Node(char x){                             //constructor
          this->isLeaf = false;
          letter = x;
          for (int i = 0; i < 25; i++) {
              this->character[i] = nullptr;   //iterating pointers to = null
          }
      }
};

/**
 * class Trie
 * 
 *     This class holds the structure of the Trie Tree. 
 *     Allows the search function to work 
 * 
 * Public Methods:
 *    
 *     Trie()                               
 *     Node name = new Node(x); 
 *     void insert(string key);
 *     bool search(string key):
 *     Node* getNode(string key);
 *     bool startWith(string key);
 *     void find_all(Node*&curr, string key);
 *     vector<string> find_all(string key):
 *     void Find()
 * 
 */
class Trie{
public:
  
    vector<string> results;
    Node* root;
    int count = 0;

/**
     * Public : Trie
     * 
     * Description:
     *      Constructor that makes the root an empty char
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
  Trie(){
    root = new Node('\0');          
  }

/**
     * Public : insert
     * 
     * Description:
     *      inserts words into the trie tree
     * 
     * Params:
     *      string  key
     * 
     * Returns:
     *      None
     */
  void insert(string key){
    // start from the root node
    Node* curr = root;
    char c;
    for (int i = 0; i < key.length(); i++){
        // create a new node if the path doesn't exist
        if (curr->character[key[i] - 'a'] == nullptr) {
            c = key[i];
            curr->character[key[i] - 'a'] = new Node(c);
        }
        // go to the next node
        curr = curr->character[key[i] - 'a'];
    }
    // mark the current node as a leaf
    curr->isLeaf = true;
  }

/**
     * Public : search
     * 
     * Description:
     *      searches for key using getNode(), gets it, 
     *      and returns if valid.
     * 
     * Params:
     *      string key
     * 
     * Returns:
     *      boolean
     */
  bool search(string key){
    Node* node = getNode(key);
    return node->isLeaf && node!= NULL;
  }

/**
     * Public : getNode
     * 
     * Description:
     *      traverses the trie tree for the key 
     *      and returns the node
     * 
     * Params:
     *      string  key
     * 
     * Returns:
     *      A Node
     */
  Node* getNode(string key){
    Node* curr = root;
    for (int i = 0; i < key.length(); i++){
      if(curr->character[key[i] - 'a'] == NULL){
        return NULL;
      }
        // go to the next node
        curr = curr->character[key[i] - 'a'];
    }
    return curr;
  }

/**
     * Public : startsWith
     * 
     * Description:
     *      uses getNode to retrieve a node, and determines
     *      if the word is in the trie tree.
     * 
     * Params:
     *      string  key
     * 
     * Returns:
     *      boolean
     */
  bool startWith(string key){
    return getNode(key) != NULL;
  }

/**
     * Public : find_all(Node*&curr, string key)
     * 
     * Description:
     *      uses recursion to find all the words in the trie
     *      tree and pushes the words to a vector of strings.
     * 
     * Params:
     *      Node*&   curr
     *      string   key
     * 
     * Returns:
     *      None
     */
  void find_all(Node*&curr, string key){
    if(curr->isLeaf){
        results.push_back(key);
      count++;
    }

    for (int i = 0; i < 26; i++) {
        if(curr->character[i]){
            find_all(curr->character[i],key+char(i+97));
        }
    }
}

/**
     * Public : find_all(string key)
     * 
     * Description:
     *      gets the node and sends it to a helper function
     *      which then returns the results vector
     * 
     * Params:
     *      string  key
     * 
     * Returns:
     *      Vector
     */
  vector<string> find_all(string key){
    Node* node = getNode(key);
    results.clear();
 // Finds all partial matches if the path exists in the trie
    find_all(node,key);
    return results;
}

/**
     * Public : Find
     * 
     * Description:
     *      function that uses getch to search a word
     *      one letter at a time
     * 
     * Params:
     *      None
     * 
     * Returns:
     *      None
     */
  void Find(){
    Timer T2;
    vector <string> result;
    char c;
    string word;
    result.clear();
    while(c != 'Z'){            //Type capital Z to end
      c = getch();
      auto start = chrono::steady_clock::now();
      word.push_back(c);
      cout <<"Word:  " <<  word << "\n\n\n";
      result = find_all(word);  //making result vector = retrieving vector
      auto end = chrono::steady_clock::now();
      cout << count << " total words found in " <<           
      chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " nanoseconds" << "\n\n\n"; 
      if(count < 10){
      for(int i = 0; i < count; i++){
        cout << result[i] << "  ";
      }
    }
    else{
    for(int i = 0; i < 10; i++){
      cout << result[i] << "  ";
    }
    cout << "\n\n";
    }
      cout << "\n\n\n\n";
      count = 0;
    }
  }
};


int main(){
  Trie trie;
  ifstream infile;
  string keyword;
  string word;
  vector <string> final;
  Timer T;
  auto start = chrono::steady_clock::now();
  
  infile.open("dictionary.txt");
  while(infile >> keyword){
    trie.insert(keyword);        //inserting words in our trie tree
  }
  auto end = chrono::steady_clock::now();
  cout << "Elapsed time in seconds to load Trie Tree: " << chrono::duration_cast<chrono::milliseconds>(end - start).count()
  << " milliseconds" << "\n\n";

  trie.Find();                   //"main" function for the search

  return 0;
};
