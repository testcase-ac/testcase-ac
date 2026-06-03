#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 4);
        m = rnd.next(1, 4);
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(1, 12);
    }

    int total = n + m;
    int maxBudget = (mode == 4 ? 100000 : rnd.next(0, 5000));

    vector<int> s(n);
    vector<vector<int>> t(n, vector<int>(total, 0));

    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            s[i] = rnd.next(0, 20);
        } else if (mode == 4 && rnd.next(0, 3) == 0) {
            s[i] = 100000;
        } else {
            s[i] = rnd.next(0, maxBudget);
        }

        vector<int> recipients;
        for (int j = 0; j < total; ++j) {
            if (i != j) {
                recipients.push_back(j);
            }
        }
        shuffle(recipients.begin(), recipients.end());

        int spend;
        if (mode == 2) {
            spend = s[i];
        } else if (mode == 3) {
            spend = rnd.next(0, min(s[i], 20));
        } else {
            spend = rnd.next(0, s[i]);
        }

        int recipientCount = static_cast<int>(recipients.size());
        int active = 0;
        if (spend > 0) {
            if (mode == 1) {
                active = rnd.next(1, min(recipientCount, 2));
            } else if (mode == 5) {
                active = rnd.next(max(1, total / 2), recipientCount);
            } else {
                active = rnd.next(1, recipientCount);
            }
        }

        for (int k = 0; k < active; ++k) {
            int remainingSlots = active - k - 1;
            int value = (remainingSlots == 0 ? spend : rnd.next(0, spend));
            t[i][recipients[k]] = value;
            spend -= value;
        }
    }

    println(n, m);
    println(s);
    for (int i = 0; i < n; ++i) {
        println(t[i]);
    }

    return 0;
}
