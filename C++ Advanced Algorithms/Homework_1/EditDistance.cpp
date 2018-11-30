#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
using namespace std;


int GetMin (int i, int j, int wordDistance[][50] ) {

  int minValue = wordDistance[i-1][j-1];

  if ( minValue > wordDistance[i-1][j] )
    minValue = wordDistance[i-1][j];

  if ( minValue > wordDistance[i][j-1] )
    minValue = wordDistance[i][j-1];

  return minValue;
}

void PrintTable ( string wordOne, string wordTwo, int wordDistance[][50]) {
  	
  for ( int m = 0; m < wordOne.length(); ++m ) {

    for ( int n = 0; n < wordTwo.length(); ++n) {

      cout << wordDistance[m][n];

    }

    cout << endl;

  }

}

int EditDistance ( string wordOne, string wordTwo ) {

  int specialCaseOne = 0;
  int specialCaseTwo = 0;

  //vector<vector<int> > wordDistance(wordOne.length(), vector<int>(wordTwo.length()));
  int wordDistance[50][50];
  //vector<vector<int> > wordDistance;
  //wordDistance.reserve( wordOne.length() );
  //for ( int i = 0; i < wordOne.length(); i++) {
  //  wordDistance[i].reserve( wordTwo.length() );
  //}
  
  /* Fills out 2D vector */
  for ( int i = 0; i < wordOne.length(); ++i ) {
    //PrintTable ( wordOne, wordTwo, wordDistance ); 
    //vector<int> Distance;
    
    for ( int j = 0; j < wordTwo.length(); ++j ) {
	    
      /* Assigns origin value */
      if ( i == 0 && j == 0 ) {
	
	if ( wordOne.substr ( i, 1 ) != wordTwo.substr ( j, 1 )){
	  
	  //Distance.push_back(1);
	  wordDistance[i][j] = 1;
	  //wordDistance[i].swap(Distance);
	
	}

	
	else {
	
	  //Distance.push_back(0);
	  wordDistance[i][j] = 0;
	  //wordDistance[i].swap(Distance);


	}

      }

      /* Assigns values down 1st row */
      else if ( i == 0 && j != 0 ) {


	if ( wordDistance[0][0] == 1 ) {

	  if ( wordOne.substr( i, 1 ) == wordTwo.substr( j, 1 ) ) {
	    
	    if ( specialCaseOne > 0 ) {

	      //Distance.push_back(wordDistance[i][j-1] + 1);
	      wordDistance[i][j] = wordDistance[i][j-1] + 1;
	      //wordDistance[i].swap(Distance);
	    }

	    else {
	      cout << "Pushing back 1" << endl;


	      //Distance.push_back(wordDistance[i][j-1]);
	      wordDistance[i][j] = wordDistance[i][j-1];
	      //wordDistance[i].swap(Distance);
	      specialCaseOne = 1;

	    }

	  }

	  else{ 

	    //Distance.push_back(wordDistance[i][j-1] + 1);
	    wordDistance[i][j] = wordDistance[i][j-1] + 1;
	    //wordDistance[i].swap(Distance);
	  }
	  }

	else{
	  
	  //Distance.push_back(wordDistance[i][j-1] + 1);
	  wordDistance[i][j] = wordDistance[i][j-1] + 1;
	  //wordDistance[i].swap(Distance);
	}
      
      }
      
      /* Assigns values across 1st column */
      else if ( i != 0 && j == 0 ) {


	if ( wordDistance[0][0] == 1 ) {

	  if ( wordTwo.substr( j, 1 ) == wordOne.substr( i, 1 ) ) {

	    if ( specialCaseTwo > 0 ) {

	      //Distance.push_back(wordDistance[i-1][j] + 1);
	      wordDistance[i][j] = wordDistance[i-1][j] + 1;
	      //wordDistance[i].swap(Distance);
	  }
	    else {

	      //Distance.push_back(wordDistance[i-1][j]);
	      wordDistance[i][j] = wordDistance[i-1][j];
	      //wordDistance[i].swap(Distance);
	      specialCaseTwo = 1;

	    }

	  }

	  else{

	    //Distance.push_back(wordDistance[i-1][j] + 1);
	    wordDistance[i][j] = wordDistance[i-1][j] + 1;
	    //wordDistance[i].swap(Distance);
	  }

	}

        else{
	  
	  //Distance.push_back(wordDistance[i-1][j] + 1);
	  wordDistance[i][j] = wordDistance[i-1][j] + 1;
	  //wordDistance[i].swap(Distance);
	}
      }
      
      /* Fills in rest of table */
      else {

	int ValueToAdd = 0;
	int minValue = GetMin( i, j, wordDistance);
	
	/* Check if letters are different */ 
	if ( wordOne.substr ( i, 1 ) != wordTwo.substr ( j, 1 )) {

	  string tempOne = wordOne.substr ( 0, i );
	  string tempTwo = wordTwo.substr ( 0, j );
	  int tempThree = tempOne.length() - tempTwo.length();

	 if ( (wordOne.substr ( i-1, 1 ) == wordTwo.substr ( j, 1 ) && wordOne.substr ( i, 1 ) == wordTwo.substr ( j-1, 1 )) && abs(tempThree) < 2 )

	   if ( minValue == 0 )
	     
	     ValueToAdd = 1;

	   else

	     ValueToAdd = 0;

	 else

	  ValueToAdd = 1;

	}
      	      
	else{
	  
	  /* Check if word length is different */
	  string strOne = wordOne.substr( 0, i );
	  string strTwo = wordTwo.substr( 0, j );
	  int strThree = strOne.length() - strTwo.length();
	  
	  if ( strOne.length() != strTwo.length() ){
	    
	    /* Add 1 if minValue = 0 or length is > than 1 */
	    if ( minValue == 0 || abs(strThree) > 1 )
	      ValueToAdd = 1;
		
	  }
	      
	}

	wordDistance[i][j] = ValueToAdd + minValue;
	//Distance.push_back(ValueToAdd + minValue);





	//cout << wordDistance[i][j] << endl;
      }
      
      //wordDistance[i] = move(Distance);
      //wordDistance[i].insert(end(wordDistance[i]), begin(Distance), end(Distance));
      //Distance.clear();
    }
  //wordDistance[i].swap(Distance);
  //PrintTable ( wordOne, wordTwo, wordDistance);
  //cout << "__________________________" << endl;
  }
  PrintTable ( wordOne, wordTwo, wordDistance);
  return wordDistance[wordOne.length()-1][wordTwo.length()-1];
}

int main ( int argc, char * argv[] ) {

	vector<string> FileWords;
  	string FileWord;
	string wordOne = argv[1];
	string ShortestWord = "fail";
	int ShortestDistance = 100;



	ifstream inFile;
	inFile.open("Words.txt");

	if (!inFile) {
	  cout << "Unable to open file" << endl;
	  exit(1);
	}

	while (inFile >> FileWord) {
	  FileWords.push_back(FileWord);
	}
	inFile.close();




	for ( int i = 0; i < FileWords.size(); i++ ) {
	 
	  string wordTwo = FileWords[i];

	  int length = EditDistance ( wordOne, wordTwo);
	  cout << wordTwo << " " << length << endl;
	  //PrintTable (wordOne, wordTwo, wordDistance);
	  
	  
	    cout << "_________________________________" << endl;
	  //if ( wordDistance[wordOne.length()-1][wordTwo.length()-1] < ShortestDistance )
	  if ( ShortestDistance > length ){
	    ShortestDistance = length;
	    ShortestWord = wordTwo;
	  }

	  //wordDistance.clear();

	}
	    cout << "The shortest word is: " << ShortestWord << endl;

	
	

	
	
	return 0;
}
