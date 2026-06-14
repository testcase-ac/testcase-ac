#include "testlib.h"

#include <string>

using namespace std;

namespace {

void readBookNumber(const string& name) {
    string token = inf.readToken("[0-9]{1,4}|[0-9]{1,4}\\.[0-9]+", name.c_str());

    size_t dot = token.find('.');
    string whole = dot == string::npos ? token : token.substr(0, dot);
    string frac = dot == string::npos ? "" : token.substr(dot + 1);

    ensuref(whole == "0" || whole[0] != '0', "%s has a leading zero: %s",
            name.c_str(), token.c_str());

    bool positive = false;
    for (char c : whole) {
        positive = positive || c != '0';
    }
    for (char c : frac) {
        positive = positive || c != '0';
    }
    ensuref(positive, "%s must be greater than 0: %s", name.c_str(), token.c_str());

    ensuref(whole.size() <= 3, "%s must be less than 1000: %s",
            name.c_str(), token.c_str());
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        readBookNumber(format("book_number_%d", i + 1));
    }
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 10000, format("weight_%d", i + 1));
    }
    inf.readEoln();

    inf.readEof();
}
