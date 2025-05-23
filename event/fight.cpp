#include "fight.hpp"



int fight (Player personnage, Monster monstre){
    std::cout << personnage.name << " VS" <<  monstre.name<< std::endl;
    while (personnage.life > 0 || monstre.life > 0){
         if (personnage.vitesse > monstre.vitesse){
            personnage.attack(monstre);
            monstre.attack(personnage);
         }
         else{
            personnage.attack(monstre);
            monstre.attack(personnage);
         }
    }

    if (personnage.life == 0){
        return 0;
    }
    else {
        return 1;
    }
} 