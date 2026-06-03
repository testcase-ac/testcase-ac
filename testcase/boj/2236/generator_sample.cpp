#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    int k;
    vector<int> importance;

    if (mode == 0) {
        n = 1;
        k = rnd.next(1, 20);
        importance = {rnd.next(0, 1000)};
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        k = rnd.next(n + 1, 20);
        int value = rnd.next(0, 1000);
        importance.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        k = rnd.next(1, 20);
        importance.assign(n, 0);
        int spikes = rnd.next(1, min(n, 4));
        vector<int> positions(n);
        for (int i = 0; i < n; ++i) positions[i] = i;
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < spikes; ++i) {
            importance[positions[i]] = rnd.next(1, 1000);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 15);
        k = rnd.next(1, min(20, n));
        int current = rnd.next(0, 40);
        for (int i = 0; i < n; ++i) {
            current = min(1000, current + rnd.next(0, 80));
            importance.push_back(current);
        }
        if (rnd.next(2) == 0) reverse(importance.begin(), importance.end());
    } else if (mode == 4) {
        n = rnd.next(5, 18);
        k = rnd.next(1, 20);
        int low = rnd.next(0, 20);
        int high = rnd.next(900, 1000);
        for (int i = 0; i < n; ++i) {
            importance.push_back((i % 2 == 0) ? high - rnd.next(0, 30) : low + rnd.next(0, 30));
        }
    } else if (mode == 5) {
        n = rnd.next(8, 25);
        k = rnd.next(1, 20);
        int groups = rnd.next(2, 5);
        vector<int> values;
        for (int i = 0; i < groups; ++i) values.push_back(rnd.next(0, 1000));
        for (int i = 0; i < n; ++i) importance.push_back(rnd.any(values));
    } else if (mode == 6) {
        n = rnd.next(20, 50);
        k = rnd.next(1, 20);
        int upper = rnd.next(50, 1000);
        for (int i = 0; i < n; ++i) importance.push_back(rnd.next(0, upper));
    } else {
        n = rnd.next(2, 20);
        k = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(5) == 0) {
                importance.push_back(rnd.next(0, 1) ? 0 : 1000);
            } else {
                importance.push_back(rnd.next(0, 1000));
            }
        }
    }

    println(n, k);
    println(importance);

    return 0;
}
