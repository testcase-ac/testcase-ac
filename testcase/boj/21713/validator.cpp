#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int readScore(const string& name) {
    string token = inf.readToken("[0-9]\\.[0-9]{2}", name);
    int value = (token[0] - '0') * 100 + (token[2] - '0') * 10 + (token[3] - '0');
    ensuref(100 <= value && value <= 600, "%s=%s is outside [1.00, 6.00]",
            name.c_str(), token.c_str());
    return value;
}

int roundedAverage(long long sum, int count) {
    return int((2 * sum + count) / (2 * count));
}

bool hasValidRemovalProcess(const vector<int>& scores, int k, int targetAverage) {
    int n = int(scores.size());
    int keptCount = n - k - 2;
    int limit = 1 << n;

    for (int mask = 0; mask < limit; ++mask) {
        if (__builtin_popcount((unsigned)mask) != keptCount) {
            continue;
        }

        long long sum = 0;
        int minKept = 601;
        int maxKept = 0;
        vector<int> removed;
        removed.reserve(k + 2);

        for (int i = 0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += scores[i];
                minKept = min(minKept, scores[i]);
                maxKept = max(maxKept, scores[i]);
            } else {
                removed.push_back(scores[i]);
            }
        }

        if (roundedAverage(sum, keptCount) != targetAverage) {
            continue;
        }

        for (int low = 0; low < int(removed.size()); ++low) {
            if (removed[low] > minKept) {
                continue;
            }
            for (int high = 0; high < int(removed.size()); ++high) {
                if (low != high && removed[high] >= maxKept) {
                    return true;
                }
            }
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 20, "n");
    inf.readSpace();
    int k = inf.readInt(0, n - 3, "k");
    inf.readEoln();

    vector<int> scores(n);
    for (int i = 0; i < n; ++i) {
        scores[i] = readScore(format("score[%d]", i + 1));
        if (i + 1 == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    int targetAverage = readScore("a");
    inf.readEoln();
    inf.readEof();

    ensuref(hasValidRemovalProcess(scores, k, targetAverage),
            "no removal process produces the stated rounded average");
}
