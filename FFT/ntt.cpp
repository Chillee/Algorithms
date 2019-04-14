template <int maxn> struct NTT {
    constexpr static int lg2(int n) { return 32 - __builtin_clz(n - 1); }
    const static int MAXN = 1 << lg2(maxn);
    const static int MOD = 998244353;
    const static int root = 3;
    int rev[MAXN], rt[MAXN];

    inline int mul(const int a, const int b) { return (long long)a * b % MOD; }
    inline int sub(const int a, const int b) { return b > a ? a - b + MOD : a - b; }
    inline int add(const int a, const int b) { return a + b >= MOD ? a + b - MOD : a + b; }

    int binExp(int base, long long exp) {
        if (exp == 0)
            return 1;
        return mul(binExp(mul(base, base), exp / 2), exp & 1 ? base : 1);
    }
    NTT() {
        int curL = (MOD - 1) >> 2;
        rt[1] = 1;
        for (int k = 2; k < MAXN; k *= 2) {
            int z = binExp(root, curL);
            curL >>= 1;
            for (int i = k / 2; i < k; i++) {
                rt[2 * i] = rt[i], rt[2 * i + 1] = mul(rt[i], z);
            }
        }
    }
    void ntt(int *a, int n) {
        for (int i = 0; i < n; i++)
            rev[i] = (rev[i / 2] | (i & 1) << lg2(n)) / 2;
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                swap(a[i], a[rev[i]]);
        for (int k = 1; k < n; k *= 2)
            for (int i = 0; i < n; i += 2 * k)
                for (int j = 0; j < k; j++) {
                    int z = mul(rt[j + k], a[i + j + k]);
                    a[i + j + k] = sub(a[i + j], z);
                    a[i + j] = add(a[i + j], z);
                }
    }
    int in[2][MAXN];
    vector<int> multiply(const vector<int> &a, const vector<int> &b) {
        int n = 1 << lg2(a.size() + b.size()-1);
        copy(a.begin(), a.end(), in[0]), copy(b.begin(), b.end(), in[1]);
        ntt(in[0], n), ntt(in[1], n);
        int invN = binExp(n, MOD - 2);
        for (int i = 0; i < n; i++)
            in[0][i] = mul(mul(in[0][i], in[1][i]), invN);
        reverse(in[0] + 1, in[0] + n);
        ntt(in[0], n);
        return vector<int>(begin(in[0]), end(in[0]));
    }
};