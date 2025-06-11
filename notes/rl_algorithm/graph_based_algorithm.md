
###  Graph Thinking Q-NET (GTQN)



#### 1) Introduction

Le graph thinking Q-net (autre idée de nom) est une idée que j'ai eu basé sur plusieurs principes ou inspiration:

    - Les chemins de pensée (un peu comme les graphs)
    - Le Q-learning (policy greedy)
    - Une méthode de rémanance (poids au graphs, -1 si c'est lien sont pas utilisées, + 1 si les liens sont utilisées, si ils tombent  à 0 ils disparaissent)


#### 2) GOAL:

    - l'objectif de cette agent n'est non pas de l'entrainer sur un env mais plutot de lui donner des idées de raisonnement partiel sur son env qu'il pourra utiliser lors de son application et update ses poids.

« Apprend et évolue par lui-même, sans supervision externe »

#### 📐 3) Métrique – Réflexion sur les critères de proximité

    Similarité cosinus : évalue l’orientation entre deux vecteurs.

    Norme euclidienne : mesure la distance réelle entre deux points.

    Rémanence : reflète la fréquence d’utilisation d’un chemin ; plus un chemin est utilisé, plus il est probablement utile.

🧪 Expérimentations

J’ai testé plusieurs combinaisons de métriques pour estimer la proximité entre deux points :

    La distance euclidienne seule

    La similarité cosinus seule

    Des combinaisons pondérées des deux

    Une formulation de type exp(cos_sim) * dist

🎯 Observations

    La distance euclidienne seule donne les résultats les plus cohérents, sans être biaisée par l’orientation des vecteurs.

    Avec des formules impliquant la similarité cosinus, on peut se retrouver avec des situations absurdes, comme considérer que (-6, -6) est plus proche de (6, 6) que (5, 6), simplement parce qu’ils pointent dans la même direction.

    La direction introduite par le cosinus perturbe trop l’ordre de proximité réel.

⚠️ Limite actuelle

La distance euclidienne ne prend pas en compte la rémanence. Or, cette notion est importante :

    Un chemin souvent emprunté est probablement plus utile ou plus fiable.

Il reste donc à explorer comment intégrer ce facteur dans la métrique finale.
 A voir


#### 4) PSEUDO-CODE

    ALTERNE ENTRE UN A* ou autre algorithme de path finding et une politique greedy

    Je définis un état initial So
    Je définis un état final Sf
    Je définis un état actuel Sa
    Je définis une constante rémanante_init = 5

    Sa = So

    Je définis une list_choice_minimal
    Je définis le graph de pensée graph
    Je définis un treshold


    TANT QUE Sa != Sf
        A*(Sa,Sf)
        -> Trouvé une solution:
            oui-> applique + (ajoute 1 points de remanentes pour chaque path ou l'on passe)
            non-> Voyage jusqu'aux points de fin 
                    Calcule la metrique
                    Ajout a la list_choice_minimal
                    ->Si il y a des chemins non explorées:
                        Pour tous les chemins non explorées
                            Snexp = step(action,Sa)
                            dist_eucl(snexp)
                            Ajout a la list_choice_minimal
                    next_step = argmin de list_choice_minimal
                    si next_step est dans graph[Sa]:
                        Oui-> ajoute une remanente +2
                        Non-> ajoute graph[sa] = { {lieu: step(next_step,Sa), Remanente: remanente_init}}
                    Sa = step(next_step,Sa)
        Applique une remanentede - 1 a tous le graph
        Supprime les path dons les points ont une remanente inférieur à threshold

                            
            








                        




