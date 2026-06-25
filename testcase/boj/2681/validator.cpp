#include "testlib.h"

#include <array>
#include <cctype>
#include <cstdlib>
#include <string>

using namespace std;

struct Point {
    long double x;
    long double y;
};

long double cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool isCanonicalDecimal(const string& token) {
    int pos = 0;
    if (pos < int(token.size()) && token[pos] == '-') {
        ++pos;
        if (pos == int(token.size()) || token[pos] == '.') {
            return false;
        }
    }

    int integerStart = pos;
    if (pos == int(token.size()) || !isdigit(static_cast<unsigned char>(token[pos]))) {
        return false;
    }
    if (token[pos] == '0') {
        ++pos;
        if (pos < int(token.size()) && isdigit(static_cast<unsigned char>(token[pos]))) {
            return false;
        }
    } else {
        while (pos < int(token.size()) && isdigit(static_cast<unsigned char>(token[pos]))) {
            ++pos;
        }
    }

    if (pos < int(token.size()) && token[pos] == '.') {
        ++pos;
        int fractionalStart = pos;
        while (pos < int(token.size()) && isdigit(static_cast<unsigned char>(token[pos]))) {
            ++pos;
        }
        if (pos == fractionalStart) {
            return false;
        }
    }

    if (pos != int(token.size())) {
        return false;
    }

    return token[integerStart] != '0' || token == "0" || token.rfind("0.", integerStart) == integerStart;
}

long double readCoordinate(const string& name) {
    string token = inf.readToken("[^ ]{1,64}", name.c_str());
    ensuref(isCanonicalDecimal(token), "%s is not a canonical decimal: %s", name.c_str(), token.c_str());
    long double value = strtold(token.c_str(), nullptr);

    // CHECK: The statement gives no coordinate bounds; cap magnitudes to keep
    // numeric test data practical while accepting ordinary decimal inputs.
    ensuref(-1000000.0L <= value && value <= 1000000.0L,
            "%s is outside the practical coordinate cap: %s",
            name.c_str(), token.c_str());

    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    const Point a{0.0L, 0.0L};
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        long double bx = readCoordinate("B_x");
        inf.readSpace();
        long double cx = readCoordinate("C_x");
        inf.readSpace();
        long double cy = readCoordinate("C_y");
        inf.readSpace();
        long double dx = readCoordinate("D_x");
        inf.readSpace();
        long double dy = readCoordinate("D_y");
        inf.readEoln();

        array<Point, 4> p = {{{0.0L, 0.0L}, {bx, 0.0L}, {cx, cy}, {dx, dy}}};
        for (int i = 0; i < 4; ++i) {
            long double area2 = cross(p[i], p[(i + 1) % 4], p[(i + 2) % 4]);
            ensuref(area2 > 0.0L,
                    "vertices A,B,C,D must form a strictly convex counterclockwise quadrilateral; turn %d has cross %.20Lf",
                    i + 1, area2);
        }
    }

    inf.readEof();
}
