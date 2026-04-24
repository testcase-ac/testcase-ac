#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the tree level N: 1 ≤ N ≤ 15
    inf.readInt(1, 15, "N");
    inf.readEoln();  // Exactly one newline after the input line
    inf.readEof();   // No extra content

    return 0;
}
