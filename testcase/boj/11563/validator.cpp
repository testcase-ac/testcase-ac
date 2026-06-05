#include "testlib.h"

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;
using namespace std;

const cpp_int SCALE = cpp_int("100000000000000000000");

struct Point {
    cpp_int x;
    cpp_int y;
};

struct Segment {
    Point a;
    Point b;
};

struct Dsu {
    vector<int> parent;
    vector<int> size;

    explicit Dsu(int n) : parent(n), size(n, 1) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int find(int v) {
        if (parent[v] == v) {
            return v;
        }
        return parent[v] = find(parent[v]);
    }

    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        if (size[a] < size[b]) {
            swap(a, b);
        }
        parent[b] = a;
        size[a] += size[b];
    }
};

bool isZero(const string& s) {
    for (char ch : s) {
        if (isdigit(static_cast<unsigned char>(ch)) && ch != '0') {
            return false;
        }
    }
    return true;
}

Point readPoint(int limit, const string& xName, const string& yName);

cpp_int readCoord(int limit, const string& name) {
    string token = inf.readToken("[^ ]{1,32}", name);
    bool negative = false;
    size_t pos = 0;

    if (token[pos] == '-') {
        negative = true;
        ++pos;
        ensuref(pos < token.size(), "%s has no digits", name.c_str());
    }

    ensuref(token[pos] != '+', "%s has a plus sign", name.c_str());

    size_t intBegin = pos;
    while (pos < token.size() && isdigit(static_cast<unsigned char>(token[pos]))) {
        ++pos;
    }
    ensuref(pos > intBegin, "%s has no integer part", name.c_str());

    string intPart = token.substr(intBegin, pos - intBegin);
    ensuref(intPart.size() == 1 || intPart[0] != '0', "%s has leading zeroes", name.c_str());

    string fracPart;
    if (pos < token.size()) {
        ensuref(token[pos] == '.', "%s has invalid decimal separator", name.c_str());
        ++pos;
        size_t fracBegin = pos;
        while (pos < token.size() && isdigit(static_cast<unsigned char>(token[pos]))) {
            ++pos;
        }
        ensuref(pos > fracBegin, "%s has no fractional digits", name.c_str());
        fracPart = token.substr(fracBegin, pos - fracBegin);
        ensuref(fracPart.size() <= 20, "%s has more than 20 fractional digits", name.c_str());
    }
    ensuref(pos == token.size(), "%s has invalid characters", name.c_str());
    ensuref(!negative || !isZero(token), "%s uses negative zero", name.c_str());

    cpp_int value = 0;
    for (char ch : intPart) {
        value *= 10;
        value += ch - '0';
    }
    value *= SCALE;
    cpp_int frac = 0;
    for (char ch : fracPart) {
        frac *= 10;
        frac += ch - '0';
    }
    for (size_t i = fracPart.size(); i < 20; ++i) {
        frac *= 10;
    }
    value += frac;
    if (negative) {
        value = -value;
    }

    cpp_int scaledLimit = cpp_int(limit) * SCALE;
    ensuref(-scaledLimit <= value && value <= scaledLimit, "%s is out of range", name.c_str());
    return value;
}

Point readPoint(int limit, const string& xName, const string& yName) {
    Point p;
    p.x = readCoord(limit, xName);
    inf.readSpace();
    p.y = readCoord(limit, yName);
    return p;
}

cpp_int cross(const Point& a, const Point& b, const Point& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int sign(const cpp_int& v) {
    if (v < 0) {
        return -1;
    }
    if (v > 0) {
        return 1;
    }
    return 0;
}

bool between(const cpp_int& a, const cpp_int& b, const cpp_int& c) {
    return min(a, b) <= c && c <= max(a, b);
}

bool onSegment(const Segment& s, const Point& p) {
    return sign(cross(s.a, s.b, p)) == 0 && between(s.a.x, s.b.x, p.x) &&
           between(s.a.y, s.b.y, p.y);
}

bool intersects(const Segment& lhs, const Segment& rhs) {
    int c1 = sign(cross(lhs.a, lhs.b, rhs.a));
    int c2 = sign(cross(lhs.a, lhs.b, rhs.b));
    int c3 = sign(cross(rhs.a, rhs.b, lhs.a));
    int c4 = sign(cross(rhs.a, rhs.b, lhs.b));

    if (c1 == 0 && onSegment(lhs, rhs.a)) {
        return true;
    }
    if (c2 == 0 && onSegment(lhs, rhs.b)) {
        return true;
    }
    if (c3 == 0 && onSegment(rhs, lhs.a)) {
        return true;
    }
    if (c4 == 0 && onSegment(rhs, lhs.b)) {
        return true;
    }
    return c1 != c2 && c3 != c4;
}

vector<Segment> readSegments(int count, int limit, const string& groupName) {
    vector<Segment> segments(count);
    for (int i = 0; i < count; ++i) {
        string prefix = groupName + "[" + to_string(i + 1) + "]";
        segments[i].a = readPoint(limit, prefix + ".xs", prefix + ".ys");
        inf.readSpace();
        segments[i].b = readPoint(limit, prefix + ".xe", prefix + ".ye");
        inf.readEoln();
        // CHECK: The statement calls each item a road segment, so a zero-length segment is not accepted.
        ensuref(segments[i].a.x != segments[i].b.x || segments[i].a.y != segments[i].b.y,
                "%s is zero-length", prefix.c_str());
    }
    return segments;
}

void ensureConnected(const vector<Segment>& segments, const string& groupName) {
    Dsu dsu(static_cast<int>(segments.size()));
    for (int i = 0; i < static_cast<int>(segments.size()); ++i) {
        for (int j = i + 1; j < static_cast<int>(segments.size()); ++j) {
            if (intersects(segments[i], segments[j])) {
                dsu.unite(i, j);
            }
        }
    }

    int root = dsu.find(0);
    for (int i = 1; i < static_cast<int>(segments.size()); ++i) {
        ensuref(dsu.find(i) == root, "%s segments %d and %d are not mutually reachable",
                groupName.c_str(), 1, i + 1);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "m");
    inf.readEoln();

    vector<Segment> sinchon = readSegments(n, 10000, "sinchon");
    vector<Segment> anam = readSegments(m, 50000, "anam");
    ensureConnected(sinchon, "sinchon");
    ensureConnected(anam, "anam");

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            ensuref(!intersects(sinchon[i], anam[j]),
                    "sinchon segment %d already reaches anam segment %d", i + 1, j + 1);
        }
    }

    inf.readEof();
}
