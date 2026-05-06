#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Allowed color names
    const string colors = "black|brown|red|orange|yellow|green|blue|violet|grey|white";

    // Read exactly three lines, each must be one of the allowed colors
    inf.readLine(colors, "color1");
    inf.readLine(colors, "color2");
    inf.readLine(colors, "color3");

    // No extra input
    inf.readEof();
    return 0;
}
