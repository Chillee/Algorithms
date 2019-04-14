template <int MAXV, class T = int> struct Dinic {
    const static bool SCALING = false; // non-scaling = V^2E, Scaling=VElog(U) with higher constant
    int lim = 1;
    const T INF = numeric_limits<T>::max();
    struct edge {
        int to, rev;
        T cap, flow;
    };
    int s = MAXV - 2, t = MAXV - 1;

    int level[MAXV], ptr[MAXV];
    vector<edge> adj[MAXV];
    void addEdge(int a, int b, T cap, bool isDirected = true) {
        adj[a].push_back({b, adj[b].size(), cap, 0});
        adj[b].push_back({a, adj[a].size() - 1, isDirected ? 0 : cap, 0});
    }
    bool bfs() {
        queue<int> q({s});
        fill(all(level), -1);
        level[s] = 0;
        while (!q.empty() && level[t] == -1) {
            int v = q.front();
            q.pop();
            for (auto e : adj[v]) {
                if (level[e.to] == -1 && e.flow < e.cap && (!SCALING || e.cap - e.flow >= lim)) {
                    q.push(e.to);
                    level[e.to] = level[v] + 1;
                }
            }
        }
        return level[t] != -1;
    }
    T dfs(int v, T flow) {
        if (v == t || !flow)
            return flow;
        for (; ptr[v] < adj[v].size(); ptr[v]++) {
            edge &e = adj[v][ptr[v]];
            if (level[e.to] != level[v] + 1)
                continue;
            if (T pushed = dfs(e.to, min(flow, e.cap - e.flow))) {
                e.flow += pushed;
                adj[e.to][e.rev].flow -= pushed;
                return pushed;
            }
        }
        return 0;
    }
    long long calc() {
        long long flow = 0;
        for (lim = SCALING ? (1 << 30) : 1; lim > 0; lim >>= 1) {
            while (bfs()) {
                fill(all(ptr), 0);
                while (T pushed = dfs(s, INF))
                    flow += pushed;
            }
        }
        return flow;
    }
};