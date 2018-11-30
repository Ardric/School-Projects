#ifndef _SPAMASSASSIN_H_
#define _SPAMASSASSIN_H_
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cmath>
using namespace std;

class Spamassassin
{
  private:
    vector<string> files;
    unordered_map<string, int> hamcount;
    unordered_map<string, int> spamcount;
    unordered_map<string, int> count;
    unordered_set<string> distinctwords;
    unordered_map<string, int> distinctcount;
    double HamFileCount = 0;
    double SpamFileCount = 0;
    double OverallFileCount = 0;

  public:
    void prepwork(string path);
    void Single(string path);
    void getfiles(istream& in);
    void WordCount(string path);
    void SeparateMapCounts(string path);
    void DistinctWordCount(string path);
};
#endif
