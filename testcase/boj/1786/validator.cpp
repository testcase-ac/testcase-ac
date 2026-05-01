#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read text T: only uppercase, lowercase letters and spaces, length 1 to 1e6
    string T = inf.readLine("[A-Za-z\\ ]{1,1000000}", "T");
    int n = (int)T.size();
    ensuref(n >= 1 && n <= 1000000, "Length of T is %d, but should be in [1,1000000]", n);

    // Read pattern P: only uppercase, lowercase letters and spaces, length 1 to 1e6
    string P = inf.readLine("[A-Za-z\\ ]{1,1000000}", "P");
    int m = (int)P.size();
    ensuref(m >= 1 && m <= 1000000, "Length of P is %d, but should be in [1,1000000]", m);

    // No other global constraints (n < m is allowed; matches will be zero)
    inf.readEof();
    return 0;
}
