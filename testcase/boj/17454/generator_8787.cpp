#include "testlib.h"
#include <vector>
#include <array>
#include <numeric>
using namespace std;

pair<int,int> randomCoprime(int lo, int hi) {
    while (true) {
        int a = rnd.next(lo, hi);
        int b = rnd.next(lo, hi);
        if (std::gcd(a, b) == 1) return {a, b};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<array<int, 6>> tests;

    // Always include some fixed interesting cases (from the statement samples)
    tests.push_back({3, 2, 3, 2, 2, 1});
    tests.push_back({2, 3, 1, 2, 1, 3});
    tests.push_back({1, 1, 2, 3, 1, 2});

    int targetT = rnd.next(3, 12);
    while ((int)tests.size() < targetT) {
        int type = rnd.next(1, 5);
        int DH, DS, HD, HS, SD, SH;

        if (type == 1) {
            // Completely random coprime pairs
            auto p1 = randomCoprime(1, 1000);
            auto p2 = randomCoprime(1, 1000);
            auto p3 = randomCoprime(1, 1000);
            DH = p1.first; DS = p1.second;
            HD = p2.first; HS = p2.second;
            SD = p3.first; SH = p3.second;
        } else if (type == 2) {
            // Small numbers, easy to inspect
            auto p1 = randomCoprime(1, 10);
            auto p2 = randomCoprime(1, 10);
            auto p3 = randomCoprime(1, 10);
            DH = p1.first; DS = p1.second;
            HD = p2.first; HS = p2.second;
            SD = p3.first; SH = p3.second;
        } else if (type == 3) {
            // Donghyun tends to be strong in polls where he appears
            int big, small;
            // H poll: D vs S (HD : HS) - favor D
            do {
                big = rnd.next(5, 20);
                small = rnd.next(1, 5);
            } while (std::gcd(big, small) != 1);
            HD = big; HS = small;

            // S poll: D vs H (SD : SH) - favor D
            do {
                big = rnd.next(5, 20);
                small = rnd.next(1, 5);
            } while (std::gcd(big, small) != 1);
            SD = big; SH = small;

            // D poll: H vs S (DH : DS) - fairly random small
            auto p = randomCoprime(1, 20);
            DH = p.first; DS = p.second;
        } else if (type == 4) {
            // Donghyun tends to be weak in polls where he appears
            int big, small;
            // H poll: D vs S (HD : HS) - favor S
            do {
                small = rnd.next(1, 5);
                big = rnd.next(5, 20);
            } while (std::gcd(big, small) != 1);
            HD = small; HS = big;

            // S poll: D vs H (SD : SH) - favor H
            do {
                small = rnd.next(1, 5);
                big = rnd.next(5, 20);
            } while (std::gcd(big, small) != 1);
            SD = small; SH = big;

            // D poll: H vs S (DH : DS) - random small
            auto p = randomCoprime(1, 20);
            DH = p.first; DS = p.second;
        } else {
            // Cyclic, tightly coupled ratios
            int a = rnd.next(1, 9);
            int b = rnd.next(1, 9);
            int c = rnd.next(1, 9);

            // D poll: H vs S = b : c
            {
                int x = b, y = c;
                int g = std::gcd(x, y);
                x /= g; y /= g;
                DH = x; DS = y;
            }

            // H poll: D vs S = c : a
            {
                int x = c, y = a;
                int g = std::gcd(x, y);
                x /= g; y /= g;
                HD = x; HS = y;
            }

            // S poll: D vs H = a : b
            {
                int x = a, y = b;
                int g = std::gcd(x, y);
                x /= g; y /= g;
                SD = x; SH = y;
            }
        }

        tests.push_back({DH, DS, HD, HS, SD, SH});
    }

    int T = (int)tests.size();
    println(T);
    for (auto &v : tests) {
        println(v[0], v[1], v[2], v[3], v[4], v[5]);
    }

    return 0;
}
