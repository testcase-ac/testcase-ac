#include "testlib.h"

#include <set>
#include <vector>

using namespace std;

int a, b, c, d;

struct Answer {
    int girls;
    int boys;

    int total() const {
        return girls + boys;
    }
};

Answer readAnswer(InStream& stream) {
    const int maxStudents = 200000;

    int girls = stream.readInt(1, maxStudents, "number of girls");
    int boys = stream.readInt(1, maxStudents, "number of boys");
    int total = girls + boys;
    if (total > maxStudents) {
        stream.quitf(_wa, "total number of students is %d, maximum supported is %d", total, maxStudents);
    }

    vector<int> girlFriends(total + 1, 0);
    vector<int> boyFriends(total + 1, 0);
    set<pair<int, int>> edges;

    long long expectedEdges = (1LL * girls * a + 1LL * girls * b + 1LL * boys * c + 1LL * boys * d) / 2;
    while (!stream.seekEof()) {
        int u = stream.readInt(1, total, "friendship endpoint");
        int v = stream.readInt(1, total, "friendship endpoint");
        if (u == v) {
            stream.quitf(_wa, "student %d is paired with themself", u);
        }
        if (u > v) {
            swap(u, v);
        }
        if (!edges.insert({u, v}).second) {
            stream.quitf(_wa, "friendship pair (%d, %d) is repeated", u, v);
        }
        if ((long long)edges.size() > expectedEdges) {
            stream.quitf(_wa, "too many friendship pairs");
        }

        bool uGirl = u <= girls;
        bool vGirl = v <= girls;
        if (uGirl && vGirl) {
            ++girlFriends[u];
            ++girlFriends[v];
        } else if (!uGirl && !vGirl) {
            ++boyFriends[u];
            ++boyFriends[v];
        } else {
            if (uGirl) {
                ++boyFriends[u];
                ++girlFriends[v];
            } else {
                ++girlFriends[u];
                ++boyFriends[v];
            }
        }
    }

    if ((long long)edges.size() != expectedEdges) {
        stream.quitf(_wa,
                     "found %d friendship pairs, expected %lld from the degree requirements",
                     (int)edges.size(),
                     expectedEdges);
    }

    for (int i = 1; i <= girls; ++i) {
        if (girlFriends[i] != a || boyFriends[i] != b) {
            stream.quitf(_wa,
                         "girl %d has %d girl friends and %d boy friends, expected %d and %d",
                         i,
                         girlFriends[i],
                         boyFriends[i],
                         a,
                         b);
        }
    }
    for (int i = girls + 1; i <= total; ++i) {
        if (girlFriends[i] != c || boyFriends[i] != d) {
            stream.quitf(_wa,
                         "boy %d has %d girl friends and %d boy friends, expected %d and %d",
                         i,
                         girlFriends[i],
                         boyFriends[i],
                         c,
                         d);
        }
    }

    return {girls, boys};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    a = inf.readInt();
    b = inf.readInt();
    c = inf.readInt();
    d = inf.readInt();

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.total() > jury.total()) {
        quitf(_wa,
              "participant uses %d students, but jury uses %d",
              participant.total(),
              jury.total());
    }
    if (participant.total() < jury.total()) {
        quitf(_fail,
              "participant found a smaller valid class: participant=%d jury=%d",
              participant.total(),
              jury.total());
    }

    quitf(_ok,
          "valid class with %d girls and %d boys",
          participant.girls,
          participant.boys);
}
