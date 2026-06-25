#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 11, "N");
    inf.readEoln();

    int roomCount = (1 << n) - 1;
    vector<long long> a = inf.readLongs(roomCount, -1000000000LL, 1000000000LL, "a_i");
    (void)a;
    inf.readEoln();

    inf.readEof();
}
