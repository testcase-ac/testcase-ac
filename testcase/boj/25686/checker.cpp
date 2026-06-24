#include "testlib.h"

#include <vector>

using namespace std;

int n;

struct Answer {
    bool impossible;
};

bool anyAligned(const vector<unsigned long long>& a, const vector<unsigned long long>& b, int offset) {
    if (offset < 0) {
        return anyAligned(b, a, -offset);
    }

    const int wordCount = (n + 63) / 64;
    for (int word = 0; word < wordCount; ++word) {
        int start = word * 64 + offset;
        if (start >= n) {
            break;
        }

        int sourceWord = start / 64;
        int bitShift = start % 64;
        unsigned long long chunk = b[sourceWord] >> bitShift;
        if (bitShift != 0 && sourceWord + 1 < wordCount) {
            chunk |= b[sourceWord + 1] << (64 - bitShift);
        }

        int remaining = n - word * 64;
        if (remaining < 64) {
            chunk &= (1ULL << remaining) - 1;
        }

        if ((a[word] & chunk) != 0) {
            return true;
        }
    }
    return false;
}

void setBit(vector<unsigned long long>& bits, int zeroBasedIndex) {
    bits[zeroBasedIndex / 64] |= 1ULL << (zeroBasedIndex % 64);
}

void clearBit(vector<unsigned long long>& bits, int zeroBasedIndex) {
    bits[zeroBasedIndex / 64] &= ~(1ULL << (zeroBasedIndex % 64));
}

bool hasForbiddenTriple(const vector<int>& values) {
    const int wordCount = (n + 63) / 64;
    vector<unsigned long long> left(wordCount, 0), right(wordCount, 0), reversedRight(wordCount, 0);

    for (int value : values) {
        setBit(right, value - 1);
        setBit(reversedRight, n - value);
    }

    for (int index = 0; index < n; ++index) {
        int middle = values[index];
        clearBit(right, middle - 1);
        clearBit(reversedRight, n - middle);

        if (anyAligned(left, reversedRight, n + 1 - 2 * middle)) {
            return true;
        }

        setBit(left, middle - 1);
    }

    return false;
}

Answer readAnswer(InStream& stream) {
    int first = stream.readInt(-1, n, "first output token");
    if (first == -1) {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after -1");
        }
        return {true};
    }
    if (first < 1) {
        stream.quitf(_wa, "first permutation value is %d, expected a value from 1 to %d or -1", first, n);
    }

    vector<int> values(n);
    vector<int> seen(n + 1, 0);
    values[0] = first;
    seen[first] = 1;

    for (int i = 1; i < n; ++i) {
        values[i] = stream.readInt(1, n, format("a[%d]", i + 1).c_str());
        if (seen[values[i]]) {
            stream.quitf(_wa, "value %d appears more than once", values[i]);
        }
        seen[values[i]] = 1;
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after permutation");
    }

    if (hasForbiddenTriple(values)) {
        stream.quitf(_wa, "permutation contains indices i < k < j with a[k] = (a[i] + a[j]) / 2");
    }

    return {false};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 100000, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs claim impossible");
        }
        quitf(_fail, "participant found a valid permutation while jury says impossible");
    }

    if (participant.impossible) {
        quitf(_wa, "participant claims impossible while jury provides a valid permutation");
    }

    quitf(_ok, "valid permutation");
}
