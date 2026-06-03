#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

void addPowerPile(vector<int>& a, int totalExp, int leaves) {
    int leafExp = totalExp - leaves;
    int count = 1 << leaves;
    for (int i = 0; i < count; ++i) a.push_back(leafExp);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a.push_back(rnd.next(0, 100000));
    } else if (mode == 1) {
        int low = rnd.next(0, 99994);
        int firstLeaves = rnd.next(0, 5);
        int secondLeaves = rnd.next(0, 5);
        addPowerPile(a, low + firstLeaves, firstLeaves);
        addPowerPile(a, low + rnd.next(1, 6) + secondLeaves, secondLeaves);
    } else if (mode == 2) {
        int n = rnd.next(3, 12);
        int start = rnd.next(0, 100000 - 2 * n);
        for (int i = 0; i < n; ++i) a.push_back(start + 2 * i);
    } else if (mode == 3) {
        int base = rnd.next(0, 99992);
        int groups = rnd.next(3, 6);
        for (int i = 0; i < groups; ++i) {
            int copies = rnd.next(1, 4);
            for (int j = 0; j < copies; ++j) a.push_back(base + i);
        }
    } else if (mode == 4) {
        int n = rnd.next(2, 14);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(0, 12));
    } else {
        int n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(99990, 100000));
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
