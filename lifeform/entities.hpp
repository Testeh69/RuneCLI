
#pragma once




#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <algorithm>
#include "spell/spellDatabase.hpp"
#include "lifeform.hpp"
#include "job/jobDatabase.hpp"
#include "../data/utilsJson.hpp"




class Player : public LifeForm {
public:
    Player(int life, int att,int mag_pow, int mag_def, int def,int agility, int vit);


    void setJob(std::string new_job);

    void displayJob();


    int attack(LifeForm& monstre, std::shared_ptr<Spell> spell_ptr);

    int menuAttack ();
    std::shared_ptr<Spell> getAttack (int index_attack);




private:
    int money = 0;
    std::string job = "Jobless";
    int lv = 1;
    int exp_gauge = 100;
    int exp_init = 0;

    //backpack -> Hashmap<Object>
    //equipement -> Hashmap<Equipement>
    
    

    void displayAttack ();


    void displayMenu();


};



class Monster : public LifeForm {
public:
    Monster(std::string& name, int life, int att,int mag_pow, int mag_def, int def,int agility, int vit);

private:
    std::string job;
    int drop_money;
    int exp_drop;
    int lv;
    //maeterials_drop -> Hasmap<Object>
};


Player createCharacter();