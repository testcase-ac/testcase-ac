#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int studentCount = 12;
    vector<vector<int>> time(studentCount, vector<int>(studentCount));

    for (int i = 0; i < studentCount; ++i) {
        for (int j = 0; j < studentCount; ++j) {
            if (j > 0) {
                inf.readSpace();
            }

            int lowerBound = (i == j) ? 0 : 1;
            int upperBound = (i == j) ? 0 : 1000;
            time[i][j] = inf.readInt(lowerBound, upperBound, "time");
        }
        inf.readEoln();
    }

    for (int i = 0; i < studentCount; ++i) {
        for (int j = i + 1; j < studentCount; ++j) {
            ensuref(time[i][j] == time[j][i],
                    "message time must be symmetric for students %d and %d: %d != %d",
                    i + 1,
                    j + 1,
                    time[i][j],
                    time[j][i]);
        }
    }

    inf.readEof();
}
