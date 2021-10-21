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

TEST(test_player_factory) {
    Player * alice = Player_factory("Alice","Simple");
    Player * bob = Player_factory("Bob","Human");
    Player * candace = Player_factory("Candace","Simple");
    Player * deez = Player_factory("Deez","Human");

    ostringstream oss1;
    oss1 << * bob;
    ASSERT_EQUAL(oss1.str(), "Bob");

  bob->add_card(Card(Card::RANK_NINE, Card::SUIT_SPADES));
  candace->add_card(Card(Card::RANK_TEN, Card::SUIT_SPADES));
  deez->add_card(Card(Card::RANK_QUEEN, Card::SUIT_SPADES));
  alice->add_card(Card(Card::RANK_KING, Card::SUIT_SPADES));
  Card upcard(Card::RANK_JACK,Card::SUIT_HEARTS);
  alice->add_and_discard(upcard);

    delete alice;
    delete bob;
    delete candace;
    delete deez;
}