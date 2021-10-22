// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Player.h"
#include "unit_test_framework.h"

#include <iostream>

using namespace std;

TEST(test_player_get_name) {
    Player * alice = Player_factory("Alice", "Simple");
    ASSERT_EQUAL("Alice", alice->get_name());

    delete alice;
}

// Add more tests here

TEST_MAIN()

TEST(test_player_making_first_round) {
    Player * alice = Player_factory("Alice","Simple");

  alice->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  Card upcard(Card::RANK_TEN,Card::SUIT_HEARTS);
  string order_up_suit = "";
  alice->make_trump(upcard,false,1,order_up_suit);
  ASSERT_EQUAL(order_up_suit, "Hearts");
  Card upcard2(Card::RANK_EIGHT,Card::SUIT_SPADES);
  order_up_suit = "";
  alice->make_trump(upcard2,true,1,order_up_suit);
  ASSERT_EQUAL(order_up_suit, "");

    delete alice;
}

TEST(test_player_making_second_round) {
    Player * alice = Player_factory("Alice","Simple");

  alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  Card upcard(Card::RANK_ACE,Card::SUIT_CLUBS);
  Card upcard2(Card::RANK_EIGHT,Card::SUIT_SPADES);
  Card upcard3(Card::RANK_TEN,Card::SUIT_HEARTS);
  Card upcard4(Card::RANK_NINE,Card::SUIT_HEARTS);
  string order_up_suit = "";
  alice->make_trump(upcard,false,2,order_up_suit);
  ASSERT_EQUAL(order_up_suit, "Spades");
  order_up_suit = "";
  alice->make_trump(upcard2,false,2,order_up_suit);
  ASSERT_EQUAL(order_up_suit, "Clubs");
  order_up_suit = "";
  alice->make_trump(upcard3,false,2,order_up_suit);
  ASSERT_EQUAL(order_up_suit, "");
  order_up_suit = "";
  alice->make_trump(upcard4,false,2,order_up_suit);
  ASSERT_EQUAL(order_up_suit, "");
  order_up_suit = "";
  alice->make_trump(upcard,true,2,order_up_suit);
  ASSERT_EQUAL(order_up_suit, "Spades");

    delete alice;
}

TEST(test_player_play) {
    Player * alice = Player_factory("Alice","Simple");

  alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  alice->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  Card led(Card::RANK_ACE,Card::SUIT_CLUBS);
  string trump = "Diamonds";

  Card played = alice->play_card(led, trump);
  ASSERT_EQUAL(played, Card(Card::RANK_KING, Card::SUIT_CLUBS));
  played = alice->play_card(led, trump);
  ASSERT_EQUAL(played, Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  played = alice->play_card(led, trump);
  ASSERT_EQUAL(played, Card(Card::RANK_TEN, Card::SUIT_SPADES));
  played = alice->play_card(led, trump);
  ASSERT_EQUAL(played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  played = alice->play_card(led, trump);
  ASSERT_EQUAL(played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  delete alice;
}

TEST(test_player_lead_all_trump) { // all trumps in hand
    Player * alice = Player_factory("Alice","Simple");

  alice->add_card(Card(Card::RANK_NINE, Card::SUIT_DIAMONDS));
  alice->add_card(Card(Card::RANK_TEN, Card::SUIT_DIAMONDS));
  alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  string trump = "Diamonds";
  Card played = alice->lead_card(trump);
  ASSERT_EQUAL(played, Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  played = alice->lead_card(trump);
  ASSERT_EQUAL(played, Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  played = alice->lead_card(trump);
  ASSERT_EQUAL(played, Card(Card::RANK_QUEEN, Card::SUIT_DIAMONDS));
  delete alice;
}

TEST(test_player_lead_edge) { // l and r bower, chooses next highest
    Player * alice = Player_factory("Alice","Simple");

  alice->add_card(Card(Card::RANK_QUEEN, Card::SUIT_CLUBS));
  alice->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_KING, Card::SUIT_CLUBS));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_DIAMONDS));
  alice->add_card(Card(Card::RANK_JACK, Card::SUIT_HEARTS));
  string trump = "Diamonds";
  Card played = alice->lead_card(trump);
  ASSERT_EQUAL(played, Card(Card::RANK_KING, Card::SUIT_CLUBS));
  delete alice;
}

