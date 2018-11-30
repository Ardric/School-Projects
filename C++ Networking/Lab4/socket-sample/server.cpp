#include "Socket.h"
#include "Timer.h"
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

int state = 1;

struct Card
{
  string value;
  bool used;
};

struct Player
{
  Socket sock;
  string position;
  vector <Card> Hand;
};

Socket listener;

vector<Player> Players;
vector<Socket> Observers;
vector<Socket> Neutral;

int dealer;

void State_2_Handler()
{
  for (int i = 0; i < Players.size(); i++)
    Players[i].Hand.erase(Players[i].Hand.begin(), Players[i].Hand.end());

  dealer  = (rand() % 3) + 1;
  vector<string> Cards { "2H", "3H", "4H", "5H", "6H", "7H", "8H", "9H", "TH", "JH", "QH", "KH", "AH",
    			 "2C", "3C", "4C", "5C", "6C", "7C", "8C", "9C", "TC", "JC", "QC", "KC", "AC",
			 "2S", "3S", "4S", "5S", "6S", "7S", "8S", "9S", "TS", "JS", "QS", "KS", "AS",
			 "2D", "3D", "4D", "5D", "6D", "7D", "8D", "9D", "TD", "JD", "QD", "KD", "AD" };

  int next;
  string card;
  string line = "+HAND ";
  Card c;

  for (int i = 0; i < 52; i++)
  {
    next = (rand() % 4) + 1;
    card = Cards.back();
    Cards.pop_back();

    for (unsigned int j = 0; j < Players.size(); j++)
    {
      if (Players[j].position == to_string(next) && Players[j].Hand.size() < 13)
      {
	c.value = card;
	c.used = false;
	Players[j].Hand.push_back(c);
      }
      else if (Players[j].position == to_string(next) && Players[j].Hand.size() == 13)
      {
	for (unsigned int x = 0; x < Players.size(); x++)
	{
	  if (Players[x].Hand.size() < 13)
	  {
	    c.value = card;
	    c.used = false;
	    Players[x].Hand.push_back(c);
	  }
	}
      }
     }
  }

  for (unsigned int i = 0; i < Players.size(); i++)
  {
    for (unsigned int j = 0; j < Players[i].Hand.size(); j++)
    {
      line = line + Players[i].Hand[j].value;
    }

    line = line + "\r\n";
    cout << "Sending cards to: " << i << endl;
    Players[i].sock.writeString(line);
    line = "+HAND ";
  }

  state = 3;
}


string State_3_Handler(string message)
{

  string line;

  if (message.substr(0,4) == "IBID")
  {
    if (message.length() != 9){}
  }
  else if (message.substr(0,4) == "CHAT")
  {
    if (message.length() > 211){}
  } 
  else 
  {
    line = "-Invalid"; 
  }

  return line; 
}
string State_4_Handler(string message){ return ""; }
void State_5_Handler(){}


int main(int argc,char** argv){
  SocketSet socketSet;
  listener.listen(argv[1]);
  listener.joinGroup(&socketSet);
  string msg = "";
  Player player;

  while(!listener.isClosed()){
    socketSet.wait(2);

    if (state == 2)
    {
      State_2_Handler();
    }
  
    if(listener.hasEvent()){

      Socket sock = listener.accept();
      sock.joinGroup(&socketSet);
      Neutral.push_back(sock);
      sock.writeString("+PLYR Welcome to the Spades server, do you want to be a player or observer?\r\n");
      cout << Neutral.size() << endl;


    }

    else{




















      for(int z = Neutral.size()-1; z >=0; --z)
      {
	if(Neutral[z].hasEvent())
	{
	  cout << "Correctly hitting vector event" << endl;
	  Neutral[z].readString(msg, 256);
	  if(!Neutral[z].isClosed())
	  {
      //sock.readString(msg, 256);
      if (msg.length() == 8){
	if (msg.substr(0,4) == "PLYR"){
	  string pos = msg.substr(5,1);
	  if (pos == "1" or pos == "2" or pos == "3" or pos == "4"){
	    for (int i = 0; i < Players.size(); i++)
	    {
	      if (pos == Players[i].position){
		Neutral[z].writeString("-Player slot" + pos + " is already taken. Closing connection.\r\n");
		Neutral[z].close();
	      }
	    }

	    if (!Neutral[z].isClosed()){
	      Neutral[z].writeString("+PLYR You have successfully been added as player " + pos + ".\r\n");
	      cout << "Check" << endl;
	      player.sock = Neutral[z];
	      player.position = pos;
	      Players.push_back(player);
	      Neutral.erase(Neutral.begin() + z);
	    }
	  }

	  else{
	    Neutral[z].writeString("-Inappropriate request, closing connectionr\r\n");
	    Neutral[z].close();
	  }

	}


	else{
	  Neutral[z].writeString("-Inappropriate request, closing connectionr\r\n");
	  Neutral[z].close();
	}

      }

      else if (msg.length() == 6){
	if (msg.substr(0,4) == "OBSV"){
	  Observers.push_back(Neutral[z]);
	      Neutral.erase(Neutral.begin() + z);
	}
	else if(msg.substr(0,4) == "PLYR") {
	  if (Players.size() == 4){
	    Neutral[z].writeString("-Inappropriate request, closing connectionr\r\n");
	    Neutral[z].close();
	  }
	  else if (Players.size() == 0){
	    Neutral[z].writeString("+PLYR Successfully connected as player 1.\r\n");
	    player.sock = Neutral[z];
	    player.position = "1";
	    Players.push_back(player);
	      Neutral.erase(Neutral.begin() + z);
	    for (int i = 0; i < Players.size(); i++){
	      cout << Players[i].position << endl;
	    }
	  }
	  else{
	    bool x = true;
	    int count = 1;
	    while(x){
	      for (int j = 0; j < Players.size(); j++){
		if (Players[j].position == to_string(count))
		  break;
		if (j == Players.size() - 1){
		  x = false;
		  Neutral[z].writeString("+PLYR Successfully connected as player " + to_string(count) + ".\r\n");
		  player.sock = Neutral[z];
		  player.position = to_string(count);
		  Players.push_back(player);
	      Neutral.erase(Neutral.begin() + z);
		  break;
		}
	      }
	      count++;
	      if (count == 5 && x == true){
		x = false;
		Neutral[z].writeString("-Inappropriate request, closing connection\r\n");
		Neutral[z].close();
	      }
	    }
	  }
	}

	else
	{
	  Neutral[z].writeString("-Inappropriate request, closing connectionr\r\n");
	  Neutral[z].close();
	}
      }

      else{
	Neutral[z].writeString("-Inappropriate request, closing connectionr\r\n");
	Neutral[z].close();
      }

      if (Players.size() == 4)
	state = 2;
	  }
	  else{
	    Neutral.erase(Neutral.begin()+z);
	  }
	}
      }































      for(int i = Players.size()-1; i >=0; --i){
	if(Players[i].sock.hasEvent()){
	  cout << "1" << endl;
	  Players[i].sock.readString(msg,256);
	  if(!Players[i].sock.isClosed()){
	    cout << msg << "\n";
	    if (state != 2 && state != 5){
	      if (msg.substr(0,4) == "QUIT")
	      {
		if (state == 1)
		{
		  Players[i].sock.close();
	    	  Players.erase(Players.begin()+i);
		  break;
		}
		  	  
		cout << "Quitting" << endl;
		state = 1;
		for (int j = 0; j < Players.size(); j++)
		  Players[j].sock.writeString("+QUIT Player " + to_string(i + 1) + " quiting.\r\n");
		
		for (int j = 0; j < Observers.size(); j++)
		  Observers[j].writeString("+QUIT Player " + to_string(i + 1) + " quiting\r\n");

		Players[i].sock.close();
	    	Players.erase(Players.begin()+i);
		break;
	      }
	    }

	    if (state != 3 && state != 4){
	      msg = "-Not allowed to send commands in current state\r\n";
	      Players[i].sock.writeString(msg);
	    }

	    else
	    {
	      if (state == 3)
		msg = State_3_Handler(msg); 
	      else if (state == 4)
		msg = State_4_Handler(msg);
	    Players[i].sock.writeString(msg);
	    }

	  }

	  else{
	    Players.erase(Players.begin()+i);
	  }

	}
      }
      for(int i = Observers.size()-1; i >=0; --i){

	if(Observers[i].hasEvent()){
	  cout << "2" << endl;
	  Observers[i].readString(msg,256);
	  if(!Observers[i].isClosed()){
	    cout << msg << "\n";

	    if (state != 2 && state != 5)
	    {
	      if (msg.substr(0,4) == "QUIT")
	      {
		  Observers[i].close();
	    	  Observers.erase(Observers.begin()+i);
	      }
	    }

	    if (state != 3 && state != 4)
	      msg = "-Not allowed to send commands in current state\r\n";

	    
	    else
	    {
	      if (state == 3)
		state = 3;
	      else if (state == 4)
		state = 4;;
	    }
	    Observers[i].writeString(msg);
	  }

	  else{
	    Observers.erase(Observers.begin()+i);
	  }

	}
      }

    }
  }
    for(unsigned int i =0; i < Players.size(); i++){
      Players[i].sock.close();
    }
    for(unsigned int i = 0; i < Observers.size(); i++){
      Observers[i].close();
    }
    return 0;
  }
