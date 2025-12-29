# PhaseTransitionGraphs  
**Phase Transition and Giant Component Analysis in Erdős–Rényi Random Graphs**

---

## 1. Introduction

Random graphs form a foundational model in modern **network science, probability theory, and randomized algorithms**.  
This project experimentally and theoretically studies **connectivity phase transitions** in the **Erdős–Rényi random graph model** using graph traversal algorithms such as **Depth-First Search (DFS)** and **Breadth-First Search (BFS)**.

The central goal is to understand **how global structure emerges from local randomness**, and why random behavior becomes **predictable with high probability** as the graph size grows.

---

## 📌 Objective

The objectives of this project are to:

- Study the **emergence of a giant connected component**
- Identify the **critical threshold** at  
  \( p = \frac{1}{n} \)
- Understand the role of **Chernoff bounds** in explaining concentration
- Validate probabilistic theory using experiments
- Analyze **finite-size effects** in random graphs

---

## 2. Erdős–Rényi Random Graph Model

We work with the classical Erdős–Rényi model denoted by:

\[
G(n, p)
\]

where:
- \( n \) is the number of vertices
- Each unordered pair of vertices forms an edge **independently** with probability \( p \)

---

### 2.1 Bernoulli Trials Interpretation

Each possible edge \( \{i, j\} \) corresponds to a **Bernoulli random variable**:

\[
X_{ij} =
\begin{cases}
1 & \text{with probability } p \\
0 & \text{with probability } 1 - p
\end{cases}
\]

Thus, a random graph is simply a **collection of independent Bernoulli trials**.

---

## 3. Critical Scaling: Why \( p = \frac{c}{n} \)

A key insight from random graph theory is that meaningful global behavior emerges when:

\[
p = \frac{c}{n}
\]

Under this scaling:
- The expected degree of a vertex is  
  \[
  \mathbb{E}[\deg(v)] = np = c
  \]
- The graph undergoes a **phase transition** at  
  \[
  c = 1
  \]

This project focuses on this **critical regime**.

---

## 4. Phase Transition Phenomenon

### 4.1 Subcritical Regime (\( c < 1 \))

- Average degree < 1  
- Graph consists of small tree-like components  
- Largest component size is  
  \[
  O(\log n)
  \]
- No giant component exists  

---

### 4.2 Supercritical Regime (\( c > 1 \))

- Average degree > 1  
- A **giant connected component** emerges  
- Size of giant component is  
  \[
  \Theta(n)
  \]
- All other components remain small  

---

### 4.3 Connectivity Threshold

A second important threshold occurs at:

\[
p \approx \frac{\log n}{n}
\]

At this point, the graph becomes **fully connected with high probability**.

---

## 5. Role of Graph Traversal Algorithms

### 5.1 DFS / BFS and Connected Components

Both DFS and BFS explore **entire connected components** starting from a single vertex.

- DFS recursively explores deep paths  
- BFS explores level by level  

In both cases:

> The size returned by DFS/BFS equals the size of the connected component containing the start node.

---

### 5.2 How DFS “Discovers” the Giant Component

DFS does not search for the giant component explicitly. Instead:

- If DFS starts outside the giant → exploration ends quickly  
- If DFS enters the giant → exploration continues for  
  \[
  \Theta(n)
  \]
  steps

This behavior mirrors a **branching process** with:

\[
\mathbb{E}[\text{new neighbors}] = np
\]

- If \( np < 1 \) → process dies out  
- If \( np > 1 \) → process survives with positive probability  

---

## 6. Probabilistic Theory: Chernoff Bounds

### 6.1 Why Concentration Matters

Many graph quantities (degree, BFS growth, number of edges) are sums of **independent Bernoulli random variables**.

Chernoff bounds guarantee that such sums are **highly concentrated around their expectation**:

\[
\Pr(|X - \mathbb{E}[X]| > \varepsilon \mathbb{E}[X])
\le e^{-\Theta(\mathbb{E}[X])}
\]

---

### 6.2 Consequences for Random Graphs

Chernoff bounds imply:

- Degrees concentrate around \( np \)
- BFS/DFS expansion is predictable
- Giant component does not appear “by accident”
- Phase transition becomes sharper as \( n \) increases  

This explains why **randomness leads to law-like behavior**.

---

## 7. Experimental Design

### 7.1 Overview of Experiments

| File | Purpose |
|----|----|
| `expt.py` | Phase transition visualization |
| `plot.cpp` | Subcritical regime validation |
| `randomgen.cpp` | With-high-probability experiment |

---

### 7.2 Phase Transition Visualization (`expt.py`)

- Generates \( G(n,p) \) graphs  
- Computes largest connected component using BFS  
- Averages results over multiple trials  
- Plots  
  \[
  \frac{\text{Largest Component Size}}{n} \quad \text{vs} \quad np
  \]

**Values tested:**  
`n = 10, 100, 200, 500`

---

### 7.3 Subcritical Regime Validation (`plot.cpp`)

- Uses  
  \[
  p = \frac{8}{9n} < \frac{1}{n}
  \]
- Demonstrates absence of giant component  
- Confirms \( O(\log n) \) growth  

---

### 7.4 With-High-Probability Experiment (`randomgen.cpp`)

- Uses  
  \[
  p = \frac{1 + \varepsilon}{n}
  \]
- Runs multiple independent trials  
- Counts how often large components appear  
- Empirically validates **WHP guarantees**

---

## 📊 Experimental Results

The following plots show the **normalized size of the largest connected component** as a function of the **expected degree \( np \)**.

---

### 🔹 n = 10

![Phase Transition n=10](results/plot_10.png)

- Strong finite-size effects  
- No sharp phase transition  

---

### 🔹 n = 100

![Phase Transition n=100](results/plot_100.png)

- Transition near \( np \approx 1 \) becomes visible  

---

### 🔹 n = 200

![Phase Transition n=200](results/plot_200.png)

- Clearer phase transition  
- Reduced variance  

---

### 🔹 n = 500

![Phase Transition n=500](results/plot_500.png)

- Sharp emergence of the giant component  
- Strong agreement with Erdős–Rényi theory  
- Concentration effects clearly visible  

---

## 🛠 How to Run

```bash
# Python experiment
python expt.py

# Subcritical regime
g++ plot.cpp -o plot
./plot

# With-high-probability experiment
g++ randomgen.cpp -o randomgen
./randomgen
