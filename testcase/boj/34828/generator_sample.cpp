#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = 100000;
    int q = rnd.next(1, 40);
    vector<pair<int, int>> queries;
    queries.reserve(q);

    auto addQuery = [&](int n, int k) {
        queries.push_back({n, k});
    };

    int mode = rnd.next(0, 5);
    for (int i = 0; i < q; ++i) {
        int n, k;
        if (mode == 0) {
            n = rnd.next(1, 30);
            k = rnd.next(1, 30);
        } else if (mode == 1) {
            k = rnd.next(1, 300);
            int steps = rnd.next(0, 20);
            int rem = rnd.next(1, k);
            n = rem + steps * k;
            if (n > MAXV) n = rem;
        } else if (mode == 2) {
            k = rnd.next(301, MAXV);
            n = rnd.next(1, MAXV);
        } else if (mode == 3) {
            n = rnd.next(1, 200);
            k = rnd.next(n, MAXV);
        } else if (mode == 4) {
            k = rnd.next(1, MAXV);
            int maxSteps = (MAXV - 1) / k;
            n = k * rnd.next(1, maxSteps);
        } else {
            n = rnd.any(vector<int>{1, 2, 3, 99999, 100000});
            k = rnd.any(vector<int>{1, 2, 3, 300, 301, 99999, 100000});
        }
        addQuery(n, k);
    }

    if (q >= 4) {
        queries[0] = {1, 1};
        queries[1] = {100000, 1};
        queries[2] = {100000, 100000};
        queries[3] = {1, 100000};
    }

    shuffle(queries.begin(), queries.end());

    println((int)queries.size());
    for (const auto& query : queries) {
        println(query.first, query.second);
    }

    return 0;
}
