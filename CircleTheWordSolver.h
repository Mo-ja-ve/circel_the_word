#include <vector>
#include <string>
#include <algorithm>
#include <omp.h>
using namespace std;

#ifndef DWJ_WORD_CIRCLE_DEF
#define DWJ_WORD_CIRCLE_DEF
#pragma parallel
class CircleTheWordSolver {
 public:
  vector<pair<int, int> > word_locations(
         vector<vector<char> > &puzzle,
         vector<string> &wordlist);
};
#endif
