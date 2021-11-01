// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "Card.h"

using namespace std;
// add any necessary #include or using directives here

// rank and suit names -- do not remove these
constexpr const char* const Card::RANK_TWO;
constexpr const char* const Card::RANK_THREE;
constexpr const char* const Card::RANK_FOUR;
constexpr const char* const Card::RANK_FIVE;
constexpr const char* const Card::RANK_SIX;
constexpr const char* const Card::RANK_SEVEN;
constexpr const char* const Card::RANK_EIGHT;
constexpr const char* const Card::RANK_NINE;
constexpr const char* const Card::RANK_TEN;
constexpr const char* const Card::RANK_JACK;
constexpr const char* const Card::RANK_QUEEN;
constexpr const char* const Card::RANK_KING;
constexpr const char* const Card::RANK_ACE;

constexpr const char* const Card::SUIT_SPADES;
constexpr const char* const Card::SUIT_HEARTS;
constexpr const char* const Card::SUIT_CLUBS;
constexpr const char* const Card::SUIT_DIAMONDS;

// add your code below
Card::Card(){
  rank=RANK_TWO;
  suit=SUIT_SPADES;
}

Card::Card(const string &rank_in, const string &suit_in){
  rank = rank_in;
  suit = suit_in;
}

string Card::get_rank() const {
  return rank;
}

string Card::get_suit() const {
  return suit;
}

string Card::get_suit(const string &trump) const {
  assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS
  || trump == SUIT_HEARTS || trump == SUIT_SPADES);
return Suit_next(trump);
}

bool Card::is_face() const{
  if(rank == RANK_JACK || rank == RANK_ACE
  || rank == RANK_KING || rank == RANK_QUEEN) {return true;}
  return false;
}

bool Card::is_right_bower(const string &trump) const{
  assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS
  || trump == SUIT_HEARTS || trump == SUIT_SPADES);
  if(suit == trump && rank == RANK_JACK){
    return true;
  }
  return false;
}

bool Card::is_left_bower(const string &trump) const{
  assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS
  || trump == SUIT_HEARTS || trump == SUIT_SPADES);

  if(rank == RANK_JACK && suit == Suit_next(trump)) 
  {return true;}
  return false;
}

bool Card::is_trump(const string &trump) const{
  assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS
  || trump == SUIT_HEARTS || trump == SUIT_SPADES);
  return is_left_bower(trump) || suit == trump;
}

bool operator<(const Card &lhs, const Card &rhs){
  int lr = 0; // lhs value of rank
  int rr = 0; // rhs value of rank
  while(lhs.get_rank() != RANK_NAMES_BY_WEIGHT[lr]) {
    ++lr;
  }  
  while(rhs.get_rank() != RANK_NAMES_BY_WEIGHT[rr]) {
    ++rr;
  }  
  if (operator==(lhs,rhs)) {return false;}
  if(lr < rr) {
    return true;
  }
  else if(lr == rr){
    int ls=0; // lhs value of suit
    int rs=0; // rhs value of suit
    while(lhs.get_suit() != SUIT_NAMES_BY_WEIGHT[ls]) {
    ++ls;
    }  
    while(rhs.get_suit() != SUIT_NAMES_BY_WEIGHT[rs]) {
    ++rs;
    }  
    return ls < rs;
  }
  else if(lr > rr) {
    return false;
  }
  return -1;
}

bool operator<=(const Card &lhs, const Card &rhs){
  return operator<(lhs,rhs) || operator==(lhs,rhs);
}

bool operator>(const Card &lhs, const Card &rhs){
  if (operator==(lhs,rhs)) {return false;}
  return !operator<(lhs,rhs);
}

bool operator>=(const Card &lhs, const Card &rhs){
  return operator>(lhs,rhs) || operator==(lhs,rhs);
}

bool operator==(const Card &lhs, const Card &rhs){
  return lhs.get_rank() == rhs.get_rank() 
  && lhs.get_suit() == rhs.get_suit();
}

bool operator!=(const Card &lhs, const Card &rhs){
  return !operator==(lhs,rhs);
}

string Suit_next(const string &suit){
  assert(suit == Card::SUIT_SPADES 
  || suit == Card::SUIT_CLUBS
  || suit == Card::SUIT_HEARTS
  || suit == Card::SUIT_DIAMONDS);
  int i = 0;
  while(suit != SUIT_NAMES_BY_WEIGHT[i]) {
    ++i;
  }
  if(i == 0) {return SUIT_NAMES_BY_WEIGHT[2];}
  if(i == 1) {return SUIT_NAMES_BY_WEIGHT[3];}
  if(i == 2) {return SUIT_NAMES_BY_WEIGHT[0];}
  if(i == 3) {return SUIT_NAMES_BY_WEIGHT[1];}
  return "did not work";
}

ostream & operator<<(ostream &os, const Card &card){
  os << card.get_rank() << " of " << card.get_suit(); 
  return os;
}

int dup(const Card &a, const Card &b,
  const string &trump){
  if(a.is_trump(trump) && !b.is_trump(trump)) {return 0;}
  if(!a.is_trump(trump) && b.is_trump(trump)) {return 1;}
  if(a.is_right_bower(trump)) {return 0;}
  if(b.is_right_bower(trump)) {return 1;}
  if(a.is_left_bower(trump)) {return 0;}
  if(b.is_left_bower(trump)) {return 1;}
  return -1;
}
bool Card_less(const Card &a, const Card &b, const string &trump){
  assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
  || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);
// first check trump & bower status for quick check
   if(dup(a,b,trump)==1){return true;}
  else if(dup(a,b,trump)==0){ return false;}
// if both are trump or non-trump, then find out manually
  return a < b;
}


bool Card_less(const Card &a, const Card &b, const Card &led_card,
  const string &trump){
  assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
  || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);
  string led = led_card.get_suit(); // led card's suit
  
  // first check trump & bower status for quick check
  if(led == trump) {return Card_less(a,b,trump);}
  if(dup(a,b,trump)==1){return true;}
  else if(dup(a,b,trump)==0){ return false;}
  

  // check led status for quick check, knowing led != trump
  // from this point, we know a & b aren't trumps
  if(a.get_suit() == led && b.get_suit() != led) {return false;}
  if(a.get_suit() != led && b.get_suit() == led) {return true;}
  if(a.get_suit() == led && b.get_suit() == led) { // compare rank
    int ar = 0; // card a rank
    int br = 0; // card b rank
    while(a.get_rank() != RANK_NAMES_BY_WEIGHT[ar]) {
    ++ar;
    }
    while(b.get_rank() != RANK_NAMES_BY_WEIGHT[br]) {
    ++br;
    }
    return ar<br;
  }
  // both aren't led or trumps
  return a < b;
}

