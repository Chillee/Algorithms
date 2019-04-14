struct seg {
    int seg[2 * MAXN][2 * MAXN];
    void modify(int qr, int qc, int val) {
        qr += N, qc += M;
        seg[qr][qc] = val;
        for (int r = qr; r > 0; r >>= 1) {
            for (int c = qc; c > 0; c >>= 1)
                seg[r][c >> 1] = seg[r][c] + seg[r][c ^ 1];
            seg[r >> 1][qc] = seg[r][qc] + seg[r ^ 1][qc];
        }
    }
    int query2(int l, int r, int row) {
        int res = 0;
        for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
            if (l & 1)
                res += seg[row][l++];
            if (r & 1)
                res += seg[row][--r];
        }
        return res;
    }
    int query(int u, int d, int l, int r) {
        int res = 0;
        for (u += N, d += N; u < d; u >>= 1, d >>= 1) {
            if (u & 1)
                res += query2(l, r, u++);
            if (d & 1)
                res += query2(l, r, --d);
        }
        return res;
    }
};