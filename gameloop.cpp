#include "gameloop.hpp"



int menu (){
    int input_user;
    std::cout<< "========RuneCLI===="<<std::endl;  
    std::cout<<"1-Arena"<<std::endl;
    std::cout<<"2-Shop" <<std::endl;
    std::cout<<"3-Exit" <<std::endl;
    std::cout<<"Choice:";
    std::cin >> input_user;
    return input_user;
}



void chooseJob(Player& character,std::unordered_map<std::string,Job>& job_list){
    std::unordered_map<int,std::string> link_job_choice = displayJob(job_list);
    int choice_job;
    std::cin>>choice_job;
    std::string job_character = link_job_choice[choice_job];
    character.setJob(job_character);
}


void gameLoop(){

    displayIntro();
    Player player = createCharacter();
    chooseJob(player, job_database);
    player.displayJob();
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