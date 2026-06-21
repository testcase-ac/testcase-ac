#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 2) {
        n = rnd.next(7, 14);
    } else {
        n = rnd.next(15, 30);
    }

    int k = (mode == 0 ? 1 : rnd.next(1, n));
    if (mode == 3 && n >= 4) {
        k = rnd.next(max(1, n - 8), n);
    }

    vector<vector<int>> groups(k);
    vector<int> order(n);
    iota(order.begin(), order.end(), 1);

    if (mode == 1) {
        for (int rank = 1; rank <= n; ++rank) {
            groups[(rank - 1) % k].push_back(rank);
        }
    } else {
        shuffle(order.begin(), order.end());
        bool allowEmpty = (k > 1 && rnd.next(0, 99) < 35);
        if (allowEmpty) {
            for (int rank : order) {
                groups[rnd.next(0, k - 1)].push_back(rank);
            }
        } else {
            for (int i = 0; i < k; ++i) {
                groups[i].push_back(order.back());
                order.pop_back();
            }
            for (int rank : order) {
                groups[rnd.next(0, k - 1)].push_back(rank);
            }
        }
    }

    println(n, k);
    for (vector<int>& group : groups) {
        sort(group.begin(), group.end());
        vector<int> ranks;
        for (int i = 0; i < int(group.size()); ++i) {
            ranks.push_back(group[i] - i - 1);
        }
        if (rnd.next(0, 99) < 60) {
            shuffle(ranks.begin(), ranks.end());
        }

        cout << group.size();
        for (int rank : ranks) {
            cout << ' ' << rank;
        }
        cout << '\n';
    }

    return 0;
}
