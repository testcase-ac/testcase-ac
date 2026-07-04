#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

long long cross(const pair<int, int>& a, const pair<int, int>& b, const pair<int, int>& c) {
    long long abx = b.first - a.first;
    long long aby = b.second - a.second;
    long long acx = c.first - a.first;
    long long acy = c.second - a.second;
    return abx * acy - aby * acx;
}

bool matchesValidatorGeometry(const vector<pair<int, int>>& p) {
    int n = (int)p.size();
    set<pair<int, int>> seen(p.begin(), p.end());
    if ((int)seen.size() != n) {
        return false;
    }

    if (n < 3) {
        return true;
    }

    long long direction = 0;
    for (int i = 0; i < n; ++i) {
        long long turn = cross(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (turn == 0) {
            return false;
        }
        long long sign = turn > 0 ? 1 : -1;
        if (direction == 0) {
            direction = sign;
        } else if (sign != direction) {
            return false;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            for (int k = j + 1; k < n; ++k) {
                long long area = cross(p[i], p[j], p[k]);
                if (area == 0 || (area > 0 ? 1 : -1) != direction) {
                    return false;
                }
            }
        }
    }

    return true;
}

vector<pair<int, int>> makeConvexPoints(int n) {
    if (n == 2) {
        int x1 = rnd.next(-20, 20);
        int y1 = rnd.next(-20, 20);
        int x2 = x1;
        int y2 = y1;
        while (x1 == x2 && y1 == y2) {
            x2 = rnd.next(-20, 20);
            y2 = rnd.next(-20, 20);
        }
        return {{x1, y1}, {x2, y2}};
    }

    for (int attempt = 0; attempt < 2000; ++attempt) {
        vector<double> angles;
        double start = rnd.next(0.0, 2.0 * acos(-1.0));
        for (int i = 0; i < n; ++i) {
            double jitter = rnd.next(-0.22, 0.22);
            angles.push_back(start + (2.0 * acos(-1.0) * i) / n + jitter);
        }
        sort(angles.begin(), angles.end());

        int radius = rnd.next(20, 200);
        int stretchX = rnd.next(1, 4);
        int stretchY = rnd.next(1, 4);
        int shiftX = rnd.next(-500, 500);
        int shiftY = rnd.next(-500, 500);

        vector<pair<int, int>> p;
        for (double angle : angles) {
            int x = shiftX + (int)llround(radius * stretchX * cos(angle));
            int y = shiftY + (int)llround(radius * stretchY * sin(angle));
            p.push_back({x, y});
        }

        if (rnd.next(2) == 1) {
            reverse(p.begin(), p.end());
        }
        if (matchesValidatorGeometry(p)) {
            return p;
        }
    }

    quitf(_fail, "failed to generate validator-compatible convex points");
}

string makeGenderString(int n) {
    int mode = rnd.next(4);
    int boys = 0;

    if (mode == 0) {
        boys = rnd.next(n / 2 + 1) * 2;
    } else if (mode == 1) {
        boys = rnd.next(2) == 0 ? 0 : n;
    } else if (mode == 2) {
        boys = n >= 4 ? 2 : n;
    } else {
        boys = n - (n >= 4 ? 2 : 0);
    }

    string s(boys, 'B');
    s += string(n - boys, 'G');

    if (mode == 3) {
        string alternating;
        for (int i = 0; i < n; ++i) {
            alternating += i % 2 == 0 ? 'B' : 'G';
        }
        if (count(alternating.begin(), alternating.end(), 'B') % 2 == 0 &&
            count(alternating.begin(), alternating.end(), 'G') % 2 == 0) {
            s = alternating;
        }
    }

    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 12) * 2;
    vector<pair<int, int>> points = makeConvexPoints(n);
    string genders = makeGenderString(n);

    println(n);
    println(genders);
    for (const auto& point : points) {
        println(point.first, point.second);
    }

    return 0;
}
