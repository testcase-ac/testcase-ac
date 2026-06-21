#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, 16);
    vector<pair<int, int>> clay;

    if (mode == 0) {
        n = rnd.next(2, 16);
        int base = rnd.next(1, 6);
        for (int i = 0; i < n; ++i) {
            int mult = rnd.next(1, 100 / base);
            int a = base * mult;
            int b = rnd.next(1, 100);
            clay.push_back({a, b});
        }
    } else if (mode == 1) {
        n = rnd.next(6, 16);
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
        shuffle(primes.begin(), primes.end());
        for (int i = 0; i < n; ++i) {
            int b = rnd.next(1, 100);
            clay.push_back({primes[i], b});
        }
    } else if (mode == 2) {
        n = rnd.next(3, 16);
        int first = rnd.next(1, 25);
        int second = rnd.next(1, 25);
        for (int i = 0; i < n; ++i) {
            int a = (i % 2 == 0 ? first : second);
            int b = rnd.next(1, 100);
            clay.push_back({a, b});
        }
    } else if (mode == 3) {
        n = rnd.next(4, 16);
        int current = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            if (i > 0 && current <= 50 && rnd.next(3) != 0) {
                current *= rnd.next(1, 2);
            }
            int a = min(current, 100);
            int b = (i % 2 == 0) ? rnd.next(70, 100) : rnd.next(1, 40);
            clay.push_back({a, b});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(1, 100);
            int b = rnd.next(1, 100);
            clay.push_back({a, b});
        }
    }

    println(n);
    for (const auto& [a, b] : clay) {
        println(a, b);
    }

    return 0;
}
