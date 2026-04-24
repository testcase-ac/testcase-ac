#include "testlib.h"
#include <set>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 5), M = rnd.next(1, 5);
    println(N, M);
    vector<int> positions;
    for(int i = 2; i <= 99; i++) {
        positions.push_back(i);
    }
    if(rnd.next() < 0.5) {
        sort(positions.begin(), positions.end(), [](int a, int b) {
            return (a % 10) > (b % 10);
        });
        shuffle(positions.end() - 9, positions.end());
        shuffle(positions.begin(), positions.end() - 9);
    } else {
        shuffle(positions.begin(), positions.end());
    }

    // Generate ladders
    for(int i = 0; i < N; i++) {
        int x, y;
        x = positions.back();
        positions.pop_back();
        y = positions.back();
        positions.pop_back();
        if(x > y) {
            swap(x, y);
        }
        println(x, y);
    }
    // Generate snakes
    for(int i = 0; i < M; i++) {
        int u, v;
        u = positions.back();
        positions.pop_back();
        v = positions.back();
        positions.pop_back();
        if(u < v) {
            swap(u, v);
        }
        println(u, v);
    }
}
