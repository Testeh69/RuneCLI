# 🧠 Seeking Formula for Damage

Un document de recherche pour explorer, comparer et formuler différentes manières de calculer les **dégâts dans un système RPG**. On y introduit l'agilité comme facteur d'atténuation ou d'évasion des dégâts.

---

## 🧭 Plan

1. Introduction  
2. Hypothèses  
3. Formule sans agilité  
4. Formule avec agilité  
5. Conclusion  

---

## 1️⃣ Introduction

Dans tout jeu de rôle, le calcul des dégâts constitue le cœur du système de combat. Il doit à la fois :
- être **lisible et compréhensible** par le joueur,
- permettre une **progression équilibrée**,
- et refléter **différentes mécaniques** comme la puissance brute, la défense, la résistance élémentaire et l’agilité.

Ce document explore plusieurs approches, de la formule simple à des modèles plus complexes intégrant de la **probabilité via l'agilité**.

---

## 2️⃣ Hypothèses

Pour simplifier l'analyse, on adopte les hypothèses suivantes :

- **Puissance d'attaque (physique ou magique)** : valeur de base du personnage.
- **TYpe d'attaque** : On dispose de deux types d'attaques, les attaques dont les dégats sont fixes et les attaques dont les valeurs dépendent de la vie de l'ennemie.
- **Puissance du sort** : de 0 à 100.
- **Défense ennemie** : constante à 50.
- **Résistance élémentaire** : comprise entre 0 et 100%.
- **Agilité** : entre 0 (aucune esquive) et 100 (évasion maximale).
- La vie initiale de l'ennemi est fixée de **30** à **150 HP**.

---

## 3️⃣ Formule sans Agilité



Ma première réflexion de base était une formule de dommage n'incluant pas l'agilité.

Pourquoi : 

    - Plus simple  à modéliser que ce soit au niveau formule que au niveau programmation.

Cependant:
    - Dans les jeux notamment dans ceux des rpg, la notion d'esquive est souvent utilisé.


Ma première hypothèse était une formule simple.

damage = (power_spell+ (attaque - defense_ennemie)) * elemental_resistance/100


## 4 Formule avec Agilité



## Conclusion