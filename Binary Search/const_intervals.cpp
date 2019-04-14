void rec(int from, int to, function<int(int)> f, int &i, int &p, int q, vector<array<int, 3>> &ints) {
    if (p == q)
        return;
    if (from == to) {
        ints.push_back({i, to, p});
        i = to;
        p = q;
    } else {
        int mid = (from + to) >> 1;
        rec(from, mid, f, i, p, f(mid), ints);
        rec(mid + 1, to, f, i, p, q, ints);
    }
}
void constantIntervals(int from, int to, function<int(int)> f, vector<array<int, 3>> &ints) {
    if (to <= from)
        return;
    int i = from;
    int p = f(i), q = f(to - 1);
    rec(from, to - 1, f, i, p, q, ints);
    ints.push_back({i, to, q});
}