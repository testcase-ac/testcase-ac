#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of people N
    int N = inf.readInt(1, 50, "N");
    inf.readEoln();

    // Read adjacency matrix: N lines, each exactly N characters of 'Y' or 'N'
    vector<string> mat(N);
    for (int i = 0; i < N; i++) {
        // Build regex for exactly N characters, each 'Y' or 'N'
        string regex = "[YN]{" + to_string(N) + "," + to_string(N) + "}";
        // Name each row for clearer error messages
        string name = "row_" + to_string(i);
        mat[i] = inf.readLine(regex.c_str(), name.c_str());
    }

    // Validate no self-friendship and symmetry of the friendship matrix
    for (int i = 0; i < N; i++) {
        // Diagonal must be 'N'
        ensuref(mat[i][i] == 'N',
                "Self-friendship detected at index %d: mat[%d][%d] = '%c'",
                i, i, i, mat[i][i]);
        for (int j = i + 1; j < N; j++) {
            // mat[i][j] must equal mat[j][i]
            ensuref(mat[i][j] == mat[j][i],
                    "Friendship asymmetry detected between %d and %d: mat[%d][%d] = '%c', mat[%d][%d] = '%c'",
                    i, j,
                    i, j, mat[i][j],
                    j, i, mat[j][i]);
        }
    }

    inf.readEof();
    return 0;
}
