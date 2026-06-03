#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

struct Circle {
    int id;
    int left;
    int right;
};

void assignByDfsOrder(int v, int& coord, const vector<vector<int>>& children, vector<Circle>& circles) {
    int left = coord;
    coord += 2;

    for (int child : children[v]) {
        assignByDfsOrder(child, coord, children, circles);
    }

    int right = coord;
    coord += 2;

    if (v != 0) {
        circles[v - 1] = {v, left, right};
    }
}

vector<Circle> makeDisjoint(int n) {
    vector<Circle> circles;
    circles.reserve(n);

    int cursor = rnd.next(-100, -20);
    for (int id = 1; id <= n; ++id) {
        int radius = rnd.next(1, 5);
        int left = cursor;
        int right = left + 2 * radius;
        circles.push_back({id, left, right});
        cursor = right + rnd.next(2, 8);
    }
    return circles;
}

vector<Circle> makeChain(int n) {
    vector<Circle> circles;
    circles.reserve(n);

    int center = rnd.next(-20, 20);
    for (int id = 1; id <= n; ++id) {
        int radius = 2 * (n - id + 1);
        circles.push_back({id, center - radius, center + radius});
    }
    return circles;
}

vector<Circle> makeMixedForest(int n) {
    vector<vector<int>> children(n + 1);

    for (int id = 1; id <= n; ++id) {
        int parent = rnd.next(0, id - 1);
        children[parent].push_back(id);
    }

    for (auto& child_list : children) {
        shuffle(child_list.begin(), child_list.end());
    }

    vector<Circle> circles(n);
    int coord = -1000;
    assignByDfsOrder(0, coord, children, circles);
    return circles;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 2);
    int n = rnd.next(2, mode == 2 ? 24 : 14);

    vector<Circle> circles;
    if (mode == 0) {
        circles = makeDisjoint(n);
    } else if (mode == 1) {
        circles = makeChain(n);
    } else {
        circles = makeMixedForest(n);
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    shuffle(order.begin(), order.end());

    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) {
        ++b;
    }

    println(n);
    for (int index : order) {
        const Circle& circle = circles[index];
        int x = (circle.left + circle.right) / 2;
        int r = (circle.right - circle.left) / 2;
        println(circle.id, x, r);
    }
    println(a, b);

    return 0;
}
