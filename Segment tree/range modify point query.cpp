int seg[2 * MAXN];

void modify(int l, int r, int val) {
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            seg[l++] += val;
        if (r & 1)
            seg[--r] += val;
    }
}

int query(int p) {
    int res = 0;
    for (p += N; p > 0; p >>= 1)
        res += seg[p];
    return res;
}