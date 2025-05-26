#include <iostream>
#include "event/fight.hpp"
#include  "lifeform/player.hpp"
#include "assets/dialog/intro.hpp"
#include "lifeform/job/job.hpp"
#include "lifeform/job/jobDatabase.hpp"
#include <unordered_map>
#include <string>





#pragma once



int menu();
void chooseJob(Player& character, std::unordered_map<std::string,Job>& job_list);
void gameLoop();