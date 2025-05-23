#include <iostream>



void displayIntro() {
    std::cout << R"(
=====================================
     ██████╗  ██╗   ██╗███╗   ██╗███████╗ ██████╗██╗     ██╗
    ██╔══ ██║ ██║   ██║████╗  ██║██╔════╝██╔════╝██║     ██║
    ██║   ██║ ██║   ██║██╔██╗ ██║█████╗  ██║     ██║     ██║
    ██████ ═╝ ██║   ██║██║╚██╗██║██╔══╝  ██║     ██║     ██║
    ██   ██╔  ╚██████╔╝██║ ╚████║███████╗╚██████╗███████╗██║
               ╚═════╝ ╚═╝  ╚═══╝╚══════╝ ╚═════╝╚══════╝╚═╝

        Welcome to RuneCLI - The Command Line RPG!
=====================================

🌟 You are a lone warrior in a cursed land.
⚔️  Fight monsters in turn-based combat.
🎯 Train your stats, equip gear, survive the dungeon.
💾 Future: Classes, shops, loot, magic, save & load...

Type a number to choose your path, adventurer:
)";

    std::cout << std::endl;
}