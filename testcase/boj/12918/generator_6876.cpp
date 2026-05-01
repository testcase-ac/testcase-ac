#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    int P = rnd.next(0, 10);          // number of symmetric pairs
    int Q = rnd.next(0, 5);           // number of axis points
    if (P == 0 && Q == 0) P = 1;      // ensure at least one point

    vector<pair<int,int>> pts;
    set<pair<int,int>> used;

    // Generate P symmetric pairs with perturbations
    for (int i = 0; i < P; i++) {
        // target center
        int t = rnd.next(-2, 2);
        int x0 = rnd.wnext(10, t) + 1;   // biasable within [1,10]
        int y0 = rnd.next(-10, 10);

        // generate two perturbed points
        pair<int,int> a, b;
        do {
            int dx = rnd.next(-3, 3), dy = rnd.next(-3, 3);
            a = { x0 + dx, y0 + dy };
        } while (used.count(a));
        used.insert(a);
        pts.push_back(a);

        do {
            int dx = rnd.next(-3, 3), dy = rnd.next(-3, 3);
            b = { -x0 + dx, y0 + dy };
        } while (used.count(b));
        used.insert(b);
        pts.push_back(b);
    }

    // Generate Q axis-biased points (target x=0)
    for (int i = 0; i < Q; i++) {
        int y0 = rnd.next(-10, 10);
        pair<int,int> p;
        do {
            int dx = rnd.next(-3, 3), dy = rnd.next(-3, 3);
            p = { dx, y0 + dy };
        } while (used.count(p));
        used.insert(p);
        pts.push_back(p);
    }

    // Shuffle final order
    shuffle(pts.begin(), pts.end());

    // Output
    int N = (int)pts.size();
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }
    return 0;
}
