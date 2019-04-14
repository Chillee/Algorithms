/* Convex Start */
vector<pt> convexHull(vector<pt> &pts) { // O(n log n)
    sort(pts.begin(), pts.end());
    vector<pt> hull;
    for (int phase = 0; phase < 2; ++phase) {
        auto start = hull.size();
        for (auto &point : pts) {
            while (hull.size() >= start + 2 && orientS(hull[hull.size() - 2], hull.back(), point) <= 0)
                hull.pop_back();
            hull.push_back(point);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    if (hull.size() == 2 && hull[0] == hull[1])
        hull.pop_back();
    return hull;
}
// if strict, returns false when A is on the boundary.
bool inConvex(vector<pt> &l, pt p, bool strict = true) { // O(log n)
    int a = 1, b = l.size() - 1, c;
    if (orientS(l[0], l[a], l[b]) > 0)
        swap(a, b);
    if (orientS(l[0], l[a], p) > 0 || orientS(l[0], l[b], p) < 0 || (strict && (orientS(l[0], l[a], p) == 0 || orientS(l[0], l[b], p) == 0)))
        return false;
    while (abs(a - b) > 1) {
        c = (a + b) / 2;
        if (orientS(l[0], l[c], p) > 0)
            b = c;
        else
            a = c;
    }
    return orientS(l[a], l[b], p) < 0 ? true : !strict;
}
// Max distance across a convex polygon
T convexDiameter(vector<pt> poly) { // O(n)
    int n = poly.size();
    auto res = T(0);
    for (int i = 0, j = n < 2 ? 0 : 1; i < j; ++i)
        for (;; j = (j + 1) % n) {
            res = max(res, (poly[i] - poly[j]).sq());
            if (orientS({0, 0}, poly[(j + 1) % n] - poly[j], poly[i + 1] - poly[i]) >= 0)
                break;
        }
    return res;
}
vector<pt> convexConvex(vector<pt> &P, vector<pt> &Q) { // O(log n)
    const int n = P.size(), m = Q.size();
    int a = 0, b = 0, aa = 0, ba = 0;
    enum { Pin, Qin, Unknown } in = Unknown;
    vector<pt> R;
    do {
        int a1 = (a + n - 1) % n, b1 = (b + m - 1) % m;
        double C = cross(P[a] - P[a1], Q[b] - Q[b1]);
        double A = cross(P[a1] - Q[b], P[a] - Q[b]);
        double B = cross(Q[b1] - P[a], Q[b] - P[a]);
        pt r;
        if (properInter(P[a1], P[a], Q[b1], Q[b], r)) {
            if (in == Unknown)
                aa = ba = 0;
            R.push_back(r);
            in = B > 0 ? Pin : (A > 0 ? Qin : in);
        }
        if (C == 0 && B == 0 && A == 0) {
            if (in == Pin) {
                b = (b + 1) % m;
                ++ba;
            } else {
                a = (a + 1) % m;
                ++aa;
            }
        } else if ((C >= 0 && A > 0) || (C < 0 && B <= 0)) {
            if (in == Pin)
                R.push_back(P[a]);
            a = (a + 1) % n;
            ++aa;
        } else {
            if (in == Qin)
                R.push_back(Q[b]);
            b = (b + 1) % m;
            ++ba;
        }
    } while ((aa < n || ba < m) && aa < 2 * n && ba < 2 * m);
    if (in == Unknown) {
        if (inConvex(Q, P[0]))
            return P;
        if (inConvex(P, Q[0]))
            return Q;
    }
    return R;
}
/** Convex End **/