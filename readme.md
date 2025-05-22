# RuneCLI

A simple command-line RPG game written in C++.

## Features




## Features to add

    Game Setup & Main Loop

        Basic CLI input/output

        Main game loop for continuous play

    Player Character

        Define player stats (HP, MP, Attack, Defense)

        Simple player creation (name, class selection optional)

    Enemy Design

        Basic enemy struct/class with stats

        Random or fixed enemy encounters

    Combat System

        Turn-based combat

        Basic attack mechanics (player attacks enemy, enemy attacks player)

        Display health updates after attacks

    Victory and Defeat

        Check for player or enemy death

        End game or restart on death

Intermediate Features (Adding Depth)

    Inventory System

        Simple inventory to hold items (potions, weapons)

        Use items during combat or outside combat

    Experience & Leveling

        Gain experience from defeating enemies

        Level up system with stat increases

    Multiple Enemy Types

        Different enemy stats and abilities

        Randomized enemy encounters

    Basic Skill System

        Implement a few special skills/spells

        Mana or stamina cost for skills

    Save/Load Game

        Save player stats and inventory to a file

        Load game from file

Advanced Features (Complex Mechanics)

    Equipment System

        Weapons and armor affecting stats

        Equip/unequip system

    Status Effects

        Poison, stun, burn, paralysis with turn-based effects

    Quests and NPCs

        Simple quest system with objectives

        Dialogue system with NPCs

    Map Exploration

        Simple grid-based map or room system

        Movement commands (N/S/E/W)

    Multiple Party Members

        Add allies/companions with their own stats

        Control multiple characters in combat

Expert-Level Features (Polish & Complexity)

    Advanced AI for Enemies

        Enemies with tactics, choosing different attacks or retreat

    Randomly Generated Dungeons

        Procedural map/dungeon generation with different rooms/enemies

    Economy System

        Currency, shops, buying/selling items

    Complex Dialogue Trees

        Multiple dialogue options affecting story or quests

    Achievements and Stats Tracking

        Track playthrough stats, unlock achievements

## Requirements

- C++17 compatible compiler (e.g., g++)

## Building

Compile the source code using:

```bash
g++ main.cpp -o rpg