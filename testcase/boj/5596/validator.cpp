#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: 4 integers (민국이's scores)
    // We don't have explicit bounds in the statement, so allow a wide int range.
    const int MIN_SCORE = -1000000000;
    const int MAX_SCORE =  1000000000;
    vector<int> a = inf.readInts(4, MIN_SCORE, MAX_SCORE, "min_guk_score");
    inf.readEoln();

    // Second line: 4 integers (만세's scores)
    vector<int> b = inf.readInts(4, MIN_SCORE, MAX_SCORE, "man_se_score");
    inf.readEoln();

    // Entire file must end immediately
    inf.readEof();

    return 0;
}
