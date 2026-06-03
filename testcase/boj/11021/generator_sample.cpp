#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int T = 1;

    if (mode == 0) {
        T = 1;
    } else if (mode == 1) {
        T = rnd.next(2, 8);
    } else if (mode == 2) {
        T = rnd.next(4, 12);
    } else {
        T = rnd.next(12, 30);
    }

    vector<pair<int, int>> cases;
    cases.reserve(T);

    if (mode == 2) {
        vector<pair<int, int>> edgeCases = {
            {1, 1}, {1, 9}, {9, 1}, {9, 9}, {2, 8}, {8, 2}
        };
        shuffle(edgeCases.begin(), edgeCases.end());
        for (int i = 0; i < T && i < int(edgeCases.size()); ++i) {
            cases.push_back(edgeCases[i]);
        }
    }

    while (int(cases.size()) < T) {
        int pattern = rnd.next(0, 4);
        int A = rnd.next(1, 9);
        int B = rnd.next(1, 9);

        if (pattern == 0) {
            A = 1;
        } else if (pattern == 1) {
            B = 9;
        } else if (pattern == 2) {
            B = A;
        } else if (pattern == 3) {
            B = 10 - A;
        }

        cases.emplace_back(A, B);
    }

    shuffle(cases.begin(), cases.end());

    println(T);
    for (auto [A, B] : cases) {
        println(A, B);
    }

    return 0;
}
