bool isPrime(ull n) {
    if (n < 2 || n % 2 == 0 || n % 3 == 0)
        return n - 2 < 2;
    ull s = __builtin_ctzll(n - 1), d = n >> s; // counts trailing zeros
    for (auto a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        ull p = binExp(a, d, n), i = s;
        while (p != 1 && p != n - 1 && a % n && i--)
            p = binExp(p, 2, n);
        if (p != n - 1 && i != s)
            return 0;
    }
    return 1;
}