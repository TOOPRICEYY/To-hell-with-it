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
        }
        return count;
    }

    int trump_face(string &suit) const { // helper
        int count = 0;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() == suit && 
            hand[i].is_face()) {++count;}
        }
        return count;
    }

    virtual const string & get_name() const{
        return name;
    }

    virtual void add_card(const Card &c, const string trump) { // helper: w/ trump
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
                return true;
            }
            else {return false;}
        }
        if (round == 2) {
            string same_color=Suit_next(upcard.get_suit());
            if(is_dealer) {
                order_up_suit = same_color;
                return true;
            }
            else if (!is_dealer) {
                if(trump_face(same_color) >= 1) {
                    order_up_suit = same_color;
                    return true;
                }
                else {return false;}
            }
        }
        return false;
    }

    virtual void add_and_discard(const Card &upcard) {
        assert(handsize > 0);
<<<<<<< HEAD
=======

>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
        array<Card, MAX_HAND_SIZE> h;
        for(int i=0; i < handsize; ++i) {
            h[i] = hand[i];
        }
        sort(h.begin(),h.end());
<<<<<<< HEAD
        for(int i=0; i < handsize; ++i) {
            cout << i << ": " << hand[i] << endl;
        }
        remove(h[0]); // 0 should be the lowest
        add_card(upcard, upcard.get_suit());
        for(int i=0; i < handsize; ++i) {
            cout << i << ": " << hand[i] << endl;
        }

=======

        remove(h[0]); // 0 should be the lowest
        add_card(upcard, upcard.get_suit());
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
    }

    virtual Card lead_card(const std::string &trump) {
        assert(handsize > 0);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);
        
        int trump_count = 0; // amount of trumps in hand
        for(int i = 0; i < handsize; ++i) { // count how many trump cards
            if (hand[i].is_trump(trump)) {
                ++trump_count;
            }
        }
        if(trump_count == handsize) {
<<<<<<< HEAD
            cout << "wrong road" << endl;
=======
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
            Card c = hand[index_high_trump(trump)]; // store copy
            remove(c); // remove from hand
            return c; // return led card
        }
<<<<<<< HEAD
        cout << "right road" << endl;
=======
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
        Card c = hand[index_high(trump)]; // whats the highest non trump
        remove(c);
        return c;
    }

    virtual Card play_card(const Card &led_card, const string &trump) {
        assert(handsize > 0);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);

        if(contains(led_card.get_suit())) {
            Card c = hand[index_high_trump(led_card.get_suit())];
            remove(c);
            return c;
        }
        array<Card, 5> h; // then just return the lowest card
        for(int i=0; i < MAX_HAND_SIZE; ++i) {
            h[i] = hand[i];
        }
        sort(h.begin(),h.end());
        return h[0]; 
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
<<<<<<< HEAD
    }

=======
        empty_hand();
    }
    
    void empty_hand() {
        for (int i = 0; i < handsize; ++i) {
          remove(hand[handsize-1]);
           --handsize;
        }
    }
        
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
    bool contains(Card a) { // helper
        return index(a) != -1;
    }

    bool contains(const string suit) { // helper
        return index(suit) != -1;
    }

    void remove(Card a) { // helper
        if(!contains(a)) {return;}
<<<<<<< HEAD
        for (int i = index(a); i < handsize; ++i) {
=======
        for (int i = index(a); i < handsize-1; ++i) {
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
            hand[i] = hand[i+1];
        }
        --handsize;
    }

<<<<<<< HEAD
=======
    int trump_face(const Card &upcard) const { // helper
        int count = 0;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() == upcard.get_suit() && 
            hand[i].is_face()) {++count;}
        }
        return count;
    }
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424

    int trump_face(string &suit) const { // helper
        int count = 0;
        for(int i=0; i < handsize; ++i) {
            if(hand[i].get_suit() == suit && 
            hand[i].is_face()) {++count;}
        }
        return count;
<<<<<<< HEAD
        Card a;
=======
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
    }

    virtual const string & get_name() const{
        return name;
    }

<<<<<<< HEAD
    virtual void add_card(const Card &c) {
        assert(handsize <= MAX_HAND_SIZE);

=======
    virtual void add_card(const Card &c, const string trump) { // helper: w/ trump
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

    virtual void add_card(const Card &c) {
        assert(handsize < MAX_HAND_SIZE);
        if(contains(c)) {return;}
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
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

<<<<<<< HEAD
    virtual bool make_trump(const Card &upcard, bool is_dealer,
=======
    virtual bool make_trump(const Card &upcard, bool is_ealer,
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
        int round, string &order_up_suit) const {
        assert(round == 1 || round == 2);

        array<Card, MAX_HAND_SIZE> h;
        for(int i=0; i < handsize; ++i) {
            h[i] = hand[i];
        }
<<<<<<< HEAD
        sort(h.begin(),h.end());

        for(int i=0; i < handsize; ++i) {
            cout << "Human player " << get_name() << "'s hand: [" << 
            i << "] " << h[i];
        }
        
        if (round == 1) {
            if(trump_face(upcard) >= 2) {
                order_up_suit = upcard.get_suit();
                return true;
            }
            else {return false;}
        }
        if (round == 2) {
            string same_color=Suit_next(upcard.get_suit());
            if(is_dealer) {
                order_up_suit = same_color;
                return true;
            }
            else if (!is_dealer) {
                if(trump_face(same_color) >= 1) {
                    order_up_suit = same_color;
                    return true;
                }
                else {return false;}
            }
        }
        return false;
=======
        sort(h.begin(),h.end()); // sort first

        for(int i = 0; i < handsize; ++i) {
            cout << "Human player " << get_name() << 
            "'s hand: [" << i << "] " << hand[i] << endl;
        }
        cout << "Human player " << get_name() << 
        ", please enter a suit, or \"pass\":" << endl;
        cin >> order_up_suit;

        if (order_up_suit == "pass") { 
            cout << get_name() << " passes" << endl;
            return false;
        }
        cout << get_name() << " orders up " << order_up_suit << endl;
        return true;
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
    }

    virtual void add_and_discard(const Card &upcard) {
        assert(handsize > 0);
<<<<<<< HEAD

        add_card(upcard);
        remove(hand[0]); // 0 should be the lowest
=======
        
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
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
    }

    virtual Card lead_card(const std::string &trump) {
        assert(handsize > 0);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);
        
<<<<<<< HEAD
        if(contains(trump)) {
=======
        int trump_count = 0; // amount of trumps in hand
        for(int i = 0; i < handsize; ++i) { // count how many trump cards
            if (hand[i].is_trump(trump)) {
                ++trump_count;
            }
        }
        if(trump_count == handsize) {
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
            Card c = hand[index_high_trump(trump)]; // store copy
            remove(c); // remove from hand
            return c; // return led card
        }
<<<<<<< HEAD
        Card c = hand[index_high(trump)];
=======
        Card c = hand[index_high(trump)]; // whats the highest non trump
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
        remove(c);
        return c;
    }

    virtual Card play_card(const Card &led_card, const string &trump) {
        assert(handsize > 0);
        assert(trump == Card::SUIT_CLUBS || trump == Card::SUIT_DIAMONDS
        || trump == Card::SUIT_HEARTS || trump == Card::SUIT_SPADES);

        if(contains(led_card.get_suit())) {
            Card c = hand[index_high_trump(led_card.get_suit())];
            remove(c);
            return c;
        }
<<<<<<< HEAD
        return hand[0]; // might not be right bcuz doesnt consider trump
        // ^ assumes that 0 is the lowest card, considering trump
=======
        array<Card, 5> h; // then just return the lowest card
        for(int i=0; i < MAX_HAND_SIZE; ++i) {
            h[i] = hand[i];
        }
        sort(h.begin(),h.end());
        return h[0]; 
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424
    }

  static const int MAX_HAND_SIZE = 5;

    private:
    string name;
    Card hand[MAX_HAND_SIZE];
<<<<<<< HEAD
    int handsize = 5;
=======
    int handsize = 0;
>>>>>>> cccb291a33ddcf13ce266d8dfe0ef9d1e23d1424

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