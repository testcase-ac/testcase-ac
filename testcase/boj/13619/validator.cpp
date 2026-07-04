#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Point {
    long long x;
    long long y;
};

long long readCoordinate(const string& name) {
    string token = inf.readToken("[0-9]{1,5}\\.[0-9]{4}", name);

    size_t dot = token.find('.');
    string integerPart = token.substr(0, dot);
    string fractionalPart = token.substr(dot + 1);

    ensuref(integerPart == "0" || integerPart[0] != '0',
            "%s has a leading zero: %s", name.c_str(), token.c_str());

    long long integerValue = 0;
    for (char c : integerPart) {
        integerValue = integerValue * 10 + (c - '0');
    }

    long long fractionalValue = 0;
    for (char c : fractionalPart) {
        fractionalValue = fractionalValue * 10 + (c - '0');
    }

    long long scaled = integerValue * 10000 + fractionalValue;
    ensuref(0 <= scaled && scaled <= 10000LL * 10000LL,
            "%s is outside [0, 10000]: %s", name.c_str(), token.c_str());
    return scaled;
}

__int128 cross(const Point& a, const Point& b, const Point& c) {
    long long bax = b.x - a.x;
    long long bay = b.y - a.y;
    long long cbx = c.x - b.x;
    long long cby = c.y - b.y;
    return static_cast<__int128>(bax) * cby - static_cast<__int128>(bay) * cbx;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    vector<Point> points(2 * n);
    for (int i = 0; i < 2 * n; ++i) {
        points[i].x = readCoordinate("X");
        inf.readSpace();
        points[i].y = readCoordinate("Y");
        inf.readEoln();
    }

    for (int i = 0; i < 2 * n; ++i) {
        const Point& a = points[i];
        const Point& b = points[(i + 1) % (2 * n)];
        const Point& c = points[(i + 2) % (2 * n)];
        // CHECK: "convex polygon vertices" is interpreted as a strictly convex polygon.
        ensuref(cross(a, b, c) > 0,
                "points must be listed as strict counter-clockwise convex polygon vertices");
    }

    inf.readEof();
}
