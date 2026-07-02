#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

static void addCycle(vector<int>& p, const vector<int>& labels, int start, int len) {
    if (len == 1) {
        p[labels[start]] = labels[start];
        return;
    }

    for (int i = 0; i < len; ++i) {
        p[labels[start + i]] = labels[start + (i + 1) % len];
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<int> lengths;

    if (mode == 0) {
        int n = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            lengths.push_back(1);
        }
    } else if (mode == 1) {
        lengths.push_back(rnd.next(2, 80));
    } else if (mode == 2) {
        int len = rnd.next(2, 25);
        lengths.push_back(len);
        lengths.push_back(len);
        int extra = rnd.next(0, 10);
        for (int i = 0; i < extra; ++i) {
            lengths.push_back(1);
        }
    } else if (mode == 3) {
        int n = rnd.next(8, 80);
        int remaining = n;
        while (remaining > 0) {
            int len = rnd.next(1, min(remaining, 12));
            lengths.push_back(len);
            remaining -= len;
        }
    } else {
        vector<int> candidates = {1, 2, 3, 4, 6, 8, 10, 12, 16, 24, 32};
        int n = rnd.next(20, 90);
        int remaining = n;
        while (remaining > 0) {
            vector<int> available;
            for (int len : candidates) {
                if (len <= remaining) {
                    available.push_back(len);
                }
            }
            int len = rnd.any(available);
            lengths.push_back(len);
            remaining -= len;
        }
    }

    shuffle(lengths.begin(), lengths.end());
    int n = accumulate(lengths.begin(), lengths.end(), 0);

    vector<int> labels(n);
    iota(labels.begin(), labels.end(), 1);
    shuffle(labels.begin(), labels.end());

    vector<int> p(n + 1);
    int start = 0;
    for (int len : lengths) {
        addCycle(p, labels, start, len);
        start += len;
    }

    println(n);
    vector<int> output(p.begin() + 1, p.end());
    println(output);

    return 0;
}
