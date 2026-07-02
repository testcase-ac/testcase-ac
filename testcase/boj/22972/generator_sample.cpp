#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<long long> positionsFromGaps(const vector<long long>& gaps) {
    vector<long long> positions = {0};
    for (long long gap : gaps) {
        positions.push_back(positions.back() + gap);
    }
    return positions;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 10);
    vector<long long> positions;

    if (mode == 0) {
        vector<long long> gaps;
        for (int i = 1; i < n; ++i) {
            gaps.push_back(rnd.next(1, 7));
        }
        positions = positionsFromGaps(gaps);
    } else if (mode == 1) {
        long long step = rnd.next(1, 12);
        long long jitterLimit = rnd.next(0, 2);
        positions = {0};
        for (int i = 1; i < n; ++i) {
            long long jitter = rnd.next(-jitterLimit, jitterLimit);
            long long nextPos = positions.back() + max(1LL, step + jitter);
            positions.push_back(nextPos);
        }
    } else if (mode == 2) {
        int pairs = (n - 1) / 2;
        long long width = rnd.next(20, 90);
        vector<long long> inner;
        for (int i = 0; i < pairs; ++i) {
            inner.push_back(rnd.next(1LL, width / 2 - 1));
        }
        sort(inner.begin(), inner.end());
        inner.erase(unique(inner.begin(), inner.end()), inner.end());
        positions = {0};
        for (long long x : inner) {
            positions.push_back(x);
            positions.push_back(width - x);
        }
        if (static_cast<int>(positions.size()) < n) {
            positions.push_back(width / 2);
        }
        positions.push_back(width);
        sort(positions.begin(), positions.end());
        positions.erase(unique(positions.begin(), positions.end()), positions.end());
        while (static_cast<int>(positions.size()) < n) {
            long long x = rnd.next(1LL, width - 1);
            if (!binary_search(positions.begin(), positions.end(), x)) {
                positions.push_back(x);
                sort(positions.begin(), positions.end());
            }
        }
        if (static_cast<int>(positions.size()) > n) {
            positions.resize(n - 1);
            if (positions.back() != width) {
                positions.push_back(width);
            }
            sort(positions.begin(), positions.end());
        }
    } else if (mode == 3) {
        vector<long long> gaps;
        long long small = rnd.next(1, 3);
        long long large = rnd.next(8, 20);
        for (int i = 1; i < n; ++i) {
            gaps.push_back(rnd.next(0, 2) == 0 ? small : large);
        }
        positions = positionsFromGaps(gaps);
    } else {
        positions = {0};
        while (static_cast<int>(positions.size()) < n) {
            long long x = rnd.next(1, 120);
            if (find(positions.begin(), positions.end(), x) == positions.end()) {
                positions.push_back(x);
            }
        }
        sort(positions.begin(), positions.end());
    }

    n = static_cast<int>(positions.size());
    vector<long long> distances;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            distances.push_back(positions[j] - positions[i]);
        }
    }
    sort(distances.begin(), distances.end());

    println(n);
    println(distances);

    return 0;
}
