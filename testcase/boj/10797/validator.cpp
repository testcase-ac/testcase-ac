#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read the date's last digit: d in [0, 9]
    int d = inf.readInt(0, 9, "date_digit");
    inf.readEoln();

    // Read exactly 5 car last digits, each in [0, 9]
    inf.readInts(5, 0, 9, "car_digit");
    inf.readEoln();

    inf.readEof();
    return 0;
}
