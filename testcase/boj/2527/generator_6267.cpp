#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    vector<vector<int>> cases;

    // 1) Proper rectangle overlap (code 'a')
    {
        int x1 = rnd.next(1, 500), y1 = rnd.next(1, 500);
        int w1 = rnd.next(5, 20), h1 = rnd.next(5, 20);
        int p1 = x1 + w1, q1 = y1 + h1;
        int x2 = rnd.next(x1 + 1, p1 - 1);
        int p2 = rnd.next(p1 + 1, p1 + rnd.next(1, 20));
        int y2 = rnd.next(y1 + 1, q1 - 1);
        int q2 = rnd.next(q1 + 1, q1 + rnd.next(1, 20));
        cases.push_back({x1, y1, p1, q1, x2, y2, p2, q2});
    }

    // 2) Segment overlap (edge) (code 'b')
    {
        int x1 = rnd.next(1, 500), y1 = rnd.next(1, 500);
        int w1 = rnd.next(5, 20), h1 = rnd.next(5, 20);
        int p1 = x1 + w1, q1 = y1 + h1;
        int x2min = max(1, x1 - 10), x2max = p1 - 1;
        int x2 = rnd.next(x2min, x2max);
        int p2low = x2 + 1;
        int p2 = rnd.next(p2low, p2low + rnd.next(1, 20));
        int y2 = q1;
        int q2 = y2 + rnd.next(1, 20);
        cases.push_back({x1, y1, p1, q1, x2, y2, p2, q2});
    }

    // 3) Point overlap (corner) (code 'c')
    {
        int x1 = rnd.next(1, 500), y1 = rnd.next(1, 500);
        int w1 = rnd.next(5, 20), h1 = rnd.next(5, 20);
        int p1 = x1 + w1, q1 = y1 + h1;
        int x2 = p1, y2 = q1;
        int p2 = x2 + rnd.next(1, 20), q2 = y2 + rnd.next(1, 20);
        cases.push_back({x1, y1, p1, q1, x2, y2, p2, q2});
    }

    // 4) No overlap (code 'd')
    {
        int x1 = rnd.next(1, 500), y1 = rnd.next(1, 500);
        int w1 = rnd.next(5, 20), h1 = rnd.next(5, 20);
        int p1 = x1 + w1, q1 = y1 + h1;
        int x2 = p1 + rnd.next(1, 20);
        int p2 = x2 + rnd.next(1, 20);
        int y2 = rnd.next(1, 500);
        int q2 = y2 + rnd.next(1, 20);
        cases.push_back({x1, y1, p1, q1, x2, y2, p2, q2});
    }

    // Randomize order of the four cases
    shuffle(cases.begin(), cases.end());

    // Output: 4 lines, each with 8 integers
    for (auto &v : cases)
        println(v);

    return 0;
}
