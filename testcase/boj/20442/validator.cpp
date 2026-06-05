#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string s = inf.readLine("[KR]+", "s");
    ensuref(s.size() <= 3000000, "s length must be at most 3000000, got %d",
            static_cast<int>(s.size()));
    inf.readEof();
}
