#pragma once

#include <string>
#include <vector>
#include <variant>


// Je pense qu'il faut la diviser en une classe parente spell
// et puis deux classes enfants attack, soutien




class Spell {

    public:

    Spell(
    const std::string name,
    const int lv_requirement,
    const std::vector<std::string> class_requirement,
    const std::string grade,
    const std::string description,
    const std::string target_spell_zone,
    const std::string attribute,
    const std::string type,
    const std::string stat_targeted
    );

    const std::string name; // nom du sort
    const int lv_requirement; // lv requirement for the attack
    const std::vector<std::string> class_requirement; // class requirement for the attack
    const std::string grade; // grade of the attack
    const std::string description; // description of the effect of the attack
    const std::string target_spell_zone; // Area target of the attack
    const std::string attribute; // Physique or magical
    const std::string type; // fire, water, none, etc ...
    const std::string stat_targeted; // stat the skills targeted


};



class Attack: public Spell {


    public:
    Attack(
            const std::string& name,
            const int lv_requirement,
            const std::vector<std::string>& class_requirement,
            const std::string& grade,
            const std::string& description,
            const std::string& target_spell_zone,
            const std::string& attribute,
            const std::string& type,
            const std::variant<int,float> effect,
            const int turn,
            const std::string& stat_targeted
        );
    



    const std::variant<int,float> effect;
    const int turn;


};


class Support: public Spell{
    public:
    Support(
            const std::string& name,
            const int lv_requirement,
            const std::vector<std::string>& class_requirement,
            const std::string& grade,
            const std::string& description,
            const std::string& target_spell_zone,
            const std::string& attribute,
            const std::string& type,
            const std::variant<int,float> boost,
            const int turn,
            const std::string& stat_targeted

        );
    



    const std::variant<int,float> boost;
    const int turn;



};