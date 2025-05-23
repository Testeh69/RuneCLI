#pragma once
#include <string>
#include <vector>


class LifeForm {
public:
    int life;
    int life_original;
    int attaque;
    int defense;
    int vitesse;
    bool status_life;
    std::string status;
    std::string name;

    void attack(LifeForm& target);

    void display_data();
};

class Player : public LifeForm {
public:
    Player(int life, int att, int def, int vit);

private:
    int money;

    
};

class Monster : public LifeForm {
public:
    Monster(int life, int att, int def, int vit);

private:
    int dropMoney;
};


Player createCharacter();