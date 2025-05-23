#include "player.hpp"

void LifeForm::attack(LifeForm& target) {
    int damage = this->attaque - target.defense;
    if (damage < 0) damage = 0;
    target.life -= damage;
    if (target.life <= 0) {
        target.status_life = false;
    }
}

Player::Player(int life, int att, int def, int vit) {
    this->name = "Runah";
    this->status = "Player";
    this->life = life;
    this->attaque = att;
    this->defense = def;
    this->vitesse = vit;
    this->status_life = true;
}

Monster::Monster(int life, int att, int def, int vit) {
    this->name = "Goblin";
    this->status = "Monster";
    this->life = life;
    this->attaque = att;
    this->defense = def;
    this->vitesse = vit;
    this->status_life = true;
}