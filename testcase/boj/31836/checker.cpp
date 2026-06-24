#include "testlib.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <vector>

using namespace std;
using boost::multiprecision::cpp_int;

int n;
vector<cpp_int> fib;

struct Answer {
    int usedCount;
};

vector<int> readGroup(InStream& stream, int count, const char* groupName, vector<int>& used) {
    vector<int> group;
    group.reserve(count);
    for (int i = 0; i < count; ++i) {
        int index = stream.readInt(1, n, format("%s[%d]", groupName, i + 1).c_str());
        if (used[index]) {
            stream.quitf(_wa, "souvenir %d is used more than once", index);
        }
        used[index] = 1;
        group.push_back(index);
    }
    stream.readEoln();
    return group;
}

Answer readAnswer(InStream& stream) {
    int x = stream.readInt(1, n, "X");
    stream.readEoln();

    vector<int> used(n + 1, 0);
    vector<int> a = readGroup(stream, x, "A", used);

    int y = stream.readInt(1, n, "Y");
    stream.readEoln();
    vector<int> b = readGroup(stream, y, "B", used);

    stream.readEof();

    cpp_int sumA = 0;
    for (int index : a) {
        sumA += fib[index];
    }

    cpp_int sumB = 0;
    for (int index : b) {
        sumB += fib[index];
    }

    if (sumA != sumB) {
        stream.quitf(_wa, "gift sums are not equal");
    }

    return {x + y};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt(2, 2000, "N");
    inf.readEoln();
    inf.readEof();

    fib.assign(n + 1, 0);
    fib[1] = 1;
    fib[2] = 1;
    for (int i = 3; i <= n; ++i) {
        fib[i] = fib[i - 1] + fib[i - 2];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.usedCount < jury.usedCount) {
        quitf(_wa,
              "participant used fewer souvenirs than jury: participant=%d jury=%d",
              participant.usedCount,
              jury.usedCount);
    }
    if (participant.usedCount > jury.usedCount) {
        quitf(_fail,
              "participant found a better distribution: participant=%d jury=%d",
              participant.usedCount,
              jury.usedCount);
    }

    quitf(_ok, "used souvenirs=%d", participant.usedCount);
}
