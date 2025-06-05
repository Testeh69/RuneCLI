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

    void loopFight();




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


int fight (Player& personnage, Monster& monstre);


void displayFightResult(FightResult result);


void fightLoop(Player& player);