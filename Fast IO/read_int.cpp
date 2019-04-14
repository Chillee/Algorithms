char gc() {
#ifdef _WIN32
    return _getchar_nolock();
#else
    return getchar_unlocked();
#endif
}
void read_int() {}
template <class T, class... S> inline void read_int(T &a, S &... b) {
    char c, s = 1;
    while (isspace(c = gc()));
    if (c == '-') s = -1, c = gc();
    for (a = c - '0'; isdigit(c = gc()); a = a * 10 + c - '0');
    a *= s;
    read_int(b...);
}