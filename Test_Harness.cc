#include <iostream>
#include "CircleTheWordSolver.h"
#include <vector>
#include <string>
using namespace std;

int main() {

  #pragma parallel

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
  #pragma parallel

  vector<pair <int,char>> word_test;
  word_test.resize(wordlist.size());
  for(int i = 0; i < wordlist.size(); i++){
      word_test[i].first = wordlist[i].length() - 1;
      word_test[i].second = wordlist[i].back();
  }
  string temp_str = "";

  size_t puzz_height = puzzle.size();

  #pragma omp parallel for
  for(int i = 0; i < puzz_height; i++){
      size_t puzz_width = puzzle[i].size();
      //cout<<endl<<" i "<<i<<endl;
      for(int j = 0; j < puzz_width; j++){
        //cout<<endl<<" j "<<j<<endl;
        int first_letterindex = 0;
        for(first_letterindex; first_letterindex < wordlist.size(); first_letterindex++)
	       if(puzzle[i][j] == wordlist[first_letterindex].front()){//  testing to see if this first letter of a word matches

         if(j + word_test[first_letterindex].first <= puzz_width)//  testing to see if word patches normally
         if(puzzle[i][j + word_test[first_letterindex].first] == word_test[first_letterindex].second){
           int b = 0; int a = j;
           while(b <= word_test[first_letterindex].first){
             temp_str += puzzle[i][a];
             b++; a++;
           }
           if(temp_str == wordlist[first_letterindex]){
             cout<<endl<<endl<<"WORD MATCH!: "<<temp_str<<endl;
             temp_str = "";
           }else{
             temp_str = "";
           }
         }

         if(j - word_test[first_letterindex].first >= 0)//  testing to see if word matches spelled backwards
         if(puzzle[i][j - word_test[first_letterindex].first] == word_test[first_letterindex].second){
           int b = 0; int a = j;
           while(b <= word_test[first_letterindex].first){
             temp_str += puzzle[i][a];
             b++; a--;
           }
           if(temp_str == wordlist[first_letterindex]){
             cout<<endl<<endl<<"MATCH: "<<temp_str<<endl;
             temp_str = "";
           }else{
             temp_str = "";
           }
         }

	       if(i + word_test[first_letterindex].first < puzz_height){//  testing if word matches vertically down
           if(puzzle[i+word_test[first_letterindex].first][j] == word_test[first_letterindex].second){
             int b = 0; int a = i;
             while(b <= word_test[first_letterindex].first){
               temp_str += puzzle[a][j];
               b++; a++;
             }

		         if(temp_str == wordlist[first_letterindex]){
               cout<<endl<<endl<<"MATCH: "<<temp_str<<endl;
               temp_str = " ";
             }else{
               temp_str = "";
             }
	         }
         }

         if(i - word_test[first_letterindex].first >= 0){// testing if word matches vertically up
           if(puzzle[i - word_test[first_letterindex].first][j] == word_test[first_letterindex].second){
             int b = 0; int a = i;
             while(b <= word_test[first_letterindex].first){
               temp_str += puzzle[a][j];
               b++; a--;
             }
             //cout<<endl<<endl<<"WORD SECOND "<<temp_str<<endl;
             if(temp_str == wordlist[first_letterindex]){
               cout<<endl<<endl<<"MATCH: "<<temp_str<<endl;
               temp_str = "";
             }else{
               temp_str = "";
             }
           }
         }

         if(i - word_test[first_letterindex].first >= 0 && j - word_test[first_letterindex].first >= 0)//  checking to see if word is spelled leftwise and vertically
           if(puzzle[i - word_test[first_letterindex].first][j - word_test[first_letterindex].first] == word_test[first_letterindex].second){
             int b = 0; int a = i; int c = j;
             while(b <= word_test[first_letterindex].first){
               temp_str += puzzle[a][c];
               b++; a--; c--;
             }
             if(temp_str == wordlist[first_letterindex]){
               cout<<endl<<endl<<"MATCH: "<<temp_str<<endl;
               temp_str ="";
             }else{
               temp_str = "";
             }
           }

           if(i - word_test[first_letterindex].first >= 0 && j + word_test[first_letterindex].first <= puzz_width)//  checking to see if word is spelled rightwise and vertically
             if(puzzle[i - word_test[first_letterindex].first][j + word_test[first_letterindex].first] == word_test[first_letterindex].second){
               int b = 0; int a = i; int c = j;
               while(b <= word_test[first_letterindex].first){
                 temp_str += puzzle[a][c];
                 b++; a--; c++;
               }
                 if(temp_str == wordlist[first_letterindex]){
                 cout<<endl<<endl<<"MATCH: "<<temp_str<<" "<<endl;
                 temp_str ="";
               }else{
                 temp_str = "";
               }
             }

             if((i + word_test[first_letterindex].first < puzz_height) && (j + word_test[first_letterindex].first < puzz_width)){ //  checking to see if word is spelled rightwise and vertically-down
               //cout<<endl<<endl<<"debug hello!"<<endl;
               //cout<<endl<<endl<<(i + word_test[first_letterindex].first)<<endl<<(j + word_test[first_letterindex].first)<<endl;
               //cout<<endl<<puzz_height<<" "<<puzz_width<<endl;
               if(puzzle[i + word_test[first_letterindex].first][j + word_test[first_letterindex].first] == word_test[first_letterindex].second){
                    int b = 0; int a = i; int c = j;
                    while(b <= word_test[first_letterindex].first){
                   temp_str += puzzle[a][c];
                   b++; a++; c++;
                 }

                  if(temp_str == wordlist[first_letterindex]){
                   cout<<endl<<endl<<"MATCH: "<<temp_str<<endl;
                   temp_str ="";
                 }else{
                   temp_str = "";
                 }
               }
             }

             if((i + word_test[first_letterindex].first < puzz_height) && (j - word_test[first_letterindex].first >= 0)){ //  checking to see if word is spelled lefttwise and vertically-down

               if(puzzle[i + word_test[first_letterindex].first][j - word_test[first_letterindex].first] == word_test[first_letterindex].second){
                    int b = 0; int a = i; int c = j;
                    while(b <= word_test[first_letterindex].first){
                   temp_str += puzzle[a][c];
                   b++; a++; c--;
                 }

                  if(temp_str == wordlist[first_letterindex]){
                   cout<<endl<<endl<<"MATCH: "<<temp_str<<endl;
                   temp_str ="";
                 }else{
                   temp_str = "";
                 }
               }
             }
         }
      }
   }
   //cout<<endl<<endl<<" debug hello 1"<<endl;
   //cout<<endl<<endl<<temp_str<<endl;
  // cout<<endl<<"height: "<<puzz_height;
  //cout<<endl<<"width: "<<puzz_width<<endl;

vector<pair<int,int>> z(1);

return z;
}
		            //cout<<endl<<" found match! "<<endl;
                //cout<<endl<<"I: "<<i<<"  J: "<<j<<" space: "<<i+word_test.first<<endl;
