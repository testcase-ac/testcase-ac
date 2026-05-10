#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N: 1 ≤ N ≤ 1,000,000
    int N = inf.readInt(1, 1000000, "N");
    // Ensure there's exactly one newline after N
    inf.readEoln();
    // No more data
    inf.readEof();

    return 0;
}
