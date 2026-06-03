#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

struct Circle {
    int id;
    int x;
    int r;
    int left;
    int right;
};

struct Endpoint {
    int coord;
    int type;
    int index;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MIN_N = 2;
    constexpr int MAX_N = 200000;
    constexpr int MIN_X = -1000000;
    constexpr int MAX_X = 1000000;
    constexpr int MIN_R = 1;
    constexpr int MAX_R = 10000;

    int n = inf.readInt(MIN_N, MAX_N, "N");
    inf.readEoln();

    vector<Circle> circles(n);
    vector<bool> seen_id(n + 1, false);
    for (int i = 0; i < n; ++i) {
        int k = inf.readInt(1, n, "k_i");
        inf.readSpace();
        int x = inf.readInt(MIN_X, MAX_X, "x_i");
        inf.readSpace();
        int r = inf.readInt(MIN_R, MAX_R, "r_i");
        inf.readEoln();

        ensuref(!seen_id[k], "duplicate circle id %d at circle line %d", k, i + 1);
        seen_id[k] = true;

        circles[i] = {k, x, r, x - r, x + r};
    }

    int a = inf.readInt(1, n, "A");
    inf.readSpace();
    int b = inf.readInt(1, n, "B");
    inf.readEoln();
    ensuref(a != b, "A and B must be distinct: %d", a);

    vector<Endpoint> endpoints;
    endpoints.reserve(2 * n);
    for (int i = 0; i < n; ++i) {
        endpoints.push_back({circles[i].left, 0, i});
        endpoints.push_back({circles[i].right, 1, i});
    }

    sort(endpoints.begin(), endpoints.end(), [](const Endpoint& lhs, const Endpoint& rhs) {
        if (lhs.coord != rhs.coord) {
            return lhs.coord < rhs.coord;
        }
        return lhs.type < rhs.type;
    });

    vector<int> stack;
    stack.reserve(n);
    for (int i = 0; i < (int)endpoints.size(); ++i) {
        if (i > 0) {
            ensuref(endpoints[i - 1].coord != endpoints[i].coord,
                    "circles %d and %d have equal boundary coordinate %d",
                    circles[endpoints[i - 1].index].id,
                    circles[endpoints[i].index].id,
                    endpoints[i].coord);
        }

        int circle_index = endpoints[i].index;
        if (endpoints[i].type == 0) {
            stack.push_back(circle_index);
        } else {
            ensuref(!stack.empty(), "right endpoint for circle %d appears without an open circle",
                    circles[circle_index].id);
            ensuref(stack.back() == circle_index,
                    "circles %d and %d intersect without strict containment",
                    circles[stack.back()].id,
                    circles[circle_index].id);
            stack.pop_back();
        }
    }
    ensuref(stack.empty(), "some circle intervals were not closed");

    inf.readEof();
}
