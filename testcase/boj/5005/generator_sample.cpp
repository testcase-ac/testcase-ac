#include "testlib.h"

#include <algorithm>
#include <tuple>
#include <vector>

using namespace std;

using Line = tuple<int, int, int, int>;

const int kCoordMin = -10000;
const int kCoordMax = 10000;

int coord() {
    return rnd.next(kCoordMin, kCoordMax);
}

Line makeLine(int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        if (x2 < kCoordMax) {
            ++x2;
        } else {
            --x2;
        }
    }
    return Line(x1, y1, x2, y2);
}

Line randomLine() {
    return makeLine(coord(), coord(), coord(), coord());
}

Line horizontalLine(int y) {
    int x1 = rnd.next(kCoordMin, kCoordMax - 1);
    int x2 = rnd.next(x1 + 1, kCoordMax);
    if (rnd.next(2)) {
        swap(x1, x2);
    }
    return Line(x1, y, x2, y);
}

Line verticalLine(int x) {
    int y1 = rnd.next(kCoordMin, kCoordMax - 1);
    int y2 = rnd.next(y1 + 1, kCoordMax);
    if (rnd.next(2)) {
        swap(y1, y2);
    }
    return Line(x, y1, x, y2);
}

Line slopeOneLine(int shift) {
    int x1 = rnd.next(kCoordMin, kCoordMax - 1);
    int x2 = rnd.next(x1 + 1, kCoordMax);
    int y1 = x1 + shift;
    int y2 = x2 + shift;
    if (y1 < kCoordMin || y1 > kCoordMax || y2 < kCoordMin || y2 > kCoordMax) {
        return randomLine();
    }
    if (rnd.next(2)) {
        swap(x1, x2);
        swap(y1, y2);
    }
    return Line(x1, y1, x2, y2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int w = rnd.next(1, 100);
    int n = rnd.next(1, 18);
    if (rnd.next(8) == 0) {
        n = rnd.next(60, 100);
    }

    vector<Line> lines;
    lines.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            lines.push_back(randomLine());
        }
    } else if (mode == 1) {
        int y = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            lines.push_back(horizontalLine(y + rnd.next(-3, 3)));
        }
    } else if (mode == 2) {
        int x = rnd.next(-20, 20);
        for (int i = 0; i < n; ++i) {
            lines.push_back(verticalLine(x + rnd.next(-3, 3)));
        }
    } else if (mode == 3) {
        Line repeated = randomLine();
        for (int i = 0; i < n; ++i) {
            lines.push_back(rnd.next(3) == 0 ? randomLine() : repeated);
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                lines.push_back(makeLine(kCoordMin, coord(), kCoordMax, coord()));
            } else if (i % 3 == 1) {
                lines.push_back(makeLine(coord(), kCoordMin, coord(), kCoordMax));
            } else {
                lines.push_back(makeLine(kCoordMin, kCoordMin, kCoordMax, kCoordMax));
            }
        }
    } else {
        int shift = rnd.next(-100, 100);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(2)) {
                lines.push_back(slopeOneLine(shift + rnd.next(-4, 4)));
            } else {
                lines.push_back(randomLine());
            }
        }
    }

    if (rnd.next(5) == 0) {
        w = rnd.next(1, min(100, 2 * n + 4));
    }

    println(w, n);
    for (const Line& line : lines) {
        int x1, y1, x2, y2;
        tie(x1, y1, x2, y2) = line;
        println(x1, y1, x2, y2);
    }

    return 0;
}
