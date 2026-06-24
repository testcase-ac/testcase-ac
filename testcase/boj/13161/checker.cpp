#include "testlib.h"

#include <sstream>
#include <string>
#include <vector>

using namespace std;

int n;
vector<int> requiredSide;
vector<vector<int>> sadness;

struct Answer {
    long long value;
};

vector<int> readGroupLine(InStream& stream, int side) {
    string line = stream.readLine();
    istringstream input(line);
    string token;
    vector<int> group;

    while (input >> token) {
        size_t parsed = 0;
        int person = 0;
        try {
            person = stoi(token, &parsed);
        } catch (...) {
            stream.quitf(_wa, "group %d contains non-integer token '%s'", side, token.c_str());
        }
        if (parsed != token.size()) {
            stream.quitf(_wa, "group %d contains malformed token '%s'", side, token.c_str());
        }
        if (person < 1 || person > n) {
            stream.quitf(_wa, "group %d member %d is outside [1, %d]", side, person, n);
        }
        group.push_back(person);
    }

    return group;
}

Answer readAnswer(InStream& stream) {
    long long claimed = stream.readLong(0, 1'000'000'000LL, "sadness sum");
    stream.readEoln();

    vector<int> sideOf(n + 1, 0);
    for (int side = 1; side <= 2; ++side) {
        vector<int> group = readGroupLine(stream, side);
        for (int person : group) {
            if (sideOf[person] != 0) {
                stream.quitf(_wa, "person %d appears more than once", person);
            }
            sideOf[person] = side;
        }
    }
    stream.readEof();

    for (int person = 1; person <= n; ++person) {
        if (sideOf[person] == 0) {
            stream.quitf(_wa, "person %d is missing", person);
        }
        if (requiredSide[person] != 0 && sideOf[person] != requiredSide[person]) {
            stream.quitf(_wa,
                         "person %d must be in group %d but is in group %d",
                         person,
                         requiredSide[person],
                         sideOf[person]);
        }
    }

    long long actual = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (sideOf[i] != sideOf[j]) {
                actual += sadness[i][j];
            }
        }
    }

    if (claimed != actual) {
        stream.quitf(_wa, "claimed sadness sum is %lld but partition has %lld", claimed, actual);
    }

    return {claimed};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    requiredSide.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        requiredSide[i] = inf.readInt();
    }

    sadness.assign(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            sadness[i][j] = inf.readInt();
        }
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_fail,
              "participant found better answer: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_wa,
              "jury has better answer: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }

    quitf(_ok, "answer=%lld", participant.value);
}
