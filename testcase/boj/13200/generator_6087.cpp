#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases between 1 and 5
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Grid size N between 1 and 7
        int N = rnd.next(1, 7);
        println(N);
        // Output an all-white grid (-2 represents white)
        vector<int> row(N, -2);
        for (int i = 0; i < N; i++) {
            println(row);
        }
    }
    return 0;
}
