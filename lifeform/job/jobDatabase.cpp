#include "job.hpp"
#include "unordered_map"
#include "jobDatabase.hpp"



std::unordered_map<std::string, Job> job_database = {
    {"Soulweaver",Soulweaver},
    {"Chronoblade", Chronoblade},
    {"Gravemind", Gravemind},
    {"Luminary", Luminary}
};






Job Soulweaver = {
    "Soulweaver",
    -10,  
    -3,   
    +12,  
    +8,   
    -4,   
    0     
};



Job Chronoblade = {
    "Chronoblade",
    +5,
    +6,
    0,
    0,
    -2,
    +8
};


Job Gravemind = {
    "Gravemind",
    +20,
    -2,
    +6,
    +10,
    +4,
    -6
};

Job Luminary = {
    "Luminary",
    +5,
    -1,
    +5,
    +6,
    0,
    +4
};
