#include <bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;
    vector<int> vis;

public:
    Graph(int n): n(n), adj(n), vis(n) {}

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int dfs(int u) {
        vis[u] = 1;
        int sz = 1;
        for (int v : adj[u])
            if (!vis[v])
                sz += dfs(v);
        return sz;
    }

    int largestComponent() {
        fill(vis.begin(), vis.end(), 0);
        int best = 0;
        for (int i = 0; i < n; i++)
            if (!vis[i])
                best = max(best, dfs(i));
        return best;
    }
};

int main() {
    ofstream out("largest_component_sizes.txt");
    mt19937 rng(random_device{}());
    uniform_real_distribution<double> U(0,1);

    vector<int> Ns = {10, 100, 200, 500};

    for (int n : Ns) {
        double p = 8.0 / (9.0 * n);
        Graph g(n);

        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (U(rng) < p)
                    g.addEdge(i, j);

        int lc = g.largestComponent();
        out << n << " " << lc << "\n";
        cout << "n=" << n << " largest_component=" << lc << endl;
    }

    out.close();
    return 0;
}
