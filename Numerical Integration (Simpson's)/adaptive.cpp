double simpson(function<double(double)> f, double a, double b) {
    double c = (a + b) / 2;
    return (b - a) / 6 * (f(a) + 4 * f(c) + f(b));
}
double rec(function<double(double)> f, double a, double b, double eps, double S, bool rel = true) {
    double c = (a + b) / 2;
    double S1 = simpson(f, a, c), S2 = simpson(f, c, b), T = S1 + S2;
    if (abs(T - S) <= 15 * eps || b - a < 1e-10 || (rel && abs((T - S) / S) <= 15 * eps))
        return T + (T - S) / 15;
    return rec(f, a, c, eps / 2, S1, rel) + rec(f, c, b, eps / 2, S2, rel);
}
double integrate(function<double(double)> f, double a, double b, double eps = 1e-8, bool rel = true) {
    return rec(f, a, b, eps, simpson(f, a, b), rel);
}
