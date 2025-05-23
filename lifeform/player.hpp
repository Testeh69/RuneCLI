#pragma once
#include <string>

class LifeForm {
public:
    int life;
    int attaque;
    int defense;
    int vitesse;
    bool status_life;
    std::string status;
    std::string name;

    void attack(LifeForm& target);
};

class Player : public LifeForm {
public:
    Player(int life, int att, int def, int vit);
};

class Monster : public LifeForm {
public:
    Monster(int life, int att, int def, int vit);
};