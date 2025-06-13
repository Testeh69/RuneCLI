import random
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import time

"""

GTQN (Graph-based Thinking Q-Network) Agent Implementation

-> Code qui ne sert à rien juste pour suivre une idée
-> Probleme de convergence


"""



class Environment:
    def __init__(self, grid_size=5, start=(0, 0), goal=(4, 4)):
        self.grid_size = grid_size
        self.start = start
        self.goal = goal
        self.actions = ['UP', 'DOWN', 'LEFT', 'RIGHT']

    def reset(self):
        self.start = (np.random.randint(0, self.grid_size), np.random.randint(0, self.grid_size))
        self.goal = (np.random.randint(0, self.grid_size), np.random.randint(0, self.grid_size))
        while self.goal == self.start:
            self.goal = (np.random.randint(0, self.grid_size), np.random.randint(0, self.grid_size))
        return self.start, self.goal

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
        if state == self.goal:
            return 10
        else:
            return -1
        


 
## GTQ-N (Graph-based Thinking Q-Network) Agent Implementation


"""
Observations:
- L'agorithme ne converge pas
- Le graph est construit mais il perd de la mémoire au fil du temps

"""
class GTQNAgent:
    def __init__(self, env, remanence_init=4, reward_goal=10):
        self.env = env
        self.graph = {}  # {state: {next_state: remanence}}
        self.remanence_init = remanence_init
        self.reward_goal = reward_goal

    def metrics(self, state, remanence=1, alpha=0.5, beta=0.5):
        distance = -np.linalg.norm(np.array(state) - np.array(self.env.goal))
        return alpha * remanence + beta * distance

    def policy(self, state, epsilon=0.5, decay=0.1, remanence=1):
        if random.random() < epsilon:
            action = random.choice(self.env.actions)
            next_state = self.env.move(state, action)
        else:
            candidates = [(action, self.env.move(state, action)) for action in self.env.actions]
            scored = [(a, s, self.metrics(s, remanence)) for a, s in candidates]
            _, next_state, _ = max(scored, key=lambda x: x[2])
        return next_state, epsilon * np.exp(-decay)

    def decay_memory(self, decay=1):
        to_delete = []
        for from_state in list(self.graph.keys()):
            for to_state in list(self.graph[from_state].keys()):
                self.graph[from_state][to_state] -= decay
                if self.graph[from_state][to_state] <= 0:
                    to_delete.append((from_state, to_state))
        for from_state, to_state in to_delete:
            del self.graph[from_state][to_state]
            if not self.graph[from_state]:
                del self.graph[from_state]

    def distribute_reward(self, path, total_reward):
        for i in range(1, len(path)):
            a, b = path[i - 1], path[i]
            bonus = self.remanence_init + total_reward * np.exp(-len(path))
            self.graph.setdefault(a, {})[b] = self.graph[a].get(b, 0) + bonus

    def train(self, epochs=500, depth=50, epsilon=1.0):
        state = self.env.start
        self.graph.setdefault(state, {})

        for epoch in range(epochs):
            state = self.env.start
            path = [state]
            total_reward = 0
            steps = 0

            while state != self.env.goal and steps < depth:
                next_state, epsilon = self.policy(state, epsilon)
                path.append(next_state)
                total_reward += self.metrics(next_state)

                self.graph.setdefault(state, {})
                self.graph[state][next_state] = self.graph[state].get(next_state, self.remanence_init)
                state = next_state
                steps += 1

            if state == self.env.goal:
                total_reward += self.reward_goal
                print(f"Epoch {epoch+1}: Reached goal in {steps} steps.")
            else:
                print(f"Epoch {epoch+1}: Did not reach goal in {steps} steps.")

            self.distribute_reward(path, total_reward)
            self.decay_memory()
            self.env.reset()
        print("Training complete -> test")

    def visualize_graph(self):
        G = nx.DiGraph()
        for a, targets in self.graph.items():
            for b, rem in targets.items():
                G.add_edge(a, b, label=f"{int(rem)}")
        pos = {n: (n[1], -n[0]) for n in G.nodes()}
        plt.figure(figsize=(10, 8))
        nx.draw(G, pos, with_labels=True, node_color='skyblue', node_size=800)
        nx.draw_networkx_edge_labels(G, pos, edge_labels=nx.get_edge_attributes(G, 'label'))
        plt.title("GTQN Graph")
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
    env = Environment(grid_size=70, start=(0, 0), goal=(69, 69))

    q_agent = QLearningAgent(env)
    gtqn_agent = GTQNAgent(env)
    
    print("Training Q-learning agent...")
    start = time.time()
    q_agent.train(epochs=200, max_steps=20)
    q_time = time.time() - start
    print(f"Q-learning training time: {q_time:.4f} seconds")

    print("\nTraining GTQN agent...")
    start = time.time()
    gtqn_agent.train(epochs=200, depth=30)
    gtqn_time = time.time() - start
    print(f"GTQN training time: {gtqn_time:.4f} seconds")

    print("\n--- Résumé ---")
    print(f"Q-learning training time: {q_time:.4f} s")
    print(f"GTQN training time: {gtqn_time:.4f} s")
    gtqn_agent.visualize_graph()
 

if __name__ == "__main__":
    compare_runtimes()