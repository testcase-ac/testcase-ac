#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for biases
    vector<int> tParams = {-2, -1, 0, 1, 2};
    vector<int> maxOptions = {5, 10, 20};

    // Sample biased dimensions N and M in [1,10]
    int tN = rnd.any(tParams);
    int tM = rnd.any(tParams);
    int N = rnd.wnext(10, tN) + 1;
    int M = rnd.wnext(10, tM) + 1;

    // Choose a maximum value for entries
    int maxVal = rnd.any(maxOptions);

    // Prepare 4 color matrices: 0=red,1=blue,2=green,3=yellow
    vector<vector<vector<int>>> A(4, vector<vector<int>>(N, vector<int>(M)));
    for (int c = 0; c < 4; c++) {
        int tC = rnd.any(tParams);
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                // Generate with weighted bias, values in [0..maxVal]
                A[c][i][j] = rnd.wnext(maxVal + 1, tC);
            }
        }
    }

    // Output
    println(N, M);
    for (int c = 0; c < 4; c++) {
        for (int i = 0; i < N; i++) {
            println(A[c][i]);
        }
    }
    return 0;
}
