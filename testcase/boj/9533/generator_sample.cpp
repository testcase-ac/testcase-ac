#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

static void splitLeaf(vector<int>& depths, int index) {
    int depth = depths[index];
    depths[index] = depth + 1;
    depths.push_back(depth + 1);
}

static vector<int> makeSkewed(int n) {
    vector<int> depths(1, 0);
    while (static_cast<int>(depths.size()) < n) {
        int deepest = 0;
        for (int i = 1; i < static_cast<int>(depths.size()); ++i) {
            if (depths[i] > depths[deepest]) deepest = i;
        }
        splitLeaf(depths, deepest);
    }
    return depths;
}

static vector<int> makeBalanced(int n) {
    vector<int> depths(1, 0);
    while (static_cast<int>(depths.size()) < n) {
        int shallowest = 0;
        for (int i = 1; i < static_cast<int>(depths.size()); ++i) {
            if (depths[i] < depths[shallowest]) shallowest = i;
        }
        splitLeaf(depths, shallowest);
    }
    return depths;
}

static vector<int> makeRandomTree(int n, int bias) {
    vector<int> depths(1, 0);
    while (static_cast<int>(depths.size()) < n) {
        int best = 0;
        for (int i = 1; i < static_cast<int>(depths.size()); ++i) {
            bool take = false;
            if (bias < 0) {
                take = depths[i] < depths[best];
            } else if (bias > 0) {
                take = depths[i] > depths[best];
            }
            if (take && rnd.next(3) != 0) best = i;
        }
        if (rnd.next(2) == 0) best = rnd.next(static_cast<int>(depths.size()));
        splitLeaf(depths, best);
    }
    return depths;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n;
    vector<int> lengths;

    if (mode == 0) {
        n = rnd.next(2, 12);
        lengths = makeBalanced(n);
    } else if (mode == 1) {
        n = rnd.next(2, 50);
        lengths = makeSkewed(n);
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        lengths = makeRandomTree(n, rnd.next(-1, 1));
    } else {
        n = rnd.next(8, 50);
        lengths = makeRandomTree(n, rnd.next(2) == 0 ? -1 : 1);
    }

    shuffle(lengths.begin(), lengths.end());

    println(n);
    println(lengths);

    return 0;
}
