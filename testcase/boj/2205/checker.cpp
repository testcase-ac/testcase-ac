#include "testlib.h"

#include <vector>

using namespace std;

struct Answer {
    vector<int> tinForLead;
};

bool isPowerOfTwo(int value) {
    return value > 0 && (value & (value - 1)) == 0;
}

Answer readAnswer(InStream& stream, int n) {
    Answer result;
    result.tinForLead.resize(n + 1);
    vector<int> used(n + 1, 0);

    for (int lead = 1; lead <= n; ++lead) {
        int tin = stream.readInt(1, n, format("tin mass for lead %d", lead).c_str());
        if (used[tin]) {
            stream.quitf(_wa, "tin mass %d is used more than once", tin);
        }
        if (!isPowerOfTwo(lead + tin)) {
            stream.quitf(_wa, "lead %d plus tin %d gives %d, which is not a power of two",
                         lead, tin, lead + tin);
        }
        used[tin] = 1;
        result.tinForLead[lead] = tin;
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d tin masses", n);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1, 10000, "n");

    readAnswer(ans, n);
    readAnswer(ouf, n);

    quitf(_ok, "valid assignment for n=%d", n);
}
