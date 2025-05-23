#include "gameloop.hpp"



using namespace std;

int menu (){
    int input_user;
    cout<< "========RuneCLI===="<<endl;  
    cout<<"1-Arena"<<endl;
    cout<<"2-Exit" << endl;
    cout<<"Choice:";
    cin >> input_user;
    return input_user;
}


void gameLoop(){

    displayIntro();
    Player player = createCharacter();
    while(player.life > 0){
        int choice_player = menu();
        if (choice_player == 1){
            fightLoop(player);
        }
        else if  (choice_player == 2)
        {
           break;
        }
        
    }

}