  //Project UID 1d9f47bfc76643019cfbf037641defe1
  #include "Pack.h"
  #include "Card.h"
  #include <iostream>




  Pack::Pack(){
      
    std::array<std::string,8> Ranks = {Card::RANK_NINE, Card::RANK_TEN, Card::RANK_JACK,
            Card::RANK_QUEEN,Card::RANK_KING, Card::RANK_ACE};
    std::array<std::string,4> Suits = {Card::SUIT_SPADES,Card::SUIT_HEARTS,
    Card::SUIT_CLUBS, Card::SUIT_DIAMONDS};
for(int c = 0; c<4; c++){
    for(int i = 0; i<6; i++){
        
            cards[((i))+(c*6)] = Card(Ranks[i],Suits[c]);
        }
    }
    next = 0;
    
  }

  // REQUIRES: pack_input contains a representation of a Pack in the
  //           format required by the project specification
  // MODIFIES: pack_input
  // EFFECTS: Initializes Pack by reading from pack_input.
  Pack::Pack(std::istream& pack_input){
    std::string suit;
    std::string null;
    std::string rank;
    int i = 0;

    pack_input >> rank >> null >> suit;
    do{
    cards[i]=Card(rank,suit);
    pack_input >> rank >> null >> suit;
    i++;
    }while(i<24);
    next = 0;

  }

  // REQUIRES: cards remain in the Pack
  // EFFECTS: Returns the next card in the pack and increments the next index
  Card Pack::deal_one(){
    return cards[next++];
  }

  // EFFECTS: Resets next index to first card in the Pack
  void Pack::reset(){
      next = 0;
  }

  // EFFECTS: Shuffles the Pack and resets the next index. This
  //          performs an in shuffle seven times. See
  //          https://en.wikipedia.org/wiki/In_shuffle.
  void print_card_array(std::array<Card,24> &card){
      for(int i = 0; i<24; i++){
          std::cout << i << ": " << card[i] << std::endl;
      }
  }
  void slice(std::array<Card,24> &cards,std::array<Card,12> &half, bool front_or_back){
      int offset = front_or_back ? 0 : 12;
      for(int i = offset; i<offset+12; ++i){
          half[i-offset] = cards[i];
      }
  }
  void Pack::shuffle(){
      next = 0;
      //print_card_array(cards);
      std::array<Card, PACK_SIZE/2> first_half;
      std::array<Card, PACK_SIZE/2> second_half;
      for(int i = 0; i<7; ++i){
        slice(cards,first_half,true);
        slice(cards,second_half,false);
        //print_card_array(first_half);
        //print_card_array(second_half);
        for(int c = 0; c<24; ++c){
            cards[c] = (c+1)%2==0 ? first_half[(c-1)/2] : second_half[(c)/2];
        }
        //std::cout << "round " << i << std::endl;
        //print_card_array(cards);
      }
      
  }

  // EFFECTS: returns true if there are no more cards left in the pack
  bool Pack::empty() const{
      return next == PACK_SIZE; 
  }