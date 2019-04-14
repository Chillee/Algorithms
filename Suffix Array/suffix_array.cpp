struct SuffixArray { // sa[0] = n, sa[i] = i-th in sorted suffix array. O(n log n)
#define rep(i, a, b) for (int i = a; i < (b); i++)
    vector<int> sa, lcp;
    SuffixArray(string &s, int lim = 256) {
        int n = s.size() + 1, k = 0, a, b;
        vector<int> x(all(s) + 1), y(n), ind(n), ws(max(n, lim)), rank(n);
        sa = lcp = y, iota(all(sa), 0);
        for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
            p = j, iota(all(y), n - j);
            rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
            rep(i, 0, n) ind[i] = x[y[i]];
            fill(all(ws), 0);
            rep(i, 0, n) ws[ind[i]]++;
            rep(i, 1, lim) ws[i] += ws[i - 1];
            for (int i = n; i--;) sa[--ws[ind[i]]] = y[i];
            swap(x, y), p = 1, x[sa[0]] = 0;
            rep(i, 1, n) a = sa[i - 1], b = sa[i], x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
        } //lcp[0] = 0, lcp[i] = lcp(sa[i], sa[i-1])
        rep(i, 1, n) rank[sa[i]] = i;
        for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
            for (k &&k--, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k++);
    }
#undef rep
};