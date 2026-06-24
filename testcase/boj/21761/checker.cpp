#include "testlib.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <array>
#include <map>
#include <utility>

using namespace std;
using boost::multiprecision::cpp_int;

int K;
array<long long, 4> initialValue;
map<pair<char, int>, int> availableCards;

struct Answer {
    cpp_int volume;
};

Answer readAnswer(InStream& stream) {
    array<long long, 4> value = initialValue;
    map<pair<char, int>, int> usedCards;

    for (int i = 0; i < K; ++i) {
        string t = stream.readToken("[A-D]", format("card[%d].type", i + 1).c_str());
        stream.readSpace();
        int u = stream.readInt(1, 1000000, format("card[%d].value", i + 1).c_str());
        stream.readEoln();

        pair<char, int> card = {t[0], u};
        ++usedCards[card];
        if (usedCards[card] > availableCards[card]) {
            stream.quitf(_wa, "card %c %d is used more times than available", card.first, card.second);
        }
        value[card.first - 'A'] += u;
    }

    stream.readEof();

    cpp_int volume = 1;
    for (long long x : value) {
        volume *= x;
    }
    return {volume};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    K = inf.readInt();
    for (int i = 0; i < 4; ++i) {
        initialValue[i] = inf.readLong();
    }
    for (int i = 0; i < n; ++i) {
        string t = inf.readToken();
        int u = inf.readInt();
        ++availableCards[{t[0], u}];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.volume < jury.volume) {
        quitf(_wa, "jury has better volume");
    }
    if (participant.volume > jury.volume) {
        quitf(_fail, "participant found a better volume than jury");
    }
    quitf(_ok, "volume is optimal");
}
