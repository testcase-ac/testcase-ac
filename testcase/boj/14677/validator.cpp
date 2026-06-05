#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    string medicines = inf.readToken("[BLD]{3,1500}", "medicines");
    ensuref((int)medicines.size() == 3 * n,
            "medicine string length must be 3N: N=%d, length=%d",
            n,
            (int)medicines.size());
    inf.readEoln();

    inf.readEof();
}
