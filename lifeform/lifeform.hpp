#pragma once


#include <unordered_map>
#include <string>
#include <array>
#include <iostream>
#include <memory>
#include "spell/spell.hpp"
#include "spell/spellDatabase.hpp"


class LifeForm {
public:
    std::string status;
    std::string name;
    int life;
    int life_original;
    int attaque;
    int magical_power;
    int magical_defense;  
    int defense;
    int agility;
    int vitesse;
    bool status_life;
    std::unordered_map<std::string, int> elemental_resistance = {
    {"fire", 0},
    {"ice", 0},
    {"water", 0},
    {"earth", 0},
    {"wind", 0},
    {"lightning", 0},
    {"light", 0},
    {"dark", 0},
    {"void", 0},
    {"time", 0},
    {"sound", 0},
    {"gravity", 0},
    {"ether", 0},
    {"dream", 0},
    {"chaos", 0},
    {"plasma", 0},
    {"toxic", 0},
    {"crystal", 0},
    {"spirit", 0}
    };

    std::unordered_map<int,std::shared_ptr<Spell>> slot_attack;
    

    void attack(LifeForm& target);

    void getAttackInSlot (std::string job);


    void displayData();
};