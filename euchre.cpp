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
                itter = (i+dealer+1)%4;
                Players[itter]->add_card(pack.deal_one());
                Players[itter]->add_card(pack.deal_one());
                if((i+c)%2 == 0){
                     Players[itter]->add_card(pack.deal_one());
                }
            }
        }
}

void createPlayers(array<Player *, 4> &Players, char * argv[]){
    for(int i = 0; i<4; i++){ // create players to spec
        Players[i] = Player_factory(argv[4+i*2],argv[5+i*2]);
    }
}

int makeTrump(array<Player *, 4> &Players, Pack &pack, int dealer, string &trump, Card &upcard){
    trump = ""; 
    int order_up = -1;
    int h = 0;
    upcard = pack.deal_one();
    cout << *Players[dealer] << " deals" << endl;
    cout << upcard << " turned up" << endl;

    while(trump == "" && h<2){
    
        for(int i = 0; i<4; i++){ // make trump
            int itter = (i+dealer+1)%4;
            string s;
            /*
            for(int i = 0; i < 5; ++i) {
                cout << "player " << Players[itter]->get_name() << 
                "'s hand: [" << i << "] " << Players[itter]->card(i) << endl;
            }
            */
            if(Players[itter]->make_trump(upcard,itter==dealer,h+1,s)){
                trump = s;
                order_up = itter;
                break;
            }
            
        }
        h++;
    }
    cout << endl;
    if(h==1){ //if trump declared in first round
        Players[dealer]->add_and_discard(upcard);
    }

    if(trump==""){ // screw the dealer
        string s;
        Players[dealer]->make_trump(upcard,true,2,s);
        trump = s;

    }
    return order_up;
}

int index_of_highest_value_card(array<Card,4> &trick, string &trump, Card &lead){
    int index = 0;
    if(Card_less(trick[0],trick[1],lead, trump)) index = 1;

    int index2 = 2;
    if(Card_less(trick[2],trick[3],lead,trump)) index2 = 3;

    if(Card_less(trick[index],trick[index2],lead,trump)) index = index2;

    return index;
}

void determine_winners(array<Player *, 4> &Players, int Scores[],int order_up, int * scores){
    int of = 1;
    if((Scores[0]+Scores[2])>(Scores[1]+Scores[3])) of = 0;

        cout << Players[0+of]->get_name() << " and " <<
        Players[2+of]->get_name() << " win the hand" << endl;
        if(order_up%2 == of && order_up!=-1){
            if(Scores[0+of]+Scores[2+of]==5){
                cout << "march!" << endl;
                scores[of]+=2;
            }else{
                 scores[of]+=1;
            }
        }else{
            cout << "euchred!" << endl;
            scores[of]+=2;
        }
        
    


    cout << Players[0]->get_name() << " and " <<
        Players[2]->get_name() << " have " << scores[0]<<" points" << endl;

    cout << Players[1]->get_name() << " and " <<
        Players[3]->get_name() << " have " << scores[1]<<" points" << endl << endl;
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
    int hand = 0;

    if(!f.is_open()) {
        string pack_filename = argv[1];
        cout << "Error opening " << pack_filename << endl;
        return 1; // return nonzero number
    }

    Pack pack(f);
    f.close();
    string s = argv[2];
    bool shuffle = s=="shuffle" ? true : false;
    //if(shuffle) pack.shuffle();
    int win_threshold =  atoi(argv[3]);
    
    

    
    hand = 0;
    int scores[2] = {0,0};
do{
    pack.reset();
    if(shuffle) pack.shuffle();
    createPlayers(Players, argv);
    deal(pack, Players, dealer);
    cout << "Hand " << hand << endl;
    int order_up = makeTrump(Players, pack, dealer, trump, upcard);
    
    int leader = dealer+1;
    array<Card, 4> trick = {};
    int trick_wins[4] = {0,0,0,0};
    
    
    for(int i = 0; i < 5; ++i){
        trick = {};
        //cout << "test lead " << Players[(leader)%4]->get_name() << endl;
        
        for(int c = 0; c < 5-i; ++c) {
                /*
                cout << "player " << Players[(leader)%4]->get_name() << 
                "'s hand: [" << c << "] " << Players[(leader)%4]->card(c) << endl;
                */
            }
        
        trick[0] = Players[(leader)%4]->lead_card(trump);

        for(int p = 1; p < 4; ++p){
            
            for(int c = 0; c < 5-i; ++c) {
                /*
                cout << "player " << Players[(leader+p)%4]->get_name() << 
                "'s hand: [" << c << "] " << Players[(leader+p)%4]->card(c) << endl;
                */
                
            }
            trick[p] = Players[(leader+p)%4]->play_card(trick[0],trump);
            
            
            
            //cout << "test play " << (leader+p)%4 << endl;
        }
        
       // for(int v = 0; v < 4; ++v) {
        //cout << "hand: [" << v << "] " << trick[v] << endl;

      //  }
        //cout <<"best index: " << index_of_highest_value_card(trick,trump,trick[0]);

        cout << Players[(index_of_highest_value_card(trick,trump,trick[0])+leader)%4]->get_name()
            << " takes the trick" << endl << endl;
        leader = (index_of_highest_value_card(trick,trump,trick[0])+leader)%4;
        trick_wins[leader]++;
    }
        determine_winners(Players,trick_wins,order_up,scores);

        dealer = (dealer+1)%4;
        hand++;
}while(scores[1]<win_threshold && scores[0]<win_threshold);

int of = 1;
if(scores[1]<win_threshold) of = 0;
cout << Players[0+of]->get_name() << " and " <<
        Players[2+of]->get_name() << " win!" << endl;
  





    for(int i = 0; i<4; i++) delete Players[i];
    
    return 0;
}