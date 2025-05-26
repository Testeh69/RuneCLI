#include <string>
#include "unordered_map"
#include <iostream>



struct Job {
    std::string job_name;
    int life;
    int attaque;
    int magical_power;
    int magical_defense;
    int defense;
    int vitesse;
};



std::unordered_map<int, std::string> displayJob(std::unordered_map<std::string,Job>& job_list){
    std::unordered_map<int, std::string> link_job_choice;

    int index = 1;
    std::cout<<"Choissisez votre job:"<<std::endl;
    for (const auto& paire :job_list){
        std::cout<<index <<"-"<< paire.first<<std::endl;
        link_job_choice.insert({index,paire.first});
        index++;
    }
    return link_job_choice;
}

