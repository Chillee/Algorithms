struct MinCostFlow {
    const static int MAXV = MAXN;
    const int INF = 1e9 + 5;
    const int s = MAXV - 2, t = MAXV - 1;
    struct edge {
        int from, to, cap, flow, cost;
    };

    int cost[MAXV][MAXV];
    vector<edge> edges;
    int dist[MAXV];
    int par[MAXV];

    int minCost(int flow) {
        int result = 0;
        while (true) {
            fill(begin(dist), end(dist), INF);
            dist[s] = 0;
            while (true) {
                bool change = false;
                for (int i = 0; i < edges.size(); i++) {
                    edge e = edges[i];
                    if (e.flow == e.cap || dist[e.from] == INF)
                        continue;
                    if (dist[e.to] > dist[e.from] + e.cost) {
                        dist[e.to] = dist[e.from] + e.cost;
                        par[e.to] = i;
                        change = true;
                    }
                }
                if (!change)
                    break;
            }

            if (dist[t] == INF) {
                return -1;
            }

            int push = flow;
            int cur = t;
            while (cur != s) {
                edge tmp = edges[par[cur]];
                int from = tmp.from, can_push = tmp.cap - tmp.flow;
                push = min(push, can_push);
                cur = from;
            }

            flow -= push;
            cur = t;
            while (cur != s) {
                edge tmp = edges[par[cur]];
                int from = tmp.from;
                edges[par[cur]].flow += push;
                edges[par[cur] ^ 1].flow -= push;
                result += push * tmp.cost;
                cur = from;
            }

            if (flow == 0)
                break;
        }
        return result;
    }

    void addEdge(int from, int to, int cap, int cost) {
        edges.push_back({from, to, cap, 0, cost});
        edges.push_back({to, from, cap, cap, -cost});
    }
};