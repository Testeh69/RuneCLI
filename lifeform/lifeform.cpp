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



void LifeForm::getAttackInSlot(std::string new_job){
    std::array<std::shared_ptr<Spell>,4> array_slot = dataBaseSpell[new_job];
    int index = 1;
    for (const auto& spell_ptr:array_slot){
        if (spell_ptr != nullptr){
            std::cout<<spell_ptr->name<<std::endl;
            std::cout<<spell_ptr->description<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            this-> slot_attack[index] =  spell_ptr;
            index++;
        }
    }
}


void LifeForm::displayData(){
    std::cout<< this->name<<std::endl;
    std::cout<< this->life<<"/"<<this->life_original<< " PV"<<std::endl;
    std::cout<<std::endl;
}