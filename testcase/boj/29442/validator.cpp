#include "testlib.h"

#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    long long totalStudents = 0;
    for (int i = 1; i <= n; ++i) {
        string row = inf.readToken("[BG]{1,100}", "row");
        inf.readEoln();

        totalStudents += row.size();
        ensuref(totalStudents <= 1000000,
                "total number of students exceeds 1000000 after row %d", i);
    }

    inf.readEof();
}
