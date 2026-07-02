#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

struct Stone {
    int s;
    int e;
    int l;
};

Stone makeStone(int s, int e, int l) {
    return Stone{s, e, l};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 14);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 12);
        vector<Stone> stones;

        if (mode == 0) {
            int sameS = rnd.next(1, 20);
            n = rnd.next(2, 12);
            for (int i = 0; i < n; ++i) {
                stones.push_back(makeStone(sameS, rnd.next(1, 300), rnd.next(0, 80)));
            }
        } else if (mode == 1) {
            n = rnd.next(2, 10);
            for (int i = 0; i < n; ++i) {
                stones.push_back(makeStone(rnd.next(1, 30), rnd.next(1, 500), 0));
            }
        } else if (mode == 2) {
            n = rnd.next(3, 10);
            for (int i = 0; i < n; ++i) {
                int s = rnd.next(1, 40);
                int e = rnd.next(1, 800);
                int l = rnd.next(200, 100000);
                stones.push_back(makeStone(s, e, l));
            }
        } else if (mode == 3) {
            n = rnd.next(4, 12);
            for (int i = 0; i < n; ++i) {
                int s = rnd.next(1, 100);
                int e = rnd.next(1, 100000);
                int l = rnd.next(0, 100000);
                stones.push_back(makeStone(s, e, l));
            }
        } else if (mode == 4) {
            n = rnd.next(3, 9);
            for (int i = 0; i < n; ++i) {
                int s = rnd.next(1, 25);
                int e = rnd.next(20, 1200);
                int l = rnd.next(1, 200);
                stones.push_back(makeStone(s, e, l));
            }
            stones.push_back(makeStone(100, 100000, rnd.next(0, 1) ? 0 : 100000));
            n = static_cast<int>(stones.size());
        } else {
            n = rnd.next(1, 12);
            for (int i = 0; i < n; ++i) {
                int s = rnd.next(1, 30);
                int e = rnd.next(1, 2000);
                int l = rnd.next(0, 300);
                stones.push_back(makeStone(s, e, l));
            }
        }

        shuffle(stones.begin(), stones.end());

        println(n);
        for (const Stone& stone : stones) {
            println(stone.s, stone.e, stone.l);
        }
    }

    return 0;
}
