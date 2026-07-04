#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> roots;
    auto addRoot = [&](int y) {
        if (find(roots.begin(), roots.end(), y) == roots.end()) {
            roots.push_back(y);
        }
    };

    int targetCount = rnd.next(8, 30);
    int mode = rnd.next(5);

    if (mode == 0) {
        addRoot(1);
        addRoot(-1);
        addRoot(2);
        addRoot(-2);
    } else if (mode == 1) {
        addRoot(1000000);
        addRoot(-1000000);
        addRoot(999999);
        addRoot(-999999);
    } else if (mode == 2) {
        int center = rnd.next(-20, 20);
        for (int offset = -3; offset <= 3; ++offset) {
            int y = center + offset;
            if (y != 0) {
                addRoot(y);
            }
        }
    } else if (mode == 3) {
        int magnitude = rnd.next(1, 1000);
        for (int multiplier = 1; multiplier <= 5; ++multiplier) {
            int y = min(1000000, magnitude * multiplier);
            addRoot(y);
            addRoot(-y);
        }
    }

    while (int(roots.size()) < targetCount) {
        int y;
        int bucket = rnd.next(4);
        if (bucket == 0) {
            y = rnd.next(-10, 10);
        } else if (bucket == 1) {
            y = rnd.next(-1000, 1000);
        } else if (bucket == 2) {
            y = rnd.any(vector<int>{-1000000, -999999, -2, -1, 1, 2, 999999, 1000000});
        } else {
            y = rnd.next(-1000000, 1000000);
        }

        if (y != 0) {
            addRoot(y);
        }
    }

    shuffle(roots.begin(), roots.end());
    println(int(roots.size()));
    for (int y : roots) {
        println(y);
    }

    return 0;
}
