import random
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import time

class Environment:
    def __init__(self, grid_size=5, start=(0, 0), goal=(4, 4)):
        self.grid_size = grid_size
        self.start = start
        self.goal = goal
        self.actions = ['UP', 'DOWN', 'LEFT', 'RIGHT']

    def move(self, state, action):
        x, y = state
        if action == 'UP':
            x = max(0, x - 1)
        elif action == 'DOWN':
            x = min(self.grid_size - 1, x + 1)
        elif action == 'LEFT':
            y = max(0, y - 1)
        elif action == 'RIGHT':
            y = min(self.grid_size - 1, y + 1)
        return (x, y)

    def calculate_reward(self, state):
        # Plus l'état est proche de l'objectif, meilleur est le reward (négatif car on minimise la distance)
        return -np.linalg.norm(np.array(state) - np.array(self.goal))


class GTQNAgent:
    def __init__(self, env: Environment, remanence_max=10, epsilon=0.2):
        self.env = env
        self.graph = {}  # {(state, action): {"next_state", "q_value", "remanence"}}
        self.remanence_max = remanence_max
        self.epsilon = epsilon

    def choose_action(self, state):
        if random.random() < self.epsilon:
            return random.choice(self.env.actions)
        best_q = float('-inf')
        best_action = random.choice(self.env.actions)
        for action in self.env.actions:
            key = (state, action)
            q = self.graph.get(key, {"q_value": -100})["q_value"]
            if q > best_q:
                best_q = q
                best_action = action
        return best_action

    def update(self, state, action, next_state, reward):
        key = (state, action)
        if key not in self.graph:
            self.graph[key] = {
                "next_state": next_state,
                "q_value": reward,
                "remanence": self.remanence_max
            }
        else:
            self.graph[key]["q_value"] = max(self.graph[key]["q_value"], reward)
            self.graph[key]["remanence"] = min(self.graph[key]["remanence"] + 1, self.remanence_max)

    def decay_remanence(self):
        for key in list(self.graph.keys()):
            self.graph[key]["remanence"] -= 1
            if self.graph[key]["remanence"] <= 0:
                del self.graph[key]

    def train(self, epochs=100, depth=10):
        for epoch in range(epochs):
            state = self.env.start
            for step in range(depth):
                action = self.choose_action(state)
                next_state = self.env.move(state, action)
                reward = self.env.calculate_reward(next_state)
                self.update(state, action, next_state, reward)
                state = next_state
                if state == self.env.goal:
                    break
            self.decay_remanence()
            print(f"Epoch {epoch + 1}: total edges = {len(self.graph)}")

    def visualize_graph(self):
        G = nx.DiGraph()
        # Ajout des arêtes
        for (state, action), data in self.graph.items():
            next_state = data["next_state"]
            label = f"{action}\nQ={round(data['q_value'], 1)}\nR={data['remanence']}"
            G.add_edge(state, next_state, label=label)

        # Recueillir tous les noeuds (sources + destinations)
        nodes = set()
        for (state, _), data in self.graph.items():
            nodes.add(state)
            nodes.add(data["next_state"])

        # Calculer les positions de tous les noeuds (x = y coord, y = -x coord pour inversion verticale)
        pos = {node: (node[1], -node[0]) for node in nodes}

        plt.figure(figsize=(10, 8))
        nx.draw(G, pos, with_labels=True, node_color="skyblue", node_size=800, edge_color='gray', font_size=8)
        nx.draw_networkx_edge_labels(G, pos, edge_labels=nx.get_edge_attributes(G, 'label'), font_size=6)
        plt.title("GTQN - Graphe de transitions apprises")
        plt.axis('off')
        plt.show()


class QLearningAgent:
    def __init__(self, env, alpha=0.1, gamma=0.9, epsilon=0.2):
        self.env = env
        self.alpha = alpha       # learning rate
        self.gamma = gamma       # discount factor
        self.epsilon = epsilon   # exploration probability
        # Q-table : dict avec clés (state, action) et valeurs Q-value
        self.q_table = {}

    def get_q(self, state, action):
        return self.q_table.get((state, action), 0.0)

    def choose_action(self, state):
        if random.random() < self.epsilon:
            return random.choice(self.env.actions)
        q_values = [self.get_q(state, a) for a in self.env.actions]
        max_q = max(q_values)
        # En cas d'égalité, on choisit aléatoirement parmi les max
        max_actions = [a for a, q in zip(self.env.actions, q_values) if q == max_q]
        return random.choice(max_actions)

    def update(self, state, action, reward, next_state):
        max_next_q = max([self.get_q(next_state, a) for a in self.env.actions])
        old_q = self.get_q(state, action)
        new_q = old_q + self.alpha * (reward + self.gamma * max_next_q - old_q)
        self.q_table[(state, action)] = new_q

    def train(self, epochs=500, max_steps=50):
        for epoch in range(epochs):
            state = self.env.start
            total_reward = 0
            for step in range(max_steps):
                action = self.choose_action(state)
                next_state = self.env.move(state, action)
                reward = self.env.calculate_reward(next_state)
                self.update(state, action, reward, next_state)
                state = next_state
                total_reward += reward
                if state == self.env.goal:
                    break
            print(f"Epoch {epoch+1}: Total reward = {total_reward:.2f}, Steps = {step+1}")

def compare_runtimes():
    env = Environment()

    q_agent = QLearningAgent(env)
    gtqn_agent = GTQNAgent(env)

    print("Training Q-learning agent...")
    start = time.time()
    q_agent.train(epochs=200, max_steps=20)
    q_time = time.time() - start
    print(f"Q-learning training time: {q_time:.4f} seconds")

    print("\nTraining GTQN agent...")
    start = time.time()
    gtqn_agent.train(epochs=200, depth=20)
    gtqn_time = time.time() - start
    print(f"GTQN training time: {gtqn_time:.4f} seconds")

    print("\n--- Résumé ---")
    print(f"Q-learning training time: {q_time:.4f} s")
    print(f"GTQN training time: {gtqn_time:.4f} s")

if __name__ == "__main__":
    compare_runtimes()