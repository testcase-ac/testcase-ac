#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Dataset {
    int n;
    int m;
    vector<int> l;
};

vector<int> windowSums(const vector<int>& k, int n, int m) {
    vector<int> l(n);
    int cur = 0;
    for (int i = 0; i < m; ++i) {
        cur += k[i];
    }
    l[0] = cur;

    for (int j = 1; j < n; ++j) {
        cur += k[j + m - 1] - k[j - 1];
        l[j] = cur;
    }
    return l;
}

vector<int> randomBits(int len, int mode) {
    vector<int> k(len);
    for (int i = 0; i < len; ++i) {
        if (mode == 0) {
            k[i] = 0;
        } else if (mode == 1) {
            k[i] = 1;
        } else if (mode == 2) {
            k[i] = i % 2;
        } else if (mode == 3) {
            k[i] = (i / max(1, rnd.next(1, 3))) % 2;
        } else {
            k[i] = rnd.next(0, 1);
        }
    }
    return k;
}

Dataset makeSolvable(int n, int m) {
    int mode = rnd.next(0, 5);
    vector<int> k = randomBits(n + m - 1, mode);
    return {n, m, windowSums(k, n, m)};
}

Dataset makePerturbed(int n, int m) {
    Dataset data = makeSolvable(n, m);
    int edits = rnd.next(1, min(n, 3));
    for (int e = 0; e < edits; ++e) {
        int pos = rnd.next(0, n - 1);
        if (data.l[pos] == 0) {
            data.l[pos] = rnd.next(1, m);
        } else if (data.l[pos] == m) {
            data.l[pos] = rnd.next(0, m - 1);
        } else {
            data.l[pos] += rnd.any(vector<int>{-1, 1});
        }
    }
    return data;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int datasetCount = rnd.next(4, 9);
    vector<Dataset> datasets;
    datasets.reserve(datasetCount);

    for (int t = 0; t < datasetCount; ++t) {
        int m;
        if (t == 0) {
            m = 1;
        } else if (t == 1) {
            m = 12;
        } else {
            m = rnd.next(1, 12);
        }

        int n;
        if (rnd.next(0, 5) == 0) {
            n = rnd.next(1, 3);
        } else {
            n = rnd.next(4, 18);
        }

        if (rnd.next(0, 3) == 0) {
            datasets.push_back(makePerturbed(n, m));
        } else {
            datasets.push_back(makeSolvable(n, m));
        }
    }

    shuffle(datasets.begin(), datasets.end());
    for (const Dataset& data : datasets) {
        println(data.n, data.m);
        println(data.l);
    }
    println(0, 0);

    return 0;
}
