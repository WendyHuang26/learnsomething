#include <iostream>
#include <vector>
#include <cmath>

const int limit = 2500;
std::vector<int> prime_numbers;

void generatePrimes() {
    std::vector<bool> sieve(limit + 1, true);
    sieve[0] = sieve[1] = false;
    for (int p = 2; p * p <= limit; p++) {
        if (sieve[p]) {
            for (int i = p * p; i <= limit; i += p) {
                sieve[i] = false;
            }
        }
    }
    for (int i = 2; i <= limit; ++i) {
        if (sieve[i]) {
            prime_numbers.push_back(i);
        }
    }
}

int count_prime_factors(int n) {
    int count = 0;
    for (int prime : prime_numbers) {
        if (prime * prime > n) break;
        if (n % prime == 0) {
            ++count;
            while (n % prime == 0) {
                n /= prime;
            }
        }
    }
    if (n > 1) ++count;
    return count;
}

void optimizedCode() {
    generatePrimes();
    for (int i = 2; i <= limit; ++i) {
        int count = count_prime_factors(i);
    }
}

int main() {
    optimizedCode();

    // Just to check output:
    for (int i = 2; i <= 10; ++i) {
        int count = count_prime_factors(i);
        std::cout << i << ": " << count << " unique primes" << std::endl;
    }

    return 0;
}
