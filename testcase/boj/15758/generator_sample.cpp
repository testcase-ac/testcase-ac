#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static vector<int> shuffledCows(int n) {
    vector<int> cows;
    for (int i = 1; i <= n; ++i) cows.push_back(i);
    shuffle(cows.begin(), cows.end());
    return cows;
}

static vector<int> makeObservationFromOrder(const vector<int>& order, int len) {
    vector<int> positions;
    for (int i = 0; i < (int)order.size(); ++i) positions.push_back(i);
    shuffle(positions.begin(), positions.end());
    positions.resize(len);
    sort(positions.begin(), positions.end());

    vector<int> observation;
    for (int pos : positions) observation.push_back(order[pos]);
    return observation;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int minN = (mode == 2 || mode == 3) ? 2 : 1;
    int n = rnd.next(minN, mode == 4 ? 24 : 12);
    int m = rnd.next(1, mode == 0 ? 6 : 14);

    vector<vector<int>> observations;
    vector<int> base = shuffledCows(n);

    if (mode == 0) {
        observations.push_back(vector<int>{rnd.next(1, n)});
    } else if (mode == 1) {
        for (int i = 0; i < m; ++i) {
            int len = rnd.next(1, min(n, 5));
            observations.push_back(makeObservationFromOrder(base, len));
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            int len = rnd.next(2, min(n, 6));
            observations.push_back(makeObservationFromOrder(base, len));
        }
        if (n >= 2) {
            int a = base[rnd.next(n)];
            int b = base[rnd.next(n)];
            while (b == a) b = base[rnd.next(n)];
            observations.push_back(vector<int>{a, b});
            observations.push_back(vector<int>{b, a});
        }
    } else if (mode == 3) {
        int block = min(n, rnd.next(2, 7));
        vector<int> cycle;
        for (int i = 0; i < block; ++i) cycle.push_back(base[i]);

        for (int i = 0; i + 1 < block; ++i) {
            observations.push_back(vector<int>{cycle[i], cycle[i + 1]});
        }
        observations.push_back(vector<int>{cycle.back(), cycle.front()});

        while ((int)observations.size() < m) {
            int len = rnd.next(1, min(n, 4));
            observations.push_back(makeObservationFromOrder(base, len));
        }
    } else {
        for (int i = 0; i < m; ++i) {
            int len = rnd.wnext(min(n, 10), 2) + 1;
            observations.push_back(makeObservationFromOrder(base, len));
        }
    }

    println(n, (int)observations.size());
    for (const vector<int>& observation : observations) {
        printf("%d", (int)observation.size());
        for (int cow : observation) printf(" %d", cow);
        printf("\n");
    }

    return 0;
}
