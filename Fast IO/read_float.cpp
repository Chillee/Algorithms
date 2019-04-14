char gc() {
#ifdef _WIN32
    return _getchar_nolock();
#else
    return getchar_unlocked();
#endif
}
void read_float() {}
template <class T, class... S> inline void read_float(T &a, S &... b) {
    int c, s = 1, fp = 0, fpl = 1;
    while (isspace(c = gc()));
    if (c == '-') s = -1, c = gc();
    for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0');
    a *= s;
    if (c == '.')
        for (; isdigit(c = gc()); fp = fp * 10 + c - '0', fpl *= 10);
    a += (double)fp / fpl;
    read_float(b...);
}