#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> a;
    set<long long> used;

    auto getUnique = [&](long long lo, long long hi) -> long long {
        while (true) {
            long long x = rnd.next(lo, hi);
            if (!used.count(x)) {
                used.insert(x);
                return x;
            }
        }
    };

    int type = rnd.next(0, 9);

    switch (type) {
        case 0: {
            // N = 3, minimal size, several compositions
            int variant = rnd.next(0, 3);
            if (variant == 0) {
                // 3 positives
                a.push_back(getUnique(1, 20));
                a.push_back(getUnique(1, 20));
                a.push_back(getUnique(1, 20));
            } else if (variant == 1) {
                // 3 negatives
                a.push_back(getUnique(-20, -1));
                a.push_back(getUnique(-20, -1));
                a.push_back(getUnique(-20, -1));
            } else if (variant == 2) {
                // 2 negatives, 1 positive
                a.push_back(getUnique(-20, -1));
                a.push_back(getUnique(-20, -1));
                a.push_back(getUnique(1, 20));
            } else {
                // includes zero: {- , 0, +}
                a.push_back(0);
                used.insert(0);
                a.push_back(getUnique(-20, -1));
                a.push_back(getUnique(1, 20));
            }
            break;
        }
        case 1: {
            // Small N, numbers near zero (hand-checkable)
            int N = rnd.next(3, 8);
            while ((int)a.size() < N) {
                long long x = rnd.next(-10LL, 10LL);
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
        case 2: {
            // Moderate N, mix of medium values and maybe extremes
            int N = rnd.next(5, 12);
            if (rnd.next(0, 1) == 0 && N >= 2) {
                a.push_back(-1000000000LL);
                used.insert(-1000000000LL);
                a.push_back(1000000000LL);
                used.insert(1000000000LL);
            }
            while ((int)a.size() < N) {
                long long x = rnd.next(-1000LL, 1000LL);
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
        case 3: {
            // Clustered near -1e9, +1e9, and 0
            int N = rnd.next(10, 20);
            while ((int)a.size() < N) {
                int group = rnd.next(0, 2);
                long long x;
                if (group == 0) {
                    // big negative
                    x = -1000000000LL + rnd.next(0, 1000);
                } else if (group == 1) {
                    // around zero
                    x = rnd.next(-1000LL, 1000LL);
                } else {
                    // big positive
                    x = 1000000000LL - rnd.next(0, 1000);
                }
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
        case 4: {
            // Ensure at least one exact zero-sum triple exists
            int N = rnd.next(3, 10);
            // build one special triple
            while (true) {
                long long x = rnd.next(-50LL, 50LL);
                long long y = rnd.next(-50LL, 50LL);
                if (x == y) continue;
                long long z = -(x + y);
                if (z < -1000000000LL || z > 1000000000LL) continue;
                if (z == x || z == y) continue;
                if (used.count(x) || used.count(y) || used.count(z)) continue;
                used.insert(x);
                used.insert(y);
                used.insert(z);
                a.push_back(x);
                a.push_back(y);
                a.push_back(z);
                break;
            }
            // fill rest with random distinct values near zero
            while ((int)a.size() < N) {
                long long v = rnd.next(-100LL, 100LL);
                if (!used.count(v)) {
                    used.insert(v);
                    a.push_back(v);
                }
            }
            break;
        }
        case 5: {
            // All positive numbers
            int N = rnd.next(3, 10);
            while ((int)a.size() < N) {
                long long x = rnd.next(1LL, 1000LL);
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
        case 6: {
            // All negative numbers
            int N = rnd.next(3, 10);
            while ((int)a.size() < N) {
                long long x = rnd.next(-1000LL, -1LL);
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
        case 7: {
            // One negative, rest positive
            int N = rnd.next(3, 12);
            long long neg = getUnique(-1000LL, -1LL);
            a.push_back(neg);
            while ((int)a.size() < N) {
                long long x = rnd.next(1LL, 1000LL);
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
        case 8: {
            // One positive, rest negative
            int N = rnd.next(3, 12);
            long long pos = getUnique(1LL, 1000LL);
            a.push_back(pos);
            while ((int)a.size() < N) {
                long long x = rnd.next(-1000LL, -1LL);
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
        case 9: {
            // Contains zero, plus mix of positives and negatives
            int N = rnd.next(3, 12);
            a.push_back(0);
            used.insert(0);
            // ensure at least one positive and one negative if possible
            if (N >= 3) {
                a.push_back(getUnique(1LL, 100LL));
                a.push_back(getUnique(-100LL, -1LL));
            }
            while ((int)a.size() < N) {
                long long x = rnd.next(-100LL, 100LL);
                if (x == 0) continue;
                if (!used.count(x)) {
                    used.insert(x);
                    a.push_back(x);
                }
            }
            break;
        }
    }

    // Shuffle to avoid any sorted bias
    shuffle(a.begin(), a.end());

    int N = (int)a.size();
    println(N);
    println(a);

    return 0;
}
