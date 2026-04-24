#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(3, 500, "N");
    inf.readEoln();

    // Read the N x N connection matrix a[i][j] ∈ {0,1}
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            a[i][j] = inf.readInt(0, 1, "connection");
            if (j + 1 < N)
                inf.readSpace();
            else
                inf.readEoln();
        }
    }

    // Validate that each switch (row) is connected to at least one light
    for (int i = 0; i < N; i++) {
        int sum = 0;
        for (int j = 0; j < N; j++)
            sum += a[i][j];
        ensuref(sum >= 1,
                "Switch %d has no lights connected to it (row %d is all zeros)", 
                i + 1, i + 1);
    }

    // Validate that each light (column) is connected to at least one switch
    for (int j = 0; j < N; j++) {
        int sum = 0;
        for (int i = 0; i < N; i++)
            sum += a[i][j];
        ensuref(sum >= 1,
                "Light %d has no switches connected to it (column %d is all zeros)", 
                j + 1, j + 1);
    }

    inf.readEof();
    return 0;
}
