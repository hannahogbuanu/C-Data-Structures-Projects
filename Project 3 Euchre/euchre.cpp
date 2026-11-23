#include <cassert>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
using namespace std;

#include "Player.hpp"
#include "Card.hpp"
#include "Pack.hpp"
#include <cstdlib>
const int NUMPLAYERS = 4;

class Game {
    public: 
        Game(const vector<Player*> &players_in, const Pack 
            &pack_in, bool shuffle_in, int points2win_in) 
            : players(players_in), pack(pack_in), shuffleOn(shuffle_in), 
            points2win(points2win_in), score_02(0) , score_13(0)
            {}
        void play();
    private:
        vector<Player*> players;
        Pack pack;
        bool shuffleOn;
        int points2win;
        int score_02;
        int score_13;


        const string & name(int i) const {
            return players[i]->get_name();
        }
        void play_hand(int hand);
        void shuffle();
        void deal(int dealer);
        int make_trump(int dealer, const Card &upcard, Suit &trump);
        int make_trumpround(int dealer, const Card &upcard, int round, Suit &trump); 
        void play_tricks(int dealer, Suit trump, int &tricks_02, int &tricks_13);
        void score_hand(int maker, int &tricks_02, int &tricks_13);

};

void Game::play() {
    int hand = 0;
    while (score_02 < points2win && score_13 < points2win) {
        play_hand(hand);
        ++hand;
    }
    int winner;
    if (score_02 >= points2win) {
        winner = 0;
    }
    else {
        winner = 1;
    }
    cout << name(winner) << " and " << name(winner + 2) << " win!" << endl;
    for (int i = 0; i < players.size(); ++i) {
        delete players[i];
    }
}

void Game::shuffle(){
    if (shuffleOn){
        pack.shuffle();
    }
    else{
        pack.reset();
    }
}

void Game::play_hand(int hand) {
    int dealer = hand % 4;
    cout << "Hand " << hand << endl;
    cout << name(dealer) << " deals" << endl;

    shuffle();
    deal(dealer);
    Card upcard = pack.deal_one();
    cout << upcard << " turned up" << endl;
    Suit trump = SPADES;
    int maker = make_trump(dealer, upcard, trump);

    int tricks_02 = 0;
    int tricks_13 = 0;
    play_tricks(dealer, trump, tricks_02, tricks_13);

    score_hand(maker, tricks_02, tricks_13);
}

void Game::deal(int dealer) {
    int batch_sizes[8] = {3, 2, 3, 2, 2, 3, 2, 3};
    for (int batch = 0; batch < 8; ++batch) {
        int player = (dealer + 1 + batch) % 4;
        for (int c = 0; c < batch_sizes[batch]; ++c) {
            players[player]->add_card(pack.deal_one());
        }
    }
}
int Game::make_trumpround(int dealer, const Card &upcard, int round, 
    Suit &trump) {
    for (int i = 1; i <= 4; ++i) {
        int player = (dealer + i) % 4;
 
        bool is_dealer = false;
        if (player == dealer) {
          is_dealer = true;
        }
 
        bool ordered_up = 
        players[player]->make_trump(upcard, is_dealer, round, trump);
 
        if (ordered_up) {
          cout << players[player]->get_name() << " orders up "
               << trump << endl;
 
          if (round == 1) {
            players[dealer]->add_and_discard(upcard);
          }
          cout << endl;
          return player;
        }
        else {
          cout << players[player]->get_name() << " passes" << endl;
        }
    }
    return -1;
}

int Game::make_trump(int dealer, const Card &upcard, Suit &trump) {
  for (int round = 1; round <= 2; ++round) {
    int maker = make_trumpround(dealer, upcard, round, trump);
    if (maker != -1) {
      return maker;
    }
  }
  assert(false);
  return -1;
}

void Game::play_tricks(int dealer, Suit trump, int &tricks_02, int &tricks_13){
    int leader = (dealer + 1) % 4;
    for (int trick = 0; trick < 5; ++trick){
        Card led_card = players[leader]->lead_card(trump);
        cout << led_card << " led by " << players[leader]->get_name() << endl;
       
        Card bestcard = led_card;
        int winner = leader;
        
        for (int i = 1; i < 4; ++i) {
            int player = (leader + i) % 4;
            Card played = players[player]->play_card(led_card, trump);
            cout << played << " played by "
                << players[player]->get_name() << endl;
    
            if (Card_less(bestcard, played, led_card, trump)) {
            bestcard = played;
            winner = player;
            }
        }
    
        cout << players[winner]->get_name() << " takes the trick" << endl;
        cout << endl;
       
        if (winner == 0 || winner == 2) {
            ++tricks_02;
        }
        else {
            ++tricks_13;
        }
    
        leader = winner;
        }

}

void Game::score_hand(int maker, int &tricks_02, int &tricks_13){

    bool team_02_won_hand = false;
    if (tricks_02 > tricks_13) {
      team_02_won_hand = true;
    }
 
    bool team_02_made_trump = false;
    if (maker == 0 || maker == 2) {
      team_02_made_trump = true;
    }
 
    if (team_02_won_hand) {
      cout << players[0]->get_name() << " and "
           << players[2]->get_name() << " win the hand" << endl;
    }
    else {
      cout << players[1]->get_name() << " and "
           << players[3]->get_name() << " win the hand" << endl;
    }

    int winning_tricks = tricks_13;
    if (team_02_won_hand) {
      winning_tricks = tricks_02;
    }
 
    bool winners_made_trump = false;
    if (team_02_won_hand == team_02_made_trump) {
      winners_made_trump = true;
    }

    int points = 0;
    if (winners_made_trump) {
      if (winning_tricks == 5) {
        cout << "march!" << endl;
        points = 2;
      }
      else {
        points = 1;
      }
    }
    else {
      cout << "euchred!" << endl;
      points = 2;
    }
 
    if (team_02_won_hand) {
      score_02 = score_02 + points;
    }
    else {
      score_13 = score_13 + points;
    }
 
    cout << players[0]->get_name() << " and " << players[2]->get_name()
         << " have " << score_02 << " points" << endl;
    cout << players[1]->get_name() << " and " << players[3]->get_name()
         << " have " << score_13 << " points" << endl;
    cout << endl;
  
}

static void print_usage() {
  cout << "Usage: euchre.exe PACK_FILENAME [shuffle|noshuffle] "
       << "POINTS_TO_WIN NAME1 TYPE1 NAME2 TYPE2 NAME3 TYPE3 "
       << "NAME4 TYPE4" << endl;
}
 
int main(int argc, char **argv) {
 
  if (argc != 12) {
    print_usage();
    return 1;
  }
 
  int points_to_win = atoi(argv[3]);
  if (points_to_win < 1 || points_to_win > 100) {
    print_usage();
    return 1;
  }
 
  
  string shuffle_arg = argv[2];
  if (shuffle_arg != "shuffle" && shuffle_arg != "noshuffle") {
    print_usage();
    return 1;
  }
 
  for (int i = 5; i <= 11; i = i + 2) {
    string type = argv[i];
    if (type != "Simple" && type != "Human") {
      print_usage();
      return 1;
    }
  }
 
  string pack_filename = argv[1];
  ifstream pack_file(pack_filename);
  if (!pack_file.is_open()) {
    cout << "Error opening " << pack_filename << endl;
    return 1;
  }
 
  
  for (int i = 0; i < argc; ++i) {
    cout << argv[i] << " ";
  }
  cout << endl;
 
  Pack pack(pack_file);
 
 
  vector<Player*> players;
  for (int i = 4; i <= 10; i = i + 2) {
    string name = argv[i];
    string type = argv[i + 1];
    players.push_back(Player_factory(name, type));
  }
 
  bool shuffle_on = false;
  if (shuffle_arg == "shuffle") {
    shuffle_on = true;
  }
 
  Game game(players, pack, shuffle_on, points_to_win);
  game.play();
 
  return 0;
}

