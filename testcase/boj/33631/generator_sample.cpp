#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int q = rnd.next(1, 30);

    array<int, 4> have;
    array<int, 4> need;

    for (int i = 0; i < 4; ++i) {
        if (mode == 0) {
            have[i] = rnd.next(1, 12);
            need[i] = rnd.next(6, 10);
        } else if (mode == 1) {
            have[i] = rnd.next(80, 100);
            need[i] = rnd.next(1, 3);
        } else if (mode == 2) {
            have[i] = rnd.next(1, 100);
            need[i] = rnd.next(1, 10);
        } else if (mode == 3) {
            have[i] = rnd.any(vector<int>{1, 2, 99, 100});
            need[i] = rnd.any(vector<int>{1, 2, 9, 10});
        } else {
            need[i] = rnd.next(1, 10);
            have[i] = need[i] * rnd.next(1, 10);
            if (have[i] > 100) have[i] = rnd.next(1, 100);
        }
    }

    vector<pair<int, int>> queries;
    queries.reserve(q);
    for (int i = 0; i < q; ++i) {
        int type;
        if (mode == 0) {
            type = (i % 3 == 0 ? 1 : rnd.next(2, 5));
        } else if (mode == 1) {
            type = (rnd.next(0, 99) < 65 ? 1 : rnd.next(2, 5));
        } else if (mode == 2) {
            type = rnd.next(1, 5);
        } else if (mode == 3) {
            type = (i % 2 == 0 ? 1 : rnd.next(2, 5));
        } else {
            type = (i < 4 ? i + 2 : 1);
        }

        int amount;
        if (type == 1) {
            if (mode == 3) {
                amount = rnd.any(vector<int>{1, 2, 19, 20});
            } else {
                amount = rnd.next(1, 20);
            }
        } else {
            if (mode == 3) {
                amount = rnd.any(vector<int>{1, 2, 99, 100});
            } else if (mode == 4 && i < 4) {
                amount = 100;
            } else {
                amount = rnd.next(1, 100);
            }
        }
        queries.push_back({type, amount});
    }

    println(have[0], have[1], have[2], have[3]);
    println(need[0], need[1], need[2], need[3]);
    println(q);
    for (auto [type, amount] : queries) {
        println(type, amount);
    }

    return 0;
}
