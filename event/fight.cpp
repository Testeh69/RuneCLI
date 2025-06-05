#include "fight.hpp"








FightOneVsOne::FightOneVsOne(Player& personnage, Monster& monstre)
    : personnage(personnage), monstre(monstre) {}


void FightOneVsOne::menuFight(){
    int choice;
    std::cout<< "Your action : 1- Attaque  2- Bag 3- Fuir"<<std::endl;
    std::cin>> choice;
    this->choice_action = choice;
};






void FightOneVsOne::makeTurnFightQueue (){
    while (!this->fight_queue.empty()) {
        this->fight_queue.pop();
    }    
    int vitesse_character = this->personnage.vitesse;
    int vitesse_monster = this->monstre.vitesse;
    if (vitesse_monster <= vitesse_character){
        while (vitesse_monster <vitesse_character){
            this->fight_queue.push(IdFight::Player);
            vitesse_character -= vitesse_monster;
        }
        this->fight_queue.push(IdFight::Monster);
    }
    else{
        while (vitesse_monster > vitesse_character){
            this->fight_queue.push(IdFight::Monster);
            vitesse_monster -= vitesse_character;
        }
        this->fight_queue.push(IdFight::Player);
    }
};


void FightOneVsOne::displayInitDataFight(){
    std::cout<<std::endl;
    std::cout << this->personnage.name << " VS " <<  this->monstre.name<< std::endl;
    std::cout<<std::endl;

};






void FightOneVsOne::displayFightResult(FightResult result) {
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
        10,   
        4   
    );
    int result = fight(player, monster);
    FightResult fightresult = static_cast<FightResult>(result);
    displayFightResult(fightresult);
}