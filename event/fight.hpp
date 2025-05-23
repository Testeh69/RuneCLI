#include "../lifeform/player.hpp"
#include <iostream>

#pragma once



enum class FightResult{
    Defeat = 0,
    Victory = 1,
    Fled = 2,
    Unknown = 3,
};


int menuFight();

int fight (Player& personnage, Monster& monstre);


void displayFightResult(FightResult result);


void fightLoop(Player& player);