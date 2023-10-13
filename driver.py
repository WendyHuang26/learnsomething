import prime
import timeit

def benchmarkedCode():
    # Call the optimized code function
    prime.optimizedCode()

    # Fetch prime factors for a range of numbers
    prime_list = prime.primeNumList(2500)  # Get the list of primes up to 2500
    for i in range(2, 11):  # Modify the range as needed
        factors = prime.prime_factors(i, prime_list)  # Pass prime_list here
        # We're calculating the factors, but not printing them

# Benchmarking
if __name__ == "__main__":
    benchmark_code = "benchmarkedCode()"
    setup_code = "from __main__ import benchmarkedCode"
    
    times = []
    for i in range(5):
        times.append(timeit.timeit(benchmark_code, setup=setup_code, number=1))
    
    res = sum(times) / 5
    print(f"Average execution time after 5 runs: {res:.6f} seconds")
