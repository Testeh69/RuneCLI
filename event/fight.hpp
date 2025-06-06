#pragma once

#include "../lifeform/entities.hpp"
#include "../lifeform/spell/spell.hpp"
#include <iostream>
#include <queue>
#include <memory>
#include <vector>





struct effectSpellToken{
    int token;
    std::vector<std::shared_ptr<Spell>> spell_ptr;
};


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






void Arena(Player& player);