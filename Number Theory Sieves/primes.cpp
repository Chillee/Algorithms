bool sieve[MAXPR];
vector<int> primes;
void calcPrimes() {
    for (int i = 2; i < MAXPR; i++) {
        if (!sieve[i])
            primes.push_back(i);
        for (int j = 0; j < primes.size() && i * primes[j] < MAXPR; j++) {
            sieve[primes[j] * i] = true;
            if (i % primes[j] == 0)
                break;
        }
    }
}