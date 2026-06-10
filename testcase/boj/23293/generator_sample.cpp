#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int differentRegion(int current) {
    int next = rnd.next(1, 52);
    if (next >= current) ++next;
    return next;
}

int differentItem(int item) {
    int other = rnd.next(1, 52);
    if (other >= item) ++other;
    return other;
}

int differentPlayer(int player, int n) {
    int target = rnd.next(1, n - 1);
    if (target >= player) ++target;
    return target;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, mode == 5 ? 35 : 12);
    int t = rnd.next(1, mode == 5 ? 120 : 45);

    vector<int> location(n + 1, 1);
    vector<int> itemHint(n + 1, 1);
    println(t, n);

    for (int line = 1; line <= t; ++line) {
        int player = rnd.next(1, n);
        int actionType;

        if (mode == 0) {
            actionType = rnd.next(0, 2);
        } else if (mode == 1) {
            actionType = rnd.next(0, 3);
        } else if (mode == 2) {
            actionType = rnd.next(1, 3);
        } else if (mode == 3) {
            actionType = rnd.next(0, 3) == 0 ? 0 : 3;
        } else {
            actionType = rnd.wnext(4, -1);
        }

        if (actionType == 0) {
            int next = differentRegion(location[player]);
            location[player] = next;
            println(line, player, "M", next);
        } else if (actionType == 1) {
            int item = location[player];
            if (mode == 1 || (mode >= 4 && rnd.next(0, 3) == 0)) {
                item = differentItem(location[player]);
            }
            itemHint[player] = item;
            println(line, player, "F", item);
        } else if (actionType == 2) {
            int first = itemHint[player];
            int second = differentItem(first);
            if (mode == 2 || (mode >= 4 && rnd.next(0, 2) == 0)) {
                first = rnd.next(1, 53);
                second = differentItem(first);
            }
            println(line, player, "C", first, second);
        } else {
            int target = differentPlayer(player, n);
            bool preferDifferentRegion = mode == 3 || (mode >= 4 && rnd.next(0, 2) == 0);
            vector<int> candidates;
            for (int other = 1; other <= n; ++other) {
                if (other == player) continue;
                if ((location[other] != location[player]) == preferDifferentRegion) {
                    candidates.push_back(other);
                }
            }
            if (!candidates.empty()) {
                target = rnd.any(candidates);
            }
            println(line, player, "A", target);
        }
    }

    return 0;
}
