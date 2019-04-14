int fac;
template <class It> int perm_to_int(It begin, It end) {
    int x = 0, n = 0;
    for (It i = begin; i != end; ++i, ++n)
        if (*i < *begin)
            ++x;
    int val = 0;
    if (n > 2)
        val = perm_to_int(++begin, end);
    else
        val = 0;
    val += fac[n - 1] * x;
    return val;
}
template <class It> void int_to_perm(int val, It begin, It end) {
    int fac = fac[end - begin - 1];
    // Note that the division result will fit in an integer !
    int x = val / fac;
    nth_element(begin, begin + x, end);
    swap(*begin, *(begin + x));
    if (end - begin > 2)
        int_to_perm(val % fac, ++begin, end);
}