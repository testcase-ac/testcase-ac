#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static void appendRandomOnes(vector<long long>& a, int maxCount) {
    int count = rnd.next(0, maxCount);
    while (count--) a.push_back(1);
}

static void appendPattern(vector<long long>& a, const vector<long long>& pattern) {
    if (rnd.next(2)) appendRandomOnes(a, 4);
    for (long long x : pattern) a.push_back(x);
    if (rnd.next(2)) appendRandomOnes(a, 4);
}

static vector<long long> makePlantedCase(int targetN) {
    vector<vector<long long>> patterns = {
        {2, 2},
        {1, 2, 3},
        {1, 1, 2, 4},
        {1, 1, 1, 2, 5},
        {1, 1, 1, 1, 2, 6},
        {2, 2, 2, 2},
    };

    vector<long long> a;
    while ((int)a.size() < targetN) {
        int choice = rnd.next(100);
        if (choice < 45) {
            appendPattern(a, rnd.any(patterns));
        } else if (choice < 75) {
            appendRandomOnes(a, 6);
            a.push_back(rnd.next(2, 8));
        } else if (choice < 90) {
            a.push_back(1);
        } else {
            a.push_back(rnd.next(9, 30));
        }
    }

    a.resize(targetN);
    return a;
}

static vector<long long> makeSmallMixedCase(int n) {
    vector<long long> a;
    int maxValue = rnd.next(2, 12);
    for (int i = 0; i < n; ++i) {
        int choice = rnd.next(100);
        if (choice < 35) a.push_back(1);
        else if (choice < 85) a.push_back(rnd.next(2, maxValue));
        else a.push_back(rnd.next(13, 100));
    }
    return a;
}

static vector<long long> makeBoundaryCase(int n) {
    vector<long long> a;
    for (int i = 0; i < n; ++i) {
        int choice = rnd.next(100);
        if (choice < 55) a.push_back(1);
        else if (choice < 75) a.push_back(2);
        else if (choice < 90) a.push_back(rnd.next(3, 20));
        else a.push_back(1000000000LL);
    }
    return a;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(3);
    int n = rnd.next(2, 80);

    vector<long long> a;
    if (mode == 0) {
        a = makePlantedCase(n);
    } else if (mode == 1) {
        a = makeSmallMixedCase(n);
    } else {
        a = makeBoundaryCase(n);
    }

    if (rnd.next(2)) shuffle(a.begin(), a.end());

    println(n);
    println(a);

    return 0;
}
