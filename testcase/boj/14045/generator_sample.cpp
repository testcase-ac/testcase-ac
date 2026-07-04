#include "testlib.h"

#include <vector>

using namespace std;

vector<int> randomSmallSequence(int n, int maxValue) {
    vector<int> values;
    for (int i = 0; i < n; ++i) {
        values.push_back(rnd.next(1, maxValue));
    }
    return values;
}

vector<int> makeMergeableBlock(int depth, int maxLeaf) {
    if (depth == 0 || rnd.next(100) < 25) {
        return {rnd.next(1, maxLeaf)};
    }

    vector<int> left = makeMergeableBlock(depth - 1, maxLeaf);
    vector<int> right = left;
    vector<int> result = left;

    if (rnd.next(2) == 0) {
        result.insert(result.end(), right.begin(), right.end());
    } else {
        vector<int> middle = makeMergeableBlock(depth - 1, maxLeaf);
        result.insert(result.end(), middle.begin(), middle.end());
        result.insert(result.end(), right.begin(), right.end());
    }

    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<int> riceballs;

    if (mode == 0) {
        int n = rnd.next(1, 30);
        int maxValue = rnd.next(3, 30);
        riceballs = randomSmallSequence(n, maxValue);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 12);
        for (int i = 0; i < pairs; ++i) {
            int value = rnd.next(1, 40);
            riceballs.push_back(value);
            riceballs.push_back(value);
            if (rnd.next(100) < 35) {
                riceballs.push_back(rnd.next(1, 40));
            }
        }
    } else if (mode == 2) {
        int groups = rnd.next(1, 8);
        for (int i = 0; i < groups; ++i) {
            int outer = rnd.next(1, 35);
            int middle = rnd.next(1, 35);
            riceballs.push_back(outer);
            riceballs.push_back(middle);
            riceballs.push_back(outer);
        }
    } else if (mode == 3) {
        riceballs = makeMergeableBlock(rnd.next(2, 4), rnd.next(1, 15));
        while ((int)riceballs.size() < 30 && rnd.next(100) < 45) {
            vector<int> block = makeMergeableBlock(rnd.next(1, 3), rnd.next(1, 20));
            riceballs.insert(riceballs.end(), block.begin(), block.end());
        }
    } else if (mode == 4) {
        int n = rnd.next(10, 35);
        for (int i = 0; i < n; ++i) {
            riceballs.push_back((i % 2 == 0) ? rnd.next(1, 6) : rnd.next(20, 35));
        }
    } else {
        int n = rnd.next(2, 30);
        int base = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            int value = base + rnd.next(0, 3);
            if (rnd.next(100) < 15) {
                value = 1000000;
            }
            riceballs.push_back(value);
        }
    }

    if ((int)riceballs.size() > 60) {
        riceballs.resize(60);
    }

    println((int)riceballs.size());
    println(riceballs);

    return 0;
}
