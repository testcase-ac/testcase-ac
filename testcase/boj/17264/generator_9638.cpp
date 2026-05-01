#include "testlib.h"
using namespace std;

struct PlayerInfo {
    string name;
    char res; // 'W' or 'L'
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> pool = {
        "JIHOON","GANGYEOP","MINSUNG","IRONMAN","ALLY","ENEMY",
        "X","Y","Z","AAA","BBB","CCC","DDD","EEE",
        "WINNER","LOSER","FRIEND","STRANGER","TEAMMATE",
        "CARRY","NOOB","PRO","MID","TOP","JUNGLE","BOT"
    };

    int N = 0, P = 0;
    int W = 0, L = 0, G = 0;
    vector<PlayerInfo> infos;
    vector<string> games;

    int type = rnd.next(0, 6); // 7 different scenario types: 0..6

    if (type == 0) {
        // General mixed small random test
        shuffle(pool.begin(), pool.end());

        int totalNames = rnd.next(3, 8);
        vector<string> names(totalNames);
        for (int i = 0; i < totalNames; ++i)
            names[i] = pool[i];

        P = rnd.next(1, totalNames);
        infos.clear();
        infos.reserve(P);

        int cntW = 0, cntL = 0;
        for (int i = 0; i < P; ++i) {
            char res = (rnd.next(0, 1) == 0 ? 'W' : 'L');
            infos.push_back({names[i], res});
            if (res == 'W') cntW++;
            else cntL++;
        }
        // Ensure at least one W and one L if possible
        if (P >= 2) {
            if (cntW == 0) {
                infos[0].res = 'W';
                cntW++;
                cntL--;
            } else if (cntL == 0) {
                infos[0].res = 'L';
                cntL++;
                cntW--;
            }
        }

        vector<string> unknownNames;
        for (int i = P; i < totalNames; ++i)
            unknownNames.push_back(names[i]);
        if (unknownNames.empty()) {
            unknownNames.push_back("UNKNOWN");
        }

        vector<int> winnerIdx, loserIdx;
        for (int i = 0; i < P; ++i) {
            if (infos[i].res == 'W') winnerIdx.push_back(i);
            else loserIdx.push_back(i);
        }

        W = rnd.next(5, 40);
        L = rnd.next(5, 40);
        G = rnd.next(10, 200);
        N = rnd.next(5, 20);

        games.clear();
        games.reserve(N);
        for (int i = 0; i < N; ++i) {
            int cat = rnd.next(0, 4); // 0-1: win, 2-3: lose, 4: unknown
            if ((cat <= 1 && !winnerIdx.empty()) ||
                (cat <= 3 && loserIdx.empty() && !winnerIdx.empty())) {
                int idx = rnd.any(winnerIdx);
                games.push_back(infos[idx].name);
            } else if ((cat <= 3 && !loserIdx.empty()) ||
                       unknownNames.empty()) {
                int idx = rnd.any(loserIdx);
                games.push_back(infos[idx].name);
            } else {
                games.push_back(rnd.any(unknownNames));
            }
        }
    } else if (type == 1) {
        // Early escape then drop below G later: must ignore later games.
        string winName = "WINNER";
        string loseName = "LOSER";
        string unkName = "STRANGER";

        W = rnd.next(5, 20);
        L = rnd.next(W, 2 * W); // L >= W > 0
        G = rnd.next(W + 1, 3 * W); // require at least 2 wins sometimes

        int need = (G + W - 1) / W; // wins needed to reach G
        int extraLosses = 2;
        N = need + extraLosses;

        P = 2;
        infos.clear();
        infos.push_back({winName, 'W'});
        infos.push_back({loseName, 'L'});

        games.clear();
        games.reserve(N);
        for (int i = 0; i < need; ++i)
            games.push_back(winName);
        // After escape, only unknown (loses) that might drop below G
        for (int i = 0; i < extraLosses; ++i)
            games.push_back(unkName);
    } else if (type == 2) {
        // Floor at zero test: big L, then wins should still escape.
        string winName = "WINNER";
        string loseName = "LOSER";
        string unkName = "UNKNOWN";

        W = 40;
        L = 50;
        G = 60;
        N = 3;

        P = 2;
        infos.clear();
        infos.push_back({winName, 'W'});
        infos.push_back({loseName, 'L'});

        games.clear();
        games.reserve(N);
        games.push_back(unkName);   // lose, but score must stay at 0
        games.push_back(winName);   // +40
        games.push_back(winName);   // +40 -> 80 >= 60
    } else if (type == 3) {
        // Unknown players are always loses.
        // If a solution treats unknown as W, it incorrectly escapes.
        string allyName = "ALLY";
        string unk1 = "STRANGERA";
        string unk2 = "STRANGERB";

        W = 30;
        L = 10;
        G = 25;
        N = 2;

        P = 1;
        infos.clear();
        infos.push_back({allyName, 'W'});

        games.clear();
        games.reserve(N);
        games.push_back(unk1);
        games.push_back(unk2);
    } else if (type == 4) {
        // W = 0: wins do not change score. G >= 1 => never escapes.
        string allyName = "ALLY";
        string enemyName = "ENEMY";
        string unkName = "STRANGER";

        W = 0;
        L = 10;
        G = 50;
        N = 5;

        P = 2;
        infos.clear();
        infos.push_back({allyName, 'W'});
        infos.push_back({enemyName, 'L'});

        games.clear();
        games.reserve(N);
        games.push_back(allyName);  // win, +0
        games.push_back(allyName);  // win, +0
        games.push_back(enemyName); // lose, -10 -> 0
        games.push_back(allyName);  // win, +0
        games.push_back(unkName);   // lose unknown, -10 -> 0
    } else if (type == 5) {
        // Big G unreachable: G larger than max possible total gain.
        shuffle(pool.begin(), pool.end());

        int totalNames = rnd.next(4, 8);
        vector<string> names(totalNames);
        for (int i = 0; i < totalNames; ++i)
            names[i] = pool[i];

        N = rnd.next(5, 20);
        W = rnd.next(5, 30);
        L = rnd.next(0, 30);
        int maxGain = W * N;
        G = rnd.next(maxGain + 1, maxGain + 100); // impossible to reach

        P = rnd.next(1, totalNames - 1); // leave at least 1 unknown
        infos.clear();
        infos.reserve(P);
        int cntW = 0;
        for (int i = 0; i < P; ++i) {
            char res = (rnd.next(0, 1) == 0 ? 'W' : 'L');
            infos.push_back({names[i], res});
            if (res == 'W') cntW++;
        }
        // Ensure at least one W among hacked players for variety
        if (cntW == 0) {
            infos[0].res = 'W';
        }

        games.clear();
        games.reserve(N);
        for (int i = 0; i < N; ++i) {
            int idx = rnd.next(0, totalNames - 1);
            games.push_back(names[idx]);
        }
    } else if (type == 6) {
        // L = 0: losses don't reduce score, only wins matter.
        shuffle(pool.begin(), pool.end());

        int totalNames = rnd.next(3, 7);
        vector<string> names(totalNames);
        for (int i = 0; i < totalNames; ++i)
            names[i] = pool[i];

        P = rnd.next(1, totalNames);
        infos.clear();
        infos.reserve(P);
        int cntW = 0;
        for (int i = 0; i < P; ++i) {
            char res = (rnd.next(0, 1) == 0 ? 'W' : 'L');
            infos.push_back({names[i], res});
            if (res == 'W') cntW++;
        }
        if (P >= 1 && cntW == 0) {
            infos[0].res = 'W';
            cntW = 1;
        }

        W = rnd.next(5, 25);
        L = 0;
        N = rnd.next(5, 15);

        int maxGain = W * N;
        G = rnd.next(1, maxGain + 5); // sometimes reachable, sometimes not

        vector<string> unknownNames;
        for (int i = P; i < totalNames; ++i)
            unknownNames.push_back(names[i]);
        if (unknownNames.empty())
            unknownNames.push_back("UNKNOWN");

        vector<int> winnerIdx, loserIdx;
        for (int i = 0; i < P; ++i) {
            if (infos[i].res == 'W') winnerIdx.push_back(i);
            else loserIdx.push_back(i);
        }

        games.clear();
        games.reserve(N);
        for (int i = 0; i < N; ++i) {
            int cat = rnd.next(0, 4); // 0-1: win, 2-3: lose, 4: unknown
            if ((cat <= 1 && !winnerIdx.empty()) ||
                (cat <= 3 && loserIdx.empty() && !winnerIdx.empty())) {
                int idx = rnd.any(winnerIdx);
                games.push_back(infos[idx].name);
            } else if ((cat <= 3 && !loserIdx.empty()) ||
                       unknownNames.empty()) {
                int idx = rnd.any(loserIdx);
                games.push_back(infos[idx].name);
            } else {
                games.push_back(rnd.any(unknownNames));
            }
        }
    }

    // Output
    println(N, P);
    println(W, L, G);
    for (int i = 0; i < P; ++i) {
        println(infos[i].name, infos[i].res);
    }
    for (int i = 0; i < N; ++i) {
        println(games[i]);
    }

    return 0;
}
