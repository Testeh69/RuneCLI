#include <iostream>
#include "event/fight.hpp"
#include  "lifeform/player.hpp"


using namespace std;

int menu (){
    int input_user;
    cout<< "Menu 1-Combat 2-Exit" << endl;
    cin >> input_user;
    return input_user;
}


int main() {
    Player player = Player(100, 10,8,13);

    while(player.life > 0){
        int choice_player = menu();
        if (choice_player == 1){
            Monster monster = Monster(30, 12, 6,12);
            int result = fight(player, monster);
            if ( result == 0){
                cout<<"You are dead!"<<endl;
                cout<<std::endl;

            }
            else if (result == 1){
                cout<<"You won !!!!!"<<endl;
                cout<<std::endl;
            }
            else if (result == 2){
                cout<<"You have fled the fight."<<endl;
                cout<<std::endl;

            }
        }
        else if  (choice_player == 2)
        {
           break;
        }
        
    }
 
    return 0;
}