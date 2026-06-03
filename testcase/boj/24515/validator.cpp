#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        string row = inf.readLine("[A-Z.]{2,1000}", "row");
        ensuref((int)row.size() == n, "row %d has length %d, expected %d", i + 1, (int)row.size(), n);

        for (int j = 0; j < n; ++j) {
            bool isEndpoint = (i == 0 && j == 0) || (i == n - 1 && j == n - 1);
            if (isEndpoint) {
                ensuref(row[j] == '.', "endpoint (%d, %d) must be '.'", i + 1, j + 1);
            } else {
                ensuref('A' <= row[j] && row[j] <= 'Z', "cell (%d, %d) must be an uppercase letter", i + 1, j + 1);
            }
        }
    }

    inf.readEof();
}
