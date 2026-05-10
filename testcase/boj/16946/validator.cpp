#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // Prepare regex for each row: exactly M characters, each '0' or '1'
    string pattern = "[01]{" + to_string(M) + "," + to_string(M) + "}";

    // Read the grid rows
    for (int i = 0; i < N; i++) {
        inf.readLine(pattern, ("row_" + to_string(i)).c_str());
    }

    // No extra content
    inf.readEof();
    return 0;
}
