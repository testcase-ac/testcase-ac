#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct Operation {
    char type;
    int x;
    int y;
    int z;
};

int takeAt(vector<int>& available, int index) {
    int value = available[index];
    available.erase(available.begin() + index);
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, mode == 3 ? 14 : 9);
    long long m = rnd.next(1, 1000000000);

    vector<Operation> operations;
    vector<int> available = {1};
    vector<int> produced;
    int nextId = 2;

    for (int i = 0; i < n; ++i) {
        bool canMerge = available.size() >= 2;
        int remaining = n - i;
        bool mustSplit = static_cast<int>(available.size()) < remaining / 3 + 1;
        bool makeSplit;

        if (!canMerge) {
            makeSplit = true;
        } else if (mustSplit) {
            makeSplit = true;
        } else if (mode == 0) {
            makeSplit = rnd.next(0, 99) < 75;
        } else if (mode == 1) {
            makeSplit = rnd.next(0, 99) < 35;
        } else {
            makeSplit = rnd.next(0, 99) < 55;
        }

        if (makeSplit) {
            int inputIndex = rnd.next(static_cast<int>(available.size()));
            int x = takeAt(available, inputIndex);
            int y = nextId++;
            int z = nextId++;
            if (rnd.next(0, 1)) {
                swap(y, z);
            }
            operations.push_back({'S', x, y, z});
            available.push_back(y);
            available.push_back(z);
            produced.push_back(y);
            produced.push_back(z);
        } else {
            int firstIndex = rnd.next(static_cast<int>(available.size()));
            int x = takeAt(available, firstIndex);
            int secondIndex = rnd.next(static_cast<int>(available.size()));
            int y = takeAt(available, secondIndex);
            if (rnd.next(0, 1)) {
                swap(x, y);
            }
            int z = nextId++;
            operations.push_back({'M', x, y, z});
            available.push_back(z);
            produced.push_back(z);
        }

        shuffle(available.begin(), available.end());
    }

    int q = rnd.next(1, 20);
    println(m, n, q);
    for (const Operation& op : operations) {
        string type(1, op.type);
        println(type, op.x, op.y, op.z);
    }

    for (int i = 0; i < q; ++i) {
        int x;
        if (rnd.next(0, 99) < 65) {
            x = rnd.any(available);
        } else {
            x = rnd.any(produced);
        }

        long long k;
        int flavor = rnd.next(0, 4);
        if (flavor == 0) {
            k = 1;
        } else if (flavor == 1) {
            k = m;
        } else if (flavor == 2) {
            k = (m + 1) / 2;
        } else if (flavor == 3) {
            k = rnd.next(1, 1000);
        } else {
            k = rnd.next(1, 1000000000);
        }
        println(x, k);
    }

    return 0;
}
