#include "testlib.h"
#include <iostream>
#include <set>
#include <utility>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(2, 5) * 2; // N is even, between 4 and 10

    set<pair<int, int>> points;

    while ((int)points.size() < N) {
        int x = rnd.next(1, 9);
        int y = rnd.next(1, 9);
        points.insert({x, y});
    }

    println(N);
    for (auto p : points) {
        println(p.first, p.second);
    }
}
