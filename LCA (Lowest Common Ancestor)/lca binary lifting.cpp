template <int MAXN> struct LCA { // O(log N) queries
    const static int MAXB = 32 - __builtin_clz(MAXN);
    int tin[MAXN], tout[MAXN], depth[MAXN], timer = 0;
    int pars[MAXN][MAXB];
    void calclca(int cur, int p = 0, int d = 0) {
        depth[cur] = d;
        tin[cur] = ++timer;
        pars[cur][0] = p;
        for (int d = 1; d < MAXB; d++)
            pars[cur][d] = pars[pars[cur][d - 1]][d - 1];
        for (auto i : adj[cur]) {
            if (i == p)
                continue;
            calclca(i, cur, d + 1);
        }
        tout[cur] = ++timer;
    }
    bool isAncestor(int p, int x) { return tin[p] <= tin[x] && tout[p] >= tout[x]; }
    int query(int a, int b) {
        if (isAncestor(a, b))
            return a;
        if (isAncestor(b, a))
            return b;
        for (int d = MAXB - 1; d >= 0; d--) {
            if (!isAncestor(pars[a][d], b))
                a = pars[a][d];
        }
        return pars[a][0];
    }
    int dist(int a, int b) {
        int lca = query(a, b);
        return depth[a] + depth[b] - 2 * depth[lca];
    }
};