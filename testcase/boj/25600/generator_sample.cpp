#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 1000 : 30);
    vector<tuple<int, int, int>> scores;
    scores.reserve(n);

    auto add = [&](int a, int d, int g) {
        scores.emplace_back(a, d, g);
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(0, 8);
            int g = rnd.next(0, 8);
            add(d + g, d, g);
        }
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        for (int i = 0; i < n; ++i) {
            int zeroKind = rnd.next(0, 3);
            int a = zeroKind == 0 ? 0 : rnd.next(0, 30);
            int d = zeroKind == 1 ? 0 : rnd.next(0, 30);
            int g = zeroKind == 2 ? 0 : rnd.next(0, 30);
            add(a, d, g);
        }
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(9900, 10000);
            int d = rnd.next(9900, 10000);
            int g = rnd.next(9900, 10000);
            add(a, d, g);
        }
    } else if (mode == 3) {
        n = rnd.next(3, 15);
        for (int i = 0; i < n; ++i) {
            int sum = rnd.next(0, 10000);
            int d = rnd.next(0, sum);
            int g = sum - d;
            int a = max(0, min(10000, sum + rnd.next(-2, 2)));
            add(a, d, g);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int limit = mode == 4 ? rnd.next(20, 500) : 10000;
            add(rnd.next(0, limit), rnd.next(0, limit), rnd.next(0, limit));
        }
    }

    shuffle(scores.begin(), scores.end());

    println((int)scores.size());
    for (auto [a, d, g] : scores) {
        println(a, d, g);
    }

    return 0;
}
