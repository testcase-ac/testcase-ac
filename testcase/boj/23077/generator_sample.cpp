#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Attraction {
    int h;
    int s;
    int e;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxH = 300000;
    int T = rnd.next(1, 6);
    bool includeLarge = rnd.next(0, 4) == 0;

    println(T);
    for (int tc = 1; tc <= T; ++tc) {
        bool largeCase = includeLarge && tc == T;
        int D = largeCase ? rnd.next(1001, 300000) : rnd.next(1, 30);
        int N = largeCase ? rnd.next(1, 12) : rnd.next(1, 18);
        int K = rnd.next(1, N);

        vector<Attraction> attractions;
        attractions.reserve(N);

        int mode = rnd.next(0, 4);
        for (int i = 0; i < N; ++i) {
            int h;
            if (mode == 0) {
                h = rnd.next(1, 30);
            } else if (mode == 1) {
                h = rnd.any(vector<int>{1, 2, 3, maxH - 1, maxH});
            } else {
                h = rnd.next(1, maxH);
            }

            int s, e;
            if (mode == 2) {
                s = 1;
                e = D;
            } else if (mode == 3) {
                s = rnd.next(1, D);
                e = s;
            } else {
                s = rnd.next(1, D);
                int spanLimit = max(0, min(D - s, rnd.next(0, min(D - 1, 8))));
                e = s + rnd.next(0, spanLimit);
            }
            attractions.push_back({h, s, e});
        }

        if (mode == 4 && D >= 2 && N >= 2) {
            attractions[0] = {maxH, 1, D / 2};
            attractions[1] = {maxH - 1, D / 2 + 1, D};
        }

        shuffle(attractions.begin(), attractions.end());

        println(D, N, K);
        for (const Attraction& attraction : attractions) {
            println(attraction.h, attraction.s, attraction.e);
        }
    }

    return 0;
}
