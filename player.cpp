#include <string>

class LifeForm {

    public:
    int life;
    int attaque;
    int defense;
    int vitesse;
    std::string status;
    std::string name;

    void attack(LifeForm Target){
        Target.life = attaque - Target.defense;
    }

};


class Player: public LifeForm {

    public: 
    Player (int life, int att, int def, int vit){
        name = "Runah";
        status ="Player"; 
        life = life;
        attaque = att;
        defense = def;
        vitesse = vit;
    }
};



class Monster: public LifeForm {

    public: 
    Monster (int life, int att, int def, int vit){
        name = "goblin";
        status ="Monster"; 
        life = life;
        attaque = att;
        defense = def;
        vitesse = vit;
    }
};