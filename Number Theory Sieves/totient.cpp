bool sieve[MAXPR];
int phi[MAXPR];
vector<int> primes;
void calcTotient() {
    phi[1] = 1;
    for (int i = 2; i < MAXPR; i++) {
        if (!sieve[i]) {
            primes.push_back(i);
            phi[i] = i - 1;
        }
        for (int j = 0; j < primes.size() && i * primes[j] < MAXPR; j++) {
            sieve[i * primes[j]] = true;
            if (i % primes[j] == 0) {
                phi[i * primes[j]] = phi[i] * primes[j];
                break;
            }
            phi[i * primes[j]] = phi[i] * phi[primes[j]];
        }
    }
}