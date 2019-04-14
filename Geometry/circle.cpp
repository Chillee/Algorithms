/* Circle Start */
struct circle {
    pt c;
    double r;
};
pt circumCenter(pt a, pt b, pt c) {
    b = b - a, c = c - a;     // consider coordinates relative to A
    assert(cross(b, c) != 0); // no circumcircle if A,B,C aligned
    return a + (b * c.sq() - c * b.sq()).perp() / cross(b, c) / 2;
}
double circumRadius(pt a, pt b, pt c) { return (a - b).abs() * (b - c).abs() * (c - a).abs() / abs(orient(a, b, c)) / 2.; }
circle circumCircle(pt a, pt b, pt c) { return {circumCenter(a, b, c), circumRadius(a, b, c)}; }
int circleLine(circle c, line l, pair<pt, pt> &out) {
    double h2 = c.r * c.r - l.sqDist(c.c);
    if (h2 >= 0) {                         // the line touches the circle
        pt p = l.proj(c.c);                // point P
        pt h = l.v * sqrt(h2) / l.v.abs(); // vector parallel to l, of length h
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}
int circleCircle(circle c1, circle c2, pair<pt, pt> &out) {
    pt d = c2.c - c1.c;
    double d2 = d.sq();
    if (d2 == 0) { // concentric circles
        assert(c1.r != c2.r);
        return 0;
    }
    double pd = (d2 + c1.r * c1.r - c2.r * c2.r) / 2; // = |O_1P| * d
    double h2 = c1.r * c1.r - pd * pd / d2;           // = hˆ2
    if (h2 >= 0) {
        pt p = c1.c + d * pd / d2, h = d.perp() * sqrt(h2 / d2);
        out = {p - h, p + h};
    }
    return 1 + sgn(h2);
}
int tangents(circle c1, circle c2, bool inner, vector<pair<pt, pt>> &out) {
    if (inner)
        c2.r = -c2.r;
    pt d = c2.c - c1.c;
    double dr = c1.r - c2.r, d2 = d.sq(), h2 = d2 - dr * dr;
    if (d2 == 0 || h2 < 0) {
        assert(h2 != 0);
        return 0;
    }
    for (int sign : {-1, 1}) {
        pt v = (d * dr + d.perp() * sqrt(h2) * sign) / d2;
        out.push_back({c1.c + v * c1.r, c2.c + v * c2.r});
    }
    return 1 + (h2 > 0);
}

// IMPORTANT: random_shuffle(pts.begin(), pts.end())
circle MEC(vector<pt> &pts, vector<pt> ch = {}) { // Minimum Enclosing Circle
    if (pts.empty() || ch.size() == 3) {
        if (ch.size() == 0)
            return {0, -1};
        else if (ch.size() == 1)
            return {ch[0], 0};
        else if (ch.size() == 2)
            return {(ch[0] + ch[1]) / 2, (ch[0] - ch[1]).abs() / 2};
        else
            return circumCircle(ch[0], ch[1], ch[2]);
    }
    auto p = pts.back();
    pts.pop_back();
    auto c = MEC(pts, ch);
    if (sgn((p - c.c).abs() - c.r) > 0) {
        ch.push_back(p);
        c = MEC(pts, ch);
    }
    pts.push_back(p);
    return c;
}
/* Circle End */