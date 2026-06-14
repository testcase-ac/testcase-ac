#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int q;

    if (mode == 0) {
        n = rnd.next(1, 4);
        q = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(5, 30);
        q = rnd.next(20, 80);
    } else if (mode == 2) {
        n = rnd.next(100000, 1000000);
        q = rnd.next(8, 40);
    } else if (mode == 3) {
        n = rnd.any(vector<int>{1, 2, 3, 999999, 1000000});
        q = rnd.next(1, 50);
    } else {
        n = rnd.next(10, 200);
        q = rnd.next(30, 100);
    }

    vector<pair<char, int>> queries;
    queries.reserve(q);

    vector<int> special;
    special.push_back(1);
    if (n > 1) special.push_back(2);
    if (n > 2) special.push_back((n + 1) / 2);
    if (n > 2) special.push_back(n - 1);
    if (n > 1) special.push_back(n);

    for (int i = 0; i < q; ++i) {
        char type;
        if (mode == 4) {
            type = (i % 2 == 0 ? 'R' : 'C');
        } else if (mode == 5) {
            type = (i < q / 2 ? 'R' : 'C');
        } else {
            type = (rnd.next(0, 1) == 0 ? 'R' : 'C');
        }

        int index;
        if (!queries.empty() && rnd.next(0, 99) < 25) {
            index = rnd.any(queries).second;
        } else if (rnd.next(0, 99) < 45) {
            index = rnd.any(special);
        } else {
            index = rnd.next(1, n);
        }

        queries.push_back({type, index});
    }

    println(n, q);
    for (auto query : queries) {
        println(string(1, query.first), query.second);
    }

    return 0;
}
