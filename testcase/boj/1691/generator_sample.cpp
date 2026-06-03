#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int w;
    int h;
    vector<pair<int, int>> pieces;

    auto addPiece = [&](int wi, int hi) {
        wi = max(1, min(wi, w));
        hi = max(1, min(hi, h));
        pieces.push_back({wi, hi});
    };

    if (mode == 0) {
        w = rnd.next(1, 12);
        h = rnd.next(1, 12);
        int n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            addPiece(rnd.next(1, w), rnd.next(1, h));
        }
    } else if (mode == 1) {
        w = rnd.next(15, 80);
        h = rnd.next(15, 80);
        int n = rnd.next(8, 30);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 1) == 0) {
                addPiece(rnd.next(1, min(w, 8)), rnd.next(1, h));
            } else {
                addPiece(rnd.next(1, w), rnd.next(1, min(h, 8)));
            }
        }
    } else if (mode == 2) {
        w = rnd.next(80, 220);
        h = rnd.next(80, 220);
        int n = rnd.next(20, 70);
        for (int i = 0; i < n; ++i) {
            int wi = rnd.next(max(1, w - 25), w);
            int hi = rnd.next(max(1, h - 25), h);
            if (rnd.next(0, 2) == 0) wi = rnd.next(1, min(w, 10));
            if (rnd.next(0, 2) == 0) hi = rnd.next(1, min(h, 10));
            addPiece(wi, hi);
        }
    } else if (mode == 3) {
        w = rnd.next(20, 100);
        h = rnd.next(20, 100);
        int baseW = rnd.next(1, w);
        int baseH = rnd.next(1, h);
        int n = rnd.next(30, 120);
        for (int i = 0; i < n; ++i) {
            int wi = baseW + rnd.next(-3, 3);
            int hi = baseH + rnd.next(-3, 3);
            addPiece(wi, hi);
        }
    } else if (mode == 4) {
        w = rnd.next(250, 600);
        h = rnd.next(250, 600);
        int n = rnd.next(40, 120);
        addPiece(w, h);
        addPiece(1, 1);
        addPiece(w, 1);
        addPiece(1, h);
        for (int i = 4; i < n; ++i) {
            int wi = rnd.next(1, min(w, 60));
            int hi = rnd.next(1, min(h, 60));
            if (rnd.next(0, 3) == 0) wi = w;
            if (rnd.next(0, 3) == 0) hi = h;
            addPiece(wi, hi);
        }
    } else {
        w = rnd.next(8, 60);
        h = rnd.next(8, 60);
        set<pair<int, int>> candidates;
        for (int a = 1; a <= min(w, 12); ++a) {
            for (int b = 1; b <= min(h, 12); ++b) {
                if (w % a == 0 || h % b == 0 || rnd.next(0, 9) == 0) {
                    candidates.insert({a, b});
                }
            }
        }
        vector<pair<int, int>> all(candidates.begin(), candidates.end());
        shuffle(all.begin(), all.end());
        int n = rnd.next(1, min<int>(200, all.size()));
        pieces.assign(all.begin(), all.begin() + n);
    }

    shuffle(pieces.begin(), pieces.end());
    if ((int)pieces.size() > 200) pieces.resize(200);

    println(w, h);
    println((int)pieces.size());
    for (auto [wi, hi] : pieces) {
        println(wi, hi);
    }

    return 0;
}
