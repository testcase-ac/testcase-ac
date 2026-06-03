#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

long long gcd_ll(long long a, long long b) {
    while (b != 0) {
        long long r = a % b;
        a = b;
        b = r;
    }
    return a;
}

long long lcm_ll(long long a, long long b) {
    return a / gcd_ll(a, b) * b;
}

void addCycle(vector<int>& p, const vector<int>& nodes) {
    int k = static_cast<int>(nodes.size());
    for (int i = 0; i < k; ++i) {
        p[nodes[i]] = nodes[(i + 1) % k] + 1;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> lengths;
    long long order = 1;
    int n = 0;

    if (mode == 0) {
        int fixedPoints = rnd.next(1, 20);
        lengths.assign(fixedPoints, 1);
    } else if (mode == 1) {
        lengths.push_back(rnd.next(2, 30));
    } else if (mode == 2) {
        int cycles = rnd.next(2, 6);
        for (int i = 0; i < cycles; ++i) {
            lengths.push_back(rnd.next(1, 8));
        }
    } else if (mode == 3) {
        vector<int> candidates = {2, 3, 4, 5, 7, 8, 9, 11, 13};
        shuffle(candidates.begin(), candidates.end());
        int cycles = rnd.next(2, 5);
        for (int i = 0; i < cycles; ++i) {
            lengths.push_back(candidates[i]);
        }
    } else {
        int cycles = rnd.next(3, 10);
        int base = rnd.next(2, 6);
        for (int i = 0; i < cycles; ++i) {
            lengths.push_back(rnd.next(1, base));
        }
    }

    vector<int> accepted;
    n = 0;
    for (int length : lengths) {
        long long nextOrder = lcm_ll(order, length);
        if (nextOrder <= 2000000000LL && n + length <= 60) {
            accepted.push_back(length);
            order = nextOrder;
            n += length;
        }
    }

    if (accepted.empty()) {
        accepted.push_back(1);
        n = 1;
    }

    vector<int> nodes(n);
    iota(nodes.begin(), nodes.end(), 0);
    shuffle(nodes.begin(), nodes.end());

    vector<int> p(n);
    int offset = 0;
    for (int length : accepted) {
        vector<int> cycle(nodes.begin() + offset, nodes.begin() + offset + length);
        if (length > 1) {
            shuffle(cycle.begin(), cycle.end());
        }
        addCycle(p, cycle);
        offset += length;
    }

    println(n);
    println(p);

    return 0;
}
