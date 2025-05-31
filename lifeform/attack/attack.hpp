#include <string>
#include <vector>

class Attack {


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
            const int boost,
            const int turn
        );
    


    const std::string name;
    const int lv_requirement;
    const std::vector<std::string> class_requirement;
    const std::string grade;
    const std::string description;
    const std::string target_spell_zone;
    const std::string& attribute;
    const std::string& type;
    const int effect;
    const int boost;
    const int turn;


};