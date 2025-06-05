#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <algorithm>
#include "spell/spellDatabase.hpp"
#include "lifeform.hpp"




#pragma once


class Player : public LifeForm {
public:
    Player(int life, int att,int mag_pow, int mag_def, int def,int agility, int vit);


    void setJob(std::string job);

    void displayJob();


    int attack(LifeForm& monstre, std::shared_ptr<Spell> spell_ptr);

    int menuAttack ();



private:
    int money = 0;
    std::string job = "Jobless";
    int lv = 1;
    int exp_gauge = 100;
    int exp_init = 0;
    std::unordered_map<int,std::shared_ptr<Spell>> slot_attack;

    //backpack -> Hashmap<Object>
    //equipement -> Hashmap<Equipement>
    
    
    void getAttackInSlot (std::string job);

    void displayAttack ();

    std::shared_ptr<Spell> getAttack (int index_attack);

    void displayMenu();


};



class Monster : public LifeForm {
public:
    Monster(int life, int att,int mag_pow, int mag_def, int def,int agility, int vit);

private:
    int drop_money;
    int exp_drop;
    int lv;
    //maeterials_drop -> Hasmap<Object>
};


Player createCharacter();