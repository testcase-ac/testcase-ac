#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> interestingK = {
        2, 3, 4, 5, 7, 10, 11, 13, 17, 19, 23, 29, 31, 50, 97, 101, 997, 1009, 99991, 100000
    };
    const vector<int> interestingN = {
        2, 3, 4, 5, 6, 10, 15, 16, 30, 60, 97, 100, 997, 1024, 99991, 100000
    };

    int q;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        q = rnd.next(1, 8);
    } else if (mode <= 3) {
        q = rnd.next(8, 35);
    } else {
        q = rnd.next(35, 90);
    }

    vector<pair<int, int>> queries;
    queries.reserve(q);

    for (int i = 0; i < q; ++i) {
        int n, k;
        int kind = rnd.next(0, 7);

        if (kind == 0) {
            n = rnd.next(2, 30);
            k = rnd.next(2, 30);
        } else if (kind == 1) {
            n = rnd.any(interestingN);
            k = rnd.any(interestingK);
        } else if (kind == 2) {
            n = rnd.next(90000, 100000);
            k = rnd.next(2, 7);
        } else if (kind == 3) {
            n = rnd.next(2, 200);
            k = rnd.next(90000, 100000);
        } else if (kind == 4) {
            n = rnd.next(2, 100000);
            k = rnd.any(interestingK);
        } else if (kind == 5) {
            n = rnd.any(interestingN);
            k = rnd.next(2, 100000);
        } else if (kind == 6) {
            int x = rnd.next(2, 100000);
            n = x;
            k = x;
        } else {
            n = rnd.next(2, 100000);
            k = rnd.next(2, 100000);
        }

        queries.push_back({n, k});
    }

    shuffle(queries.begin(), queries.end());

    println(q);
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
