#include <iostream>
#include <string>
#include "player.hpp"
#include "job/job.hpp"
#include "job/jobDatabase.hpp"



// LIFEFORM method

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


// PLayer method


Player::Player(int life, int att,int mag_pow, int mag_def, int def,int agility, int vit) {
    this->name = "Runah";
    this->status = "Player";
    this->life_original = life;
    this->life = life;
    this->attaque = att;
    this->magical_power = mag_pow;
    this->defense = def;
    this->magical_defense = mag_def;
    this->vitesse = vit;
    this->status_life = true;
    this->agility = agility;
}


void Player::setJob(std::string new_job){
    this->job = new_job;
    Job define_job = job_database[new_job];
    this->life_original += define_job.life;
    this->life  += define_job.life;
    this->attaque += define_job.attaque;
    this->magical_power += define_job.magical_power;
    this->magical_defense += define_job.magical_defense;
    this->defense += define_job.defense;
    this->vitesse += define_job.vitesse;
    getAttackInSlot(new_job);
}


void Player::getAttackInSlot(std::string new_job){
    std::array<std::shared_ptr<Spell>,4> array_slot = dataBaseSpell[new_job];

    for (const auto& spell_ptr:array_slot){
        if (spell_ptr != nullptr){
            std::cout<<spell_ptr->name<<std::endl;
            std::cout<<spell_ptr->description<<std::endl;
            std::cout<<std::endl;
            std::cout<<std::endl;
            this-> slot_attack[spell_ptr -> name] =  spell_ptr;
        }
    }
}


void Player::displayJob(){
    std::cout<<"Vous avez choisie le job suivant ->"<<this->job<<std::endl;
}


void Player::menuAttack(){

    std::cout<<"Choissisez l'action à entreprendre...";
}



// MOnster method


Monster::Monster(int life, int att,int mag_pow, int mag_def, int def,int agility, int vit){
    this->name = "Goblin";
    this->status = "Monster";
    this->life_original = life;
    this->life = life;
    this->attaque = att;
    this->magical_power = mag_pow;
    this->defense = def;
    this->magical_defense = mag_def;
    this->vitesse = vit;
    this->status_life = true;
    this->agility = agility;
    this->slot_attack[0] = sneaky_stab.name;
    this-> slot_attack[1] = tricksters_guile.name;
}





// Function
Player createCharacter(){
    Player player = Player(100,10,10,10,10,10,10);
    std::string username;
    std::cout<<"Enter your username"<<std::endl;
    std::cin>>username;
    std::cout<<std::endl;
    player.name = username;
    return player;
}