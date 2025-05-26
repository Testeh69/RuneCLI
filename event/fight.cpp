#include "fight.hpp"






int menuFight(){
    int choice_action;
    std::cout<< "Your action : 1- Attaque 2- Fuir"<<std::endl;
    std::cin>> choice_action;
    return choice_action;
}


int fight (Player& personnage, Monster& monstre){
    std::cout << personnage.name << " VS " <<  monstre.name<< std::endl;
    std::cout<<std::endl;
    int output_fight;
    while (personnage.status_life && monstre.status_life){
        personnage.displayData();
        monstre.displayData(); 
        if (personnage.vitesse > monstre.vitesse){
            int player_action = menuFight();
            if (player_action == 1){
                personnage.attack(monstre);
            }
            else if (player_action == 2){
                output_fight = 2;
                break;
            }
            if (monstre.status_life){
                monstre.attack(personnage);
           }
         }
         else{
            monstre.attack(personnage);
            if (personnage.status_life){
                int player_action = menuFight();
                if (player_action == 1){
                    personnage.attack(monstre);
                }
                else if (player_action == 2){
                    output_fight = 2;
                    break;
                }
            }
         }
    }

    if (personnage.life == 0){
        output_fight = 0;
        return output_fight;
    }
    else if (monstre.life == 0) {
        output_fight = 1;
        return output_fight;
    }
    else {
        return output_fight;
    }

} 




void displayFightResult(FightResult result) {
    switch (result) {
        case FightResult::Defeat:
            std::cout << "\n💀 You are dead!\n";
            break;
        case FightResult::Victory:
            std::cout << "\n🏆 You won the fight!\n";
            break;
        case FightResult::Fled:
            std::cout << "\n🏃‍♂️ You fled the fight.\n";
            break;
        default:
            std::cout << "\n❓ Unknown fight result.\n";
            break;
    }
}



void fightLoop(Player& player){
    Monster monster = Monster(
        30, 
        12,  
        6,   
        4,   
        8,   
        18   
    );
    int result = fight(player, monster);
    FightResult fightresult = static_cast<FightResult>(result);
    displayFightResult(fightresult);
}