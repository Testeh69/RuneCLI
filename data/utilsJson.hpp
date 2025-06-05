#include <nlohmann/json.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <fstream>
#include <variant>
#include <vector>
#include "../lifeform/spell/spell.hpp"


#pragma once


class JsonLoader {


    public:

     std::shared_ptr<Spell> buildSpellObjectFromJsonFile(std::string& spell_name);



};