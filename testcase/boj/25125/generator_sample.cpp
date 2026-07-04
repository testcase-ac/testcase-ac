#include "testlib.h"

#include <vector>

using namespace std;

vector<int> randomArray(int n, int lo, int hi) {
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        values.push_back(rnd.next(lo, hi));
    }
    return values;
}

vector<int> balancedArray(int pairs) {
    vector<int> values;
    values.reserve(2 * pairs);
    for (int i = 0; i < pairs; ++i) {
        int x = rnd.next(1, 1000);
        values.push_back(x);
        values.push_back(-x);
    }
    shuffle(values.begin(), values.end());
    return values;
}

vector<int> oneAddFriendlyArray() {
    int a = rnd.next(-30, 30);
    int b = rnd.next(-30, 30);
    int z = rnd.next(-30, 30);
    while (z == 0) {
        z = rnd.next(-30, 30);
    }
    return {a, b, z, -z};
}

vector<int> boundaryArray(int n) {
    vector<int> pool = {-1000, -999, -500, -1, 0, 1, 500, 999, 1000};
    vector<int> values;
    values.reserve(n);
    for (int i = 0; i < n; ++i) {
        values.push_back(rnd.any(pool));
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(8, 18);
    println(t);

    for (int caseNo = 0; caseNo < t; ++caseNo) {
        int mode = rnd.next(0, 7);
        int k = rnd.next(0, 1) == 0 ? 1 : rnd.next(2, 12);
        vector<int> values;

        if (mode == 0) {
            int n = rnd.next(1, 8);
            values = randomArray(n, -10, 10);
        } else if (mode == 1) {
            int pairs = rnd.next(1, 5);
            values = balancedArray(pairs);
        } else if (mode == 2) {
            values = oneAddFriendlyArray();
            k = 1;
        } else if (mode == 3) {
            int n = rnd.next(2, 10);
            values = boundaryArray(n);
        } else if (mode == 4) {
            int n = rnd.next(1, 6);
            values.assign(n, 0);
        } else if (mode == 5) {
            int n = rnd.next(20, 60);
            values = randomArray(n, -3, 3);
        } else {
            int n = rnd.next(2, 12);
            int lo = rnd.next(-1000, 0);
            int hi = rnd.next(0, 1000);
            values = randomArray(n, lo, hi);
        }

        println((int)values.size(), k);
        println(values);
    }

    return 0;
}
