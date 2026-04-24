#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n: number of coins
    int n = inf.readInt(3, 10000, "n");
    inf.readEoln();

    // S: initial state string of length n, only 'o' and 'x'
    string S = inf.readLine("[ox]+", "S");
    ensuref((int)S.size() == n,
            "Length of S is %d but expected %d", (int)S.size(), n);
    // (Regex "[ox]+" ensures every character is 'o' or 'x' and length>=1)

    // T: target state string of length n, only 'o' and 'x'
    string T = inf.readLine("[ox]+", "T");
    ensuref((int)T.size() == n,
            "Length of T is %d but expected %d", (int)T.size(), n);

    // i and j: selected coin positions, with 0 <= i < j <= n-1
    int i = inf.readInt(0, n - 1, "i");
    inf.readSpace();
    int j = inf.readInt(0, n - 1, "j");
    inf.readEoln();
    ensuref(i < j,
            "Index constraint violated: i = %d is not less than j = %d", i, j);

    inf.readEof();
    return 0;
}
