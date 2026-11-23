#include <cassert>
#include <iostream>
#include <array>
#include "Pack.hpp"

using namespace std;
Pack::Pack() {
    int index = 0;
    for (int s = SPADES; s <= DIAMONDS; ++s) {
        for (int r = NINE; r <= ACE; ++r) {
            cards[index] = Card(Rank(r), Suit(s));
            ++index;
        }
    }
    next = 0;
}
Pack::Pack(std::istream& pack_input){
    for (int i = 0; i < PACK_SIZE; ++i) {
        pack_input >> cards[i];
    }
    next = 0;
}

Card Pack::deal_one() {
    Card deal = cards[next];
    ++next;
    return deal;
}

void Pack::reset(){
    next = 0;
}

void Pack::shuffle(){
    array<Card, PACK_SIZE/2> secondhcards;
    array<Card, PACK_SIZE/2> firsthalfcards;
    for (int i = 0; i < 7; ++i) {
        for (int index = 0; index < PACK_SIZE/2; ++index){
            secondhcards[index] = cards[PACK_SIZE/2 +index];
            firsthalfcards[index] = cards[index];
        }
    
        for (int x = 0; x < PACK_SIZE/2; ++x){
            cards[2*x] = secondhcards[x];
            cards[2*x + 1] = firsthalfcards[x];
        }
    }
    reset();
}

bool Pack::empty() const{
    return (next == 24);
}