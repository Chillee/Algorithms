/* Polygon Start */
double areaTriangle(pt a, pt b, pt c) { return abs(cross(b - a, c - a)) / 2.0; }
double areaPolygon(vector<pt> p) { // if negative, p is in clock-wise order.
    double area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++)
        area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n -1
    return area / 2.0;
}
// true if P at least as high as A (blue part)
bool above(pt a, pt p) { return p.y >= a.y; }
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) { return (above(q, a) - above(p, a)) * orient(a, p, q) > 0; }
// if strict, returns false when A is on the boundary
bool inPolygon(vector<pt> &p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}
/* Polygon End */