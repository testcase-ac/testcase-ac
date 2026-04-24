#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the single integer N, number of disks
    inf.readInt(1, 20, "N");
    // Ensure end of line after N
    inf.readEoln();
    // No more content
    inf.readEof();
    return 0;
}
