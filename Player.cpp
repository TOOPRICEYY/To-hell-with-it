// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <array>
#include <string>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <cstring>
#include <algorithm>
#include "Player.h"

using namespace std;

class Simple : public Player {
    public:
    
    Simple(string name_in) { // initializes player
        name = name_in;
        empty_hand();
    }

    virtual Card card(int i) {
        return hand[i];
    }

    void empty_hand() {
        for (int i = 0; i < handsize; ++i) {
          remove(hand[handsize-1]);
           --handsize;
        }
    }
        
    bool contains(Card a) { // helper
        return index(a) != -1;
    }

    bool contains(const string suit) { // helper
        return index(suit) != -1;
    }

    void remove(Card a) { // helper
        if(!contains(a)) {return;}
        for (int i = index(a); i < handsize-1; ++i) {
            hand[i] = hand[i+1];
        }
        --handsize;
    }

    int trump_face(const Card &upcard) const { // helper
        int count = 0;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() == upcard.get_suit() && 
            hand[i].is_face()) {++count;}
            // already accounts for right bower
            if(hand[i].is_left_bower(upcard.get_suit())) {++count;}
            // considers trump card, left bower too
        }
        return count;
    }

    int trump_face(string &suit) const { // helper
        int count = 0;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() == suit && 
            hand[i].is_face()) {++count;}
        }
        // do not account for left bower, cannot pick that suit
        return count;
    }

    virtual const string & get_name() const{
        return name;
    }

    virtual void add_card(const Card &c,const string trump) { // helper: w/ trump
        assert(handsize < MAX_HAND_SIZE);
        if(contains(c)) {return;}
        if(!contains(c)) {

            int index = handsize;
            while (index > 0 && Card_less(c,hand[index-1],trump)) {
                hand[index] = hand[index-1];
                --index;
            }
            
            hand[index] = c;

            ++handsize;

        }
    }
    virtual void add_card(const Card &c,const string &trump, Card * hand, int &handsize) { // helper: w/ trump
        assert(handsize < MAX_HAND_SIZE+1);
            int index = handsize;

            while (index > 0 && Card_less(c,hand[index-1],trump)) {
                hand[index] = hand[index-1];
                --index;
            }
            hand[index] = c;
            ++handsize;
    }

    virtual void add_card(const Card &c) {
        assert(handsize < MAX_HAND_SIZE);
        if(contains(c)) {return;}
        if(!contains(c)) {
            int index = handsize;
            while (index > 0 && hand[index-1] > c) {
                hand[index] = hand[index-1];
                --index;
            }
            hand[index] = c;
            ++handsize;
        }
    }

    virtual bool make_trump(const Card &upcard, bool is_dealer,
        int round, string &order_up_suit) const {
        assert(round == 1 || round == 2);

        if (round == 1) {
            if(trump_face(upcard) >= 2) {
                order_up_suit = upcard.get_suit();
                cout << get_name() << " orders up " << order_up_suit << endl;
                return true;
            }
            else {
                cout << get_name() << " passes" << endl;
                return false;
            }
        }
        if (round == 2) {
            string same_color=Suit_next(upcard.get_suit());
            if(is_dealer) {
                order_up_suit = same_color;
                cout << get_name() << " orders up " << order_up_suit << endl;
                return true;
            }
            else if (!is_dealer) {
                if(trump_face(same_color) >= 1) {
                    order_up_suit = same_color;
                    cout << get_name() << " orders up " << order_up_suit << endl;
                    return true;
                }
                else {
                    cout << get_name() << " passes" << endl;
                    return false;
                    }
            }
        }
        cout << get_name() << " passes" << endl;
        return false;
    }


    
    virtual void add_and_discard(const Card &upcard) {
        assert(handsize > 0);
        Card h[MAX_HAND_SIZE+1];
        Card ht[MAX_HAND_SIZE+1];

        for(int i=0; i < handsize; ++i) {
            h[i] = hand[i];
           // cout << "i: "<<i<<"Card: "<<h[i] << endl;
        }
        h[handsize] = upcard;
        
        int hi = handsize+1;
        int temp = 0;
        empty_hand();
        for(int i=0; i < hi; ++i) {
            add_card(h[i],upcard.get_suit(),ht,temp);
        }

        for(int i=1; i < hi; ++i) {
            hand[i-1]=ht[i];
            
        }
        handsize = hi-1;
        /*
         for(int i=0; i < hi-1; ++i) {
            cout << "i: "<<i<<" Card: "<<hand[i] << endl;
        }
        */
    }

    Card Highest_trump_or_bower(const std::string &trump){
        Card h[MAX_HAND_SIZE];
         for(int i=0; i < handsize; ++i) {
            h[i] = hand[i];
        }
        int hi = handsize;
        empty_hand();
        handsize = 0;
        for(int i=0; i < hi; ++i) {
            add_card(h[i],trump);

        }
        handsize = hi;
        

        return hand[hi-1];
    }

    virtual Card lead_card(const std::string &trump) {
        assert(handsize > 0);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);
        
        int left_bower = -1;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].is_left_bower(trump)) {left_bower = i;}
        }
        
        Card a;
        bool contains_trump = contains(trump);
        if (left_bower != -1) {
            a = hand[left_bower];
            hand[left_bower] = Card(a.get_rank(),trump);
        }
       

        int trump_count = 0; // amount of trumps in hand
        for(int i = 0; i < handsize; ++i) { // count how many trump cards
            if (hand[i].is_trump(trump)&&!hand[i].is_left_bower(trump)) {
                ++trump_count;
            }
        }
      
        if(trump_count == handsize) {
            if (left_bower != -1) {
            hand[left_bower] = a;
            }
            //cout << "all trumps " << endl;
            ;
            Card c = Highest_trump_or_bower(trump);
            remove(c); // remove from hand
            cout << c << " led by " << get_name() << endl;

            return c; // return led card
        }
      
        if (left_bower != -1 && !contains_trump) {
            hand[left_bower] = a;
        }
        
        int index = index_high(trump);

        if (left_bower != -1 && contains_trump) {
            hand[left_bower] = a;
        }
    

        Card c = hand[index]; // whats the highest non trump
       
        remove(c);

        cout << c << " led by " << get_name() << endl;
        return c;
    }

    int contains_left_bower(const Card &led_card,const string &trump){
        int left_bower = -1;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].is_left_bower(trump)) {left_bower = i;}
        }
        return left_bower;
    }

    virtual Card play_card(const Card &led_card, const string &trump) {
        assert(handsize > 0);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);

        int left_bower = -1;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].is_left_bower(trump)) {left_bower = i;}}
        Card a;
        if (left_bower != -1) {a = hand[left_bower];
            hand[left_bower] = Card(a.get_rank(),trump);
        }
        Card led_card2 = led_card;
        if(led_card.is_left_bower(trump)){
            led_card2 = Card(led_card.get_rank(),trump);
        }
 
        if(contains(led_card2.get_suit())&& handsize>1) {
            int index = index_high_trump(led_card2.get_suit());
            if (left_bower != -1) {hand[left_bower] = a;}
            Card c = hand[index];
            remove(c);
            cout << c << " played by " << get_name() << endl;
            return c;
        }
        if (left_bower != -1) {hand[left_bower] = a;}
        array<Card, 5> h;
        int hi = handsize;
        for(int i=0; i < handsize; ++i) {h[i] = hand[i];}
        if(handsize>1){empty_hand();
            for(int i=0; i < hi; ++i) {add_card(h[i],trump);}}
        Card c = hand[0];
        cout << hand[0] << " played by " << get_name() << endl;
        remove(c);
        return c; 
    }

  static const int MAX_HAND_SIZE = 5;

    private:
    string name;
    Card hand[MAX_HAND_SIZE];
    int handsize = 0;

    int index(Card a) const{ // index given card
        for(int i=0; i < handsize; ++i) {
            if(hand[i] == a) {
                return i;
            }
        }
        
        return -1;
    }

    int index(const string suit) const{ // index given suit
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() == suit) {
                return i;
            }
        }
        return -1;
    }

    int index_high_trump(const string trump) const{ // highest card, trump
        int high = 0;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() == trump) {
                high = i;
            }
        }
        if(high < 5 && high >= 0) {return high;}
        return -1;
    }

    int index_high(const string trump) const{ // highest card, no trump
        int high = 0;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() != trump) {
                high = i;
            }
        }
        if(high < 5 && high >= 0) {return high;}
        return -1;
    }
};


class Human : public Player {
    public:
    
    Human(string name_in) { // initializes player
        name = name_in;
        empty_hand();
    }
    virtual Card card(int i) {
        return hand[i];
    }
    
    void empty_hand() {
        for (int i = 0; i < handsize; ++i) {
          remove(hand[handsize-1]);
           --handsize;
        }
    }
        
    bool contains(Card a) { // helper
        return index(a) != -1;
    }


     void remove(Card a) { // helper
        if(!contains(a)) {return;}
        for (int i = index(a); i < handsize-1; ++i) {
            hand[i] = hand[i+1];
        }
        --handsize;
    }


    virtual const string & get_name() const{
        return name;
    }

    virtual void add_card(const Card &c) {
        assert(handsize < MAX_HAND_SIZE);
        if(contains(c)) {return;}
        if(!contains(c)) {
            int index = handsize;
            while (index > 0 && hand[index-1] > c) {
                hand[index] = hand[index-1];
                --index;
            }
            hand[index] = c;
            ++handsize;
        }
    }

    virtual bool make_trump(const Card &upcard, bool is_ealer,
        int round, string &order_up_suit) const {
        assert(round == 1 || round == 2);

        array<Card, MAX_HAND_SIZE> h;
        for(int i=0; i < handsize; ++i) {
            h[i] = hand[i];
        }
        sort(h.begin(),h.end()); // sort first

        for(int i = 0; i < handsize; ++i) {
            cout << "Human player " << get_name() << 
            "'s hand: [" << i << "] " << h[i] << endl;
        }
        cout << "Human player " << get_name() << 
        ", please enter a suit, or \"pass\":" << endl;
        cin >> order_up_suit;

        if (order_up_suit == "pass") { 
            cout << get_name() << " passes" << endl;
            return false;
        }
        cout << get_name() << " orders up " << order_up_suit << endl << endl;
        return true;
    }

    virtual void add_and_discard(const Card &upcard) {
        assert(handsize > 0);
        
        for(int i = 0; i < handsize; ++i) {
            cout << "Human player " << get_name() << 
            "'s hand: [" << i << "] " << hand[i] << endl;
        }
        cout << "Discard upcard: [-1]" << endl;
        cout << "Human player " << get_name() << 
        ", please select a card to discard:" << endl;

        int input;
        cin >> input;

        if(input == -1) {return;} // want to discard upcard, do nothing
        
        remove(hand[input]); // discard chosen card then add upcard
        add_card(upcard);
    }

    Card gen_play_card(const std::string &trump){
        assert(handsize > 0);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);
        
        array<Card, MAX_HAND_SIZE> h;
        for(int i=0; i < handsize; ++i) {
            h[i] = hand[i];
        }
        sort(h.begin(),h.end()); // sort first

        for(int i = 5-handsize; i < 5; ++i) {
            cout << "Human player " << get_name() << 
            "'s hand: [" << i-(5-handsize) << "] " << h[i] << endl;
        }
        cout << "Human player " << get_name() << 
        ", please select a card:" << endl;
        
        int input;
        cin >> input;

        return h[(5-handsize)+input];
    }

    virtual Card lead_card(const std::string &trump) {
        assert(handsize > 0);
        Card c = gen_play_card(trump);
        cout << c << " led by " << get_name() << endl;
        remove(c);


        return c;
    }

    virtual Card play_card(const Card &led_card, const string &trump) {
        assert(handsize > 0);
          Card c = gen_play_card(trump);
        cout << c << " played by " << get_name() << endl;
        remove(c);

        return c;
    }

  static const int MAX_HAND_SIZE = 5;

    private:
    string name;
    Card hand[MAX_HAND_SIZE];
    int handsize = 0;

    int index(Card a) const{ // index given card
        for(int i=0; i < handsize; ++i) {
            if(hand[i] == a) {
                
                return i;
            }
        }
        return -1;
    }
};

Player * Player_factory(const string &name, const string &strategy) {
    assert(strategy == "Simple" || strategy == "Human");

    if(strategy == "Simple") {
        return new Simple(name);
    }
    return new Human(name);
}

ostream & operator<<(ostream &os, const Player &p) {
    string name = p.get_name();
    os << name;
    return os;
}