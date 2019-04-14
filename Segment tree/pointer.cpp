struct Tree {
    Tree *pl, *pr;
    int nl = 0, nr = 0, val = 0;

    void updateVal() { val = pl->val + pr->val; }

    Tree(int l, int r, int A[]) {
        nl = l, nr = r;
        if (nl + 1 == nr) {
            val = A[nl];
            return;
        }
        pl = new Tree(nl, nl + nr >> 1, A);
        pr = new Tree(nl + nr >> 1, nr, A);
        updateVal();
    }
    void modify(int p, int x) {
        if (p < nl || nr <= p) {
            return;
        }
        if (nl + 1 == nr) {
            val = x;
            return;
        }
        pl->modify(p, x);
        pr->modify(p, x);
        updateVal();
    }
    int query(int l, int r) {
        if (l <= nl && r >= nr)
            return val;
        if (l >= nr || nl >= r)
            return 0;
        return pl->query(l, r) + pr->query(l, r);
    }
};