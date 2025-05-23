#include <iostream>

#include "player.hpp"

void LifeForm::attack(LifeForm& target) {
    int damage = this->attaque - target.defense;
    std::cout << this->name << " deals " << damage << " damage to " << target.name << std::endl;    std::cout<<std::endl;
    if (damage < 0) damage = 0;
    target.life -= damage;
    if (target.life <= 0) {
        target.status_life = false;
        std::cout << this -> name << " killed " << target.name<<std::endl;
    }
}



void LifeForm::display_data(){
    std::cout<< this->name<<std::endl;
    std::cout<< this->life<<"/"<<this->life_original<< " PV"<<std::endl;
    std::cout<<std::endl;

}


Player::Player(int life, int att, int def, int vit) {
    this->name = "Runah";
    this->status = "Player";
    this->life_original = life;
    this->life = life;
    this->attaque = att;
    this->defense = def;
    this->vitesse = vit;
    this->status_life = true;
}

Monster::Monster(int life, int att, int def, int vit) {
    this->name = "Goblin";
    this->status = "Monster";
    this->life_original = life;
    this->life = life;
    this->attaque = att;
    this->defense = def;
    this->vitesse = vit;
    this->status_life = true;
}