#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Record {
    string robot;
    int block;
};

struct Claim {
    bool possible;
};

int n, m;
vector<Record> records;

string otherRobot(const string& robot) {
    return robot == "A" ? "B" : "A";
}

Claim readClaim(InStream& stream) {
    string verdict = stream.readToken("YES|NO", "verdict");
    if (verdict == "NO") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after NO");
        }
        return {false};
    }

    vector<bool> used(2 * n + 1, false);
    int recordIndex = 0;
    string expectedRobot = "A";
    string previousRobot;
    int previousBlock = -1;

    for (int i = 0; i < 2 * n; ++i) {
        string robot = stream.readToken("A|B", format("move[%d].robot", i + 1).c_str());
        string action = stream.readToken("BLOCK|CHAIN", format("move[%d].action", i + 1).c_str());
        int block = stream.readInt(1, 2 * n, format("move[%d].block", i + 1).c_str());

        if (robot != expectedRobot) {
            stream.quitf(_wa, "move %d is by %s, expected %s", i + 1, robot.c_str(), expectedRobot.c_str());
        }
        if (used[block]) {
            stream.quitf(_wa, "block %d is used more than once", block);
        }
        used[block] = true;

        if (action == "BLOCK") {
            if (recordIndex >= m) {
                stream.quitf(_wa, "extra BLOCK move at move %d", i + 1);
            }
            const Record& expected = records[recordIndex];
            if (robot != expected.robot || block != expected.block) {
                stream.quitf(_wa,
                             "BLOCK record %d is %s BLOCK %d, expected %s BLOCK %d",
                             recordIndex + 1,
                             robot.c_str(),
                             block,
                             expected.robot.c_str(),
                             expected.block);
            }
            ++recordIndex;
        } else {
            if (i == 0) {
                stream.quitf(_wa, "first move cannot be CHAIN");
            }
            if (previousRobot == robot) {
                stream.quitf(_wa, "move %d chains after the same robot", i + 1);
            }
            if (block <= previousBlock) {
                stream.quitf(_wa,
                             "move %d chains block %d on block %d",
                             i + 1,
                             block,
                             previousBlock);
            }
        }

        previousRobot = robot;
        previousBlock = block;
        expectedRobot = otherRobot(expectedRobot);
    }

    if (recordIndex != m) {
        stream.quitf(_wa, "only %d of %d input BLOCK records were used", recordIndex, m);
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after full move log");
    }
    return {true};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    records.resize(m);
    for (int i = 0; i < m; ++i) {
        records[i].robot = inf.readToken();
        inf.readToken();
        records[i].block = inf.readInt();
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.possible) {
        if (!participant.possible) {
            quitf(_wa, "jury has a valid construction but participant answered NO");
        }
        quitf(_ok, "valid construction");
    }

    if (participant.possible) {
        quitf(_fail, "participant found a valid construction but jury answered NO");
    }
    quitf(_ok, "both outputs report NO");
}
