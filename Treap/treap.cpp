auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 rnd(seed);

struct node {
    node *l = nullptr, *r = nullptr;
    int val, key = rnd();
    int sz = 1;
    node(int value) : val(value) {}
    ~node() { delete l, delete r; }
    node *upd() {
        sz = 1 + (l ? l->sz : 0) + (r ? r->sz : 0);
        return this;
    }
};

struct treap {
    node *root;
    treap() { root = nullptr; }
    void split(node *t, int val, node *&l, node *&r) {
        if (!t) {
            l = nullptr, r = nullptr;
            return;
        } else if (t->val < val) {
            split(t->r, val, t->r, r);
            l = t;
        } else {
            split(t->l, val, l, t->l);
            r = t;
        }
        t->upd();
    }
    node *merge(node *l, node *r) {
        if (!l || !r)
            return (l ? l : r);
        if (l->key > r->key) {
            l->r = merge(l->r, r);
            return l->upd();
        } else {
            r->l = merge(r->l, l);
            return r->upd();
        }
    }
    bool find(node *t, int val) {
        if (!t)
            return false;
        if (t->val == val)
            return true;
        return find((t->val > val) ? t->l : t->r, val);
    }
    void insert(int val) {
        if (find(root, val))
            return;
        node *l, *r;
        split(root, val, l, r);
        root = merge(l, merge(new node(val), r));
    }
    void erase(int val) {
        if (!find(root, val))
            return;
        node *l, *t, *r;
        split(root, val, l, t);
        split(t, val + 1, t, r);
        delete t;
        root = merge(l, r);
    }
    int size() { return root ? root->sz : 0; }
    int index(node *t, int i) {
        int lsz = t->l ? t->l->sz : 0;
        if (i == lsz)
            return t->val;
        if (i < lsz)
            return index(t->l, i);
        return index(t->r, i - lsz - 1);
    }
    int indexof(node *t, int x) {
        int lsz = t->l ? t->l->sz : 0;
        if (t->val == x)
            return lsz;
        if (t->val < x)
            return lsz + 1 + indexof(t->r, x);
        return indexof(t->l, x);
    }
};