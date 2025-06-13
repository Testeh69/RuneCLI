
🧠 GTQN — Graph Thinking Q-NET

    Un algorithme inspiré du Q-learning et des systèmes de pensée graphiques, basé sur une idée simple mais expérimentale, qui reste à justifier mathématiquement ou à raffiner.

1. ✨ Introduction

Le Graph Thinking Q-NET (GTQN) est un prototype d’algorithme d’apprentissage hybride combinant :

    🧭 Représentation graphe des pensées / transitions,

    🔁 Q-learning sans table ni réseau de neurones,

    🧠 Rémanence : une forme de mémoire pondérée des chemins explorés.

Il s’inspire de plusieurs principes :

    Les “chemins de pensée” représentés comme des arcs pondérés,

    La politique gloutonne des algorithmes RL,

    La mise à jour des “poids de pensée” via une dynamique de décroissance (decay) et de renforcement (reinforcement),

    Une boucle agent-environnement librement inspirée du paradigme RL :

        Observer l’état actuel,

        Agir via une politique,

        Observer les conséquences,

        Ajuster les poids du graphe.

2. 🎯 Objectif

L’objectif de GTQN n’est pas d’entraîner une politique globale sur l’environnement via gradient ou Q-table.

C’est de donner à un agent une structure de raisonnement partielle, capable d’exploiter son historique de navigation dans un graphe dynamique et pondéré.

En d’autres termes :

    “Un agent qui apprend par lui-même, sans supervision externe, en construisant une carte mentale pondérée de l’espace.”

3. 📐 Métriques et Proximité

GTQN explore plusieurs façons de mesurer la “proximité” entre états, essentielles à la navigation :

    Distance euclidienne : simple et robuste.

    Similarité cosinus : capturant les directions mais produisant des résultats incohérents (ex : (-6, -6) vu comme proche de (6, 6)).

    Formules combinées :

        exp(cos_sim) * dist : souvent instable.

        Pondérations linéaires : peu efficaces.

🔎 Observation-clé :

    La distance euclidienne seule reste la plus fiable pour guider les transitions, sans perturber l’ordre naturel de proximité.

📌 Limite actuelle :

La distance euclidienne ignore la rémanence : or, un chemin souvent emprunté est potentiellement plus fiable.
👉 Il reste à inventer une formule mixte : Proximité = f(dist, rémanence).
4. ⚠️ Problèmes rencontrés

    📉 Non-convergence : les formules heuristiques sont trop instables.

    🌱 Explosion du graphe :

        Trop de noeuds générés.

        Rémanence insuffisamment punitive.

🧩 Solutions envisagées :

    Limite stricte du nombre de noeuds.

    Decay stochastique des poids.

    Seuillage : suppression des arcs dont la rémanence < threshold.

5. 🧠 Conclusion critique

    En l’état, GTQN est dominé par des algorithmes plus simples.

Alternatives plus efficaces :

    Politique gloutonne (greedy) + heatmap d’exploration.

    Q-learning tabulaire ou Deep RL.

    Graph-based search (A*) avec métriques heuristiques.

➡️ GTQN n’apporte pas de bénéfice clair comparé à ces approches.
Mais ses concepts peuvent être réutilisés comme modules :

    Pour l’explicabilité (visualiser les chemins empruntés),

    Pour des comportements semi-scriptés (IA NPC avec mémoire adaptative),

    Pour un moteur narratif ou de décision “psychologique”.

