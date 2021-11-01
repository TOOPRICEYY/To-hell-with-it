// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Card.h"
#include "unit_test_framework.h"
#include <cassert>
#include <iostream>

using namespace std;


TEST(test_card_ctor) {
    Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());
}

// Add more test cases here

TEST_MAIN()

TEST(test_card_trump) {
    Card c;
    Card();
    Card c2(Card::RANK_JACK, Card::SUIT_CLUBS);
    Card t(Card::RANK_NINE, Card::SUIT_SPADES);
    ASSERT_EQUAL(t.get_suit(), c.get_suit());
    ASSERT_TRUE(operator<(c,t) && c.is_trump(Card::SUIT_SPADES));
    ASSERT_TRUE(c2.is_trump(Card::SUIT_SPADES));
    ASSERT_EQUAL(Suit_next(c2.get_suit()), t.get_suit());
    operator<<(cout, c);
}

TEST(test_operators) {

   Card c(Card::RANK_ACE, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Card::RANK_ACE, c.get_rank());
    ASSERT_EQUAL(Card::SUIT_HEARTS, c.get_suit());

    Card Queen_of_spades(Card::RANK_QUEEN,Card::SUIT_SPADES);
    Card Queen_of_hearts(Card::RANK_QUEEN,Card::SUIT_HEARTS);
    Card Ten_of_hearts(Card::RANK_TEN, Card::SUIT_HEARTS);
    ASSERT_EQUAL(Queen_of_spades.is_face(),true);
    ASSERT_EQUAL(Ten_of_hearts.is_face(),false);
    ASSERT_EQUAL(Ten_of_hearts<Queen_of_spades,true);
    ASSERT_EQUAL(Queen_of_spades<Queen_of_hearts,true);
    ASSERT_EQUAL(Ten_of_hearts<Ten_of_hearts,false);
    ASSERT_EQUAL(Ten_of_hearts<=Ten_of_hearts,true);
    ASSERT_EQUAL(Ten_of_hearts!=Ten_of_hearts,false);


    ostringstream s;
    s<<Ten_of_hearts;
    ASSERT_EQUAL("Ten of Hearts"==s.str(),true);

    ASSERT_EQUAL(Suit_next(Card::SUIT_CLUBS),Card::SUIT_SPADES); // next card exaustive tests
    ASSERT_EQUAL(Suit_next(Card::SUIT_HEARTS),Card::SUIT_DIAMONDS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_DIAMONDS),Card::SUIT_HEARTS);
    ASSERT_EQUAL(Suit_next(Card::SUIT_SPADES),Card::SUIT_CLUBS);

    ASSERT_EQUAL(Card_less(Ten_of_hearts,Queen_of_spades,Card::SUIT_HEARTS),false); // trump tests
    ASSERT_EQUAL(Card_less(Ten_of_hearts,Queen_of_spades,Card::SUIT_DIAMONDS),true);
}

TEST(test_card_less) {

    Card KingClubs(Card::RANK_KING,Card::SUIT_CLUBS);
    Card KingDiamonds(Card::RANK_KING,Card::SUIT_DIAMONDS);
    Card QueenSpades(Card::RANK_QUEEN,Card::SUIT_SPADES);
    Card JackClubs(Card::RANK_JACK,Card::SUIT_CLUBS);
    Card AceHearts(Card::RANK_ACE,Card::SUIT_HEARTS);
    Card JackSpades(Card::RANK_JACK,Card::SUIT_SPADES);
    Card led_card(Card::RANK_NINE,Card::SUIT_HEARTS);
    string trump = "Spades";
    ASSERT_EQUAL(Card_less(KingClubs,KingDiamonds,trump), true);
    ASSERT_EQUAL(Card_less(KingClubs,QueenSpades,trump),true);
    ASSERT_EQUAL(Card_less(QueenSpades,JackClubs,led_card,trump),true);
    ASSERT_EQUAL(Card_less(led_card,KingClubs,led_card,trump),false);
    ASSERT_EQUAL(Card_less(JackSpades,QueenSpades,led_card,trump),false);
    ASSERT_EQUAL(Card_less(JackSpades,JackClubs,trump),false);
}