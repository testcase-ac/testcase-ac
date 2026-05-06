#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(8, 99999, "N");
    inf.readEoln();

    const set<int> allowed = {8, 26, 213, 2012, 99991, 99999};
    ensuref(allowed.count(n), "N must be one of 8, 26, 213, 2012, 99991, 99999, got %d", n);

    inf.readEof();
    return 0;
}
