bool checkhp(line &a, line &b, line &me) { return sgn(me.side(inter(a, b).second)) > 0; }
vector<pt> halfPlaneIntersection(vector<line> border) { // O(n log n): Finds convex polygon of intersecting half planes.
    border.push_back(line{pt{-INF, -INF}, pt{INF, -INF}});
    border.push_back(line{pt{INF, -INF}, pt{INF, INF}});
    border.push_back(line{pt{INF, INF}, pt{-INF, INF}});
    border.push_back(line{pt{-INF, INF}, pt{-INF, -INF}});

    sort(border.begin(), border.end(), [](auto a, auto b) { return polarCmp()(a.v, b.v); });
    auto eq = [](line a, line b) { return sgn(atan2(a.v.y, a.v.x) - atan2(b.v.y, b.v.x)) == 0; };
    border.resize(unique(border.begin(), border.end(), eq) - border.begin());
    deque<line> deq;
    for (int i = 0; i < border.size(); ++i) {
        line cur = border[i];
        while (deq.size() > 1 && !checkhp(deq[deq.size() - 2], deq[deq.size() - 1], cur))
            deq.pop_back();
        while (deq.size() > 1 && !checkhp(deq[0], deq[1], cur))
            deq.pop_front();
        deq.push_back(cur);
    }
    while (deq.size() > 1 && !checkhp(deq[deq.size() - 2], deq[deq.size() - 1], deq[0]))
        deq.pop_back();

    vector<pt> pts;
    for (int i = 0; i < deq.size(); i++)
        pts.push_back(inter(deq[i], deq[(i + 1) % deq.size()]).second);
    return pts;
}