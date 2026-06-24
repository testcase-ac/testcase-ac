#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct Light {
    int row;
    long long col;
    int index;
};

int H, N;
vector<Light> lights;

struct Answer {
    bool possible;
};

string readDecision(InStream& stream) {
    string token = stream.readToken("[A-Za-z]+", "decision");
    for (char& ch : token) {
        ch = char(toupper(ch));
    }
    if (token != "YES" && token != "NO") {
        stream.quitf(_wa, "decision must be YES or NO, found %s", token.c_str());
    }
    return token;
}

Answer readAnswer(InStream& stream) {
    string decision = readDecision(stream);
    if (decision == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    vector<int> move(N);
    vector<int> used(N + 1, 0);
    vector<long long> finalCol(N);
    for (int i = 0; i < N; ++i) {
        move[i] = stream.readInt(1, N, format("B_%d", i + 1).c_str());
        if (used[move[i]]) {
            stream.quitf(_wa, "movement distance %d is repeated", move[i]);
        }
        used[move[i]] = 1;
        finalCol[i] = lights[i].col + move[i];
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after movement distances");
    }

    vector<long long> sortedFinal = finalCol;
    sort(sortedFinal.begin(), sortedFinal.end());
    for (int i = 1; i < N; ++i) {
        if (sortedFinal[i - 1] == sortedFinal[i]) {
            stream.quitf(_wa, "two lights end in column %lld", sortedFinal[i]);
        }
    }

    vector<Light> byRow = lights;
    sort(byRow.begin(), byRow.end(), [](const Light& a, const Light& b) {
        if (a.row != b.row) return a.row < b.row;
        return a.col < b.col;
    });

    for (int i = 1; i < N; ++i) {
        if (byRow[i - 1].row != byRow[i].row) continue;

        int left = byRow[i - 1].index;
        int right = byRow[i].index;
        if (finalCol[left] >= finalCol[right]) {
            stream.quitf(_wa,
                         "lights %d and %d in row %d do not preserve order: final columns %lld and %lld",
                         left + 1,
                         right + 1,
                         byRow[i].row,
                         finalCol[left],
                         finalCol[right]);
        }
    }

    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    H = inf.readInt();
    N = inf.readInt();
    lights.resize(N);
    for (int i = 0; i < N; ++i) {
        lights[i].row = inf.readInt();
        lights[i].col = inf.readLong();
        lights[i].index = i;
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (!jury.possible && participant.possible) {
        quitf(_fail, "participant provided a valid witness while jury says NO");
    }
    if (jury.possible && !participant.possible) {
        quitf(_wa, "jury says YES but participant says NO");
    }

    quitf(_ok, "%s", participant.possible ? "valid assignment" : "NO matches jury");
}
