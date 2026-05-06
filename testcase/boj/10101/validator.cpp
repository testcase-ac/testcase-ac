#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read three angles, each strictly between 0 and 180.
    int a1 = inf.readInt(1, 179, "angle1");
    inf.readEoln();
    int a2 = inf.readInt(1, 179, "angle2");
    inf.readEoln();
    int a3 = inf.readInt(1, 179, "angle3");
    inf.readEoln();

    // No extra data allowed
    inf.readEof();
    return 0;
}
