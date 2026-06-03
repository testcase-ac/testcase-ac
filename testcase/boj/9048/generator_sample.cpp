#include "testlib.h"

#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int f;
        int r;
        vector<pair<int, int>> cells;

        if (mode == 0) {
            f = rnd.next(1, 6);
            r = rnd.next(1, 8);
        } else if (mode == 1) {
            f = rnd.next(1, 12);
            r = rnd.next(1, 12);
        } else if (mode == 2) {
            f = rnd.next(2, 15);
            r = rnd.next(2, 15);
            for (int floor = 1; floor <= f; ++floor) {
                if (rnd.next(0, 1)) cells.push_back({floor, 1});
                if (r > 1 && rnd.next(0, 1)) cells.push_back({floor, r});
            }
        } else if (mode == 3) {
            f = rnd.next(3, 18);
            r = rnd.next(3, 18);
            int base = rnd.next(1, f);
            int span = rnd.next(0, min(3, f - 1));
            for (int floor = max(1, base - span); floor <= min(f, base + span); ++floor) {
                int count = rnd.next(1, min(r, 6));
                set<int> rooms;
                while ((int)rooms.size() < count) rooms.insert(rnd.next(1, r));
                for (int room : rooms) cells.push_back({floor, room});
            }
        } else if (mode == 4) {
            f = rnd.next(1, 8);
            r = rnd.next(1, 8);
            for (int floor = 1; floor <= f; ++floor) {
                for (int room = 1; room <= r; ++room) {
                    if (rnd.next() < 0.75) cells.push_back({floor, room});
                }
            }
        } else {
            f = rnd.next(20, 30);
            r = rnd.next(20, 30);
            int count = rnd.next(1, 30);
            set<pair<int, int>> chosen;
            while ((int)chosen.size() < count) {
                chosen.insert({rnd.next(1, f), rnd.next(1, r)});
            }
            cells.assign(chosen.begin(), chosen.end());
        }

        if (mode == 0) {
            cells.clear();
        } else if (mode == 1) {
            int count = rnd.next(1, min(f * r, 12));
            set<pair<int, int>> chosen;
            while ((int)chosen.size() < count) {
                chosen.insert({rnd.next(1, f), rnd.next(1, r)});
            }
            cells.assign(chosen.begin(), chosen.end());
        }

        shuffle(cells.begin(), cells.end());

        println(f, r, (int)cells.size());
        for (auto cell : cells) {
            println(cell.first, cell.second);
        }
    }

    return 0;
}
