#include "testlib.h"
#include <string>

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    std::string ratio = inf.readToken("[1-9][0-9]*:[1-9][0-9]*", "n:m");

    size_t colon = ratio.find(':');
    std::string nText = ratio.substr(0, colon);
    std::string mText = ratio.substr(colon + 1);
    ensuref(nText.size() <= 9, "n must be at most 100000000");
    ensuref(mText.size() <= 9, "m must be at most 100000000");

    long long n = std::stoll(nText);
    long long m = std::stoll(mText);
    ensuref(n <= 100000000LL, "n must be at most 100000000");
    ensuref(m <= 100000000LL, "m must be at most 100000000");

    inf.readEoln();
    inf.readEof();
}
