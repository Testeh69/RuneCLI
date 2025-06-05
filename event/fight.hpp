#include "../lifeform/entities.hpp"
#include <iostream>
#include <queue>


#pragma once






enum class FightResult{
    Defeat = 0,
    Victory = 1,
    Fled = 2,
    Unknown = 3,
};


enum class IdFight{
    Player = 0,
    Monster = 1,
};



class FightOneVsOne{


    public:
    FightOneVsOne(Player& personnage , Monster& Monstre);

    int fightLoop();



    private:
    
    void displayInitDataFight();
    void menuFight();
    void makeTurnFightQueue ();
    void displayFightResult(FightResult result); 
    
    std::queue<IdFight> fight_queue;
    Player& personnage;
    Monster& monstre;
    int choice_action;



};






void fightLoop(Player& player);