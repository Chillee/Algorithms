array<vector<int>, 2> manacher(string &s) { // (even, odd)
    int n = s.size();
    array<vector<int>, 2> p = {vector<int>(n), vector<int>(n)};
    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0)
        for (int i = 0; i < n; i++) {
            if (i < r)
                p[z][i] = min(r - i + !z, p[z][l + r - i + !z]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r)
                l = L, r = R;
        }
    return p;
}