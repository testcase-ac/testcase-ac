#include "testlib.h"

#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> queries;
    int mode = rnd.next(0, 4);

    if (mode == 0) {
        int count = rnd.next(1, 4);
        for (int i = 0; i < count; ++i) {
            queries.push_back(rnd.next(2, 5));
        }
    } else if (mode == 1) {
        queries = {2, 3, 15, 16};
        shuffle(queries.begin(), queries.end());
        queries.resize(rnd.next(2, static_cast<int>(queries.size())));
    } else if (mode == 2) {
        int count = rnd.next(4, 10);
        int lo = rnd.next(2, 12);
        int hi = rnd.next(lo, 16);
        for (int i = 0; i < count; ++i) {
            queries.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 3) {
        int repeated = rnd.next(2, 16);
        int count = rnd.next(3, 8);
        for (int i = 0; i < count; ++i) {
            queries.push_back(repeated);
        }
    } else {
        set<int> chosen;
        int count = rnd.next(5, 12);
        while (static_cast<int>(chosen.size()) < count) {
            chosen.insert(rnd.next(2, 16));
        }
        queries.assign(chosen.begin(), chosen.end());
        shuffle(queries.begin(), queries.end());
    }

    for (int n : queries) {
        println(n);
    }
    println(-1);

    return 0;
}
