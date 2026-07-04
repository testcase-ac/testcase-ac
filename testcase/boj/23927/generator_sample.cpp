#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(6);
        int N = 1;
        if (mode == 0) {
            N = rnd.next(1, 3);
        } else if (mode == 1) {
            N = rnd.next(2, 12);
        } else {
            N = rnd.next(4, 30);
        }

        vector<pair<long long, long long>> points;
        points.reserve(N);

        long long baseX = rnd.next(-50, 50);
        long long baseY = rnd.next(-50, 50);

        if (mode == 0) {
            for (int i = 0; i < N; ++i) {
                points.push_back({baseX, baseY});
            }
        } else if (mode == 1) {
            for (int i = 0; i < N; ++i) {
                points.push_back({baseX + i, baseY});
            }
            shuffle(points.begin(), points.end());
        } else if (mode == 2) {
            for (int i = 0; i < N; ++i) {
                points.push_back({baseX, baseY + i});
            }
        } else if (mode == 3) {
            for (int i = 0; i < N; ++i) {
                long long x = baseX + rnd.next(-8, 8);
                long long y = baseY + rnd.next(-8, 8);
                points.push_back({x, y});
            }
        } else if (mode == 4) {
            long long anchor = rnd.any(vector<long long>{-1000000000LL, -999999937LL,
                                                         999999937LL, 1000000000LL});
            for (int i = 0; i < N; ++i) {
                long long dx = rnd.next(-20, 20);
                long long dy = rnd.next(-20, 20);
                points.push_back({max(-1000000000LL, min(1000000000LL, anchor + dx)),
                                  max(-1000000000LL, min(1000000000LL, -anchor + dy))});
            }
        } else {
            for (int i = 0; i < N; ++i) {
                long long x = baseX + rnd.next(-15, 15);
                long long y = rnd.next(-3, 3) == 0 ? baseY : baseY + rnd.next(-15, 15);
                points.push_back({x, y});
            }
        }

        println(N);
        for (const auto& point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}
