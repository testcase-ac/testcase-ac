#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first gear string: non-empty, length <= 100, chars only '1' or '2'
    string s1 = inf.readLine("[12]{1,100}", "gear1");
    // Read second gear string: same constraints
    string s2 = inf.readLine("[12]{1,100}", "gear2");

    // We must guarantee that the answer (minimal width) exists.
    // For this problem, any two such gear strings always have a valid alignment:
    // aligning them without overlap (side by side) is always valid and yields
    // width = len(s1) + len(s2). So no further global validity check is needed.

    inf.readEof();
}
