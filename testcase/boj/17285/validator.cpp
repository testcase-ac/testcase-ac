#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string t = inf.readLine("[^]{10,100}", "T");
    for (int i = 0; i < int(t.size()); ++i) {
        unsigned char ch = static_cast<unsigned char>(t[i]);
        ensuref(32 <= ch && ch <= 126, "T[%d] is not printable ASCII: %d", i, int(ch));
    }
    inf.readEof();
}
