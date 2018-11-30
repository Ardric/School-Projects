#include "Socket.h"
#include "Timer.h"
#include <vector>
#include <string>
#include <stdlib.h>
using namespace std;

int state = 1;
void broadcast(string message);
void reset();

struct In_Play
{
  int value;
  string suit;
  int team;
};

struct Team
{
  int team;
  int bid;
  int tricks_won = 0;
  int score = 0;
};

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
  bool bid = false;
  bool played_card = false;
  int team;
};

Socket listener;

vector<In_Play> Tricks;
vector<Team> Teams;
vector<Player> Players;
vector<Socket> Observers;

int Score = 100;
int dealer;
int turn;
bool broken = false;

void State_2_Handler()
{
  for (int i = 0; i < Players.size(); i++)
    Players[i].Hand.erase(Players[i].Hand.begin(), Players[i].Hand.end());

  dealer  = (rand() % 4) + 1;
  turn = (dealer % 4) + 1;
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
  for (int i = 0; i < Players.size(); i++)
  {
    if (to_string(turn) == Players[i].position)
    {
      Players[i].sock.writeString("+PLYR Your turn to bid.\r\n");
      break;
    }
  }
}


string State_3_Handler(string message, Player &p)
{

  string line;
  int bid;

  if (message.substr(0,4) == "IBID")
  {
    if (message.length() != 9){
      line = "-Invalid command\r\n";
    }

    else
    {
      if (p.position != to_string(turn))
	return line = "-Not your turn to bid.\r\n";

      bid = atoi(message.substr(5,2).c_str());

      for(int i = 0; i < Teams.size(); i++)
      {
	if( p.team == Teams[i].team )
	{
	  Teams[i].bid += bid;
	  p.bid = true;
	  line = "+ACTV T" + to_string(p.team) + " BID " + to_string(Teams[i].bid) + ".\r\n";
	}
      }
    }
  }
  else if (message.substr(0,4) == "CHAT")
  {
    if (message.substr(5).length() > 256){
      line = "+" + message.substr(0, 254) + "\r\n";
    }
    else 
      line = "+" + message;
  } 
  else 
  {
    line = "-Invalid command\r\n"; 
  }

  return line; 
}

string State_4_Handler(string message, Player &p){ 


  string line;
  string card;
  In_Play cur_play;
  int val;
  int spades = 0;
  int clubs = 0;
  int hearts = 0;
  int diamonds = 0;
  int index;
  bool found = false;

  if (message.substr(0,4) == "CARD")
  {
    if (message.length() != 9){
      line = "-Invalid command\r\n";
    }

    else
    {
      if (p.position != to_string(turn))
	return line = "-Not your turn to play a card.\r\n";

      card = message.substr(5,2);

      for (int i = 0; i < 13; i++)
      {
	if (p.Hand[i].used == false)
	{
	  if (p.Hand[i].value.substr(1,1) == "H")
	    ++hearts;
	  if (p.Hand[i].value.substr(1,1) == "S")
	    ++spades;
	  if (p.Hand[i].value.substr(1,1) == "D")
	    ++diamonds;
	  if (p.Hand[i].value.substr(1,1) == "C")
	    ++clubs;
	}

	if (card == p.Hand[i].value)
	{
	  index = i;
	  found = true;
	  if (p.Hand[i].used == true)
	    return line = "-Card has already been played.\r\n";
	}
	if (i == 12 && found == true)
	  break;
	if (i == 12)
	  return line = "-Card is not in your hand.\r\n";
      }

      cout << "Current hard being judged: " << card << endl;
      if (Tricks.size() == 0)
      {
	if (card.substr(1,1) == "S")
	{
	  if (broken == true)
	  {
	    if (card.substr(0,1) == "T")
	      val = 10;
	    else if (card.substr(0,1) == "J")
	      val = 11;
	    else if (card.substr(0,1) == "Q")
	      val = 12;
	    else if (card.substr(0,1) == "K")
	      val = 13;
	    else if (card.substr(0,1) == "A")
	      val = 14;
	    else
	      val = atoi(card.substr(0,1).c_str());

	    cur_play.value = val;
	    cur_play.suit = "S";
	    cur_play.team = p.team;
	    Tricks.push_back(cur_play);
	    p.Hand[index].used = true;
	    return line = "+ACTV P" + p.position +  " PLAY " + card + ".\r\n";
	  }
	  else
	    return line = "-Spades hasn't been broken yet.\r\n"; 
	}
	else{
	  if (card.substr(0,1) == "T")
	    val = 10;
	  else if (card.substr(0,1) == "J")
	    val = 11;
	  else if (card.substr(0,1) == "Q")
	    val = 12;
	  else if (card.substr(0,1) == "K")
	    val = 13;
	  else if (card.substr(0,1) == "A")
	    val = 14;
	  else
	    val = atoi(card.substr(0,1).c_str());

	  cur_play.value = val;
	  cur_play.suit = card.substr(1,1);
	  cur_play.team = p.team;
	  Tricks.push_back(cur_play);
	  p.Hand[index].used = true;
	  return line = "+ACTV P" + p.position +  " PLAY " + card + ".\r\n";
	}
      }

      else
      {
	if (card.substr(1,1) != Tricks[0].suit)
	{
	  if (Tricks[0].suit == "S")
	  {
	    if (spades == 0)
	    {
	      if (card.substr(0,1) == "T")
		val = 10;
	      else if (card.substr(0,1) == "J")
		val = 11;
	      else if (card.substr(0,1) == "Q")
		val = 12;
	      else if (card.substr(0,1) == "K")
		val = 13;
	      else if (card.substr(0,1) == "A")
		val = 14;
	      else
		val = atoi(card.substr(0,1).c_str());

	      cur_play.value = val;
	      cur_play.suit = card.substr(1,1);
	      cur_play.team = p.team;
	      Tricks.push_back(cur_play);
	      p.Hand[index].used = true;
	      return line = "+ACTV P" + p.position +  " PLAY " + card + ".\r\n";
	    }
	    else
	      return line = "-You still have cards of type: " + Tricks[0].suit + ".\r\n";
	  }

	  if (Tricks[0].suit == "C")
	  {
	    if (clubs == 0)
	    {
	      if (card.substr(0,1) == "T")
		val = 10;
	      else if (card.substr(0,1) == "J")
		val = 11;
	      else if (card.substr(0,1) == "Q")
		val = 12;
	      else if (card.substr(0,1) == "K")
		val = 13;
	      else if (card.substr(0,1) == "A")
		val = 14;
	      else
		val = atoi(card.substr(0,1).c_str());

	      cur_play.value = val;
	      cur_play.suit = card.substr(1,1);
	      if (card.substr(1,1) == "S")
		broken = true;
	      cur_play.team = p.team;
	      Tricks.push_back(cur_play);
	      p.Hand[index].used = true;
	      return line = "+ACTV P" + p.position +  " PLAY " + card + ".\r\n";
	    }
	    else
	      return line = "-You still have cards of type: " + Tricks[0].suit + ".\r\n";
	  }

	  if (Tricks[0].suit == "H")
	  {
	    if (hearts == 0)
	    {
	      if (card.substr(0,1) == "T")
		val = 10;
	      else if (card.substr(0,1) == "J")
		val = 11;
	      else if (card.substr(0,1) == "Q")
		val = 12;
	      else if (card.substr(0,1) == "K")
		val = 13;
	      else if (card.substr(0,1) == "A")
		val = 14;
	      else
		val = atoi(card.substr(0,1).c_str());

	      cur_play.value = val;
	      cur_play.suit = card.substr(1,1);
	      if (card.substr(1,1) == "S")
		broken = true;
	      cur_play.team = p.team;
	      Tricks.push_back(cur_play);
	      p.Hand[index].used = true;
	      return line = "+ACTV P" + p.position +  " PLAY " + card + ".\r\n";
	    }
	    else
	      return line = "-You still have cards of type: " + Tricks[0].suit + ".\r\n";
	  }

	  if (Tricks[0].suit == "D")
	  {
	    if (diamonds == 0)
	    {
	      if (card.substr(0,1) == "T")
		val = 10;
	      else if (card.substr(0,1) == "J")
		val = 11;
	      else if (card.substr(0,1) == "Q")
		val = 12;
	      else if (card.substr(0,1) == "K")
		val = 13;
	      else if (card.substr(0,1) == "A")
		val = 14;
	      else
		val = atoi(card.substr(0,1).c_str());

	      cur_play.value = val;
	      cur_play.suit = card.substr(1,1);
	      if (card.substr(1,1) == "S")
		broken = true;
	      cur_play.team = p.team;
	      Tricks.push_back(cur_play);
	      p.Hand[index].used = true;
	      return line = "+ACTV P" + p.position +  " PLAY " + card + ".\r\n";
	    }
	    else
	      return line = "-You still have cards of type: " + Tricks[0].suit + ".\r\n";
	  }
	}
	else
	{
	  if (card.substr(0,1) == "T")
	    val = 10;
	  else if (card.substr(0,1) == "J")
	    val = 11;
	  else if (card.substr(0,1) == "Q")
	    val = 12;
	  else if (card.substr(0,1) == "K")
	    val = 13;
	  else if (card.substr(0,1) == "A")
	    val = 14;
	  else
	    val = atoi(card.substr(0,1).c_str());

	  cur_play.value = val;
	  cur_play.suit = card.substr(1,1);
	  cur_play.team = p.team;
	  Tricks.push_back(cur_play);
	  p.Hand[index].used = true;
	  return line = "+ACTV P" + p.position +  " PLAY " + card + ".\r\n";
	} 
      }

    }
  }
  else if (message.substr(0,4) == "CHAT")
  {
    if (message.substr(5).length() > 256){
      line = "+" + message.substr(0, 254) + "\r\n";
    }
    else 
      line = "+" + message;
  } 
  else 
  {
    line = "-Invalid command\r\n"; 
  }

  return line;

}

void State_5_Handler()
{
  //Gets called if 13 plays have occured
  //Have a team score ?
  //Add up team score based on bid and tricks_won
  //if score < global score
  //ACTV
  //state = 2
  //else
  //ACTV
  //state = 1
  int Team_1_score = 0;
  int Team_2_score = 0;

  for (int i = 0; i < Teams.size(); i++)
  {
    if (Teams[i].bid == Teams[i].tricks_won)
      Teams[i].score += (Teams[i].bid * 10);
    else if (Teams[i].bid > Teams[i].tricks_won)
      Teams[i].score -= (Teams[i].bid * 10);
    else 
      Teams[i].score = ((Teams[i].bid * 10) + (Teams[i].tricks_won - Teams[i].bid));

    if (Teams[i].team == 1)
      Team_1_score = Teams[i].score;
    else
      Team_2_score = Teams[i].score;
  }

  if (Team_1_score > Score)
  {
    broadcast("+ACTV GAME OVER T1 SCORE " + to_string(Team_1_score) + ".\r\n");
    reset();
    state = 2;
  }
  else if (Team_2_score > Score)
  {
    broadcast("+ACTV GAME OVER T2 SCORE " + to_string(Team_2_score) + ".\r\n");
    reset();
    state = 2;
  }
  else
  {
    broadcast("+ACTV ROUND OVER\r\n");
    broadcast("+ACTV T1 SCORE " + to_string(Team_1_score) + ".\r\n");
    broadcast("+ACTV T2 SCORE " + to_string(Team_2_score) + ".\r\n");
    state = 2;
  }
  for (int j = 0; j < Players.size(); j++)
  {
    Players[j].played_card = false;
    Players[j].bid = false;
  }
}
void broadcast(string message){
  for (int j = 0; j < Players.size(); j++)
    Players[j].sock.writeString(message);

  for (int j = 0; j < Observers.size(); j++)
    Observers[j].writeString(message);
}

void check_trick()
{
  string first = Tricks[0].suit;
  int best_so_far = Tricks[0].value;
  int index = 0;


  for (int i = 1; i < Tricks.size(); i++)
  {
    if (first == "S" && Tricks[i].suit == "S")
    {
      if(best_so_far <  Tricks[i].value)
      {
	best_so_far = Tricks[i].value;
	index = i;
      }
    }

    else if (first != "S" && Tricks[i].suit == "S")
    {
      first = "S";
      best_so_far = Tricks[i].value;
      index = i;
    }

    else if (first == Tricks[i].suit)
    {
      if (best_so_far < Tricks[i].value)
      {
	best_so_far = Tricks[i].value;
	index = i;
      }
    }
  }

  for (int i = 0; i < Teams.size(); i++)
  {
    if (Tricks[index].team == Teams[i].team)
    {
      Teams[i].tricks_won++;
    }
  }
  Tricks.clear();

  for (int i = 0; i < Players.size(); i++)
  {
    Players[i].played_card = false;
  }

}
int bid_count = 0;

void reset()
{
  for (int i = 0; i < Teams.size(); i++)
  {
    Teams[i].bid = 0;
    Teams[i].tricks_won = 0;
  }

  bid_count = 0;
  for (int j = 0; j < Players.size(); j++)
  {
    Players[j].played_card = false;
    Players[j].bid = false;
  }

  Tricks.clear();

}

int main(int argc,char** argv){
  SocketSet socketSet;
  listener.listen(argv[1]);
  listener.joinGroup(&socketSet);
  string msg = "";
  Player player;
  Team T;
  T.team = 1;
  T.bid = 0;
  Teams.push_back(T);
  T.team = 2;
  T.bid = 0;
  Teams.push_back(T);

  while(!listener.isClosed()){
    socketSet.wait(2);

    if (state == 2)
    {
      State_2_Handler();
    }

    if (state == 5)
      State_5_Handler();

    if (state == 3){
      for (int i = 0; i < Players.size(); i++)
      {
	if (to_string(turn) == Players[i].position)
	{
	  if (Players[i].bid == false)
	    break;

	  else
	  {
	    ++bid_count;
	    turn = (turn % 4) + 1;

	    if (bid_count == 4)
	    {
	      bid_count = 0;
	      state = 4;
	      for (int i = 0; i < Players.size(); i++)
	      {
		if (to_string(turn) == Players[i].position)
		{
		  Players[i].sock.writeString("+PLYR Your turn to play a card.\r\n");
		  break;
		}
	      }
	    }

	    else
	    {
	      for (int j = 0; j < Players.size(); j++)
	      {
		if (to_string(turn) == Players[j].position)
		{
		  Players[j].sock.writeString("+PLYR Your turn to bid.\r\n");
		  break;
		}
	      }
	    }
	  }
	}	  
      }
    }

    if (state == 4){
      for (int i = 0; i < Players.size(); i++)
      {
	if (to_string(turn) == Players[i].position)
	{
	  if (Players[i].played_card == false)
	    break;

	  else
	  {
	    ++bid_count;
	    turn = (turn % 4) + 1;
	    cout << "Currently players turn: "  << turn << endl;
	    cout << "Tricks size: " << Tricks.size() << endl;

	    if (bid_count % 4 == 0)
	    {
	      check_trick();
	    }

	    if (bid_count == 52)
	    {
	      state = 5;
	    }

	    else
	    {
	      for (int j = 0; j < Players.size(); j++)
	      {
		if (to_string(turn) == Players[j].position)
		{
		  Players[j].sock.writeString("+PLYR Your turn to play a card.\r\n");
		  break;
		}
	      }
	    }
	  }
	}
      }
    }

    if(listener.hasEvent()){
      if (state != 1)
	continue;

      Socket sock = listener.accept();
      sock.joinGroup(&socketSet);
      sock.writeString("+PLYR Welcome to the Spades server, do you want to be a player or observer?\r\n");
      sock.readString(msg, 256);
      if (msg.length() == 8){
	if (msg.substr(0,4) == "PLYR"){
	  string pos = msg.substr(5,1);
	  if (pos == "1" or pos == "2" or pos == "3" or pos == "4"){
	    for (int i = 0; i < Players.size(); i++)
	    {
	      if (pos == Players[i].position){
		sock.writeString("-Player slot" + pos + " is already taken. Closing connection.\r\n");
		sock.close();
	      }
	    }

	    if (!sock.isClosed()){
	      cout << "Check" << endl;
	      player.sock = sock;
	      player.position = pos;
	      if (pos == "1" or pos == "3")
		player.team = 1;
	      else
		player.team = 2;
	      sock.writeString("+PLYR You have successfully been added as player " + pos + " on team " + to_string(player.team) + ".\r\n");
	      Players.push_back(player);
	    }
	  }

	  else{
	    sock.writeString("-Inappropriate request, closing connection\r\n");
	    sock.close();
	  }

	}


	else{
	  sock.writeString("-Inappropriate request, closing connection\r\n");
	  sock.close();
	}

      }

      else if (msg.length() == 6){
	if (msg.substr(0,4) == "OBSV")
	  Observers.push_back(sock);
	else if(msg.substr(0,4) == "PLYR") {
	  if (Players.size() == 4){
	    sock.writeString("-Inappropriate request, closing connection\r\n");
	    sock.close();
	  }
	  else if (Players.size() == 0){
	    sock.writeString("+PLYR You have successfully been added as player 1 on team 1.\r\n");
	    player.sock = sock;
	    player.position = "1";
	    player.team = 1;
	    Players.push_back(player);
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
		  player.sock = sock;
		  player.position = to_string(count);
		  if (count == 1 or count == 3)
		    player.team = 1;
		  else
		    player.team = 2;
		  sock.writeString("+PLYR You have successfully been added as player " + to_string(count) + " on team " + to_string(player.team) + ".\r\n");
		  Players.push_back(player);
		  break;
		}
	      }
	      count++;
	      if (count == 5 && x == true){
		x = false;
		sock.writeString("-Inappropriate request, closing connection\r\n");
		sock.close();
	      }
	    }
	  }
	}

	else
	{
	  sock.writeString("-Inappropriate request, closing connection\r\n");
	  sock.close();
	}
      }

      else{
	sock.writeString("-Inappropriate request, closing connection\r\n");
	sock.close();
      }

      if (Players.size() == 4)
	state = 2;
    }

    else{
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

		reset();

		/*
		   for (int i = 0; i < Teams.size(); i++)
		   {
		   Teams[i].bid = 0;
		   Teams[i].tricks_won = 0;
		   }
		   */
		//		  bid_count = 0;
		cout << "Quitting" << endl;
		state = 1;
		for (int j = 0; j < Players.size(); j++)
		{
		  //		    Players[j].played_card = false;
		  //		    Players[j].bid = false;
		  Players[j].sock.writeString("+QUIT Player " + to_string(i + 1) + " quiting.\r\n");
		}

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
	      {
		msg = State_3_Handler(msg, Players[i]); 
		if (msg.substr(1,4) == "CHAT" or msg.substr(1,4) == "ACTV"){
		  broadcast(msg);
		}
	      }
	      else if (state == 4){
		msg = State_4_Handler(msg, Players[i]);
		if (msg.substr(0,1) == "+" && msg.substr(1,4) != "CHAT")
		  Players[i].played_card = true;
		if (msg.substr(1,4) == "CHAT" or msg.substr(1,4) == "ACTV"){
		  broadcast(msg);}
	      }

	      if (msg.substr(1,4) != "CHAT" and  msg.substr(1,4) != "ACTV")
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
