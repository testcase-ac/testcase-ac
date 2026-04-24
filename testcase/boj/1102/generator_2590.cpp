#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of power plants
    int N = rnd.next(2, 10);
    // Restart costs matrix
    vector<vector<int>> cost(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = rnd.next(0, 36);
        }
    }
    // Initial on/off status
    string init;
    init.reserve(N);
    for (int i = 0; i < N; i++) {
        char c = rnd.next(0, 1) ? 'Y' : 'N';
        init.push_back(c);
    }
    // Required number of running plants
    int P = rnd.next(0, N);

    // Emit the test case
    println(N);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d%c", cost[i][j], (j + 1 == N ? '\n' : ' '));
        }
    }
    println(init);
    println(P);
    return 0;
}
