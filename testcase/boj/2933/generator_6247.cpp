#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Cave dimensions
    int R = rnd.next(4, 10);
    int C = rnd.next(3, 10);

    // Initialize empty cave
    vector<string> cave(R, string(C, '.'));

    // Choose one column to fill with a single connected cluster
    int col = rnd.next(0, C - 1);
    int h = rnd.next(1, R);  // cluster height
    for (int i = R - h; i < R; i++) {
        cave[i][col] = 'x';
    }

    // Number of throws
    int N = rnd.next(1, min(R, 7));
    vector<int> throws;
    for (int i = 0; i < N; i++) {
        // Can throw at any height; may or may not hit the cluster
        throws.push_back(rnd.next(1, R));
    }

    // Output
    println(R, C);
    for (int i = 0; i < R; i++) {
        println(cave[i]);
    }
    println(N);
    println(throws);

    return 0;
}
