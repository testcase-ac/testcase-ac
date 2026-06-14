#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

vector<int> identityPermutation(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    return p;
}

vector<int> randomPermutation(int n) {
    vector<int> p = identityPermutation(n);
    shuffle(p.begin(), p.end());
    return p;
}

vector<int> rotatedPermutation(int n, int shift) {
    vector<int> p = identityPermutation(n);
    rotate(p.begin(), p.begin() + shift % n, p.end());
    return p;
}

vector<int> blockyPermutation(int n) {
    vector<int> p = identityPermutation(n);
    int blockSize = rnd.next(1, min(n, 4));
    for (int l = 0; l < n; l += blockSize) {
        int r = min(n, l + blockSize);
        if (rnd.next(2) == 0) {
            reverse(p.begin() + l, p.begin() + r);
        } else {
            shuffle(p.begin() + l, p.begin() + r);
        }
    }
    return p;
}

vector<int> relabel(const vector<int>& p, const vector<int>& labels) {
    vector<int> result;
    result.reserve(p.size());
    for (int id : p) {
        result.push_back(labels[id - 1]);
    }
    return result;
}

vector<int> makePreference(int n, int mode, int row, const vector<int>& labels) {
    vector<int> p;
    if (mode == 0) {
        p = identityPermutation(n);
    } else if (mode == 1) {
        p = identityPermutation(n);
        reverse(p.begin(), p.end());
    } else if (mode == 2) {
        p = rotatedPermutation(n, row + rnd.next(n));
    } else if (mode == 3) {
        p = blockyPermutation(n);
    } else {
        p = randomPermutation(n);
    }

    if (rnd.next(100) < 25) {
        shuffle(p.begin(), p.end());
    }
    return relabel(p, labels);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<int> sizes;
    sizes.reserve(t);

    long long totalPreferenceIds = 0;
    for (int tc = 0; tc < t; ++tc) {
        int n;
        int sizeMode = rnd.next(100);
        if (sizeMode < 15) {
            n = 1;
        } else if (sizeMode < 65) {
            n = rnd.next(2, 8);
        } else if (sizeMode < 90) {
            n = rnd.next(9, 20);
        } else {
            n = rnd.next(21, 40);
        }

        if (totalPreferenceIds + 2LL * n * n >= 5000000LL) {
            n = 1;
        }
        totalPreferenceIds += 2LL * n * n;
        sizes.push_back(n);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = sizes[tc];
        int menMode = rnd.next(5);
        int womenMode = rnd.next(5);
        vector<int> womenLabels = randomPermutation(n);
        vector<int> menLabels = randomPermutation(n);

        println(n);
        for (int man = 0; man < n; ++man) {
            println(makePreference(n, menMode, man, womenLabels));
        }
        for (int woman = 0; woman < n; ++woman) {
            println(makePreference(n, womenMode, woman, menLabels));
        }
    }
}
