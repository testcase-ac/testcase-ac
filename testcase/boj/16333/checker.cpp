#include "testlib.h"

#include <vector>

using namespace std;

struct Wish {
    int x;
    int y;
};

struct TestCase {
    int n;
    int m;
    vector<Wish> wishes;
};

vector<TestCase> tests;

void readAnswer(InStream& stream) {
    for (int tc = 0; tc < (int)tests.size(); ++tc) {
        const TestCase& test = tests[tc];

        int minimumGranted = test.m / 4 + 1;
        int k = stream.readInt(minimumGranted, test.m, "K");
        if (!stream.seekEoln()) {
            stream.quitf(_pe, "expected end of line after K in test case %d", tc + 1);
        }

        vector<int> usedWish(test.m + 1, 0);
        vector<int> asSource(test.n + 1, 0);
        vector<int> asTarget(test.n + 1, 0);

        for (int i = 0; i < k; ++i) {
            int id = stream.readInt(1, test.m, format("wish[%d]", i + 1).c_str());
            if (usedWish[id]) {
                stream.quitf(_wa, "wish %d is listed more than once in test case %d", id, tc + 1);
            }
            usedWish[id] = 1;

            const Wish& wish = test.wishes[id - 1];
            asSource[wish.x] = 1;
            asTarget[wish.y] = 1;
        }
        if (!stream.seekEoln()) {
            stream.quitf(_pe,
                         "expected end of line after wish list in test case %d",
                         tc + 1);
        }

        for (int person = 1; person <= test.n; ++person) {
            if (asSource[person] && asTarget[person]) {
                stream.quitf(_wa,
                             "person %d must be both happy and unhappy in test case %d",
                             person,
                             tc + 1);
            }
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_pe, "extra output after the last test case");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    tests.resize(t);
    for (int tc = 0; tc < t; ++tc) {
        int n = inf.readInt();
        int m = inf.readInt();
        tests[tc].n = n;
        tests[tc].m = m;
        tests[tc].wishes.resize(m);

        for (int i = 0; i < m; ++i) {
            tests[tc].wishes[i].x = inf.readInt();
            tests[tc].wishes[i].y = inf.readInt();
        }
    }

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "all selected wishes are valid");
}
