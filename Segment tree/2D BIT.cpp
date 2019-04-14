int N, M;
int bit[MAXN][MAXN];
int sum(int x, int y) {
    int ret = 0;
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1)
        for (int j = y; j >= 0; j = (j & (j + 1)) - 1)
            ret += bit[i][j];
    return ret;
}
void add(int x, int y, int delta) {
    for (int i = x; i < N; i = i | (i + 1))
        for (int j = y; j < M; j = j | (j + 1))
            bit[i][j] += delta;
}