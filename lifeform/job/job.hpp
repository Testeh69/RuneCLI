#include <string>
#include <unordered_map>

#pragma once

struct Job {
    std::string job_name;
    int life;
    int attaque;
    int magical_power;
    int magical_defense;
    int defense;
    int vitesse;
};




std::unordered_map<int, std::string> displayJob(std::unordered_map<std::string,Job>& job_list);