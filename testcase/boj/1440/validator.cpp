#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // The input is a single line in the format DD:DD:DD, always 8 characters.
    string s = inf.readLine("[0-9]{2}:[0-9]{2}:[0-9]{2}", "time");
    ensuref(s.size() == 8, "Input line must be exactly 8 characters, got %zu", s.size());
    ensuref(s[2] == ':' && s[5] == ':', "Colons must be at positions 2 and 5");

    inf.readEof();
}
