#include "testlib.h"

#include <cerrno>
#include <cstdlib>
#include <string>

using namespace std;

double readProbabilityToken() {
    string token = inf.readToken("[^ ]{1,64}", "t");

    bool canonical = false;
    if (token == "0" || token == "1") {
        canonical = true;
    } else if (token.rfind("0.", 0) == 0 && token.size() > 2) {
        canonical = true;
        for (size_t i = 2; i < token.size(); ++i) {
            canonical = canonical && token[i] >= '0' && token[i] <= '9';
        }
    } else if (token.rfind("1.", 0) == 0 && token.size() > 2) {
        canonical = true;
        for (size_t i = 2; i < token.size(); ++i) {
            canonical = canonical && token[i] == '0';
        }
    }
    ensuref(canonical, "t must be a canonical decimal real in [0, 1], got '%s'",
            token.c_str());

    errno = 0;
    char* end = nullptr;
    double value = strtod(token.c_str(), &end);
    ensuref(errno == 0 && end != token.c_str() && *end == '\0',
            "failed to parse t: '%s'", token.c_str());
    ensuref(0.0 <= value && value <= 1.0, "t out of range: %.17g", value);
    return value;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        int n = inf.readInt(0, 30, "n");
        inf.readSpace();

        if (n == 0) {
            string terminator = inf.readToken("[^ ]{1,64}", "terminator_t");
            ensuref(terminator == "0", "n = 0 is only valid in terminator line '0 0'");
            inf.readEoln();
            break;
        }

        readProbabilityToken();
        inf.readEoln();

        ++cases;
        // CHECK: the statement gives no number-of-lines limit, so cap practical input size.
        ensuref(cases <= 100000, "too many cases: %d", cases);
    }

    inf.readEof();
}
