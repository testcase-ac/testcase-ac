#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Disease {
    int r;
    int b;
    int d;
};

pair<int, int> nonzeroPills(int limit) {
    int r = rnd.next(0, limit);
    int b = rnd.next(0, limit);
    if (r + b == 0) {
        if (rnd.next(2) == 0) {
            r = 1;
        } else {
            b = 1;
        }
    }
    return {r, b};
}

pair<int, int> boundedReachableTarget(const vector<Disease>& diseases) {
    vector<int> order(diseases.size());
    for (int i = 0; i < int(order.size()); ++i) {
        order[i] = i;
    }
    shuffle(order.begin(), order.end());

    int r = 0;
    int b = 0;
    for (int idx : order) {
        if (rnd.next(3) == 0 && r + diseases[idx].r <= 50 && b + diseases[idx].b <= 50) {
            r += diseases[idx].r;
            b += diseases[idx].b;
        }
    }

    if (r + b == 0) {
        for (const Disease& disease : diseases) {
            if (disease.r <= 50 && disease.b <= 50) {
                return {disease.r, disease.b};
            }
        }
    }

    return {r, b};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n = rnd.next(1, mode == 4 ? 35 : 18);
    int m = rnd.next(1, mode == 4 ? 35 : 16);
    vector<Disease> diseases;

    if (mode == 0) {
        for (int i = 0; i < m; ++i) {
            auto [r, b] = nonzeroPills(8);
            diseases.push_back({r, b, rnd.next(0, 30)});
        }
    } else if (mode == 1) {
        auto base = nonzeroPills(10);
        for (int i = 0; i < m; ++i) {
            int r = rnd.next(3) == 0 ? base.first : rnd.next(0, 12);
            int b = rnd.next(3) == 0 ? base.second : rnd.next(0, 12);
            if (r + b == 0) {
                r = base.first;
                b = base.second;
            }
            diseases.push_back({r, b, rnd.next(0, 100)});
        }
    } else if (mode == 2) {
        for (int i = 0; i < m; ++i) {
            int r = rnd.next(2) == 0 ? 0 : rnd.next(1, 20);
            int b = r == 0 ? rnd.next(1, 20) : rnd.next(0, 20);
            diseases.push_back({r, b, rnd.next(0, 100)});
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            auto [r, b] = nonzeroPills(50);
            int risk = rnd.next(4) == 0 ? 0 : rnd.next(70, 100);
            diseases.push_back({r, b, risk});
        }
    } else {
        for (int i = 0; i < m; ++i) {
            auto [r, b] = nonzeroPills(6);
            diseases.push_back({r, b, rnd.next(0, 15)});
        }
    }

    vector<pair<int, int>> students;
    for (int i = 0; i < n; ++i) {
        int kind = rnd.next(4);
        pair<int, int> pills;
        if (kind == 0) {
            pills = {rnd.next(0, 50), rnd.next(0, 50)};
            if (pills.first + pills.second == 0) {
                pills.first = 1;
            }
        } else if (kind == 1) {
            const Disease& disease = rnd.any(diseases);
            pills = {disease.r, disease.b};
        } else if (kind == 2) {
            pills = boundedReachableTarget(diseases);
        } else {
            pills = rnd.next(2) == 0 ? make_pair(50, rnd.next(0, 50)) : make_pair(rnd.next(0, 50), 50);
            if (pills.first + pills.second == 0) {
                pills.second = 1;
            }
        }
        students.push_back(pills);
    }

    println(n, m);
    for (const Disease& disease : diseases) {
        println(disease.r, disease.b, disease.d);
    }
    for (auto [r, b] : students) {
        println(r, b);
    }

    return 0;
}
