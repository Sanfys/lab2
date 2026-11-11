#pragma once
#include <vector>
#include <cmath>

// n-те просте число (n >= 1) перебором простих дільників
inline long long NthPrime(int n)
{
    std::vector<long long> primes;
    long long c = 2;
    while ((int)primes.size() < n)
    {
        bool ok = true;
        for (long long p : primes)
        {
            if (p * p > c) break;
            if (c % p == 0) { ok = false; break; }
        }
        if (ok) primes.push_back(c);
        ++c;
    }
    return primes.back();
}

inline bool IsPrime(long long x)
{
    if (x < 2) return false;
    for (long long d = 2; d * d <= x; ++d)
        if (x % d == 0) return false;
    return true;
}
