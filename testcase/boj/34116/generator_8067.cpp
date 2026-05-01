#include "testlib.h"
#include <set>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of points N between 2 and 12, skewed towards smaller values
    int N = rnd.wnext(11, -2) + 2;
    // Choose a pattern type for diversity
    int type = rnd.next(0, 3);
    set<pair<int,int>> pts;
    // Generate unique points according to the selected pattern
    while ((int)pts.size() < N) {
        int x, y;
        switch (type) {
            case 0:
                // Uniform random in box [-20,20]
                x = rnd.next(-20, 20);
                y = rnd.next(-20, 20);
                break;
            case 1:
                // All points on a horizontal line y = const
                y = rnd.next(-10, 10);
                x = rnd.next(-20, 20);
                break;
            case 2: {
                // All points on a diagonal line y = x + d
                int d = rnd.next(-10, 10);
                x = rnd.next(-20, 20);
                y = x + d;
                break;
            }
            case 3: {
                // Two clusters around random centers
                int cx1 = rnd.next(-15, 15), cy1 = rnd.next(-15, 15);
                int cx2 = rnd.next(-15, 15), cy2 = rnd.next(-15, 15);
                if (rnd.next(0,1) == 0) {
                    x = cx1 + rnd.next(-3,3);
                    y = cy1 + rnd.next(-3,3);
                } else {
                    x = cx2 + rnd.next(-3,3);
                    y = cy2 + rnd.next(-3,3);
                }
                break;
            }
        }
        pts.emplace(x, y);
    }
    // Shuffle for random order
    vector<pair<int,int>> v(pts.begin(), pts.end());
    shuffle(v.begin(), v.end());
    // Output
    println(N);
    for (auto &p : v) {
        println(p.first, p.second);
    }
    return 0;
}
