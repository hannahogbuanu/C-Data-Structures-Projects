#include <cassert>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

#include "Player.hpp"

class SimplePlayer : public Player {
    public:
        SimplePlayer(const string &inputname) 
            :name(inputname) {}
        
        const string & get_name() const override {
            return name;
        }
    
        void add_card(const Card &c) override;

        bool make_trump(const Card &upcard, 
            bool is_dealer, int round, 
            Suit &order_up_suit) const override;

        void add_and_discard(const Card &upcard) override;

        Card lead_card(Suit trump) override;

        Card play_card(const Card &led_card, Suit trump) override;

    private:
        string name;
        vector<Card> hand;
};

class HumanPlayer : public Player {
    public:
        HumanPlayer(const string &inputname) 
            :name(inputname) {}
        
        const string & get_name() const override {
            return name;
        }
    
        void add_card(const Card &c) override;

        bool make_trump(const Card &upcard, 
            bool is_dealer, int round, Suit 
            &order_up_suit) const override;

        void add_and_discard(const Card &upcard) override;

        Card lead_card(Suit trump) override;

        Card play_card(const Card &led_card, Suit trump) override;

    private:
        string name;
        vector<Card> hand;

        void print_hand() const {
            for (size_t i=0; i < hand.size(); ++i){

                cout << "Human player " << name << "'s hand: "
                    << "[" << i << "] " << hand[i] << "\n";
            }
        }
};

void SimplePlayer::add_card(const Card &c){
    hand.push_back(c);
}
bool SimplePlayer::make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const {
    Suit considered;
    if (round == 1){
        considered = upcard.get_suit();
    }             
    if (round == 2) {
        considered = Suit_next(upcard.get_suit());
    }   
    int count = 0;
    for (int i = 0; i < hand.size(); ++i){
        if (hand[i].is_face_or_ace() && hand[i].is_trump(considered)) {
            ++count;
        }
    } 
    int neededtoO;
    if (round == 1) {
        neededtoO = 2;
    }
    if (round == 2){
        neededtoO = 1;
    }

    if (count >= neededtoO || (round == 2 && is_dealer)){
        order_up_suit = considered;
        return true;
    }
    return false;
}



void SimplePlayer::add_and_discard(const Card &upcard) {
    hand.push_back(upcard);
    Suit trump = upcard.get_suit();
    int lowest = 0;
    for (int i = 1; i < hand.size(); ++i) {
        if (Card_less(hand[i], hand[lowest], trump)==true){
            lowest = i;
        }
    }
    hand.erase(hand.begin()+lowest);
}

Card SimplePlayer::lead_card(Suit trump) {
    int highest = -1;
    for (int i = 0; i< hand.size(); ++i){
        if(!hand[i].is_trump(trump)){
            if (highest == -1 || Card_less(hand[highest], hand[i], trump)) {
                highest = i;
            }
        }
    }
    if (highest == -1){
        highest = 0;
        for (int i = 1; i < hand.size(); ++i){
            if(Card_less(hand[highest], hand[i], trump)){
                highest = i;
            }
        }
    }
    Card chosen = hand[highest];
    hand.erase(hand.begin()+highest);
    return chosen;
}

Card SimplePlayer::play_card(const Card &led_card, Suit trump) {
    Suit led_suit = led_card.get_suit(trump);
    int highest = -1;
    for (int i = 0; i < hand.size(); ++i) {
        if(hand[i].get_suit(trump)==led_suit){
            if (highest == -1 || Card_less(hand[highest], hand[i], led_card, trump)){
                highest = i;
            }
        }
    }
    if (highest == -1){
        highest = 0;
        for (int i = 1; i < hand.size(); ++i){
            if(Card_less(hand[i], hand[highest], led_card, trump)){
                highest = i;
            }
        }
    }
    Card chosen = hand[highest];
    hand.erase(hand.begin()+highest);
    return chosen;

}
///////////////////
void HumanPlayer::add_card(const Card &c){
    hand.push_back(c);
    sort(hand.begin(), hand.end());
    
}
bool HumanPlayer::make_trump(const Card &upcard, bool is_dealer,
                          int round, Suit &order_up_suit) const {
    print_hand();
    cout << "Human player " << name << ", please enter a suit, or \"pass\":\n";
    string decision;
    cin >> decision;
    if (decision != "pass") {
        order_up_suit = string_to_suit(decision);
        return true;
    }
    else {
        return false;
    }
}



void HumanPlayer::add_and_discard(const Card &upcard) {
    print_hand();
    cout << "Discard upcard: [-1]\n";
    cout << "Human player " << name << ", please select a card to discard:\n";
    int choice;
    cin >> choice;
    if (choice == -1) {
        return;
    }
    hand.erase(hand.begin() + choice);
    hand.push_back(upcard);
    sort(hand.begin(), hand.end());
}

Card HumanPlayer::lead_card(Suit trump) {
    print_hand();
    cout << "Human player " << name << ", please select a card:\n";
    int choice;
    cin >> choice;
    Card chosen = hand[choice];
    hand.erase(hand.begin()+choice);
    return chosen;
}

Card HumanPlayer::play_card(const Card &led_card, Suit trump) {
    return lead_card(trump);

}

Player * Player_factory(const std::string &name, const std::string &strategy) {
    if(strategy == "Simple"){
        return new SimplePlayer(name);
    }
    if(strategy == "Human"){
        return new HumanPlayer(name);
    }
    assert(false);
    return nullptr;
}

std::ostream & operator<<(std::ostream &os, const Player &p) {
  os << p.get_name();
  return os;
}
