#include "testlib.h"

#include <string>

using namespace std;

namespace {

string readSubject(const char* name, bool allowWildcard) {
    string pattern = allowWildcard ? "kor|eng|math|-" : "kor|eng|math";
    return inf.readToken(pattern, name);
}

string readFruit(const char* name, bool allowWildcard) {
    string pattern = allowWildcard ? "apple|pear|orange|-" : "apple|pear|orange";
    return inf.readToken(pattern, name);
}

string readColor(const char* name, bool allowWildcard) {
    string pattern = allowWildcard ? "red|blue|green|-" : "red|blue|green";
    return inf.readToken(pattern, name);
}

void readTriple(bool allowWildcard, const char* prefix) {
    readSubject((string(prefix) + "_subject").c_str(), allowWildcard);
    inf.readSpace();
    readFruit((string(prefix) + "_fruit").c_str(), allowWildcard);
    inf.readSpace();
    readColor((string(prefix) + "_color").c_str(), allowWildcard);
    inf.readEoln();
}

} // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        readTriple(false, "student");
    }

    for (int i = 0; i < m; ++i) {
        readTriple(true, "query");
    }

    inf.readEof();
}
