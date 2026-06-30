#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <set>
#include <string>
#include <tuple>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

int k, n;

cpp_int parsePositive(InStream& stream, const char* name) {
    string token = stream.readToken("[0-9]+", name);
    if (token.size() > 100) {
        stream.quitf(_wa, "%s has %d digits, expected at most 100", name, int(token.size()));
    }
    if (token.size() > 1 && token[0] == '0') {
        stream.quitf(_wa, "%s has a leading zero", name);
    }
    if (token == "0") {
        stream.quitf(_wa, "%s must be positive", name);
    }

    cpp_int value = 0;
    for (char ch : token) {
        value *= 10;
        value += ch - '0';
    }
    return value;
}

struct Triple {
    cpp_int a;
    cpp_int b;
    cpp_int c;
    string key;
};

vector<Triple> readAns(InStream& stream) {
    vector<Triple> triples;
    set<string> seen;

    for (int i = 0; i < n; ++i) {
        cpp_int a = parsePositive(stream, format("a[%d]", i + 1).c_str());
        cpp_int b = parsePositive(stream, format("b[%d]", i + 1).c_str());
        cpp_int c = parsePositive(stream, format("c[%d]", i + 1).c_str());

        cpp_int lhs = a * a + b * b + c * c;
        cpp_int rhs = cpp_int(k) * (a * b + b * c + c * a) + 1;
        if (lhs != rhs) {
            stream.quitf(_wa, "triple %d does not satisfy the equation", i + 1);
        }

        string key = a.str() + "," + b.str() + "," + c.str();
        if (seen.count(key)) {
            stream.quitf(_wa, "duplicate triple at position %d", i + 1);
        }
        seen.insert(key);
        triples.push_back({a, b, c, key});
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d triples", n);
    }
    return triples;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    k = inf.readInt();
    n = inf.readInt();

    readAns(ans);
    readAns(ouf);

    quitf(_ok, "all %d triples are valid", n);
}
