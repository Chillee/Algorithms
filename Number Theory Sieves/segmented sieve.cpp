vector<int> primes;
const int MAXPR = MAXN;
void calcPrimes() {
    const int S = round(sqrt(MAXPR));
    vector<bool> sieve(S + 1, true);
    vector<array<int, 2>> cp;
    primes.push_back(2);
    for (int i = 3; i < S; i += 2) {
        if (!sieve[i])
            continue;
        cp.push_back({i, (i * i - 1) / 2});
        for (int j = i * i; j <= S; j += 2 * i)
            sieve[j] = false;
    }
    vector<char> block(S);
    int high = (MAXPR - 1) / 2;
    for (int low = 0; low <= high; low += S) {
        fill(block.begin(), block.end(), true);
        for (auto &i : cp) {
            int p = i[0], idx = i[1];
            for (; idx < S; idx += p)
                block[idx] = false;
            i[1] = idx - S;
        }
        if (low == 0)
            block[0] = false;
        for (int i = 0; i < S && low + i <= high; i++)
            if (block[i])
                primes.push_back((low + i) * 2 + 1);
    };
}