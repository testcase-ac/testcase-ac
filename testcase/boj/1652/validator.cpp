#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Prepare a regex that matches exactly N characters, each '.' or 'X'
    string row_regex = "[.X]{" + to_string(N) + "," + to_string(N) + "}";

    // Read each of the N rows
    for (int i = 1; i <= N; i++) {
        // Read exactly N non-whitespace characters: '.' or 'X'
        inf.readToken(row_regex.c_str(), "row");
        // Ensure the row ends with a single newline
        inf.readEoln();
    }

    // No extra data allowed
    inf.readEof();
    return 0;
}
