import numpy as np
import matplotlib.pyplot as plt
from collections import deque
from tqdm import tqdm

def generate_random_graph(n, p):
    A = np.triu((np.random.rand(n, n) < p).astype(int), 1)
    return A + A.T

def connected_comps(n, A):
    visited = [False] * n
    largest = 0

    def bfs(start):
        q = deque([start])
        visited[start] = True
        size = 0
        while q:
            u = q.popleft()
            size += 1
            for v in np.where(A[u] == 1)[0]:
                if not visited[v]:
                    visited[v] = True
                    q.append(v)
        return size

    for i in range(n):
        if not visited[i]:
            largest = max(largest, bfs(i))
    return largest

def get_largest_comp(n, p, k):
    total = 0
    for _ in range(k):
        A = generate_random_graph(n, p)
        total += connected_comps(n, A)
    return total / (k * n)

def plot(n):
    p_vals = np.linspace(0, (np.log(n) + 2) / n, 80)
    y = []

    for p in tqdm(p_vals, desc=f"Simulating n={n}"):
        y.append(get_largest_comp(n, p, 30))

    plt.figure(figsize=(9,6))
    plt.plot(p_vals * n, y, label="Largest component / n")
    plt.axvline(1, color='r', linestyle='--', label='np = 1 (Percolation)')
    plt.axvline(np.log(n), color='g', linestyle='--', label='np = log n (Connectivity)')
    plt.xlabel("Expected degree (np)")
    plt.ylabel("Largest component / n")
    plt.title(f"Phase Transition in Random Graph (n = {n})")
    plt.legend()
    plt.grid()
    plt.savefig(f"results/plot_{n}.png", dpi=300)
    plt.close()

def main():
    for n in [10, 100, 200, 500]:
        plot(n)

if __name__ == "__main__":
    main()
