#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_M = 1000000000;

    int mode = rnd.next(0, 5);
    int k = rnd.next(1, mode == 5 ? 80 : 25);
    int n = rnd.next(1, min(30, k + rnd.next(0, 10)));
    int m;

    vector<int> nextVideo(k + 1);
    vector<int> initial(n);

    if (mode == 0) {
        m = 1;
        for (int i = 1; i <= k; ++i) nextVideo[i] = i;
    } else if (mode == 1) {
        m = rnd.next(2, min(MAX_M, 3 * max(1, k) + 10));
        for (int i = 1; i <= k; ++i) nextVideo[i] = i % k + 1;
    } else if (mode == 2) {
        m = rnd.any(vector<int>{2, 3, 10, 1000, MAX_M});
        int sink = rnd.next(1, k);
        for (int i = 1; i <= k; ++i) nextVideo[i] = sink;
        nextVideo[sink] = sink;
    } else if (mode == 3) {
        m = rnd.next(1, MAX_M);
        int cycleStart = rnd.next(1, k);
        for (int i = 1; i < k; ++i) nextVideo[i] = i + 1;
        nextVideo[k] = cycleStart;
    } else if (mode == 4) {
        m = rnd.next(1, MAX_M);
        vector<int> order(k);
        for (int i = 0; i < k; ++i) order[i] = i + 1;
        shuffle(order.begin(), order.end());
        int pos = 0;
        while (pos < k) {
            int len = rnd.next(1, k - pos);
            for (int i = 0; i < len; ++i) {
                nextVideo[order[pos + i]] = order[pos + (i + 1) % len];
            }
            pos += len;
        }
    } else {
        m = rnd.next(1, MAX_M);
        for (int i = 1; i <= k; ++i) nextVideo[i] = rnd.next(1, k);
    }

    for (int i = 0; i < n; ++i) {
        if (rnd.next(0, 3) == 0) {
            initial[i] = i % k + 1;
        } else {
            initial[i] = rnd.next(1, k);
        }
    }

    println(n, k, m);
    println(initial);
    for (int i = 1; i <= k; ++i) {
        if (i > 1) cout << ' ';
        cout << nextVideo[i];
    }
    cout << '\n';

    return 0;
}
