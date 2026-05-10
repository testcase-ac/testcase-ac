#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of card bundles
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each bundle size
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 1000, "card_size");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
