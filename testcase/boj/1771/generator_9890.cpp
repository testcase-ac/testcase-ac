#include "testlib.h"
using namespace std;

vector<int> buildInc(int l, int r) {
    if (l == r) return {l};
    int m = (l + r) / 2;
    vector<int> left = buildInc(l, m);
    vector<int> right = buildInc(m + 1, r);
    left.insert(left.end(), right.begin(), right.end());
    return left;
}

vector<int> buildDec(int l, int r) {
    if (l == r) return {l};
    int m = (l + r) / 2;
    vector<int> left = buildDec(l, m);
    vector<int> right = buildDec(m + 1, r);
    right.insert(right.end(), left.begin(), left.end());
    return right;
}

vector<int> buildRandRec(int l, int r, bool skew) {
    if (l == r) return {l};
    int len = r - l + 1;
    int m;
    if (len == 2) {
        m = l;
    } else if (skew && rnd.next(0, 1) == 0) {
        if (rnd.next(0, 1) == 0) m = l;
        else m = r - 1;
    } else {
        m = rnd.next(l, r - 1);
    }

    bool nextSkewLeft = skew && (rnd.next(0, 1) == 0);
    bool nextSkewRight = skew && (rnd.next(0, 1) == 0);

    vector<int> left = buildRandRec(l, m, nextSkewLeft);
    vector<int> right = buildRandRec(m + 1, r, nextSkewRight);

    if (rnd.next(0, 1) == 0) {
        left.insert(left.end(), right.begin(), right.end());
        return left;
    } else {
        right.insert(right.end(), left.begin(), left.end());
        return right;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(1, 6);
    int N;
    vector<int> a;

    switch (scenario) {
        case 1:
            // Trivial smallest case
            N = 1;
            a = {1};
            break;
        case 2:
            // Small, strictly increasing
            N = rnd.next(2, 6);
            a = buildInc(1, N);
            break;
        case 3:
            // Small, strictly decreasing
            N = rnd.next(2, 6);
            a = buildDec(1, N);
            break;
        case 4:
            // Medium, random balanced structure
            N = rnd.next(5, 12);
            a = buildRandRec(1, N, false);
            break;
        case 5:
            // Medium-large, random balanced structure
            N = rnd.next(10, 20);
            a = buildRandRec(1, N, false);
            break;
        case 6:
        default:
            // Larger up to 30, skewed random structure
            N = rnd.next(15, 30);
            a = buildRandRec(1, N, true);
            break;
    }

    println(N);
    println(a);

    return 0;
}
