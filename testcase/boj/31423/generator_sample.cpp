#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomName(int maxLength) {
    int length = rnd.next(1, maxLength);
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        char c = char('a' + rnd.next(0, 25));
        s.push_back(c);
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(2, 15);
    int maxNameLength = rnd.next(1, 8);

    vector<string> names(n + 1);
    for (int i = 1; i <= n; ++i) {
        names[i] = randomName(maxNameLength);
    }

    vector<pair<int, int>> operations;

    if (mode == 0) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());
        int root = order[0];
        for (int k = 1; k < n; ++k) {
            operations.push_back({root, order[k]});
        }
    } else if (mode == 1) {
        vector<int> order(n);
        for (int i = 0; i < n; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());
        for (int k = 0; k + 1 < n; ++k) {
            operations.push_back({order[k + 1], order[k]});
        }
    } else if (mode == 2) {
        vector<int> alive(n);
        for (int i = 0; i < n; ++i) alive[i] = i + 1;
        shuffle(alive.begin(), alive.end());
        while (alive.size() > 1) {
            int sourcePos = rnd.next(1, (int)alive.size() - 1);
            operations.push_back({alive[0], alive[sourcePos]});
            alive.erase(alive.begin() + sourcePos);
            if (rnd.next(0, 1)) {
                rotate(alive.begin(), alive.begin() + 1, alive.end());
            }
        }
    } else {
        vector<int> alive(n);
        for (int i = 0; i < n; ++i) alive[i] = i + 1;
        while (alive.size() > 1) {
            int a = rnd.next(0, (int)alive.size() - 1);
            int b = rnd.next(0, (int)alive.size() - 2);
            if (b >= a) ++b;
            operations.push_back({alive[a], alive[b]});
            alive.erase(alive.begin() + b);
        }
    }

    println(n);
    for (int i = 1; i <= n; ++i) {
        println(names[i]);
    }
    for (auto [i, j] : operations) {
        println(i, j);
    }

    return 0;
}
