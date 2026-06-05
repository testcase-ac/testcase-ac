#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Seed {
    int t1;
    int t2;
    vector<int> pieces;
};

vector<int> randomPieces(int n, int count) {
    vector<int> pieces;
    for (int i = 1; i <= n; ++i) {
        pieces.push_back(i);
    }
    shuffle(pieces.begin(), pieces.end());
    pieces.resize(count);
    sort(pieces.begin(), pieces.end());
    return pieces;
}

Seed makeSeed(int n, int t1, int t2, int minPieces, int maxPieces) {
    int count = rnd.next(minPieces, maxPieces);
    return {t1, t2, randomPieces(n, count)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(3, 8);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, mode == 5 ? 20 : 12);
        vector<Seed> seeds;

        if (mode == 0) {
            int m = rnd.next(1, 6);
            for (int i = 0; i < m; ++i) {
                int t = rnd.next(0, 100);
                seeds.push_back(makeSeed(n, t, t, 0, n));
            }
        } else if (mode == 1) {
            int m = rnd.next(1, 8);
            for (int i = 0; i < m; ++i) {
                int t1 = rnd.next(0, 95);
                int t2 = rnd.next(t1 + 1, min(100, t1 + rnd.next(1, 12)));
                seeds.push_back(makeSeed(n, t1, t2, 0, n));
            }
        } else if (mode == 2) {
            int m = rnd.next(max(1, n / 2), n + 4);
            for (int i = 0; i < m; ++i) {
                int t1 = rnd.next(0, 20);
                int t2 = rnd.next(t1 + 1, min(100, t1 + rnd.next(1, 8)));
                int count = rnd.next(1, min(n, 3));
                seeds.push_back(makeSeed(n, t1, t2, count, count));
            }
        } else if (mode == 3) {
            int m = rnd.next(2, 10);
            int start = rnd.next(0, 70);
            for (int i = 0; i < m; ++i) {
                int t1 = min(100, start + rnd.next(0, 8));
                int t2 = rnd.next(t1, min(100, t1 + rnd.next(0, 15)));
                int minPieces = rnd.next(0, 1);
                seeds.push_back(makeSeed(n, t1, t2, minPieces, n));
            }
        } else if (mode == 4) {
            int m = rnd.next(1, 10);
            int missing = rnd.next(1, n);
            for (int i = 0; i < m; ++i) {
                int t1 = rnd.next(0, 90);
                int t2 = rnd.next(t1, min(100, t1 + rnd.next(0, 10)));
                vector<int> choices;
                for (int p = 1; p <= n; ++p) {
                    if (p != missing) {
                        choices.push_back(p);
                    }
                }
                shuffle(choices.begin(), choices.end());
                choices.resize(rnd.next(0, (int)choices.size()));
                sort(choices.begin(), choices.end());
                seeds.push_back({t1, t2, choices});
            }
        } else {
            int m = rnd.next(12, 25);
            for (int i = 0; i < m; ++i) {
                int t1 = rnd.next(0, 99);
                int t2 = rnd.next(t1, 100);
                int count = rnd.wnext(n + 1, rnd.next(-2, 2));
                seeds.push_back({t1, t2, randomPieces(n, count)});
            }
        }

        shuffle(seeds.begin(), seeds.end());
        println(n, (int)seeds.size());
        for (const Seed& seed : seeds) {
            printf("%d %d %d", seed.t1, seed.t2, (int)seed.pieces.size());
            for (int piece : seed.pieces) {
                printf(" %d", piece);
            }
            printf("\n");
        }
    }

    return 0;
}
