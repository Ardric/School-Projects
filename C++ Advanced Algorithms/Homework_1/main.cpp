#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

struct item{

  string name;
  double value;
  double weight;
  double rVal;
  double ratio;
  bool inBag = false;// = false;
};

bool cmp(item  a,item  b){
  return a.weight < b.weight;
}




void showBag(vector<item>& items){

  int totalWeight = 0;
  int totalValue = 0;
  int totalR = 0;
  cout << "Everything in the bag: " << endl;

  for (item i : items){


    if (i.inBag == true){
      
//      cout << "In bag cout" << endl;  
      totalWeight += i.weight;
      totalValue += i.value;
      totalR += i.rVal;
      cout << i.name << '\t' << i.weight << '\t' << i.value << endl;
  
    }
  }

  cout << "Total weight: " << totalWeight << '\t' << "Total value: " << totalValue << '\t' << "Total R: " << totalR << endl;
}//end func




void fillBag(vector<item>& items, int maxWeight){//, int remainingWeight){

  if (maxWeight == 0){

    return;

  }


  double bestR = -1;
  

  for (int k = 0; k < items.size(); k++){

    if (items[k].ratio > bestR){

      if (items[k].weight < maxWeight && maxWeight-items[k].weight >= 0){

	if (items[k].inBag == false){

           bestR = k;

	}else{continue;}

      }else{continue;}
    }else{continue;}

  }


 if (bestR != -1){


  items[bestR].inBag = true;
  cout << "Adding: "<< items[bestR].name <<'\t' <<  "Remaining: " << maxWeight-items[bestR].weight <<'\t' << "Show: " << items[bestR].inBag << endl;


  fillBag(items, maxWeight-items[bestR].weight);
 }
 else {return;}



}//end func



int main(){

  string temp = "";
  ifstream infile("input.txt");
  vector<item> items;

  int maxWeight = 10;

  while (getline(infile, temp)){

    int firstsplit = temp.find(";");
    int lastsplit = temp.find_last_of(";");

 
    item toAdd;
    toAdd.name = temp.substr(0, firstsplit);
    toAdd.value = atof(temp.substr(firstsplit+1, lastsplit-firstsplit-1).c_str());
    toAdd.weight = atof(temp.substr(lastsplit+1, temp.length()).c_str());
    toAdd.rVal = toAdd.value - toAdd.weight;
    toAdd.ratio = toAdd.value / toAdd.weight;

    items.push_back(toAdd);
  }

  sort(items.begin(), items.end(), cmp);




  int remainingWeight = maxWeight;
  fillBag(items, remainingWeight);
  showBag(items);

  
/*  
  cout << "LINE" << endl;

  for (item i : items){

    cout << i.name << '\t' << i.weight << '\t' << i.value << '\t' << i.rVal << '\t' << i.inBag << endl;
  }
*/

  return 0;

  
  
}
