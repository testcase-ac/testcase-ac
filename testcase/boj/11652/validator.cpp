#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cards
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Value bounds: [-2^62, 2^62]
    const long long MINV = -(1LL << 62);
    const long long MAXV =  (1LL << 62);

    // Read each card value on its own line
    for (int i = 0; i < N; i++) {
        inf.readLong(MINV, MAXV, "card_value");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
