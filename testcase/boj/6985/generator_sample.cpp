#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Rect {
    int left;
    int right;
    int bottom;
    int top;
};

static pair<int, int> randomCell(int width, int height) {
    return {rnd.next(0, width - 1), rnd.next(0, height - 1)};
}

static bool contains(const Rect& rect, int x, int y) {
    return rect.left <= x && x <= rect.right && rect.bottom <= y && y <= rect.top;
}

static bool touchesEndpoint(const Rect& rect, pair<int, int> start, pair<int, int> finish) {
    return contains(rect, start.first, start.second) ||
           contains(rect, finish.first, finish.second);
}

static void addRectIfValid(vector<Rect>& rects, const Rect& rect,
                           pair<int, int> start, pair<int, int> finish) {
    if (!touchesEndpoint(rect, start, finish)) {
        rects.push_back(rect);
    }
}

static vector<Rect> makeObstacles(int width, int height,
                                  pair<int, int> start,
                                  pair<int, int> finish,
                                  int mode) {
    vector<Rect> rects;

    if (mode == 0) {
        return rects;
    }

    if (mode == 1) {
        int count = rnd.next(1, 8);
        for (int i = 0; i < count; ++i) {
            int x = rnd.next(0, width - 1);
            int y = rnd.next(0, height - 1);
            addRectIfValid(rects, {x, x, y, y}, start, finish);
        }
        return rects;
    }

    if (mode == 2) {
        int count = rnd.next(1, 5);
        for (int i = 0; i < count; ++i) {
            int left = rnd.next(0, width - 1);
            int right = rnd.next(left, min(width - 1, left + rnd.next(0, 4)));
            int bottom = rnd.next(0, height - 1);
            int top = rnd.next(bottom, min(height - 1, bottom + rnd.next(0, 4)));
            addRectIfValid(rects, {left, right, bottom, top}, start, finish);
        }
        return rects;
    }

    if (mode == 3 && width >= 3) {
        int wallX = rnd.next(1, width - 2);
        int gapY = rnd.next(0, height - 1);
        if (gapY > 0) {
            addRectIfValid(rects, {wallX, wallX, 0, gapY - 1}, start, finish);
        }
        if (gapY + 1 < height) {
            addRectIfValid(rects, {wallX, wallX, gapY + 1, height - 1}, start, finish);
        }
        return rects;
    }

    if (mode == 4 && height >= 3) {
        int wallY = rnd.next(1, height - 2);
        int gapX = rnd.next(0, width - 1);
        if (gapX > 0) {
            addRectIfValid(rects, {0, gapX - 1, wallY, wallY}, start, finish);
        }
        if (gapX + 1 < width) {
            addRectIfValid(rects, {gapX + 1, width - 1, wallY, wallY}, start, finish);
        }
        return rects;
    }

    int attempts = rnd.next(1, min(20, width * height));
    for (int i = 0; i < attempts; ++i) {
        int x = rnd.next(0, width - 1);
        int y = rnd.next(0, height - 1);
        if (rnd.next(0, 4) == 0) {
            int x2 = min(width - 1, x + rnd.next(0, 1));
            int y2 = min(height - 1, y + rnd.next(0, 1));
            addRectIfValid(rects, {x, x2, y, y2}, start, finish);
        } else {
            addRectIfValid(rects, {x, x, y, y}, start, finish);
        }
    }
    return rects;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(1, 6);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        int mode = rnd.next(0, 5);
        int width;
        int height;
        if (mode == 0) {
            width = rnd.next(1, 4);
            height = rnd.next(1, 4);
        } else if (mode <= 2) {
            width = rnd.next(4, 10);
            height = rnd.next(4, 10);
        } else {
            width = rnd.next(8, 16);
            height = rnd.next(8, 16);
        }

        pair<int, int> start = randomCell(width, height);
        pair<int, int> finish = randomCell(width, height);
        if (width * height > 1) {
            while (finish == start) {
                finish = randomCell(width, height);
            }
        }

        vector<Rect> obstacles = makeObstacles(width, height, start, finish, mode);

        println(width, height);
        println(start.first, start.second, finish.first, finish.second);
        println(static_cast<int>(obstacles.size()));
        for (const Rect& rect : obstacles) {
            println(rect.left, rect.right, rect.bottom, rect.top);
        }
    }

    return 0;
}
