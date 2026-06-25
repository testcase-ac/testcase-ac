#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> randomCounts(int n) {
    vector<int> counts;
    int remaining = n;
    while (remaining > 0) {
        int take = rnd.next(1, min(remaining, 5));
        counts.push_back(take);
        remaining -= take;
    }
    if (rnd.next(2) == 0) {
        shuffle(counts.begin(), counts.end());
    }
    return counts;
}

static vector<int> randomIds(int count) {
    vector<int> pool;
    pool.push_back(1);
    pool.push_back(1000000);
    while ((int)pool.size() < count) {
        int value = rnd.next(1, 1000000);
        if (find(pool.begin(), pool.end(), value) == pool.end()) {
            pool.push_back(value);
        }
    }
    shuffle(pool.begin(), pool.end());
    pool.resize(count);
    return pool;
}

static vector<int> buildList(const vector<int>& counts) {
    vector<int> ids = randomIds((int)counts.size());
    vector<int> result;
    for (int i = 0; i < (int)counts.size(); ++i) {
        for (int j = 0; j < counts[i]; ++j) {
            result.push_back(ids[i]);
        }
    }
    shuffle(result.begin(), result.end());
    return result;
}

static vector<int> makeDifferentCounts(const vector<int>& counts, int n) {
    if (n == 1) {
        return counts;
    }

    vector<int> result = counts;
    if ((int)result.size() == 1) {
        result = {1, n - 1};
    } else {
        int from = -1;
        for (int i = 0; i < (int)result.size(); ++i) {
            if (result[i] > 1) {
                from = i;
                break;
            }
        }
        if (from == -1) {
            result.pop_back();
            result.back()++;
        } else {
            result[from]--;
            result.push_back(1);
        }
    }
    shuffle(result.begin(), result.end());
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (tc == 1) {
            n = rnd.next(2, 5);
        } else {
            n = rnd.next(6, 30);
        }

        vector<int> cornellCounts = randomCounts(n);
        bool lovely = (n == 1 || rnd.next(2) == 0);
        vector<int> whiteCounts = lovely ? cornellCounts : makeDifferentCounts(cornellCounts, n);

        println(n);
        println(buildList(cornellCounts));
        println(buildList(whiteCounts));
    }

    return 0;
}
