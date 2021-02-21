#include <iostream>
#include "CircleTheWordSolver.h"
#include <vector>
#include <string>
using namespace std;

int main() {
  int n, m;
  cin >> n;
  cin >> m;
  vector<vector<char> > puzzle;
  puzzle.resize(n);
  for (size_t i=0;i<n;i++) {
    puzzle[i].resize(m);
    for (size_t j=0;j<m;j++) {
      char c;
      cin >> c; // ignore whitespace
      if (!cin.fail()) {
	puzzle[i][j] = c;
      } else {
	cout << "Bad input --- puzzle" << endl;
	exit(-1);
      }
    }
  }
  int k;
  cin >> k; // # of words;

  vector<string> wordlist;
  for (size_t i=0;i<k; i++) {
    string t;
    cin >> t;
    if (!cin.fail()) {
      wordlist.push_back(t);
    } else {
      cout << "Bad Input --- wordlist"  << endl;
    }
  }
  vector<pair<int, int> > locations;
  CircleTheWordSolver obj;

  locations = obj.word_locations(puzzle,wordlist);

  for (size_t i=0;i<locations.size();i++) {
    if (locations[i] == make_pair(-1,-1) ) {
      cout << wordlist[i] << " not found " << endl;
    } else {
      cout << wordlist[i] << " found at location " << locations[i].first << "," << locations[i].second << endl;
    }
  }
}

vector<pair<int,int>> CircleTheWordSolver::word_locations(vector<vector<char> > &puzzle, vector<string> &wordlist){

  vector<pair <int,char>> word_test;
  word_test.resize(wordlist.size());
  for(int i = 0; i < wordlist.size(); i++){
      word_test[i].first = wordlist[i].length() - 1;
      word_test[i].second = wordlist[i].back();
  }
  string temp_str = "";
  cout<<endl<<endl<<"WORD TEST VEC: "<<word_test[wordlist.size()-1].first<<word_test[wordlist.size()-1].second<<endl;
 // cout<<endl<<endl<<"TEST: "<<word_test.first<<" "<<word_test.second<<endl<<endl;

  size_t puzz_height = puzzle.size();

  for(int i = 0; i < puzz_height; i++){
      size_t puzz_width = puzzle[i].size();

      for(int j = 0; j < puzz_width; j++){
	       if(puzzle[i][j] == wordlist[0].front()){//  testing to see if this first letter of a word match

	       if(puzzle[i][j + word_test[0].first] == word_test[0].second){
                      
	       }
	       if(i + word_test[0].first < puzz_height){
           if(puzzle[i+word_test[0].first][j] == word_test[0].second){
             for(int a = i; a < puzz_height; a++)
               temp_str+=puzzle[a][j];
		         if(temp_str == wordlist[0]){
               cout<<endl<<endl<<"MATCH: "<<temp_str<<" "<<wordlist[0]<<endl;
             }else{
               temp_str = "";
             }
	         }
         }
         }
      }
   }
   cout<<endl<<endl<<temp_str<<endl;
  // cout<<endl<<"height: "<<puzz_height;
  //cout<<endl<<"width: "<<puzz_width<<endl;

vector<pair<int,int>> z(1);

return z;
}
		            //cout<<endl<<" found match! "<<endl;
                //cout<<endl<<"I: "<<i<<"  J: "<<j<<" space: "<<i+word_test.first<<endl;
