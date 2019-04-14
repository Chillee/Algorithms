ll chinese(ll a, ll m, ll b, ll n) { //x = a %m, x = b%n, gcd(m,n)=1
    ll x, y;
    euclid(m, n, x, y);
    ll ret = a * (y + m) % m * n + b * (x + n) % n * m;
    if (ret >= m * n)
        ret -= m * n;
    return ret;
}
ll chinese_common(ll a, ll m, ll b, ll n) { // gcd(m,n) != 1
    ll d = __gcd(m, n);
    if (((b -= a) %= n) < 0)
        b += n;
    if (b % d)
        return -1; // No solution
    return d * chinese(ll(0), m / d, b / d, n / d) + a;
}