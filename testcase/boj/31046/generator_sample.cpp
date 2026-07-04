#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct Circle {
    int x;
    int y;
    int r;
};

bool canAdd(const vector<Circle>& circles, const Circle& next) {
    for (const Circle& cur : circles) {
        long long dx = next.x - cur.x;
        long long dy = next.y - cur.y;
        long long radiusSum = next.r + cur.r;
        if (dx * dx + dy * dy < radiusSum * radiusSum) {
            return false;
        }
    }
    return true;
}

vector<Circle> makeGridCase(int n) {
    vector<pair<int, int>> cells;
    for (int x = -880; x <= 880; x += 220) {
        for (int y = -880; y <= 880; y += 220) {
            cells.push_back({x, y});
        }
    }
    shuffle(cells.begin(), cells.end());

    vector<Circle> circles;
    for (int i = 0; i < n; ++i) {
        int r = rnd.next(1, 70);
        circles.push_back({cells[i].first, cells[i].second, r});
    }
    return circles;
}

vector<Circle> makeLineCase(int n) {
    vector<Circle> circles;
    int y = rnd.next(-700, 700);
    int x = rnd.next(-950, -850);
    int previousRadius = rnd.next(1, 45);
    circles.push_back({x, y, previousRadius});

    for (int i = 1; i < n; ++i) {
        int r = rnd.next(1, 45);
        int gap = rnd.next(0, 70);
        x += previousRadius + r + gap;
        circles.push_back({x, y + rnd.next(-12, 12), r});
        previousRadius = r;
    }
    return circles;
}

vector<Circle> makeRandomSparseCase(int targetN) {
    vector<Circle> circles;
    for (int attempts = 0; attempts < 8000 && (int)circles.size() < targetN; ++attempts) {
        Circle next{
            rnd.next(-1000, 1000),
            rnd.next(-1000, 1000),
            rnd.next(1, 55),
        };
        if (canAdd(circles, next)) {
            circles.push_back(next);
        }
    }

    if ((int)circles.size() < targetN) {
        return makeGridCase(targetN);
    }
    return circles;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    vector<Circle> circles;

    if (mode == 0) {
        circles.push_back({rnd.next(-1000, 1000), rnd.next(-1000, 1000), rnd.next(1, 100)});
    } else if (mode == 1) {
        circles = makeLineCase(rnd.next(2, 12));
    } else if (mode == 2) {
        circles = makeGridCase(rnd.next(2, 25));
    } else {
        circles = makeRandomSparseCase(rnd.next(2, 25));
    }

    println((int)circles.size());
    for (const Circle& circle : circles) {
        println(circle.x, circle.y, circle.r);
    }

    return 0;
}
