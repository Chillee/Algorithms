int seg[2 * MAXN];
void build() {
    for (int i = N - 1; i >= 0; i--)
        seg[i] = seg[i << 1] + seg[i << 1 | 1];
}

void modify(int p, int val) {
    for (seg[p += N] = val; p > 0; p >>= 1)
        seg[p >> 1] = seg[p] + seg[p ^ 1];
}

int query(int l, int r) {
    int res = 0;
    for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1)
            res += seg[l++];
        if (r & 1)
            res += seg[--r];
    }
    return res;
}