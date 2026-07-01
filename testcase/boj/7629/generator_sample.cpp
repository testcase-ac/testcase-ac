#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> cases;
    int mode = rnd.next(0, 4);
    int caseCount = rnd.next(3, 12);

    if (mode == 0) {
        for (int i = 0; i < caseCount; ++i) {
            cases.push_back(rnd.next(1, 12));
        }
    } else if (mode == 1) {
        for (int i = 0; i < caseCount; ++i) {
            cases.push_back(rnd.next(1, 100));
        }
    } else if (mode == 2) {
        for (int i = 0; i < caseCount; ++i) {
            cases.push_back(rnd.next(900, 1000));
        }
    } else {
        vector<int> anchors = {1, 2, 3, 10, 50, 100, 500, 999, 1000};
        shuffle(anchors.begin(), anchors.end());
        for (int value : anchors) {
            if (static_cast<int>(cases.size()) == caseCount) break;
            cases.push_back(value);
        }
        while (static_cast<int>(cases.size()) < caseCount) {
            int bucket = rnd.next(0, 3);
            if (bucket == 0) {
                cases.push_back(rnd.next(1, 20));
            } else if (bucket == 1) {
                cases.push_back(rnd.next(21, 300));
            } else {
                cases.push_back(rnd.next(301, 1000));
            }
        }
        shuffle(cases.begin(), cases.end());
    }

    for (int n : cases) {
        println(n);
    }
    println(0);

    return 0;
}
