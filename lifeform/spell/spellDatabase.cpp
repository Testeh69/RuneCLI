#include "spellDatabase.hpp"

//Databse spell




std::unordered_map<std::string, std::array<std::shared_ptr<Spell>, 4>> dataBaseSpell;




//SOulweaver

Attack mind_spike(
    "Mind Spike",
    1,
    {"Soulweaver"},
    "B",
    "Un pic mental qui perce la conscience ennemie, infligeant des dégâts psioniques et perturbant la concentration.",
    "Single Target",
    "Magical",
    "Spirit",
    30,
    1,
    "life"
);


Support soul_heal(
    "Soul Heal",
    1,
    {"Soulweaver"},
    "A",
    "Soigne les pv grâce à la magie de l'âme.",
    "Single Ally",
    "Magical",
    "Spirit",
    20,  // boost régénération ou protection
    4,
    "life"
);

//Chronoblade


Attack chrono_slash(
    "Chrono Slash",
    1,
    {"Chronoblade"},
    "B",
    "A blade strike that fractures time around the enemy, dealing damage and delaying their next action.",
    "Single Target",
    "Physical",
    "Time",
    40,        // direct damage
    1,
    "life"          // 1 turn delay effect
);


Support time_surge(
    "Time Surge",
    1,
    {"Chronoblade"},
    "A",
    "Accelerates an ally’s perception and reaction, allowing them to act twice as fast for a short time.",
    "Single Ally",
    "Magical",
    "Time",
    2.0f,      // 2x speed
    2,
    "vitesse"
);



//Gravemind


Attack soul_rend(
    "Soul Rend",
    1,
    {"Gravemind"},
    "A",
    "Rips a fragment of the target's soul, causing damage over time and reducing vitality.",
    "Single Target",
    "Magical",
    "Dark",
    25.5f,     // damage over time effect
    3,
    "life"          // lasts for 3 turns
);


Support veil_of_oblivion(
    "Veil of Oblivion",
    1,
    {"Gravemind"},
    "S",
    "Shrouds an ally in necrotic mist, making them harder to detect and partially immune to mental effects.",
    "Single Ally",
    "Magical",
    "Dark",
    0.75f,     // 25% resistance boost
    4,
    "defense"          
);

//Luminary

Attack radiant_flare(
    "Radiant Flare",
    1,
    {"Luminary"},
    "B",
    "Une explosion de lumière pure qui brûle les ennemis et peut aveugler temporairement.",
    "Area of Effect",
    "Magical",
    "Light",
    35.5f,
    0,
    "life"
);

Support blessing_of_dawn(
    "Blessing of Dawn",
    1,
    {"Luminary"},
    "A",
    "Bénit un allié avec la lumière de l'aube, augmentant sa défense et sa résistance aux ténèbres.",
    "Single Ally",
    "Magical",
    "Light",
    1.25f,  // boost défense 25%
    3,
    "life"

);



//Goblin

Attack sneaky_stab(
    "Sneaky Stab",
    1,
    {"Goblin"},
    "C",
    "Une attaque rapide et sournoise qui inflige des dégâts physiques en exploitant la surprise.",
    "Single Target",
    "Physical",
    "None",
    20,
    0,
    "life"
);

Support tricksters_guile(
    "Trickster's Guile",
    1,
    {"Goblin"},
    "B",
    "Augmente l'agilité et la chance de l'allié, améliorant les chances de critique et d'esquive.",
    "Single Ally",
    "Magical",
    "None",
    1.4f,  // 40% boost agilité/chance
    2,
    "agility"
);



//

void loadDataSpell(const std::string& job) {
    if (job == "Soulweaver") {
        dataBaseSpell["Soulweaver"] = {
            std::make_shared<Attack>(mind_spike),
            std::make_shared<Support>(soul_heal),
            nullptr,
            nullptr
        };
    } else if (job == "Chronoblade") {
        dataBaseSpell["Chronoblade"] = {
            std::make_shared<Attack>(chrono_slash),
            std::make_shared<Support>(time_surge),
            nullptr,
            nullptr
        };
    } else if (job == "Gravemind") {
        dataBaseSpell["Gravemind"] = {
            std::make_shared<Attack>(soul_rend),
            std::make_shared<Support>(veil_of_oblivion),
            nullptr,
            nullptr
        };
    } else if (job == "Luminary") {
        dataBaseSpell["Luminary"] = {
            std::make_shared<Attack>(radiant_flare),
            std::make_shared<Support>(blessing_of_dawn),
            nullptr,
            nullptr
        };
    } else if (job == "Goblin") {
        dataBaseSpell["Goblin"] = {
            std::make_shared<Attack>(sneaky_stab),
            std::make_shared<Support>(tricksters_guile),
            nullptr,
            nullptr
        };
    } 
}
