#pragma once
#include <string>
#include <vector>


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
    int vitesse;
    bool status_life;
    
    

    void attack(LifeForm& target);

    void display_data();
};

class Player : public LifeForm {
public:
    Player(int life, int att,int mag_pow, int mag_def, int def, int vit);


    void setJob(std::string job);

private:
    int money = 0;
    std::string job = "Jobless";
    
};

class Monster : public LifeForm {
public:
    Monster(int life, int att,int mag_pow, int mag_def, int def, int vit);

private:
    int dropMoney;
};


Player createCharacter();