#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // CHECK: The Korean input text names X singular, but N, the English variant,
    // and the official sample define exactly N integers on the second line.
    vector<long long> X = inf.readLongs(N, 1LL, 1000000000000000000LL, "X_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
