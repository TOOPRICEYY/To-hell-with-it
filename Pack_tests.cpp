// Project UID 1d9f47bfc76643019cfbf037641defe1

#include "Pack.h"
#include "unit_test_framework.h"

#include <iostream>
#include <fstream>

using namespace std;

void pack_print(Pack pack){
    while(!pack.empty()){
        std::cout<<pack.deal_one()<<std::endl;
    }
    pack.reset();

}

TEST(test_pack_default_ctor) {
    ifstream fin("./pack.in");

    Pack pack(fin);
    pack_print(pack);
    fin.close();
    Card first = pack.deal_one();
    std::cout<<std::endl;
    ASSERT_EQUAL(Card::RANK_NINE, first.get_rank());
    ASSERT_EQUAL(Card::SUIT_SPADES, first.get_suit());
    pack.shuffle();
    pack_print(pack);
    first = pack.deal_one();

}

// Add more tests here

TEST_MAIN()
