#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read first word line: non-empty, length <= 2000, arbitrary characters allowed
    string s1 = inf.readLine("[^]+", "first_word");
    ensuref(!s1.empty(), "first word must be non-empty");
    ensuref((int)s1.size() <= 2000, "first word length must not exceed 2000, got %d", (int)s1.size());

    // Read second word line: non-empty, length <= 2000, arbitrary characters allowed
    string s2 = inf.readLine("[^]+", "second_word");
    ensuref(!s2.empty(), "second word must be non-empty");
    ensuref((int)s2.size() <= 2000, "second word length must not exceed 2000, got %d", (int)s2.size());

    // No extra lines or spaces allowed
    inf.readEof();
}
