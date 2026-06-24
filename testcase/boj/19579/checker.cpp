#include "testlib.h"

#include <vector>

using namespace std;

int n, m;
vector<long long> mood;
vector<pair<int, int>> dependencies;

struct Answer {
    int count;
    long long value;
};

Answer readAnswer(InStream& stream) {
    int count = stream.readInt(0, n, "item count");
    stream.readEoln();

    vector<int> chosen(n + 1, 0);
    long long value = 0;
    for (int i = 0; i < count; ++i) {
        if (i > 0) {
            stream.readSpace();
        }
        int item = stream.readInt(1, n, format("item[%d]", i + 1).c_str());
        if (chosen[item]) {
            stream.quitf(_wa, "item %d appears more than once", item);
        }
        chosen[item] = 1;
        value += mood[item];
    }
    stream.readEoln();
    stream.readEof();

    for (const auto& dependency : dependencies) {
        int item = dependency.first;
        int required = dependency.second;
        if (chosen[item] && !chosen[required]) {
            stream.quitf(_wa,
                         "item %d is chosen but required item %d is not chosen",
                         item,
                         required);
        }
    }

    return {count, value};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    m = inf.readInt();

    mood.assign(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        mood[i] = inf.readLong();
    }

    dependencies.reserve(m);
    for (int i = 0; i < m; ++i) {
        int item = inf.readInt();
        int required = inf.readInt();
        dependencies.push_back({item, required});
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.value < jury.value) {
        quitf(_wa,
              "jury has better value: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }
    if (participant.value > jury.value) {
        quitf(_fail,
              "participant found better value: jury=%lld participant=%lld",
              jury.value,
              participant.value);
    }

    quitf(_ok, "value=%lld items=%d", participant.value, participant.count);
}
