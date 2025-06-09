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

int Player::attack(LifeForm& target, std::shared_ptr<Spell> spell_ptr){
    //Retourne le nombre de tour que le sort va durer
    
    std::string spell_name = spell_ptr->name;
    auto stat_targeted = spell_ptr->stat_targeted;
    std::string type_spell = spell_ptr->type;
    std::string attribute_spell = spell_ptr->attribute;
    int damage = 0;
    int multiplier = 0;
    auto elemental_resistance = target.elemental_resistance[attribute_spell];
    
    //Attack spell calculation
  
    if (auto attack_spell = std::dynamic_pointer_cast<Attack>(spell_ptr)) {
        auto& effect = attack_spell->effect;
        int base_damage = 0;
        if (std::holds_alternative<float>(effect)) {
            float ratio = std::get<float>(effect);
            base_damage = static_cast<int>(ratio * target.life);
        } else if (std::holds_alternative<int>(effect)) {
            base_damage = std::get<int>(effect);
        }

        float raw_damage = static_cast<float>(base_damage);

        if (stat_targeted == "life") {
            if (type_spell == "Magical") {
                raw_damage += this->magical_power - target.magical_defense;
            } 
            else if (type_spell == "Physical") {
                raw_damage += this->attaque - target.defense;
            }

            raw_damage *= (elemental_resistance / 100.0f);

            int final_damage = std::max(0, static_cast<int>(raw_damage));
            target.life -= final_damage;
        }
    }
    //Support spell calculation
    else if (auto support_spell = std::dynamic_pointer_cast<Support>(spell_ptr)) {
        
    }
    else {
        std::cerr << "Unknown spell type!" << std::endl;
        return 0; // Return 0 if the spell type is unknown
    }
    return spell_ptr->turn;
    
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