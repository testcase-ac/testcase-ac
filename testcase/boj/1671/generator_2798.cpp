#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of sharks
    int N = rnd.next(1, 10);
    // Maximum attribute value
    int max_attr = rnd.next(1, 20);
    // Weight parameters for diversity in each dimension
    int t1 = rnd.next(-3, 3);
    int t2 = rnd.next(-3, 3);
    int t3 = rnd.next(-3, 3);

    vector<array<int,3>> sharks;
    sharks.reserve(N);
    for (int i = 0; i < N; i++) {
        int size = rnd.wnext(max_attr, t1) + 1;
        int speed = rnd.wnext(max_attr, t2) + 1;
        int intel = rnd.wnext(max_attr, t3) + 1;
        sharks.push_back({size, speed, intel});
    }
    // Shuffle input order for extra diversity
    shuffle(sharks.begin(), sharks.end());

    // Output
    println(N);
    for (auto &sh : sharks) {
        println(sh[0], sh[1], sh[2]);
    }
    return 0;
}
