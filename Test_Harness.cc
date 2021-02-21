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

  pair <int,char> word_test(wordlist[0].length(), wordlist[0].back());

 // cout<<endl<<endl<<"TEST: "<<word_test.first<<" "<<word_test.second<<endl<<endl;

  size_t puzz_height = puzzle.size();

  for(int i = 0; i < puzz_height; i++){
      size_t puzz_width = puzzle[i].size();

      for(int j = 0; j < puzz_width; j++){
	if(puzzle[i][j] == wordlist[0].front()){//  testing to see if this first letter of a word match
	  //cout<<endl<<endl<<"MATCH: "<<puzzle[i][j]<<"  "<<wordlist[0].front()<<endl;
	  if(puzzle[i][(j + (word_test.first)-1)] == word_test.second){
		//cout<<endl<<" found match! "<<endl;
		//cout<<endl<<"I: "<<i<<"  J: "<<j<<" space: "<<j+((word_test.first)-1)<<endl;

	  }
	  if(puzzle[i+word_test.first][j] == word_test.second){
		cout<<endl<<" found match! "<<endl;
                cout<<endl<<"I: "<<i<<"  J: "<<j<<" space: "<<i+((word_test.first))<<endl;
	  }
        }
      }
  }
  // cout<<endl<<"height: "<<puzz_height;
  //cout<<endl<<"width: "<<puzz_width<<endl;

vector<pair<int,int>> z(1);

return z;
}
