#include <iostream>
#include <random>
#include <cstdlib>
#include <chrono>
#include <map>
#include <numeric>
using namespace std;

static std::mt19937_64 seedRng;
using uint64 = unsigned long long;
using uint128 = __uint128_t;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device

uint64 mulMod(uint64 a, uint64 b, uint64 mod) {
    return static_cast<uint128>(a) * b % mod;
}

uint64 powMod(uint64 a, uint64 e, uint64 mod) {
    uint64 result = 1;
    while (e > 0) {
        if (e & 1) {
            result = mulMod(result, a, mod);
        }
        a = mulMod(a, a, mod);
        e >>= 1;
    }
    return result;
}

bool isPrime(uint64 n) {
    if (n < 2) {
        return false;
    }
    for (uint64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL,
                     23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) {
            return n == p;
        }
    }

    uint64 d = n - 1;
    int shifts = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++shifts;
    }

    for (uint64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL,
                     1795265022ULL}) {
        if (a % n == 0) {
            continue;
        }
        uint64 x = powMod(a, d, n);
        if (x == 1 || x == n - 1) {
            continue;
        }
        bool witness = true;
        for (int r = 1; r < shifts; ++r) {
            x = mulMod(x, x, n);
            if (x == n - 1) {
                witness = false;
                break;
            }
        }
        if (witness) {
            return false;
        }
    }

    return true;
}

uint64 rho(uint64 n) {
    if (n % 2 == 0) {
        return 2;
    }
    if (n % 3 == 0) {
        return 3;
    }

    for (uint64 c = 1;; ++c) {
        uint64 x = 2;
        uint64 y = 2;
        uint64 d = 1;
        while (d == 1) {
            x = (mulMod(x, x, n) + c) % n;
            y = (mulMod(y, y, n) + c) % n;
            y = (mulMod(y, y, n) + c) % n;
            uint64 diff = x > y ? x - y : y - x;
            d = std::gcd(diff, n);
        }
        if (d != n) {
            return d;
        }
    }
}

void addFactors(uint64 n, map<uint64, int>& factors) {
    if (n == 1) {
        return;
    }
    if (isPrime(n)) {
        ++factors[n];
        return;
    }

    uint64 factor = rho(n);
    addFactors(factor, factors);
    addFactors(n / factor, factors);
}

bool hasAllowedDivisorCount(uint64 n) {
    map<uint64, int> factors;
    addFactors(n, factors);

    int count = 1;
    for (auto [prime, exponent] : factors) {
        count *= exponent + 1;
        if (count > 47) {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	random_device rd;
	mt19937_64 g(rd());
	uniform_int_distribution<int> t(1,60);
	uniform_int_distribution<long long> n(1,99999999999999);
	int c=t(g);
	cout<<c;
	while(c--) {
	    long long value;
	    do {
	        value = n(g);
	    } while(!hasAllowedDivisorCount(value));
	    cout<<"\n\n"<<value;
	}
	cout<<'\n';
}
