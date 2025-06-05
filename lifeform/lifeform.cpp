#include "lifeform.hpp"




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



void LifeForm::displayData(){
    std::cout<< this->name<<std::endl;
    std::cout<< this->life<<"/"<<this->life_original<< " PV"<<std::endl;
    std::cout<<std::endl;
}