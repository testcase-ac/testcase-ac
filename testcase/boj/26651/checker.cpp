#include "testlib.h"

#include <string>

using namespace std;

long long countGramPanSubstrings(const string& s) {
    long long total = 0;
    int n = int(s.size());

    for (int l = 0; l < n;) {
        int r = l + 1;
        while (r < n && s[r - 1] <= s[r]) {
            ++r;
        }

        bool seen[26] = {};
        int lastA = -1;
        int firstZ = -1;
        for (int i = l; i < r; ++i) {
            int c = s[i] - 'A';
            seen[c] = true;
            if (c == 0) {
                lastA = i;
            }
            if (c == 25 && firstZ == -1) {
                firstZ = i;
            }
        }

        bool hasAll = true;
        for (bool has : seen) {
            hasAll = hasAll && has;
        }
        if (hasAll) {
            total += 1LL * (lastA - l + 1) * (r - firstZ);
        }

        l = r;
    }

    return total;
}

struct Answer {
    string value;
    long long count;
};

Answer readAnswer(InStream& stream) {
    string s = stream.readToken("[A-Z]{1,100000}", "S");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after S");
    }
    return {s, countGramPanSubstrings(s)};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long x = inf.readLong(0LL, 1000000000LL, "X");

    Answer jury = readAnswer(ans);
    if (jury.count != x) {
        quitf(_fail, "jury answer has %lld gram-pan substrings, expected %lld", jury.count, x);
    }

    Answer participant = readAnswer(ouf);
    if (participant.count != jury.count) {
        quitf(_wa,
              "participant answer has %lld gram-pan substrings, expected %lld",
              participant.count,
              jury.count);
    }

    quitf(_ok, "answer has %lld gram-pan substrings", participant.count);
}
