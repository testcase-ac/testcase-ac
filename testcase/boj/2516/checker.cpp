#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<vector<int>> enemies;

struct Claim {
    vector<int> cage;
};

Claim readClaim(InStream& stream) {
    vector<int> cage(n + 1, -1);

    for (int side = 0; side < 2; ++side) {
        int count = stream.readInt(1, n - 1, format("cage %d size", side + 1).c_str());

        for (int i = 0; i < count; ++i) {
            int monkey = stream.readInt(1, n, format("cage %d monkey %d", side + 1, i + 1).c_str());
            if (cage[monkey] != -1) {
                stream.quitf(_wa, "monkey %d is listed more than once", monkey);
            }
            cage[monkey] = side;
        }
    }
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after the two cage descriptions");
    }

    for (int monkey = 1; monkey <= n; ++monkey) {
        if (cage[monkey] == -1) {
            stream.quitf(_wa, "monkey %d is not assigned to either cage", monkey);
        }
    }

    for (int monkey = 1; monkey <= n; ++monkey) {
        int sameCageEnemies = 0;
        for (int enemy : enemies[monkey]) {
            if (cage[monkey] == cage[enemy]) {
                ++sameCageEnemies;
            }
        }
        if (sameCageEnemies > 1) {
            stream.quitf(_wa,
                         "monkey %d has %d enemies in the same cage",
                         monkey,
                         sameCageEnemies);
        }
    }

    return {cage};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    enemies.assign(n + 1, {});
    for (int monkey = 1; monkey <= n; ++monkey) {
        int count = inf.readInt();
        enemies[monkey].reserve(count);
        for (int i = 0; i < count; ++i) {
            enemies[monkey].push_back(inf.readInt());
        }
    }

    readClaim(ans);
    readClaim(ouf);

    quitf(_ok, "valid partition");
}
