int dfs(int cur, int prv = -1, int d = 0) {
    dist[cur] = d;
    int mx = cur;
    for (auto i : adj[cur]) {
        if (i == prv)
            continue;
        int res = dfs(i, cur, d + 1);
        if (dist[res] > dist[mx])
            mx = res;
    }
    return mx;
}
cout<<dist[dfs(dfs(0))]<<endl;