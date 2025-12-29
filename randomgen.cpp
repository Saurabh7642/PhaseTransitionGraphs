#include <bits/stdc++.h>
using namespace std;

class Graph {
    int n;
    vector<vector<int>> adj;
    vector<int> vis;

public:
    Graph(int n): n(n), adj(n), vis(n) {}

    void clear() {
        for (auto &v : adj) v.clear();
    }

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
    const int n = 500;
    const double eps = 1.0 / 9.0;
    const double p = (1 + eps) / n;
    const int k = 30;
    const double threshold = 10 * log(n);

    mt19937 rng(random_device{}());
    uniform_real_distribution<double> U(0,1);

    Graph g(n);
    int count = 0, mx = 0;

    for (int it = 0; it < k; it++) {
        g.clear();
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                if (U(rng) < p)
                    g.addEdge(i, j);

        int lc = g.largestComponent();
        mx = max(mx, lc);
        if (lc >= threshold) count++;
        cout << "iter " << it << " largest=" << lc << endl;
    }

    cout << "Above threshold: " << count << "/" << k << endl;
    cout << "Max observed: " << mx << endl;
    return 0;
}
