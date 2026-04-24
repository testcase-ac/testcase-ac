#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // There must be exactly 5 agent code names, one per line.
    // Each code name: 1 to 10 characters, only uppercase letters, digits, or dash '-'.
    for (int i = 1; i <= 5; i++) {
        // Place dash first in the character class to avoid range syntax.
        inf.readLine("[-A-Z0-9]{1,10}", "agent_name");
    }

    // No extra characters or lines after the fifth name.
    inf.readEof();
    return 0;
}
