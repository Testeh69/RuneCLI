#include "spell.hpp"




Spell::Spell(
    const std::string name,
    const int lv_requirement,
    const std::vector<std::string> class_requirement,
    const std::string grade,
    const std::string description,
    const std::string target_spell_zone,
    const std::string attribute,
    const std::string type,
    const std::string stat_targeted
):
    name(name),
    lv_requirement(lv_requirement),
    class_requirement(class_requirement),
    grade(grade),
    description(description),
    target_spell_zone(target_spell_zone),
    attribute(attribute),
    type(type),
    stat_targeted(stat_targeted)
{}



Attack::Attack(
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
): 
    Spell(name,lv_requirement,class_requirement,grade,description,target_spell_zone,attribute,type, stat_targeted),
    effect(effect),
    turn(turn)
{}


Support::Support(
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
    const std::string & stat_targeted
):
    Spell(name,lv_requirement,class_requirement,grade,description,target_spell_zone,attribute,type, stat_targeted),
    boost(boost),
    turn(turn)

{}