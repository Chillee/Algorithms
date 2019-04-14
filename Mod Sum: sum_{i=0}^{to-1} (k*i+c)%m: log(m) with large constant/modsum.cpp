typedef unsigned long long ull;
ull sumsq(ull to) { return to / 2 * ((to - 1) | 1); }
ull divsum(ull to, ull c, ull k, ull m) {
    ull res = k / m * sumsq(to) + c / m * to;
    k %= m, c %= m;
    if (!k)
        return res;
    ull to2 = (to * k + c) / m;
    return res + (to - 1) * to2 - divsum(to2, m - 1 - c, m, k);
}
ll modsum(ull to, ll c, ll k, ll m) { // sum_{i=0}^{to-1} (k*i+c)%m: mod is inside summation
    c = ((c % m) + m) % m;
    k = ((k % m) + m) % m;
    return to * c + k * sumsq(to) - m * divsum(to, c, k, m);
}