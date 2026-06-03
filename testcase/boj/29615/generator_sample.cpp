#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(1, 14);
    }
    int m = rnd.next(1, n);

    vector<int> waiting(n);
    for (int i = 0; i < n; ++i) {
        waiting[i] = i + 1;
    }

    if (mode == 1) {
        reverse(waiting.begin(), waiting.end());
    } else if (mode == 2) {
        int split = rnd.next(0, n);
        rotate(waiting.begin(), waiting.begin() + split, waiting.end());
    } else if (mode == 3) {
        vector<int> odd, even;
        for (int value = 1; value <= n; ++value) {
            if (value % 2 == 1) {
                odd.push_back(value);
            } else {
                even.push_back(value);
            }
        }
        waiting.clear();
        for (int value : odd) {
            waiting.push_back(value);
        }
        for (int value : even) {
            waiting.push_back(value);
        }
    } else if (mode >= 4) {
        shuffle(waiting.begin(), waiting.end());
    }

    vector<int> friends;
    if (mode == 0) {
        for (int i = 0; i < m; ++i) {
            friends.push_back(waiting[i]);
        }
    } else if (mode == 1) {
        for (int i = n - m; i < n; ++i) {
            friends.push_back(waiting[i]);
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n && (int)friends.size() < m; i += 2) {
            friends.push_back(i);
        }
        for (int i = 2; i <= n && (int)friends.size() < m; i += 2) {
            friends.push_back(i);
        }
    } else {
        vector<int> labels = waiting;
        shuffle(labels.begin(), labels.end());
        friends.assign(labels.begin(), labels.begin() + m);
    }

    shuffle(friends.begin(), friends.end());

    println(n, m);
    println(waiting);
    println(friends);

    return 0;
}
