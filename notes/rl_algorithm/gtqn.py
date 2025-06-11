import random
import numpy as np
import matplotlib.pyplot as plt
import networkx as nx
import time




## GTQ-N (Graph-based Thinking Q-Network) Agent Implementation

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
        return -np.linalg.norm(np.array(state) - np.array(self.goal))


class GTQNAgent:

    def __init__(self, env: Environment, remanence_init=4):
        self.env = env
        self.graph = {}  # {state: {next_state: [remanence, reward]}}
        self.remanence_init = remanence_init

    def train(self, epochs=500, bonus_remanence=100, loss_memo=1, depth=50, espilon=0.1):
        for epoch in range(epochs):
            state = self.env.start
            total_reward = 0
            step = 0
            while state != self.env.goal and step < depth:
                # Choisir l'action avec le meilleur reward immédiat (greedy)
                list_max = []
                if random.random() < espilon:
                    # Exploration aléatoire
                    action = random.choice(self.env.actions)
                    next_state = self.env.move(state, action)
                    reward = self.env.calculate_reward(next_state)
                else:
                    for action in self.env.actions:
                        next_s = self.env.move(state, action)
                        r = self.env.calculate_reward(next_s)
                        list_max.append((action, r, next_s))

                    # Choix de l'action qui minimise la distance (maximise reward négatif)
                
                
                    best = max(list_max, key=lambda x: x[1])
                    action, reward, next_state = best

                if state not in self.graph:
                    self.graph[state] = {}

                if next_state not in self.graph[state]:
                    self.graph[state][next_state] = [self.remanence_init, reward]
                else:
                    self.graph[state][next_state][0] += bonus_remanence
                    self.graph[state][next_state][1] += -reward
                
                # Oublie partielle
                keys_to_remove = []
                for from_state in self.graph:
                    for to_state in list(self.graph[from_state].keys()):
                        self.graph[from_state][to_state][0] -= loss_memo
                        if self.graph[from_state][to_state][0] <= 0:
                            keys_to_remove.append((from_state, to_state))

                for from_state, to_state in keys_to_remove:
                    del self.graph[from_state][to_state]
                    if not self.graph[from_state]:
                        del self.graph[from_state]

                state = next_state
                total_reward += reward
                step += 1

            print(f"Epoch {epoch+1}: Start={self.env.start}, Goal={self.env.goal}, State = {state} Total reward = {total_reward:.2f}, Steps = {step}")
        return self.graph
    
    def test(self, start=None, goal=None):
        visited = []
        if start is None:
            start = self.env.start
        if goal is None:
            goal = self.env.goal

        state = start
        total_reward = 0
        steps = 0

        while state != goal:
            visited.append(state)
        
            if state not in self.graph or not self.graph[state]:
                list_action = []
                for action in self.env.actions:
                    next_state = self.env.move(state, action)
                    if next_state in visited:
                        continue
                    reward = self.env.calculate_reward(next_state)
                    list_action.append((next_state, reward))
                next_state, reward = max(list_action, key=lambda x: x[1])
                self.graph[state] = {next_state: [self.remanence_init, reward]}
            else:
                next_state, (remanence, reward) = max(self.graph[state].items(), key=lambda x: x[1][1])
            total_reward += reward
            state = next_state
            steps += 1

        print(f"Test completed: Start={start}, Goal={goal}, Final State={state}, Total Reward={total_reward:.2f}, Steps={steps}")

    def visualize_graph(self):
        G = nx.DiGraph()
        for from_state, transitions in self.graph.items():
            for to_state, (remanence, reward) in transitions.items():
                label = f"R={round(reward,1)}\nM={int(remanence)}"
                G.add_edge(from_state, to_state, label=label)

        pos = {node: (node[1], -node[0]) for node in G.nodes()}
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
    gtqn_agent.visualize_graph()

if __name__ == "__main__":
    compare_runtimes()