#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

struct Sidewalk {
    int left;
    int right;
    double speed;
};

static double randomSpeed(double lo, double hi) {
    int scaled = rnd.next(static_cast<int>(lo * 10), static_cast<int>(hi * 10));
    return scaled / 10.0;
}

static vector<pair<int, int>> makeSegments(int n, int x, bool touchEdges) {
    vector<int> cuts;
    cuts.push_back(0);
    cuts.push_back(x);

    int need = 2 * n;
    for (int guard = 0; static_cast<int>(cuts.size()) < need + 2 && guard < 10000; ++guard) {
        cuts.push_back(rnd.next(0, x));
        sort(cuts.begin(), cuts.end());
        cuts.erase(unique(cuts.begin(), cuts.end()), cuts.end());
    }

    vector<pair<int, int>> all;
    for (int i = 0; i + 1 < static_cast<int>(cuts.size()); ++i) {
        if (cuts[i] < cuts[i + 1]) {
            all.push_back({cuts[i], cuts[i + 1]});
        }
    }
    shuffle(all.begin(), all.end());
    all.resize(n);
    sort(all.begin(), all.end());

    if (touchEdges && n > 0) {
        all.front().first = 0;
        all.back().second = x;
        for (int i = 1; i < n; ++i) {
            if (all[i - 1].second > all[i].first) {
                all[i].first = all[i - 1].second;
            }
            if (all[i].first == all[i].second) {
                all[i].second = min(x, all[i].first + 1);
            }
        }
    }

    return all;
}

static void printCase(int n, int x, double v, const vector<Sidewalk>& sidewalks) {
    cout << fixed << setprecision(1);
    cout << n << ' ' << x << ' ' << v << '\n';
    for (const Sidewalk& s : sidewalks) {
        cout << s.left << ' ' << s.right << ' ' << s.speed << '\n';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(0, 8);
    int x = rnd.next(1, 200);
    double v = randomSpeed(1.0, 100.0);
    vector<Sidewalk> sidewalks;

    if (mode == 0) {
        n = rnd.next(0, 2);
    } else if (mode == 1) {
        n = rnd.next(2, 6);
        if (n % 2 == 1) --n;
    } else if (mode == 2) {
        n = rnd.next(1, 5);
        v = randomSpeed(1.0, 15.0);
    } else if (mode == 3) {
        n = rnd.next(3, 8);
        x = rnd.next(50, 500);
    } else if (mode == 4) {
        n = rnd.next(1, 4);
        x = rnd.any(vector<int>{1, 2, 10, 1000000});
        v = rnd.any(vector<double>{1.0, 22.4, 66.0, 100.0});
    }
    n = min(n, x);

    vector<pair<int, int>> segments = makeSegments(n, x, mode == 4);
    for (int i = 0; i < n; ++i) {
        double speed = randomSpeed(-100.0, 100.0);
        if (mode == 1) {
            speed = (i % 2 == 0 ? 1 : -1) * randomSpeed(20.0, 100.0);
        } else if (mode == 2) {
            speed = rnd.any(vector<double>{-100.0, -99.9, 99.9, 100.0});
        } else if (mode == 3) {
            speed = randomSpeed(-5.0, 5.0);
        }
        sidewalks.push_back({segments[i].first, segments[i].second, speed});
    }

    sort(sidewalks.begin(), sidewalks.end(), [](const Sidewalk& a, const Sidewalk& b) {
        return a.left < b.left;
    });
    printCase(n, x, v, sidewalks);
    return 0;
}
