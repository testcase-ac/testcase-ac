#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> sortedValues(int count, int parity, int lo, int hi) {
    vector<int> values;
    for (int i = 0; i < count; ++i) {
        int x = rnd.next(lo, hi);
        if ((x & 1) != parity) ++x;
        if (x > hi) x -= 2;
        values.push_back(x);
    }
    sort(values.begin(), values.end());
    return values;
}

int boundedByParity(int value, int parity) {
    if ((value & 1) != parity) ++value;
    if (value > 1000000000) value -= 2;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 24);
    vector<int> a;

    if (mode == 0) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 80));
        sort(a.begin(), a.end());
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(1, 80));
        sort(a.rbegin(), a.rend());
    } else if (mode == 2) {
        int oddCount = rnd.next(0, n);
        int evenCount = n - oddCount;
        vector<int> odd = sortedValues(oddCount, 1, 1, 99);
        vector<int> even = sortedValues(evenCount, 0, 1, 100);
        while (!odd.empty() || !even.empty()) {
            bool takeOdd = even.empty() || (!odd.empty() && rnd.next(0, 1));
            if (takeOdd) {
                a.push_back(odd.back());
                odd.pop_back();
            } else {
                a.push_back(even.back());
                even.pop_back();
            }
        }
        reverse(a.begin(), a.end());
    } else if (mode == 3) {
        int currentParity = rnd.next(0, 1);
        int base = rnd.next(1, 20);
        while ((int)a.size() < n) {
            int len = min(n - (int)a.size(), rnd.next(1, 5));
            vector<int> block;
            for (int i = 0; i < len; ++i) {
                block.push_back(boundedByParity(base + rnd.next(0, 40), currentParity));
            }
            if (rnd.next(0, 1)) sort(block.begin(), block.end());
            else sort(block.rbegin(), block.rend());
            a.insert(a.end(), block.begin(), block.end());
            currentParity ^= 1;
            base += rnd.next(0, 12);
        }
    } else if (mode == 4) {
        int distinct = rnd.next(1, min(n, 6));
        vector<int> pool;
        for (int i = 0; i < distinct; ++i) pool.push_back(rnd.next(1, 30));
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 5) {
        n = rnd.next(18, 40);
        for (int i = 0; i < n; ++i) {
            int parity = (i / rnd.next(1, 4)) & 1;
            a.push_back(boundedByParity(rnd.next(1, 200), parity));
        }
        shuffle(a.begin(), a.end());
    } else {
        for (int i = 0; i < n; ++i) {
            int edge = rnd.next(0, 9);
            if (edge == 0) a.push_back(1);
            else if (edge == 1) a.push_back(1000000000);
            else a.push_back(rnd.next(1, 200));
        }
    }

    println(n);
    println(a);

    return 0;
}
