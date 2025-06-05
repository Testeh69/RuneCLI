#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <algorithm>
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

    std::array<std::string,4> slot_attack;
    

    void attack(LifeForm& target);

    void displayData();
};

class Player : public LifeForm {
public:
    Player(int life, int att,int mag_pow, int mag_def, int def,int agility, int vit);


    void setJob(std::string job);

    void displayJob();


    void menuAttack ();



private:
    int money = 0;
    std::string job = "Jobless";
    int lv = 1;
    int exp_gauge = 100;
    int exp_init = 0;
    std::unordered_map<std::string,std::shared_ptr<Spell>> slot_attack;

    //backpack -> Hashmap<Object>
    //equipement -> Hashmap<Equipement>
    
    
    void getAttackInSlot (std::string job);


};

class Monster : public LifeForm {
public:
    Monster(int life, int att,int mag_pow, int mag_def, int def,int agility, int vit);

private:
    int drop_money;
    int exp_drop;
    int lv;
    //maeterials_drop -> Hasmap<Object>
    //slot_attack -> Hashmap<Attack>
};


Player createCharacter();