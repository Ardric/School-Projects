#include "Spamassassin.h"


void Spamassassin::Single(string path)
{
  string phrase;
  double ham = 0;
  double spam = 0;
  DistinctWordCount(path);
  cout << "OverallFileCount: " << OverallFileCount << endl;
  double HamChance = (HamFileCount / 2602);
  double SpamChance = (SpamFileCount / 2602);
  cout << "Please type a phrase so we can determine whether it is ham or spam." << endl;
  getline(cin, phrase);
  istringstream sin(phrase);
  while (sin >> phrase)
  {
    ham = hamcount[phrase];
    spam = spamcount[phrase];

    if ((ham + spam) == 0)
      continue;
    else if (spam == 0 && ham > 0)
      spam = (1 / (10 * OverallFileCount));
    else if (ham == 0 && spam > 0)
      ham = (1 / (10 * OverallFileCount));

    HamChance += log10(ham / HamFileCount);
    SpamChance += log10(spam / SpamFileCount);
  }
  if (HamChance > SpamChance)
    cout << "HAM" << endl;
  if (HamChance < SpamChance)
    cout << "SPAM" << endl;
  if (HamChance == SpamChance)
    cout << "Not Working" << endl;
}

void Spamassassin::SeparateMapCounts(string path)
{
  string temp, temp2, word;
  string index = "index";
  ifstream in;
  int spamCount = 0;
  int hamCount = 0;

  in.open(path + index);
  getfiles(in);

  for (unsigned int i = 0; i < files.size(); ++i)
  {
    temp = files[i];
    ifstream fin;
    if (temp.substr(6,2) == "sp")
    {
      fin.open(path + temp);
      getline(fin, temp2);
      getline(fin, temp2);
      while (fin >> temp2)
      {
	++spamcount[temp2];
	++spamCount;
      }
    }
    else
    {
      fin.open(path + temp);
      getline(fin, temp2);
      getline(fin, temp2);
      while (fin >> temp2)
      {
	++hamcount[temp2];
	++hamCount;
      }
    }
  }
  cout << "HamCount: " << hamCount << endl;
  cout << "SpamCount: " << spamCount << endl;
}
void Spamassassin::DistinctWordCount(string path)
{
  string temp, temp2;
  string index = "index";
  ifstream in;
  int count = 0;
  int hamCount = 0;
  int spamCount = 0;

  in.open(path + index);
  getfiles(in);

  for (unsigned int i = 0; i < files.size(); ++i)
  {
    temp = files[i];
    ifstream fin;
    fin.open(path + temp);
    getline(fin, temp2);
    getline(fin, temp2);
    while (fin >> temp2)
    {
      distinctwords.insert(temp2);
    }
    if (temp.substr(6,2) == "sp")
    { ++OverallFileCount;
      ++SpamFileCount;
      for (auto i : distinctwords)
      {
	++spamcount[i];
	++spamCount;
      }
    }
    else
    {
      ++OverallFileCount;
      ++HamFileCount;
      for (auto i : distinctwords)
      {
	++hamcount[i];
	++hamCount;
      }
    }
    for (auto i : distinctwords)
    {	
      ++distinctcount[i];
      ++count;
    }
    distinctwords.clear();
  }
  cout << "Total count of words accross files, not duplicates within the same file: " << count << endl;
  cout << "Total count of words across files, not duplicates within the same  Ham file: " << hamCount << endl << "Total count of wards across files, not duplicates within the same Spam file: " << spamCount << endl;
}

void Spamassassin::WordCount(string path)
{
  int count = 0;
  string temp, temp2, word;
  string index = "index";
  ifstream in;

  in.open(path + index);
  getfiles(in);

  for (unsigned int i = 0; i < files.size(); ++i)
  {
    temp = files[i];
    ifstream fin;
    fin.open(path + temp);
    getline(fin, temp2);
    getline(fin, temp2);
    while (fin >> temp2)
    {
      ++count;
    }
  }
  cout << "Total number of words in all test files: " << count << endl;
}

void Spamassassin::getfiles(istream& in)
{
  string name;
  string str;

  while (getline(in, name))
  {
    str = name;
    if (str.substr(0,6) != "part10")
    {
      files.push_back(name);
    }
  }
}

void Spamassassin::prepwork(string path)
{
  string temp, temp2;
  string index = "index";
  ifstream in;

  in.open(path + index);
  getfiles(in);

  for (unsigned int i = 0; i < files.size(); ++i)
  {
    temp = files[i];
    ifstream fin;
    fin.open(path + temp);
    getline(fin, temp2);
    getline(fin, temp2);
    fin >> temp2;
    cout << temp2 << endl;
  }
}

int main(int argc, char * argv[])
{
  Spamassassin x;
  string arg1 = argv[1];
  string arg2 = argv[2];

  if ( arg1 != "")
  {
    if (arg2 == "prep")
    {
      x.prepwork(arg1);
    }
    if (arg2 == "single")
    {
      x.Single(arg1);
    }
    if (arg2 == "count")
    {
      x.WordCount(arg1);
    }
    if (arg2 == "maps")
    {
      x.SeparateMapCounts(arg1);
    }
    if (arg2 == "distinctcount")
    {
      x.DistinctWordCount(arg1);
    }
  }

  else
    cout << "The second arguement doesn't match any options." << endl;

  return 0;
}
