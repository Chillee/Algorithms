int mobius[MAXPR];
bool sieve[MAXPR];
vector<int> primes;
void calcMobius() {
    mobius[1] = 1;
    for (int i = 2; i < MAXPR; i++) {
        if (!sieve[i]) {
            primes.push_back(i);
            mobius[i] = -1;
        }
        for (int j = 0; j < primes.size() && i * primes[j] < MAXPR; j++) {
            sieve[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                mobius[i * primes[j]] = 0;
                break;
            }
            mobius[i * primes[j]] = mobius[i] * -1;
        }
    }
}