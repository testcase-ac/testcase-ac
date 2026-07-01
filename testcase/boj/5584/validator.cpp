#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Rect {
    int x1;
    int y1;
    int x2;
    int y2;
};

static long long coveredArea(vector<Rect> rects) {
    vector<int> xs;
    xs.reserve(rects.size() * 2);
    for (const Rect& r : rects) {
        xs.push_back(r.x1);
        xs.push_back(r.x2);
    }
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    long long area = 0;
    for (int i = 0; i + 1 < static_cast<int>(xs.size()); ++i) {
        int left = xs[i];
        int right = xs[i + 1];
        if (left == right) {
            continue;
        }

        vector<pair<int, int>> ys;
        for (const Rect& r : rects) {
            if (r.x1 <= left && right <= r.x2) {
                ys.push_back({r.y1, r.y2});
            }
        }
        if (ys.empty()) {
            continue;
        }

        sort(ys.begin(), ys.end());
        long long coveredY = 0;
        int currentL = ys[0].first;
        int currentR = ys[0].second;
        for (int j = 1; j < static_cast<int>(ys.size()); ++j) {
            if (ys[j].first > currentR) {
                coveredY += currentR - currentL;
                currentL = ys[j].first;
                currentR = ys[j].second;
            } else {
                currentR = max(currentR, ys[j].second);
            }
        }
        coveredY += currentR - currentL;
        area += coveredY * (right - left);
    }
    return area;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(1, 1000000, "w");
    inf.readSpace();
    int h = inf.readInt(1, 1000000, "h");
    inf.readEoln();

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    vector<Rect> rects;
    rects.reserve(n);
    for (int i = 0; i < n; ++i) {
        Rect r;
        r.x1 = inf.readInt(0, w - 1, "x1");
        inf.readSpace();
        r.y1 = inf.readInt(0, h - 1, "y1");
        inf.readSpace();
        r.x2 = inf.readInt(r.x1 + 1, w, "x2");
        inf.readSpace();
        r.y2 = inf.readInt(r.y1 + 1, h, "y2");
        inf.readEoln();
        rects.push_back(r);
    }

    long long boardArea = 1LL * w * h;
    ensuref(coveredArea(rects) < boardArea,
            "masking tape must not cover the entire board");

    inf.readEof();
}
