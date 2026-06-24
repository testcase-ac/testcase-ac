#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

int n;

struct Answer {
    cpp_int value;
};

Answer readAnswer(InStream& stream) {
    vector<int> used(n + 1, 0);
    cpp_int value = 1;

    for (int i = 1; i <= n; ++i) {
        int x = stream.readInt(1, n, format("p[%d]", i).c_str());
        if (used[x]) {
            stream.quitf(_wa, "p[%d]=%d is repeated", i, x);
        }
        used[x] = 1;

        if (i % 2 == 1) {
            value *= x;
        } else {
            value += x;
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }
    return {value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(1, 100, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa, "jury has better value");
    }
    if (participant.value > jury.value) {
        quitf(_fail, "participant has better value than jury");
    }
    quitf(_ok, "optimal value matched");
}
