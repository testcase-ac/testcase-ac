#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int T = rnd.next(1, 100);
    vector<int> edges;
    edges.reserve(T);

    if (mode == 0) {
        T = rnd.next(1, 12);
        for (int i = 0; i < T; ++i) {
            edges.push_back(rnd.next(1, 20));
        }
    } else if (mode == 1) {
        T = rnd.next(8, 30);
        int start = rnd.next(1, 5000 - T + 1);
        for (int i = 0; i < T; ++i) {
            edges.push_back(start + i);
        }
    } else if (mode == 2) {
        T = rnd.next(10, 60);
        vector<int> interesting = {1, 2, 3, 4, 5, 10, 20, 50, 100, 4990, 4999, 5000};
        for (int i = 0; i < T; ++i) {
            edges.push_back(rnd.any(interesting));
        }
    } else if (mode == 3) {
        T = rnd.next(20, 100);
        int lo = rnd.next(1, 4500);
        int hi = rnd.next(lo, 5000);
        for (int i = 0; i < T; ++i) {
            edges.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 4) {
        T = 100;
        for (int i = 0; i < T; ++i) {
            edges.push_back(rnd.next(1, 5000));
        }
    } else {
        T = rnd.next(1, 100);
        for (int i = 0; i < T; ++i) {
            if (rnd.next(0, 3) == 0) {
                edges.push_back(rnd.next(1, 15));
            } else if (rnd.next(0, 2) == 0) {
                edges.push_back(rnd.next(4980, 5000));
            } else {
                edges.push_back(rnd.next(1, 5000));
            }
        }
    }

    shuffle(edges.begin(), edges.end());

    println(T);
    for (int edge : edges) {
        println(edge);
    }

    return 0;
}
