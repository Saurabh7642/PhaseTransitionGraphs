# PhaseTransitionGraphs  
**Phase Transition and Giant Component Analysis in Erdős–Rényi Random Graphs**

---

## 🔍 Overview

This project experimentally and theoretically studies **connectivity phase transitions** in **Erdős–Rényi random graphs** using **graph traversal algorithms (DFS/BFS)** and **probabilistic analysis**.

The key idea explored is:

> *How simple random edge choices lead to sharp, predictable global structure in large networks.*

This phenomenon is fundamental to randomized algorithms, network science, and probability theory.

---

## 🎯 Objective

The objectives of this project are to:

- Observe the **emergence of a giant connected component**
- Identify the **critical threshold** at  
  \( p = \frac{1}{n} \)
- Understand **why randomness becomes predictable**
- Validate theory using **Chernoff bounds**
- Study **finite-size effects** through experiments

---

## 📘 Theoretical Background

### Erdős–Rényi Random Graph Model

We use the classical random graph model:

\[
G(n, p)
\]

where:
- \( n \) is the number of vertices
- Each unordered pair of vertices forms an edge **independently** with probability \( p \)

Each edge corresponds to a **Bernoulli random variable**, making the graph a collection of independent probabilistic trials.

---

### Critical Scaling: Why \( p = \frac{c}{n} \)

Choosing

\[
p = \frac{c}{n}
\]

keeps the **expected degree** constant:

\[
\mathbb{E}[\deg(v)] = np = c
\]

This scaling reveals a **phase transition** at:

- **\( c < 1 \)** → graph has only small components  
- **\( c > 1 \)** → a giant component emerges  

---

### Connectivity Threshold

A second threshold occurs at:

\[
p \approx \frac{\log n}{n}
\]

Beyond this value, the graph becomes **fully connected with high probability**.

---

## 🧠 Role of DFS / BFS

Depth-First Search (DFS) and Breadth-First Search (BFS) are used to explore **connected components**.

Key insight:

> DFS does not search for the giant component —  
> once it enters it, exploration naturally expands to linear size.

This behavior is explained using a **branching process**, where growth depends on the expected number of neighbors \( np \).

---

## 🧪 Experiments Performed

### 1️⃣ Phase Transition Visualization (`expt.py`)

- Generates random graphs \( G(n,p) \)
- Computes the largest connected component using BFS
- Averages results over multiple trials
- Plots  
  \[
  \frac{\text{Largest Component Size}}{n} \quad \text{vs} \quad np
  \]

**Graph sizes tested:**  
`n = 10, 100, 200, 500`

---

### 2️⃣ Subcritical Regime Validation (`plot.cpp`)

- Uses  
  \[
  p = \frac{8}{9n} < \frac{1}{n}
  \]
- Confirms absence of a giant component
- Largest component remains small (theoretically \( O(\log n) \))

---

### 3️⃣ With-High-Probability Experiment (`randomgen.cpp`)

- Uses  
  \[
  p = \frac{1 + \varepsilon}{n}
  \]
- Runs multiple independent trials
- Empirically validates **with high probability (WHP)** guarantees

---

## 📊 Experimental Results

The following plots show the **normalized size of the largest connected component** as a function of the **expected degree \( np \)**.

---

### 🔹 n = 10 (Very small graph)

![Phase Transition n=10](results/plot_10.png)

- Strong finite-size effects
- No sharp phase transition
- High randomness dominates behavior

---

### 🔹 n = 100

![Phase Transition n=100](results/plot_100.png)

- Transition near \( np \approx 1 \) becomes visible
- Giant component begins to emerge

---

### 🔹 n = 200

![Phase Transition n=200](results/plot_200.png)

- Clearer phase transition
- Reduced variance compared to smaller graphs

---

### 🔹 n = 500 (Closest to theory)

![Phase Transition n=500](results/plot_500.png)

- Sharp emergence of the giant component near \( np = 1 \)
- Strong agreement with Erdős–Rényi theory
- Concentration effects clearly visible

---

## 📐 Why Theory Matches Experiments

Chernoff bounds guarantee strong concentration of sums of independent Bernoulli variables.

As a result:
- Vertex degrees concentrate around \( np \)
- DFS/BFS expansion becomes predictable
- The phase transition sharpens as \( n \) increases

This explains why **randomness leads to law-like behavior** in large graphs.

---

## ⚠️ Scalability Notes

The exact Erdős–Rényi model requires \( O(n^2) \) edge checks.

To ensure feasibility:
- Experiments are conducted for moderate \( n \)
- The probabilistic model remains unchanged
- Only finite-size effects are introduced

---

## 🛠 How to Run

```bash
# Python experiment (phase transition plots)
python expt.py

# Subcritical regime experiment
g++ plot.cpp -o plot
./plot

# With-high-probability experiment
g++ randomgen.cpp -o randomgen
./randomgen
