#include <string>
#include <vector>



// Je pense qu'il faut la diviser en une classe parente spell
// et puis deux classes enfants attack, soutien




class Spell {

    public:
    const std::string name;
    const int lv_requirement;
    const std::vector<std::string> class_requirement;
    const std::string grade;
    const std::string description;
    const std::string target_spell_zone;
    const std::string attribute;
    const std::string type;


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
            const int effect,
            const int turn
        );
    



    const int effect;
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
            const int boost,
            const int turn
        );
    



    const int boost;
    const int turn;



};