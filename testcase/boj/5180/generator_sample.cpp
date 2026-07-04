#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

namespace {

const long double kTwoPi = 2.0L * acosl(-1.0L);

string formatReal(long double value) {
    ostringstream out;
    out << fixed << setprecision(6) << static_cast<double>(value);
    string s = out.str();
    while (s.size() > 1 && s.back() == '0') {
        s.pop_back();
    }
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }
    return s;
}

long double angleOnGrid(int numerator, int denominator) {
    return kTwoPi * static_cast<long double>(numerator) /
           static_cast<long double>(denominator);
}

long double radiusFromSlot(int slot) {
    return static_cast<long double>(slot) / 200.0L;
}

void addPoint(vector<pair<string, string>>& points, set<pair<string, string>>& used,
              long double angle, long double radius) {
    string alpha = formatReal(angle);
    string r = formatReal(radius);
    if (used.insert({alpha, r}).second) {
        points.push_back({alpha, r});
    }
}

vector<pair<string, string>> sameRayCase() {
    int n = rnd.next(2, 8);
    int angleSlot = rnd.next(0, 31);
    long double angle = angleOnGrid(angleSlot, 32);

    vector<pair<string, string>> points;
    set<pair<string, string>> used;
    for (int i = 0; i < n; ++i) {
        addPoint(points, used, angle, radiusFromSlot(i + 1));
    }
    return points;
}

vector<pair<string, string>> symmetricCase() {
    int slices = rnd.any(vector<int>{2, 3, 4, 5, 6});
    int perSlice = rnd.next(1, 4);
    long double offset = angleOnGrid(rnd.next(0, 23), 24 * slices);

    vector<pair<string, string>> points;
    set<pair<string, string>> used;
    for (int layer = 0; layer < perSlice; ++layer) {
        long double base = offset + angleOnGrid(layer, perSlice * slices * 2);
        if (base >= kTwoPi) {
            base -= kTwoPi;
        }
        for (int s = 0; s < slices; ++s) {
            long double angle = base + angleOnGrid(s, slices);
            if (angle >= kTwoPi) {
                angle -= kTwoPi;
            }
            addPoint(points, used, angle, radiusFromSlot(10 + layer * slices + s));
        }
    }
    shuffle(points.begin(), points.end());
    return points;
}

vector<pair<string, string>> randomCase() {
    int n = rnd.next(1, 18);
    int denominator = rnd.next(24, 96);

    vector<pair<string, string>> points;
    set<pair<string, string>> used;
    while (static_cast<int>(points.size()) < n) {
        int angleSlot = rnd.next(0, denominator - 1);
        int radiusSlot = rnd.next(1, 200);
        addPoint(points, used, angleOnGrid(angleSlot, denominator),
                 radiusFromSlot(radiusSlot));
    }
    return points;
}

vector<pair<string, string>> boundaryCase() {
    vector<pair<string, string>> points;
    set<pair<string, string>> used;
    addPoint(points, used, 0.0L, 1.0L);

    int extra = rnd.next(1, 7);
    for (int i = 0; i < extra; ++i) {
        int denominator = rnd.next(30, 90);
        int angleSlot = rnd.next(1, denominator - 1);
        addPoint(points, used, angleOnGrid(angleSlot, denominator),
                 radiusFromSlot(rnd.next(1, 199)));
    }
    return points;
}

vector<pair<string, string>> makeCase(int mode) {
    if (mode == 0) {
        return sameRayCase();
    }
    if (mode == 1) {
        return symmetricCase();
    }
    if (mode == 2) {
        return boundaryCase();
    }
    return randomCase();
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(3, 8);
    println(k);
    for (int tc = 0; tc < k; ++tc) {
        vector<pair<string, string>> points = makeCase(tc % 4);
        println(static_cast<int>(points.size()));
        for (const auto& point : points) {
            println(point.first, point.second);
        }
    }

    return 0;
}
