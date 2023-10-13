import timeit
import unittest

def primeNumList(n):
    # generate a list of prime numbers up to limit n
    primes = [True] * (n + 1)
    p = 2
    while p**2 <= n:
        if primes[p]:
            for i in range(p**2, n + 1, p):
                primes[i] = False
        p += 1
    return [i for i in range(2, n + 1) if primes[i]] # this part GPTed :(

def prime_factors(n, prime_list):
    # get the prime factors of n using a given prime_list
    factors = []
    for prime in prime_list:
        if prime * prime > n:
            break
        while n % prime == 0:
            if prime not in factors:
                factors.append(prime)
            n //= prime
    if n > 1:
        factors.append(n)
    return factors

def optimizedCode():
    limit = 2500
    prime_list = primeNumList(limit)
    for i in range(2, limit):
        uniquePrimes = prime_factors(i, prime_list)

class TestOptimizedCode(unittest.TestCase):

    def test_prime_factors(self):
        results = {
            2: [2],
            3: [3],
            4: [2],
            5: [5],
            6: [2, 3],
            12: [2, 3],
            100: [2, 5],
            169: [13],
            200: [2, 5],
            2310: [2, 3, 5, 7, 11],
        }

        limit = 2500
        prime_list = primeNumList(limit)
        for num, expected_factors in results.items():
            with self.subTest(num=num):
                self.assertEqual(prime_factors(num, prime_list), expected_factors)


# Benchmark the code
if __name__ == "__main__":
    unittest.main(exit=False)
    benchmark_code = "optimizedCode()"
    setup_code = "from __main__ import optimizedCode"

    # Measure the execution time of optimizedCode function
    times = []
    for i in range(0, 5):
        times.append(timeit.timeit(benchmark_code, setup=setup_code, number=1))

    res = sum(times) / 5

    print(f"Average execution time after 5 runs: {res:.6f} seconds")
