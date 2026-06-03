#include "testlib.h"
#include <vector>
using namespace std;

vector<int> buildAffine(int n, int a, int b, int first) {
    vector<int> values(1, first);
    while ((int)values.size() < n) {
        int next = values.back() * a + b;
        if (next < -100 || next > 100) {
            break;
        }
        values.push_back(next);
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    vector<int> values;

    if (mode == 0) {
        values.push_back(rnd.next(-100, 100));
    } else if (mode == 1) {
        values.push_back(rnd.next(-100, 100));
        values.push_back(rnd.next(-100, 100));
    } else if (mode == 2) {
        int n = rnd.next(3, 50);
        int x = rnd.next(-100, 100);
        values.assign(n, x);
    } else if (mode == 3) {
        int n = rnd.next(3, 20);
        int diff = rnd.next(-8, 8);
        while (diff == 0) {
            diff = rnd.next(-8, 8);
        }
        int lo = -100 - diff * (n - 1);
        int hi = 100 - diff * (n - 1);
        if (lo > hi) {
            swap(lo, hi);
        }
        int first = rnd.next(max(-100, lo), min(100, hi));
        for (int i = 0; i < n; ++i) {
            values.push_back(first + diff * i);
        }
    } else if (mode == 4) {
        int n = rnd.next(3, 12);
        for (int attempt = 0; attempt < 100 && values.empty(); ++attempt) {
            int a = rnd.next(-3, 3);
            int b = rnd.next(-20, 20);
            int first = rnd.next(-30, 30);
            vector<int> candidate = buildAffine(n, a, b, first);
            if ((int)candidate.size() == n) {
                values = candidate;
            }
        }
        if (values.empty()) {
            values = buildAffine(n, 2, 1, rnd.next(-5, 5));
        }
    } else if (mode == 5) {
        values = {rnd.next(-100, 100), rnd.next(-100, 100), rnd.next(-100, 100)};
        if (values[0] == values[1] && values[1] == values[2]) {
            values[2] = values[2] == 100 ? 99 : values[2] + 1;
        }
    } else {
        int n = rnd.next(4, 10);
        int start = rnd.next(-10, 10);
        values = buildAffine(n, rnd.any(vector<int>{-2, -1, 2, 3}), rnd.next(-5, 5), start);
        while ((int)values.size() < n) {
            values.push_back(rnd.next(-100, 100));
        }
        int pos = rnd.next(2, n - 1);
        values[pos] = values[pos] == 100 ? 99 : values[pos] + 1;
    }

    println((int)values.size());
    println(values);
    return 0;
}
