/**
 * This program uses a "getch" function which means "get character".
 * However, getch does not print the character to the terminal, it 
 * lets you decide what to do based on what character you are pressing.
 * 
 * You can test which characters are being pressed using thier ascii values. 
 * 
 * An ascii table here should be helpful 
 *      http://www.asciitable.com/
 * 
 * Some integer values for some keys:
 *      LowerCase Letters   = 97(a) -> 122(z)
 *      UpperCase Letters   = 65(A) -> 90(Z)
 *      Enter Key           = 10
 *      Space Bar           = 32
 *      
 *      Arrow Keys          = Have same values as some letters
 *                            so we can't distinguish between 
 *                            the two (in this context).
 * 
 * 
 */

#include "mygetch.hpp"
#include "termcolor.hpp"
#include "timer.hpp"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define RED termcolor::red

struct wordNode {
  string word;
  wordNode* next;
  wordNode(string x) {
    word = x;
    next  = nullptr;
  }
};

class LList {
  private:
    wordNode* head;
    wordNode* tail;
    int size;
  public:
    LList() {
	    head = tail = nullptr;
      size = 0;
    }
    
    void push (string data) {
      if (tail == nullptr) {
        head = tail = new wordNode (data);
      }
      else if (head == tail) {
        wordNode* temp = new wordNode (data);
        tail = temp;
        head->next = tail;
        tail->next = nullptr;
        temp = nullptr;
        delete temp;
      }
      else {
        wordNode* temp;
        temp = tail;
        tail = new wordNode (data);
        temp->next = tail;
        tail->next = nullptr;
      }
      size++;
    }

    string popRear () {
      string popped;                   // value to be popped and returned
      wordNode* temp = head;            // Needed to relink and reconnect tail
      while (temp->next != tail) {  // Travels to node before tail
        temp = temp->next;
      }
      tail = temp;                  // Moves tail back up by 1
      temp = temp->next;            // Moves temp to old tail
      tail->next = nullptr;         // Cuts off linking
      temp->next = nullptr;         // Cuts off linking
      popped = temp->word;          // Stores data before deletion
      delete temp;                  // Deletes popped node
      size--;
      return popped;
    }

    void findWords (vector<string> &matches, string term) {
      matches.clear();
      wordNode* travel = head;
      size_t found;           // size_t is an integer position of
                            // found item. -1 if its not found.

      while (travel -> next) { // loop through list
        found = travel->word.find(term);    // check for substr match

        if(found == 0) {          // if found >= 0 (its found then)
          matches.push_back(travel->word);     // add to matches
        }
        travel = travel->next; // traverses list
      }
    }
};

int main() {
    char k;                 // holder for character being typed
    string word = "";       // var to concatenate letters to
    int loc;                // location of substring to change its color

    ofstream fout("temp.txt");

    Timer T;   // create a timer
    T.Start(); // start it
    LList dict;
    vector<string> matches;
    string data;
    ifstream fin("dictionary.txt");

    while (!fin.eof()) {
      fin >> data;
      dict.push(data);
    }
    T.End(); // end the current timer
    
    // print out how long it took to load the animals file
    cout << T.Seconds() << " seconds to read in and print dictionary to list" << endl;
    cout << T.MilliSeconds() << " milli to read in and print dictionary to list" << endl;
    cout << T.NanoSeconds() << " nano to read in and print dictionary to list" << endl;

    cout << "Type keys and watch what happens. Type capital Z to quit." << endl;

    // While capital Z is not typed keep looping
    while ((k = getch()) != 'Z') {
        T.Start(); // start it
        // Tests for a backspace and if pressed deletes
        // last letter from "word".
        if ((int)k == 127) {
            if (word.size() > 0) {
                word = word.substr(0, word.size() - 1);
            }
        } else {
            // Make sure a letter was pressed and only letter
            if (!isalpha(k)) {
                cout << "Letters only!" << endl;
                continue;
            }

            // We know its a letter, lets make sure its lowercase.
            // Any letter with ascii value < 97 is capital so we
            // lower it.
            if ((int)k < 97) {
                k += 32;
            }
            word += k; // append char to word
        }

        // Find any animals in the array that partially match
        // our substr word

        dict.findWords(matches, word);

        /*if(word.size()>2){
          cout<<"matches:\n";
          for(int i=0;i<matches.size();i++){
            cout<<matches[i]<<endl;
          }
          cout<<"++++++++++++++\n";
        }*/


        if ((int)k != 32) { // if k is not a space print it
            T.End();
            cout << termcolor::red << word << termcolor::reset << endl << endl;
            cout << matches.size() << " words found in " << T.NanoSeconds() << " nanoseconds" << endl << endl;
            //cout << "Keypressed: " << termcolor::blue << k << " = " << (int)k << termcolor::reset << endl;
            //cout << "Current Substr: " << termcolor::red << word << termcolor::reset << endl;
            //cout << "Words Found: ";
            cout << termcolor::green;
            // This prints out all found matches
            for (int i = 0; i < matches.size(); i++) {
              //cout<<i<<". "<<matches[i]<<endl;
                // find the substring in the word
                loc = matches[i].find(word);
                // if its found
                //
                if (loc != string::npos) {
                    //print one letter at a time turning on red or green
                    // depending on if the matching subtring is being printed
                    for (int j = 0; j < matches[i].size(); j++) {
                        // if we are printing the substring turn it red
                        if (j >= loc && j <= loc + word.size() - 1) {
                            cout << termcolor::red;
                        } else {
                            cout << termcolor::green;
                        }
                        cout << matches[i][j];
                    }
                    cout << termcolor::green;
                }
                cout << " ";
              if(i>9){
                break;
              }
            }
            cout << termcolor::reset << endl
                 << endl;
            }
          cout <<endl;
        }
    
    return 0;
}
