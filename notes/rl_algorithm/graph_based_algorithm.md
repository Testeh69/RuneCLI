
### Graph Thinking Q-NET (GTQN)


Le graph thinking Q-net (autre idée de nom) est une idée que j'ai eu basé sur plusieurs principes ou inspiration:

    - Les chemins de pensée (un peu comme les graphs)
    - Le Q-learning (policy greedy)
    - Une méthode de rémanance (poids au graphs, -1 si c'est lien sont pas utilisées, + 1 si les liens sont utilisées, si ils tombent  à 0 ils disparaissent)


GOAL:
    - l'objectif de cette agent n'est non pas de l'entrainer sur un env mais plutot de lui donner des idées de raisonnement partiel sur son env qu'il pourra utiliser lors de son application et update ses poids.

    """ Il doit être self learner """

PSEUDO-CODE


    INITIAL_STATE = S0
    FINAL_STATE = Sf
    MAX_REMANENCE = 10
    GraphThinking = {}
    EPOCHS = 100
    DEPTH = 6

    def getState(action, current_state):
        # Génère un nouvel état à partir de l’action et de l’état courant
        return next_state

    def calculateReward(state):
        # Reward basé sur la distance entre state et FINAL_STATE
        return -norm(state - FINAL_STATE)

    def loadActions(state):
        # Renvoie une liste d’actions possibles à partir de cet état
        return actions

    def takeAction(state, action):
        return getState(action, state)


    FUNCTION : 
    for epoch in range(EPOCHS):
        current_state = INITIAL_STATE
        
        for step in range(DEPTH):
            actions = loadActions(current_state)
            result = {}

            for action in actions:
                next_state = takeAction(current_state, action)
                reward = calculateReward(next_state)
                key = (current_state, action)
                
                # Met à jour ou crée la transition dans le graphe
                if key not in GraphThinking:
                    GraphThinking[key] = {
                        "next_state": next_state,
                        "q_value": reward,
                        "remanence": MAX_REMANENCE
                    }
                else:
                    GraphThinking[key]["q_value"] = max(GraphThinking[key]["q_value"], reward)
                    GraphThinking[key]["remanence"] += 1
            
            # Choix greedy
            best_action = max(actions, key=lambda a: GraphThinking.get((current_state, a), {"q_value": -float('inf')})["q_value"])
            current_state = takeAction(current_state, best_action)

        # Rémanence decay
        for key in list(GraphThinking.keys()):
            GraphThinking[key]["remanence"] -= 1
            if GraphThinking[key]["remanence"] <= 0:
                del GraphThinking[key]

                        




