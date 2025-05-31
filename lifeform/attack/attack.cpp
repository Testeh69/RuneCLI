#include "attack.hpp"






Attack::Attack(
    const std::string& name,
    int lv_requirement,
    const std::vector<std::string>& class_requirement,
    const std::string& grade,
    const std::string& description,
    const std::string& target_spell_zone,
    const std::string& attribute,
    const std::string& type,
    int effect,
    int boost,
    int turn
) : name(name),
    lv_requirement(lv_requirement),
    class_requirement(class_requirement),
    grade(grade),
    description(description),
    target_spell_zone(target_spell_zone),
    attribute(attribute),
    type(type),
    effect(effect),
    boost(boost),
    turn(turn)
{}