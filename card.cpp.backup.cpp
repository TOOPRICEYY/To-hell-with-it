// Project UID 1d9f47bfc76643019cfbf037641defe1

#include <cassert>
#include <iostream>
#include <string>
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


int iia(const char* const C[], const int len, string a){ // index in array
    int ret = -1;
    for(int i = 0; i<len; i++){
        if(*C[i]==*a.c_str()){
            ret = i;
            break;
        }
    }
    return ret;
}


Card::Card(){
    rank = Card::RANK_TWO;
    suit = Card::SUIT_SPADES;
}

Card::Card(const std::string &rank_in, const std::string &suit_in){
    suit = "na";
    rank = "na";
    for(int i = 0; i<NUM_RANKS; i++){
        if(rank_in==RANK_NAMES_BY_WEIGHT[i]){
            rank = RANK_NAMES_BY_WEIGHT[i];
            break;
        }
    }
    assert(rank!="na");

    for(int i = 0; i<NUM_SUITS; i++){
        if(suit_in==SUIT_NAMES_BY_WEIGHT[i]){
            suit = SUIT_NAMES_BY_WEIGHT[i];
            break;
        }
    }
    assert(suit!="na");
}

  //EFFECTS Returns the rank
  std::string Card::get_rank() const {
      return rank;

  }

  //EFFECTS Returns the suit.  Does not consider trump.
    std::string Card::get_suit() const {
      return suit;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns the suit
  //HINT: the left bower is the trump suit!
string Card::get_suit(const string &trump) const {
  assert(trump == SUIT_CLUBS || trump == SUIT_DIAMONDS
  || trump == SUIT_HEARTS || trump == SUIT_SPADES);
return Suit_next(trump);
}

  //EFFECTS Returns true if card is a face card (Jack, Queen, King or Ace)
  bool Card::is_face() const{
      if(iia(RANK_NAMES_BY_WEIGHT,NUM_RANKS,rank)>8) return true;
      return false;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the trump suit
  bool Card::is_right_bower(const std::string &trump) const{
      return rank==Card::RANK_JACK && suit==trump;
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if card is the Jack of the next suit
  bool Card::is_left_bower(const std::string &trump) const{
      return rank==Card::RANK_JACK && suit==Suit_next(trump);
  }

  //REQUIRES trump is a valid suit
  //EFFECTS Returns true if the card is a trump card.  All cards of the trump
  // suit are trump cards.  The left bower is also a trump card.
  bool Card::is_trump(const std::string &trump) const{
      return suit==trump || is_left_bower(trump);
  }


//EFFECTS Returns true if lhs is lower value than rhs.
//  Does not consider trump.
bool operator<(const Card &lhs, const Card &rhs){
    if(iia(RANK_NAMES_BY_WEIGHT,NUM_RANKS,lhs.get_rank())<iia(RANK_NAMES_BY_WEIGHT,NUM_RANKS,rhs.get_rank())){
        return true;
    }else if(iia(SUIT_NAMES_BY_WEIGHT,NUM_SUITS,lhs.get_suit())<iia(SUIT_NAMES_BY_WEIGHT,NUM_SUITS,rhs.get_suit())&&rhs.get_rank()==lhs.get_rank()){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is lower value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator<=(const Card &lhs, const Card &rhs){
    if(lhs<rhs||lhs==rhs){
        return true;
    }
    return false;

}

//EFFECTS Returns true if lhs is higher value than rhs.
//  Does not consider trump.
bool operator>(const Card &lhs, const Card &rhs){
    if(iia(RANK_NAMES_BY_WEIGHT,NUM_RANKS,lhs.get_rank())>iia(RANK_NAMES_BY_WEIGHT,NUM_RANKS,rhs.get_rank())){
        return true;
    }else if(iia(SUIT_NAMES_BY_WEIGHT,NUM_SUITS,lhs.get_suit())>iia(SUIT_NAMES_BY_WEIGHT,NUM_SUITS,rhs.get_suit())&&rhs.get_rank()==lhs.get_rank()){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is higher value than rhs or the same card as rhs.
//  Does not consider trump.
bool operator>=(const Card &lhs, const Card &rhs){
    if(lhs>rhs||lhs==rhs){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is same card as rhs.
//  Does not consider trump.
bool operator==(const Card &lhs, const Card &rhs){
    if(lhs.get_rank() == rhs.get_rank()&&lhs.get_suit() == rhs.get_suit()){
        return true;
    }
    return false;
}

//EFFECTS Returns true if lhs is not the same card as rhs.
//  Does not consider trump.
bool operator!=(const Card &lhs, const Card &rhs){
    if(lhs==rhs){
        return false;
    }
    return true;
}

//REQUIRES suit is a valid suit
//EFFECTS returns the next suit, which is the suit of the same color
std::string Suit_next(const std::string &suit){
    int i = iia(SUIT_NAMES_BY_WEIGHT,NUM_SUITS,suit)+1;
    if(i%2 == 0){
        return SUIT_NAMES_BY_WEIGHT[i-2];
    }
    return SUIT_NAMES_BY_WEIGHT[i];
}

//EFFECTS Prints Card to stream, for example "Two of Spades"
std::ostream & operator<<(std::ostream &os, const Card &card){

    os << card.get_rank() << " of " << card.get_suit();

    return os;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses trump to determine
// order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const std::string &trump){
    if(a==b) return false;
    if(a.is_trump(trump)<b.is_trump(trump)) return true;
    if(a.is_trump(trump)>b.is_trump(trump)) return false;
    if(a.is_right_bower(trump)) return false;
    if(b.is_right_bower(trump)) return true;
    if(a.is_left_bower(trump)) return false;
    if(b.is_left_bower(trump)) return true;
    return a<b;
}

//REQUIRES trump is a valid suit
//EFFECTS Returns true if a is lower value than b.  Uses both the trump suit
//  and the suit led to determine order, as described in the spec.
bool Card_less(const Card &a, const Card &b, const Card &led_card,
               const std::string &trump){
    if(a==b) return false;
    if(a.is_trump(trump)<b.is_trump(trump)) return true;
    if(a.is_trump(trump)>b.is_trump(trump)) return false;
    if(a.is_right_bower(trump)) return false;
    if(b.is_right_bower(trump)) return true;
    if(a.is_left_bower(trump)) return false;
    if(b.is_left_bower(trump)) return true;
    if(a.is_trump(led_card.get_suit())<b.is_trump(led_card.get_suit())) return true;
    if(a.is_trump(led_card.get_suit())>b.is_trump(led_card.get_suit())) return false;
    return a<b;

}



// NOTE: We HIGHLY recommend you check out the operator overloading
// tutorial in the project spec (see the appendices) before implementing
// the following operator overload functions:
//   operator<<
//   operator<
//   operator<=
//   operator>
//   operator>=
//   operator==
//   operator!=
