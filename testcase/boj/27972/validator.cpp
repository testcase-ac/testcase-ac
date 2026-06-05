#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 500000, "M");
    inf.readEoln();

    vector<long long> p = inf.readLongs(m, 1LL, 1000000000LL, "p_i");
    inf.readEoln();

    inf.readEof();
}
