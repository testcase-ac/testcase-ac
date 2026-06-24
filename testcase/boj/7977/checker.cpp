#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int charIndex(char c) {
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

int lcsLength(const string& a, const string& b) {
    const int n = (int)b.size();
    const int words = (n + 63) / 64;
    vector<vector<unsigned long long>> mask(4, vector<unsigned long long>(words, 0));

    for (int i = 0; i < n; ++i) {
        mask[charIndex(b[i])][i / 64] |= 1ULL << (i % 64);
    }

    vector<unsigned long long> state(words, 0);
    const unsigned long long lastMask =
        n % 64 == 0 ? ~0ULL : ((1ULL << (n % 64)) - 1ULL);

    for (char c : a) {
        const vector<unsigned long long>& currentMask = mask[charIndex(c)];
        unsigned long long subtractBorrow = 0;
        unsigned long long shiftCarry = 1;

        for (int i = 0; i < words; ++i) {
            unsigned long long x = state[i] | currentMask[i];
            unsigned long long shifted = (state[i] << 1) | shiftCarry;
            shiftCarry = state[i] >> 63;

            unsigned long long subtrahend = shifted + subtractBorrow;
            subtractBorrow = (subtrahend < shifted) || (x < subtrahend);
            unsigned long long diff = x - subtrahend;
            state[i] = x & (x ^ diff);
        }
        state.back() &= lastMask;
    }

    int result = 0;
    for (unsigned long long word : state) {
        result += __builtin_popcountll(word);
    }
    return result;
}

struct Answer {
    int claimed;
    string dna;
    int actual;
};

Answer readAnswer(InStream& stream, int n, const string& original) {
    int claimed = stream.readInt(0, n, "similarity");
    stream.readEoln();

    string dna = stream.readToken("[ACGT]+", "dna");
    if ((int)dna.size() != n) {
        stream.quitf(_wa, "dna length is %d, expected %d", (int)dna.size(), n);
    }
    stream.readEoln();
    stream.readEof();

    int actual = lcsLength(original, dna);
    if (claimed != actual) {
        stream.quitf(_wa, "claimed similarity is %d, but actual LCS is %d", claimed, actual);
    }
    return {claimed, dna, actual};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();
    string original = inf.readToken("[ACGT]+", "dna");
    inf.readEoln();
    inf.readEof();

    if ((int)original.size() != n) {
        quitf(_fail, "input dna length is %d, expected %d", (int)original.size(), n);
    }

    Answer jury = readAnswer(ans, n, original);
    Answer participant = readAnswer(ouf, n, original);

    if (participant.actual > jury.actual) {
        quitf(_wa,
              "jury has better similarity: jury=%d participant=%d",
              jury.actual,
              participant.actual);
    }
    if (participant.actual < jury.actual) {
        quitf(_fail,
              "participant found better similarity: jury=%d participant=%d",
              jury.actual,
              participant.actual);
    }

    quitf(_ok, "similarity=%d", participant.actual);
}
