#include "fight.hpp"
#include <queue>





std::queue<IdFight> makeTurnFightQueue (Player& character, Monster& monster){
    int vitesse_character = character.vitesse;
    int vitesse_monster = monster.vitesse;
    std::queue<IdFight> fight_queue;
    if (vitesse_monster <= vitesse_character){
        while (vitesse_monster <vitesse_character){
            fight_queue.push(IdFight::Player);
            vitesse_character -= vitesse_monster;
        }
        fight_queue.push(IdFight::Monster);
    }
    else{
        while (vitesse_monster > vitesse_character){
            fight_queue.push(IdFight::Monster);
            vitesse_monster -= vitesse_character;
        }
        fight_queue.push(IdFight::Player);
    }
    return fight_queue;
}





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
    int choice_player;
    while (personnage.status_life && monstre.status_life){
        personnage.displayData();
        monstre.displayData(); 
        std::queue<IdFight> turn_fight_queue = makeTurnFightQueue(personnage, monstre);
        IdFight turn_character;
        while (!turn_fight_queue.empty()){
            turn_character = turn_fight_queue.front();
            turn_fight_queue.pop();
            switch (turn_character)
            {
            case IdFight::Player:
                choice_player = menuFight();
                switch (choice_player)
                {
                case 1:
                    personnage.attack(monstre);
                
                case 2:
                    output_fight = 2;
                    break;
                default:
                    break;
                }
            
            case IdFight::Monster:
                monstre.attack(personnage);
            default:
                break;
            }
            if (personnage.life <= 0) {
                output_fight = 0;
            }
            else if (monstre.life <= 0){
                output_fight = 1;
            }

        }
    }
    return output_fight;
    

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
        4   
    );
    int result = fight(player, monster);
    FightResult fightresult = static_cast<FightResult>(result);
    displayFightResult(fightresult);
}