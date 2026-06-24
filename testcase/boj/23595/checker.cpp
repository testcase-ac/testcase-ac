#include "testlib.h"

#include <vector>

using namespace std;

const long long LIMIT = 1000000;

struct Answer {
    vector<vector<long long>> coeffs;
};

Answer readAnswer(InStream& stream, const vector<long long>& roots) {
    Answer answer;
    answer.coeffs.resize(roots.size());

    for (int i = 0; i < int(roots.size()); ++i) {
        long long a = stream.readLong(-LIMIT, LIMIT, format("A[%d]", i + 1));
        long long b = stream.readLong(-LIMIT, LIMIT, format("B[%d]", i + 1));
        long long c = stream.readLong(-LIMIT, LIMIT, format("C[%d]", i + 1));

        if (a == 0 || b == 0 || c == 0) {
            stream.quitf(_wa, "case %d has a zero coefficient", i + 1);
        }

        long long y = roots[i];
        __int128 value = (__int128)a * y * y + (__int128)b * y + c;
        if (value != 0) {
            stream.quitf(_wa,
                         "case %d does not satisfy equation at Y=%lld: A=%lld B=%lld C=%lld",
                         i + 1, y, a, b, c);
        }

        answer.coeffs[i] = {a, b, c};
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d cases", int(roots.size()));
    }
    return answer;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    vector<long long> roots(t);
    for (int i = 0; i < t; ++i) {
        roots[i] = inf.readLong();
    }

    Answer jury = readAnswer(ans, roots);
    Answer participant = readAnswer(ouf, roots);
    if (participant.coeffs.size() != jury.coeffs.size()) {
        quitf(_fail, "internal case count mismatch");
    }

    quitf(_ok, "%d valid equations", t);
}
