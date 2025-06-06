#include "entities.hpp"





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
    loadDataSpell(new_job);
    getAttackInSlot(new_job);
}





void Player::displayJob(){
    std::cout<<"Vous avez choisie le job suivant ->"<<this->job<<std::endl;
    std::cout<<std::endl;
}


void Player::displayAttack(){
    int index_action = 1;
    for (const auto& attack_name : this->slot_attack){
        std::cout<<index_action<<" - ";
        std::cout<<slot_attack[attack_name.first]->name<<std::endl;
        std::cout<<slot_attack[attack_name.first]->description<<std::endl;
        index_action++;
    }
}

void Player::displayMenu(){
    displayAttack();
    std::cout<<"5 - Retour"<<std::endl;
}

int Player::menuAttack(){
    displayMenu();
    std::cout<<"Choissisez l'action à entreprendre -> ";
    int input_player;
    std::cin>>input_player;
    return input_player;
}


std::shared_ptr<Spell> Player::getAttack(int index_attack){
    std::shared_ptr<Spell> spell_ptr_selected = this->slot_attack[index_attack];
    return spell_ptr_selected;
}

int Player::attack(LifeForm& monstre, std::shared_ptr<Spell> spell_ptr){
    std::string spell_name = spell_ptr->name;
    return 1;
    
}






Monster::Monster(std::string& name ,int life, int att,int mag_pow, int mag_def, int def,int agility, int vit){
    this->name = name;
    this->job = name;
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
    loadDataSpell(this->job);
    getAttackInSlot(this->job);
  
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