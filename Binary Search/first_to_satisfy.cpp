int binSearch(int l, int r) {
    int mid = (l+r)/2;
    if (l==r) return l;
    if (f(mid)) return binSearch(l, mid);
    else return binSearch(mid+1, r);
}