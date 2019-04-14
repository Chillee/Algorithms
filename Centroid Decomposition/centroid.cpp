int sz[MAXN];
int cpar[MAXN];
bool dead[MAXN];
int sizedfs(int cur, int p) {
    sz[cur] = 1;
    for (auto i : adj[cur]) {
        if (i != p && !dead[i])
            sz[cur] += sizedfs(i, cur);
    }
    return sz[cur];
}
int getCentroid(int cur, int p, int n) {
    for (auto i : adj[cur]) {
        if (i != p && !dead[i] && sz[i] > n / 2)
            return getCentroid(i, cur, n);
    }
    return cur;
}
void decompose(int cur, int p) {
    sizedfs(cur, cur);
    int centr = getCentroid(cur, cur, sz[cur]);
    cpar[centr] = p;
    dead[centr] = true;
    for (auto i : adj[centr]) {
        if (!dead[i] && i != p)
            decompose(i, centr);
    };
}