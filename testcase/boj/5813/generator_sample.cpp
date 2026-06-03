#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

const int MAX_COORD = 2147483646;

void addCell(vector<pair<int, int> >& cells, int x, int y) {
    cells.push_back(make_pair(x, y));
}

void addRectangle(vector<pair<int, int> >& cells, int h, int w) {
    for (int x = 0; x < h; ++x) {
        for (int y = 0; y < w; ++y) {
            addCell(cells, x, y);
        }
    }
}

void makeRectangle(vector<pair<int, int> >& cells) {
    int h = rnd.next(1, 7);
    int w = rnd.next(1, 7);
    addRectangle(cells, h, w);
}

void makeMonotonePath(vector<pair<int, int> >& cells) {
    int steps = rnd.next(1, 35);
    int x = 0;
    int y = 0;
    addCell(cells, x, y);
    for (int i = 0; i < steps; ++i) {
        if (rnd.next(2) == 0) {
            ++x;
        } else {
            ++y;
        }
        addCell(cells, x, y);
    }
}

void makeSkyline(vector<pair<int, int> >& cells) {
    int h = rnd.next(2, 8);
    int prev = rnd.next(1, 7);
    for (int x = 0; x < h; ++x) {
        int width = max(1, prev + rnd.next(-2, 2));
        for (int y = 0; y < width; ++y) {
            addCell(cells, x, y);
        }
        prev = width;
    }
}

void makeComb(vector<pair<int, int> >& cells) {
    int spine = rnd.next(4, 12);
    int maxTooth = rnd.next(1, 5);
    for (int y = 0; y < spine; ++y) {
        addCell(cells, 0, y);
        int tooth = rnd.next(0, maxTooth);
        for (int x = 1; x <= tooth; ++x) {
            addCell(cells, x, y);
        }
    }
}

void makeNotchedRectangle(vector<pair<int, int> >& cells) {
    int h = rnd.next(3, 8);
    int w = rnd.next(3, 8);
    int side = rnd.next(4);
    int cutLen = rnd.next(1, max(1, min(h, w) - 1));
    int start = rnd.next(1, max(1, (side < 2 ? w : h) - cutLen));

    set<pair<int, int> > removed;
    for (int i = 0; i < cutLen; ++i) {
        if (side == 0) removed.insert(make_pair(0, start + i));
        if (side == 1) removed.insert(make_pair(h - 1, start + i));
        if (side == 2) removed.insert(make_pair(start + i, 0));
        if (side == 3) removed.insert(make_pair(start + i, w - 1));
    }

    for (int x = 0; x < h; ++x) {
        for (int y = 0; y < w; ++y) {
            if (!removed.count(make_pair(x, y))) {
                addCell(cells, x, y);
            }
        }
    }
}

void normalizeAndPrint(vector<pair<int, int> > cells) {
    sort(cells.begin(), cells.end());
    cells.erase(unique(cells.begin(), cells.end()), cells.end());
    shuffle(cells.begin(), cells.end());

    int baseX;
    int baseY;
    if (rnd.next(5) == 0) {
        baseX = rnd.next(MAX_COORD - 100, MAX_COORD - 20);
        baseY = rnd.next(MAX_COORD - 100, MAX_COORD - 20);
    } else {
        baseX = rnd.next(1, 200);
        baseY = rnd.next(1, 200);
    }

    println(int(cells.size()));
    for (size_t i = 0; i < cells.size(); ++i) {
        println(baseX + cells[i].first, baseY + cells[i].second);
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int> > cells;
    int mode = rnd.next(5);
    if (mode == 0) {
        makeRectangle(cells);
    } else if (mode == 1) {
        makeMonotonePath(cells);
    } else if (mode == 2) {
        makeSkyline(cells);
    } else if (mode == 3) {
        makeComb(cells);
    } else {
        makeNotchedRectangle(cells);
    }

    normalizeAndPrint(cells);
    return 0;
}
