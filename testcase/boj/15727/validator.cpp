#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L: distance from Seongwoo to Mingun's house
    inf.readInt(1, 1000000, "L");
    inf.readEoln();

    inf.readEof();
    return 0;
}
