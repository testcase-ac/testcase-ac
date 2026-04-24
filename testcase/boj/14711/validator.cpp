#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    // Read the first row string of length N, composed only of '#' and '.'
    string pattern = "[#\\.]{"+ to_string(N) +","+ to_string(N) +"}";
    string S = inf.readLine(pattern.c_str(), "S");

    // No extra data
    inf.readEof();
    return 0;
}
