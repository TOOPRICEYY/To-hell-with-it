// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <fstream>

#include "Card.h"
#include "Pack.h"
#include "Player.h"





using namespace std;


void deal(Pack &pack, array<Player *, 4> Players, int dealer){
    int itter;
          for(int c = 0; c<2; c++){
            for(int i = 0; i<4; i++){
                itter = (i+dealer)%4;
                Players[itter]->add_card(pack.deal_one());
                Players[itter]->add_card(pack.deal_one());
                if((i+c)%2 == 0){
                     Players[itter]->add_card(pack.deal_one());
                }
            }
        }
}

int main(int argc, char * argv[]){

    ifstream f(argv[1]);
    if(argc!=12){
        cout << "please enter 12 arguments";
        return 1;
    }
    if(atoi(argv[3])<1 || atoi(argv[3])>100){
        cout << "please enter score between 1 and 100";
        return 1;
    }

    
    array<Player *, 4> Players;
    Card upcard;
    string trump = ""; 
    int dealer = 0;
    int h = 0;

    if(f.is_open()){ // if open and santized run
        Pack pack(f);
        f.close();

        bool shuffle = string(strlen(argv[2]), argv[2])=="shuffle" ? true : false;
        if(shuffle) pack.shuffle();
        //int win_threshold =  atoi(argv[3]);
        
        for(int i = 0; i<4; i++){ // create players to spec
            Players[i] = Player_factory(argv[4+i*2],argv[5+i*2]);
        }

    

        deal(pack, Players, dealer);
        trump = ""; 
        h = 0;


        while(trump == ""){
            upcard = pack.deal_one();
            cout << "Hand " << h << endl;
            cout << Players[dealer] << " Deals" << endl;
            cout << upcard << " turned up" << endl;

            for(int i = 0; i<4; i++){ // make trump
                int itter = (i+dealer)%4;
                string s = upcard.get_suit();
                if(Players[itter]->make_trump(upcard,dealer==itter,h,s)){
                    trump = upcard.get_suit();
                    break;
                }
            }


        }


        dealer = (dealer+1)%4;
  









    }else{
        cout << "please enter a valid pack in file";
        return 1;
    }

    for(int i = 0; i<4; i++) delete Players[i];
    
    return 0;
}