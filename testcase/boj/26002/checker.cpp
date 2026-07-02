#include "testlib.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

int h, w, n;
vector<vector<int>> board;
vector<pair<int, int>> posByNumber;

struct Claim {
    bool impossible;
    int kiosk;
    int maxDistance;
};

int parseNonNegativeIntToken(InStream& stream, const string& token, const char* name) {
    if (token.empty()) {
        stream.quitf(_wa, "%s is empty", name);
    }
    for (char ch : token) {
        if (!isdigit(static_cast<unsigned char>(ch))) {
            stream.quitf(_wa, "%s must be a non-negative integer, found '%s'", name, token.c_str());
        }
    }

    long long value = 0;
    for (char ch : token) {
        value = value * 10 + (ch - '0');
        if (value > n) {
            stream.quitf(_wa, "%s is too large: %s", name, token.c_str());
        }
    }
    return static_cast<int>(value);
}

int nextPlot(int current, int destination) {
    auto [r, c] = posByNumber[current];
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    int best = -1;
    int bestDestDiff = n + 1;
    int bestCurrentDiff = n + 1;
    for (int dir = 0; dir < 4; ++dir) {
        int nr = r + dr[dir];
        int nc = c + dc[dir];
        if (nr < 0 || nr >= h || nc < 0 || nc >= w) {
            continue;
        }

        int candidate = board[nr][nc];
        int destDiff = abs(candidate - destination);
        int currentDiff = abs(candidate - current);
        if (destDiff < bestDestDiff ||
            (destDiff == bestDestDiff && currentDiff < bestCurrentDiff)) {
            best = candidate;
            bestDestDiff = destDiff;
            bestCurrentDiff = currentDiff;
        }
    }
    return best;
}

int distanceFromKiosk(int kiosk, int destination) {
    if (kiosk == destination) {
        return 0;
    }

    vector<bool> seen(n + 1, false);
    int current = kiosk;
    for (int steps = 0; steps <= n; ++steps) {
        if (current == destination) {
            return steps;
        }
        if (seen[current]) {
            return -1;
        }
        seen[current] = true;
        current = nextPlot(current, destination);
    }
    return -1;
}

int computeClaimedMaxDistance(InStream& stream, int kiosk) {
    int maxDistance = 0;
    for (int destination = 1; destination <= n; ++destination) {
        int distance = distanceFromKiosk(kiosk, destination);
        if (distance < 0) {
            stream.quitf(_wa,
                         "destination %d is not reachable from claimed kiosk %d",
                         destination,
                         kiosk);
        }
        if (distance > maxDistance) {
            maxDistance = distance;
        }
    }
    return maxDistance;
}

Claim readClaim(InStream& stream) {
    string first = stream.readToken("[A-Za-z0-9]+", "first token");
    if (first == "impossible") {
        if (!stream.seekEof()) {
            stream.quitf(_wa, "extra output after impossible sentinel");
        }
        return {true, -1, -1};
    }
    if (first == "Impossible" || first == "IMPOSSIBLE") {
        stream.quitf(_wa, "impossible sentinel must be lowercase");
    }

    int kiosk = parseNonNegativeIntToken(stream, first, "kiosk");
    if (kiosk < 1 || kiosk > n) {
        stream.quitf(_wa, "kiosk number %d is outside [1, %d]", kiosk, n);
    }
    int reportedMaxDistance = stream.readInt(0, n, "max distance");
    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after max distance");
    }

    int actualMaxDistance = computeClaimedMaxDistance(stream, kiosk);
    if (actualMaxDistance != reportedMaxDistance) {
        stream.quitf(_wa,
                     "claimed kiosk %d has max distance %d, but output reports %d",
                     kiosk,
                     actualMaxDistance,
                     reportedMaxDistance);
    }
    return {false, kiosk, reportedMaxDistance};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    h = inf.readInt(2, 40, "h");
    w = inf.readInt(2, 40, "w");
    n = h * w;
    board.assign(h, vector<int>(w));
    posByNumber.assign(n + 1, {-1, -1});

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            int value = inf.readInt(1, n, "a_ij");
            board[i][j] = value;
            posByNumber[value] = {i, j};
        }
    }

    Claim jury = readClaim(ans);
    Claim participant = readClaim(ouf);

    if (jury.impossible) {
        if (participant.impossible) {
            quitf(_ok, "both outputs report impossible");
        }
        quitf(_fail,
              "participant supplied valid kiosk %d with max distance %d while jury says impossible",
              participant.kiosk,
              participant.maxDistance);
    }

    if (participant.impossible) {
        quitf(_wa, "participant says impossible, but jury has kiosk %d", jury.kiosk);
    }
    if (participant.maxDistance > jury.maxDistance) {
        quitf(_wa,
              "participant max distance %d is worse than jury max distance %d",
              participant.maxDistance,
              jury.maxDistance);
    }
    if (participant.maxDistance < jury.maxDistance) {
        quitf(_fail,
              "participant max distance %d is better than jury max distance %d",
              participant.maxDistance,
              jury.maxDistance);
    }

    quitf(_ok, "kiosk %d has optimal max distance %d", participant.kiosk, participant.maxDistance);
}
