#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<int> increasing(int n) {
    vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i + 1;
    return p;
}

vector<int> balancedOrder(int lo, int hi) {
    if (lo > hi) return {};

    int mid = (lo + hi) / 2;
    if ((hi - lo + 1) % 2 == 0 && rnd.next(2) == 1) ++mid;

    vector<int> p{mid};
    vector<int> left = balancedOrder(lo, mid - 1);
    vector<int> right = balancedOrder(mid + 1, hi);

    while (!left.empty() || !right.empty()) {
        bool takeLeft = right.empty() || (!left.empty() && rnd.next(2) == 0);
        if (takeLeft) {
            p.push_back(left.front());
            left.erase(left.begin());
        } else {
            p.push_back(right.front());
            right.erase(right.begin());
        }
    }

    return p;
}

vector<int> alternatingExtremes(int n) {
    vector<int> p;
    int lo = 1, hi = n;
    bool takeLow = rnd.next(2) == 0;
    while (lo <= hi) {
        if (takeLow) {
            p.push_back(lo++);
        } else {
            p.push_back(hi--);
        }
        if (rnd.next(3) != 0) takeLow = !takeLow;
    }
    return p;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(8, 20);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(5);
        int n = (tc == 0 ? 1 : rnd.next(2, 20));
        vector<int> p = increasing(n);

        if (mode == 0) {
            if (rnd.next(2) == 0) reverse(p.begin(), p.end());
        } else if (mode == 1) {
            p = balancedOrder(1, n);
        } else if (mode == 2) {
            shuffle(p.begin(), p.end());
        } else if (mode == 3) {
            p = alternatingExtremes(n);
        } else {
            int root = rnd.next(1, n);
            vector<int> left, right;
            for (int x = 1; x <= n; ++x) {
                if (x < root) left.push_back(x);
                if (x > root) right.push_back(x);
            }
            shuffle(left.begin(), left.end());
            shuffle(right.begin(), right.end());
            p = {root};
            if (rnd.next(2) == 0) {
                p.insert(p.end(), left.begin(), left.end());
                p.insert(p.end(), right.begin(), right.end());
            } else {
                p.insert(p.end(), right.begin(), right.end());
                p.insert(p.end(), left.begin(), left.end());
            }
        }

        println(n);
        println(p);
    }

    return 0;
}
