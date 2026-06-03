#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int k = inf.readInt(1, 20, "K");
    inf.readEoln();

    vector<int> importance = inf.readInts(n, 0, 1000, "importance");
    inf.readEoln();

    inf.readEof();
}
