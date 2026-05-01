#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of segments
    int N = rnd.next(1, 8);
    println(N);
    vector<int> sides = {0, 1, 2, 3}; // 0: left, 1: right, 2: bottom, 3: top
    for (int i = 0; i < N; i++) {
        int s1 = rnd.next(0, 3);
        vector<int> others;
        for (int s : sides) if (s != s1) others.push_back(s);
        int s2 = rnd.any(others);
        auto genPt = [&](int s) {
            int x, y;
            if (s == 0) { // left
                x = rnd.next(-100, -11);
                y = rnd.next(-100, 100);
            } else if (s == 1) { // right
                x = rnd.next(11, 100);
                y = rnd.next(-100, 100);
            } else if (s == 2) { // bottom
                y = rnd.next(-100, -11);
                x = rnd.next(-100, 100);
            } else { // top
                y = rnd.next(11, 100);
                x = rnd.next(-100, 100);
            }
            return make_pair(x, y);
        };
        auto p1 = genPt(s1);
        auto p2 = genPt(s2);
        println(p1.first, p1.second, p2.first, p2.second);
    }
    return 0;
}
