#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_COORD = 1000000000LL;

    int mode = rnd.next(0, 4);
    int M = rnd.next(1, mode == 0 ? 2 : 8);
    int N = rnd.next(1, mode == 0 ? 3 : 12);
    long long L;
    if (mode == 0) {
        L = rnd.next(1, 6);
    } else if (mode == 4) {
        L = rnd.next(999999900LL, MAX_COORD);
    } else {
        L = rnd.next(2, 40);
    }

    set<long long> usedShooters;
    vector<long long> shooters;
    while ((int)shooters.size() < M) {
        long long x;
        if (mode == 4) {
            x = rnd.next(MAX_COORD - 200, MAX_COORD);
        } else if (mode == 3) {
            x = rnd.next(1, 200);
        } else {
            x = rnd.next(1, 60);
        }
        if (usedShooters.insert(x).second) {
            shooters.push_back(x);
        }
    }

    set<pair<long long, long long>> usedAnimals;
    vector<pair<long long, long long>> animals;
    while ((int)animals.size() < N) {
        long long a, b;
        long long s = rnd.any(shooters);
        int pattern = rnd.next(0, 5);

        if (mode == 4) {
            long long dx = rnd.next(0LL, min(80LL, L - 1));
            a = max(1LL, s - dx);
            b = rnd.next(1LL, min(MAX_COORD, L - dx));
        } else if (pattern == 0) {
            a = s;
            b = rnd.next(1LL, min(20LL, L));
        } else if (pattern == 1) {
            long long dx = rnd.next(0LL, min(20LL, L - 1));
            a = max(1LL, s - dx);
            b = max(1LL, L - dx);
        } else if (pattern == 2) {
            long long dx = rnd.next(0LL, min(20LL, L - 1));
            a = min(MAX_COORD, s + dx);
            b = max(1LL, L - dx + 1);
        } else if (pattern == 3) {
            a = rnd.next(1, 80);
            b = rnd.next(1, 80);
        } else {
            long long dx = rnd.next(1, 25);
            a = (rnd.next(0, 1) == 0) ? max(1LL, s - dx) : min(MAX_COORD, s + dx);
            b = rnd.next(1, 25);
        }

        if (usedAnimals.insert({a, b}).second) {
            animals.push_back({a, b});
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(shooters.begin(), shooters.end());
    }
    shuffle(animals.begin(), animals.end());

    println(M, N, L);
    println(shooters);
    for (auto [a, b] : animals) {
        println(a, b);
    }

    return 0;
}
