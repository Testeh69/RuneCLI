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


int FightOneVsOne::fightLoop(){
    this->displayInitDataFight();
    
    int turn = 1;
    while (this->personnage.life>0 && this->monstre.life> 0){
        std::cout<<"Tour: "<<turn<<std::endl;
        makeTurnFightQueue();
        while (!this->fight_queue.empty() && (this->personnage.life>0 && this->monstre.life> 0)){
            enum IdFight id = this->fight_queue.front();
            this->fight_queue.pop();
            switch(id){
                case IdFight::Player:
                    this->menuFight();
                    switch (this->choice_action){
                        case 1 :
                            //Fight menu
                            break;
                        case 2 :
                            //Bag menu
                            break;
                        case 3 :
                            //Fuir
                            break; 
                    }
                    break;
                case IdFight::Monster:
                    break;
            }

        };
        
        turn++;
        
        
    }
    return 0;
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



void Arena(Player& player){
        std::string name_monster = "Goblin";
        Monster goblin(name_monster, 30, 15, 2, 3, 8, 12, 10);
        FightOneVsOne fightArena(player, goblin);
        int result = fightArena.fightLoop();
        

}