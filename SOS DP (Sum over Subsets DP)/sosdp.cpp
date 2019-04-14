int F[1 << MAXBITS];
for (int i = 0; i <= MAXBITS; ++i) {
    for (int mask = 0; mask < (1 << MAXBITS); ++mask) {
        if (mask & (1 << i)) {
            F[mask] = max(F[mask], F[mask ^ (1 << i)]);
        }
    }
}