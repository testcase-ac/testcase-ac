#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of license plates
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    // Each of the next N lines must be in the format LLL-DDDD
    // where L is [A-Z] and D is [0-9], exactly 3 letters, a dash, and 4 digits.
    for (int i = 0; i < N; i++) {
        // This reads the entire line (excluding the EOL) and checks the regex
        inf.readLine("[A-Z]{3}-[0-9]{4}", "plate");
    }

    // No extra content after the N lines
    inf.readEof();
    return 0;
}
