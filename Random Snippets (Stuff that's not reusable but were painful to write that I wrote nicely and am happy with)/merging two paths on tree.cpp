pair<bool, array<int, 2>> canMerge(array<int, 4> pts) {
    auto cmp = [&](int a, int b) { return make_pair(lca.depth[a], a) > make_pair(lca.depth[b], b); };
    sort(pts.begin(), pts.end(), cmp);
    do {
        if (lca.dist(pts[0], pts[1]) + lca.dist(pts[1], pts[2]) + lca.dist(pts[2], pts[3]) == lca.dist(pts[0], pts[3]))
            return {true, {pts[0], pts[3]}};
    } while (next_permutation(pts.begin() + 1, pts.end(), cmp));
    return {false, {0, 0}};
}