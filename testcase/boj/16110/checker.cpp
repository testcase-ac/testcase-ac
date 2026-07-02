#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

struct Schedule {
    vector<int> kangarooCount;
    vector<int> kiwiCount;
};

int n, m, k;
vector<int> needKangaroo, needKiwi;

pair<int, int> parseBattleToken(InStream& stream, int round, int stadium) {
    string token = stream.readToken();
    int vPos = -1;
    for (int i = 0; i < (int)token.size(); ++i) {
        if (token[i] == 'v') {
            if (vPos != -1) {
                stream.quitf(_wa, "battle[%d][%d] has more than one 'v': %s",
                             round + 1, stadium + 1, token.c_str());
            }
            vPos = i;
        }
    }

    if (vPos <= 0 || vPos + 1 >= (int)token.size()) {
        stream.quitf(_wa, "battle[%d][%d] must have form avb: %s",
                     round + 1, stadium + 1, token.c_str());
    }
    for (int i = 0; i < (int)token.size(); ++i) {
        if (i == vPos) {
            continue;
        }
        if (!isdigit((unsigned char)token[i])) {
            stream.quitf(_wa, "battle[%d][%d] contains a non-digit id: %s",
                         round + 1, stadium + 1, token.c_str());
        }
    }

    long long kangaroo = 0;
    for (int i = 0; i < vPos; ++i) {
        kangaroo = kangaroo * 10 + (token[i] - '0');
        if (kangaroo > m) {
            stream.quitf(_wa, "kangaroo id %lld in battle[%d][%d] is out of range 1..%d",
                         kangaroo, round + 1, stadium + 1, m);
        }
    }
    long long kiwi = 0;
    for (int i = vPos + 1; i < (int)token.size(); ++i) {
        kiwi = kiwi * 10 + (token[i] - '0');
        if (kiwi > k) {
            stream.quitf(_wa, "kiwi id %lld in battle[%d][%d] is out of range 1..%d",
                         kiwi, round + 1, stadium + 1, k);
        }
    }
    if (kangaroo < 1 || kiwi < 1) {
        stream.quitf(_wa, "battle[%d][%d] ids must be positive: %s",
                     round + 1, stadium + 1, token.c_str());
    }
    return {(int)kangaroo, (int)kiwi};
}

Schedule readSchedule(InStream& stream) {
    Schedule schedule;
    schedule.kangarooCount.assign(m + 1, 0);
    schedule.kiwiCount.assign(k + 1, 0);

    vector<vector<int>> kangarooInStadium(n, vector<int>(m + 1, 0));
    vector<vector<int>> kiwiInStadium(n, vector<int>(k + 1, 0));

    for (int round = 0; round < n; ++round) {
        vector<int> kangarooInRound(m + 1, 0);
        vector<int> kiwiInRound(k + 1, 0);
        for (int stadium = 0; stadium < n; ++stadium) {
            auto [kangaroo, kiwi] = parseBattleToken(stream, round, stadium);

            if (kangarooInRound[kangaroo]) {
                stream.quitf(_wa, "kangaroo %d appears more than once in round %d",
                             kangaroo, round + 1);
            }
            if (kiwiInRound[kiwi]) {
                stream.quitf(_wa, "kiwi %d appears more than once in round %d",
                             kiwi, round + 1);
            }
            if (kangarooInStadium[stadium][kangaroo]) {
                stream.quitf(_wa, "kangaroo %d appears more than once in stadium %d",
                             kangaroo, stadium + 1);
            }
            if (kiwiInStadium[stadium][kiwi]) {
                stream.quitf(_wa, "kiwi %d appears more than once in stadium %d",
                             kiwi, stadium + 1);
            }

            kangarooInRound[kangaroo] = 1;
            kiwiInRound[kiwi] = 1;
            kangarooInStadium[stadium][kangaroo] = 1;
            kiwiInStadium[stadium][kiwi] = 1;
            ++schedule.kangarooCount[kangaroo];
            ++schedule.kiwiCount[kiwi];
        }
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d battles", n * n);
    }
    return schedule;
}

void validateCounts(InStream& stream, const Schedule& schedule) {
    for (int kangaroo = 1; kangaroo <= m; ++kangaroo) {
        if (schedule.kangarooCount[kangaroo] != needKangaroo[kangaroo]) {
            stream.quitf(_wa, "kangaroo %d fights %d times, expected %d",
                         kangaroo, schedule.kangarooCount[kangaroo], needKangaroo[kangaroo]);
        }
    }
    for (int kiwi = 1; kiwi <= k; ++kiwi) {
        if (schedule.kiwiCount[kiwi] != needKiwi[kiwi]) {
            stream.quitf(_wa, "kiwi %d fights %d times, expected %d",
                         kiwi, schedule.kiwiCount[kiwi], needKiwi[kiwi]);
        }
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();
    k = inf.readInt();
    needKangaroo.assign(m + 1, 0);
    needKiwi.assign(k + 1, 0);
    for (int i = 1; i <= m; ++i) {
        needKangaroo[i] = inf.readInt();
    }
    for (int i = 1; i <= k; ++i) {
        needKiwi[i] = inf.readInt();
    }

    Schedule jury = readSchedule(ans);
    validateCounts(ans, jury);

    Schedule participant = readSchedule(ouf);
    validateCounts(ouf, participant);

    quitf(_ok, "valid schedule");
}
