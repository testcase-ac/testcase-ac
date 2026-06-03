#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    string skewer = inf.readToken("[st]{2,100}", "skewer");
    ensuref((int)skewer.size() == n,
            "skewer length must equal N: N=%d, length=%d", n,
            (int)skewer.size());
    inf.readEoln();

    bool hasBalancedSuffix = false;
    int sausages = 0;
    int riceCakes = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (skewer[i] == 's') {
            ++sausages;
        } else {
            ++riceCakes;
        }
        if (sausages == riceCakes) {
            hasBalancedSuffix = true;
        }
    }
    ensuref(hasBalancedSuffix,
            "input must allow a nonempty balanced skewer after removing a prefix");

    inf.readEof();
}
