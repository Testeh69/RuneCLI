#include "utilsJson.hpp"







using json = nlohmann::json;


std::unique_ptr<Spell> buildSpellObjectFromJsonFile(const std::string& path_json_file, const std::string& spell_id) {
    std::ifstream ifs(path_json_file);
    if (!ifs.is_open()) {
        throw std::runtime_error("Impossible d'ouvrir le fichier JSON");
    }

    json j;
    ifs >> j;

    for (const auto& spell_json : j) {
        if (spell_json.contains("id") && spell_json["id"] == spell_id) {
            std::string type = spell_json["type"].get<std::string>();

            std::string name = spell_json["name"].get<std::string>();
            int lv = spell_json["lv_requirement"].get<int>();
            std::vector<std::string> class_req = spell_json["class_requirement"].get<std::vector<std::string>>();
            std::string grade = spell_json["grade"].get<std::string>();
            std::string desc = spell_json["description"].get<std::string>();
            std::string zone = spell_json["target_spell_zone"].get<std::string>();
            std::string attr = spell_json["attribute"].get<std::string>();
            int turn = spell_json["turn"].get<int>();
            std::string stat_targeted = spell_json["stat_targeted"].get<std::string>();
            if (type == "Attack") {
                std::string attack_type = spell_json["attack_type"].get<std::string>();
                std::variant<int,float> effect;
                if (spell_json["effect"].is_number_float()) {
                    effect = spell_json["effect"].get<float>();
                } else {
                    effect = spell_json["effect"].get<int>();
                }
                return std::make_unique<Attack>(
                    name, lv, class_req, grade, desc, zone, attr, attack_type, effect, turn, stat_targeted
                );
            } else if (type == "Support") {
                std::string support_type = spell_json["support_type"].get<std::string>();
                std::variant<int,float> boost;
                if (spell_json["boost"].is_number_float()) {
                    boost = spell_json["boost"].get<float>();
                } else {
                    boost = spell_json["boost"].get<int>();
                }
                return std::make_unique<Support>(
                    name, lv, class_req, grade, desc, zone, attr, support_type, boost, turn, stat_targeted
                );
            } else {
                throw std::runtime_error("Type de sort inconnu : " + type);
            }
        }
    }

    throw std::runtime_error("Sort avec l'id '" + spell_id + "' non trouvé dans le fichier JSON");
}
