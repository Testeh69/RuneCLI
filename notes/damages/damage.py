import numpy as np
import matplotlib.pyplot as plt

# Constantes
raw_power_spell = np.arange(0, 100, 2)
elemental_resistances = np.arange(0, 100, 20)  # Plus espacé pour lisibilité
attack_power = 100
defense_power = 50
agility = 30
ennemi_life = 150

# Formule de dommage simple
def compute_damage(raw_power_spell, elemental_resistance, attack_power=attack_power, defense_power=defense_power):
    raw = raw_power_spell + (attack_power - defense_power)
    damage = raw * (1 - elemental_resistance / 100)
    return damage




# Formule de dommage proportionnel à la vie
def compute_float_damage(raw_power_spell, elemental_resistance, attack_power=attack_power, defense_power=defense_power, life=ennemi_life):
    raw = (raw_power_spell / 100 * life) + (attack_power - defense_power)
    damage = raw * (1 - elemental_resistance / 100)
    return damage 


def loi_normale(x, mu=agility, sigma=1):
    """Calcul de la loi normale."""
    return (1 / (sigma * np.sqrt(2 * np.pi))) * np.exp(-0.5 * ((x - mu) / sigma) ** 2)


def compute_damage_with_agility(raw_power_spell, elemental_resistance, agility=agility):
    """Calcul des dommages en tenant compte de l'agilité."""
    # On suppose que l'agilité affecte la puissance d'attaque
    attack_power_with_agility = attack_power * (1 - loi_normale(agility))
    raw = raw_power_spell + (attack_power_with_agility - defense_power)
    damage = raw * (1 - elemental_resistance / 100)
    return damage



# Affichage des deux courbes
def plot_damage_curve():
    plt.figure(figsize=(12, 7))
    
    for res in elemental_resistances:
        # Courbe 1 : dommages fixes
        fixed_damage = compute_damage(raw_power_spell, elemental_resistance=res)
        hp_fixed = np.clip(ennemi_life - fixed_damage, 0, ennemi_life)
        plt.plot(raw_power_spell, hp_fixed, linestyle='-', label=f'Fix {res}%')

        # Courbe 2 : dommages proportionnels
        float_damage = compute_float_damage(raw_power_spell, elemental_resistance=res)
        hp_float = np.clip(ennemi_life - float_damage, 0, ennemi_life)
        plt.plot(raw_power_spell, hp_float, linestyle='--', label=f'Float {res}%')

    plt.title('Remaining HP vs Raw Power Spell')
    plt.xlabel('Raw Power Spell')
    plt.ylabel('Remaining HP (Monster)')
    plt.grid(True)
    plt.legend(title="Type & Elemental Resistance")
    plt.tight_layout()


def plot_damage_with_agility():
    plt.figure(figsize=(12, 7))
    
    for res in elemental_resistances:
        # Courbe avec agilité
        damage_with_agility = compute_damage_with_agility(raw_power_spell, elemental_resistance=res)
        hp_with_agility = np.clip(ennemi_life - damage_with_agility, 0, ennemi_life)
        plt.plot(raw_power_spell, hp_with_agility, linestyle='-', label=f'Fix {res}%')

    plt.title('Remaining HP vs Raw Power Spell with Agility')
    plt.xlabel('Raw Power Spell')
    plt.ylabel('Remaining HP (Monster)')
    plt.grid(True)
    plt.legend(title="Elemental Resistance")
    plt.tight_layout()


#plot_damage_curve()
plot_damage_with_agility()
plt.show()


