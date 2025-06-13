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
        return -np.linalg.norm(np.array(state) - np.array(self.goal))


## GTQ-N (Graph-based Thinking Q-Network) Agent Implementation


"""
Observations:
- L'agorithme ne converge pas
- Le graph est construit mais il perd de la mémoire au fil du temps

"""
class GTQNAgent:

    def __init__(self, env: Environment, remanence_init=4,reward_target_sucess=10):
        self.env = env
        self.reward_target_sucess = reward_target_sucess
        self.graph = {}  # {state: {next_state: [remanence, reward]}}
        self.remanence_init = remanence_init
    
    def metrics(self, state = None, remanence = 1, alpha = 0.5, beta = 0.5):
        """
        remanence: Importance de la lisaison dans le state
        Plus le chemin est utilisé, plus la remanence est elevée
        Plus la remanence est élevée, plus le chemin est important
        car il ressort dans beaucoup de chemins
        """
        actual_state = state if state is not None else self.env.start
        target_state = self.env.goal
        distance = -np.linalg.norm(np.array(actual_state) - np.array(target_state))
        return  alpha*remanence + beta*distance       

    def policy(self,state, epsilon = 0.5, decay = 0.1, remanence = 1):
        number = random.random()
        if number < epsilon:
            action = random.choice(self.env.actions)
            next_state = self.env.move(state, action)
            reward = self.metrics(next_state, remanence)
        else:
            reward_posible_actions = []
            for action in self.env.actions:
                next_state = self.env.move(state, action)
                reward = self.metrics(next_state, remanence)
                reward_posible_actions.append((action, reward, next_state))
            action, reward, next_state = max(reward_posible_actions, key=lambda x: x[1])
        updated_epsilon = epsilon* np.exp(-decay)
        return next_state, updated_epsilon, reward
    




    def decay_memory(self, loss_neurone=1):
        keys_to_remove = []
        for from_state in list(self.graph.keys()):
            for to_state in list(self.graph[from_state].keys()):
                self.graph[from_state][to_state] -= loss_neurone
                if self.graph[from_state][to_state] <= 0:
                    keys_to_remove.append((from_state, to_state))

        for from_state, to_state in keys_to_remove:
            del self.graph[from_state][to_state]
            if not self.graph[from_state]:
                del self.graph[from_state]

    
    def distribute_reward(self, history, total_rewards, test_validated = 0):
        len_chain = len(history)
        for x in range(1,len(history)-1):
            state = history[x-1]
            next_state = history[x]
            if state in self.graph and next_state in self.graph[state]:
                self.graph[state][next_state] += np.exp(-len_chain)+total_rewards* test_validated
            else:
                self.graph[state][next_state] = self.remanence_init + np.exp(-len_chain) + total_rewards * test_validated


    def train(self, epochs=500,life = 10,resseting_test = 0.4, bonus_remanence=5, loss_memo=1, depth=50, epsilon=0.1):
        test_validated = 0
        queue_test_not_validated = []
        history = []
        epsilon = 1
        for epoch in range(epochs):
            state = self.env.start
            self.graph[state]= {}
            total_reward = 0
            steps = 0
            while state != self.env.goal and steps < depth:
                next_state, epsilon, reward = self.policy(state, epsilon)
                history.append((state))
                total_reward += reward
                steps+=1
                if next_state not in self.graph[state]:
                    self.graph[state][next_state] = self.remanence_init
                    self.graph[next_state] = {}
                    state = next_state
                else:
                    self.graph[state][next_state] += bonus_remanence
                    state = next_state
            
            if state == self.env.goal:
                total_reward += self.reward_target_sucess
                test_validated += 1
                if (self.env.start, self.env.goal) in queue_test_not_validated:
                    queue_test_not_validated.remove((self.env.start, self.env.goal))

                print(f"Epoch {epoch+1}: Goal reached in {steps} steps with total reward {total_reward:.2f}")
                life = 10
                self.env.reset()
                print(f"New start: {self.env.start}, New goal: {self.env.goal}")
               
            else:
                print(f"Epoch {epoch+1}: Goal not reached in {steps} steps, total reward {total_reward:.2f}")
                queue_test_not_validated.append((self.env.start, self.env.goal))
                life -= 1
            self.distribute_reward(history, total_reward, test_validated)
            self.decay_memory(loss_memo)
            history.clear()
            if life <= 0:
                life = 10
                if queue_test_not_validated:
                    draw = np.random.random()
                    if draw < resseting_test:
                        self.env.start, self.env.goal = random.choice(queue_test_not_validated)
                        print(f"Resetting test with start={self.env.start}, goal={self.env.goal}")

        print(f"Training completed: Total epochs = {epochs}, Validated tests = {test_validated}, Remaining tests = {len(queue_test_not_validated)}")
        if queue_test_not_validated:
            print("Unvalidated tests remaining:")
            for start, goal in queue_test_not_validated:
                print(f"Start: {start}, Goal: {goal}")
        return self.graph
        
    

   
      
        

    def visualize_graph(self):
        G = nx.DiGraph()
        for from_state, transitions in self.graph.items():
            for to_state, remanence in transitions.items():
                label = f"REMANENCE={int(remanence)}"
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
    env = Environment(grid_size=20)

    q_agent = QLearningAgent(env)
    gtqn_agent = GTQNAgent(env)
    """
    print("Training Q-learning agent...")
    start = time.time()
    q_agent.train(epochs=200, max_steps=20)
    q_time = time.time() - start
    print(f"Q-learning training time: {q_time:.4f} seconds")
"""    
    print("\nTraining GTQN agent...")
    start = time.time()
    gtqn_agent.train(epochs=50, depth=20)
    gtqn_time = time.time() - start
    print(f"GTQN training time: {gtqn_time:.4f} seconds")

    print("\n--- Résumé ---")
    #print(f"Q-learning training time: {q_time:.4f} s")
    print(f"GTQN training time: {gtqn_time:.4f} s")
    gtqn_agent.visualize_graph()
 

if __name__ == "__main__":
    compare_runtimes()