#include "fight.hpp"



int menu_fight(){
    int choice_action;
    std::cout<< "Your action : 1- Attaque 2- Fuir"<<std::endl;
    std::cin>> choice_action;
    return choice_action;
}


int fight (Player& personnage, Monster& monstre){
    std::cout << personnage.name << " VS " <<  monstre.name<< std::endl;
    int output_fight;
    while (personnage.status_life || monstre.status_life){
        personnage.display_data();
        monstre.display_data(); 
        if (personnage.vitesse > monstre.vitesse){
            int player_action = menu_fight();
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
                int player_action = menu_fight();
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