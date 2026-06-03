#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

vector<int> shuffledUniquePositions(int n, int l) {
    vector<int> candidates;
    for (int x = 1; x < l; ++x)
        candidates.push_back(x);
    shuffle(candidates.begin(), candidates.end());

    vector<int> positions(candidates.begin(), candidates.begin() + n);
    shuffle(positions.begin(), positions.end());
    return positions;
}

vector<int> clusteredPositions(int n, int l) {
    vector<int> positions;
    set<int> used;
    int center = rnd.next(1, l - 1);
    int radius = rnd.next(1, min(30, l - 1));

    for (int attempts = 0; (int)positions.size() < n && attempts < 2000; ++attempts) {
        int x = center + rnd.next(-radius, radius);
        if (x < 1 || x >= l)
            continue;
        if (used.insert(x).second)
            positions.push_back(x);
    }

    while ((int)positions.size() < n) {
        int x = rnd.next(1, l - 1);
        if (used.insert(x).second)
            positions.push_back(x);
    }

    shuffle(positions.begin(), positions.end());
    return positions;
}

vector<int> endpointHeavyPositions(int n, int l) {
    vector<int> positions;
    set<int> used;
    vector<int> candidates;

    for (int x = 1; x < l && x <= 20; ++x)
        candidates.push_back(x);
    for (int x = max(1, l - 20); x < l; ++x)
        candidates.push_back(x);

    shuffle(candidates.begin(), candidates.end());
    for (int x : candidates) {
        if ((int)positions.size() == n)
            break;
        if (used.insert(x).second)
            positions.push_back(x);
    }

    while ((int)positions.size() < n) {
        int x = rnd.next(1, l - 1);
        if (used.insert(x).second)
            positions.push_back(x);
    }

    shuffle(positions.begin(), positions.end());
    return positions;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int l = rnd.any(vector<int>{100, 101, rnd.next(120, 300), rnd.next(301, 1000)});
    int n = 1;
    int m = 1;

    if (mode == 0) {
        n = rnd.next(1, min(8, l - 2));
        m = rnd.any(vector<int>{1, 2, min(100, l - n - 1)});
    } else if (mode == 1) {
        n = rnd.next(1, min(12, l - 2));
        m = rnd.next(1, min(12, l - n - 1));
    } else if (mode == 2) {
        n = rnd.next(2, min(20, l - 2));
        m = rnd.next(1, min(30, l - n - 1));
    } else if (mode == 3) {
        n = rnd.next(1, min(40, l - 2));
        m = rnd.next(1, min(100, l - n - 1));
    } else {
        n = rnd.any(vector<int>{1, 2, 49, 50});
        n = min(n, l - 2);
        m = rnd.next(1, min(100, l - n - 1));
    }

    vector<int> positions;
    if (mode == 1) {
        positions = clusteredPositions(n, l);
    } else if (mode == 2) {
        positions = endpointHeavyPositions(n, l);
    } else {
        positions = shuffledUniquePositions(n, l);
    }

    println(n, m, l);
    println(positions);

    return 0;
}
