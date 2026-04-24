#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(4, 8);
    vector<pair<int,int>> cases;
    // ensure all parity combinations
    cases.emplace_back(3, 3); // odd-odd: no solution
    cases.emplace_back(4, 3); // even-odd: solution
    cases.emplace_back(3, 4); // odd-even: solution
    cases.emplace_back(4, 4); // even-even: solution
    // add random diverse sizes
    for (int i = 4; i < T; i++) {
        int mtype = rnd.next(0, 2);
        int m = (mtype == 0 ? rnd.next(3, 10)
               : mtype == 1 ? rnd.next(11, 50)
                            : rnd.next(51, 100));
        int ntype = rnd.next(0, 2);
        int n = (ntype == 0 ? rnd.next(3, 10)
               : ntype == 1 ? rnd.next(11, 50)
                             : rnd.next(51, 100));
        cases.emplace_back(m, n);
    }
    shuffle(cases.begin(), cases.end());
    println(T);
    for (auto &p : cases) {
        println(p.first, p.second);
    }
    return 0;
}
