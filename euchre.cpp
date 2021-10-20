// Project UID 1d9f47bfc76643019cfbf037641defe1
#include <iostream>
#include <fstream>

#include "Card.h"
#include "Pack.h"
#include "Player.h"





using namespace std;

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
    if(f.is_open()){ // if open and santized run
        Pack pack(f);
        f.close();

        bool shuffle =  argv[2]=="shuffle" ? true : false;
        int win_threshold =  atoi(argv[3]);
        
        
        for(int i = 0; i<4; i++){ // create players to spec
            Players[i] = Player_factory(argv[4+i*2],argv[5+i*2]);
        }
        for(int i = 0; i<4; i++){
            for(int i = 0; i<4; i++){ //"change something in euchre real quick" -truong ryan 2021
                Players[i]->add_card(pack.deal_one());
            }
        }









    }else{
        cout << "please enter a valid pack in file";
        return 1;
    }

    for(int i = 0; i<4; i++) delete Players[i];
    
    return 0;
}