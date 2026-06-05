#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    vector<int> breeds = inf.readInts(n, 1, 100, "breed_id");
    (void)breeds;
    inf.readEoln();

    inf.readEof();
}
