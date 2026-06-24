#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

struct Answer {
    bool noAnswer;
    long long hello;
    long long world;
};

static int digitAt(const string& s, int index, const char* field) {
    if (s[index] < '0' || s[index] > '9') {
        quitf(_fail, "internal parser error for %s", field);
    }
    return s[index] - '0';
}

static Answer readAnswer(InStream& stream, long long n) {
    string first = stream.readLine();
    if (first == "No Answer") {
        stream.readEof();
        return {true, 0, 0};
    }

    string second = stream.readLine();
    string third = stream.readLine();
    string fourth = stream.readLine();
    stream.readEof();

    if (first.size() != 7 || first.substr(0, 2) != "  ") {
        stream.quitf(_wa, "first line must contain two spaces followed by hello");
    }
    if (second.size() != 7 || second.substr(0, 2) != "+ ") {
        stream.quitf(_wa, "second line must contain '+ ' followed by world");
    }
    if (third != "-------") {
        stream.quitf(_wa, "third line must be seven hyphens");
    }
    if (fourth.size() != 7) {
        stream.quitf(_wa, "fourth line must have width 7");
    }

    string helloText = first.substr(2);
    string worldText = second.substr(2);
    for (char c : helloText) {
        if (c < '0' || c > '9') {
            stream.quitf(_wa, "hello contains a non-digit character");
        }
    }
    for (char c : worldText) {
        if (c < '0' || c > '9') {
            stream.quitf(_wa, "world contains a non-digit character");
        }
    }

    string expectedSum = to_string(n);
    if (expectedSum.size() > 7) {
        stream.quitf(_wa, "sum does not fit the required width");
    }
    string paddedSum(7 - expectedSum.size(), ' ');
    paddedSum += expectedSum;
    if (fourth != paddedSum) {
        stream.quitf(_wa, "sum line is '%s', expected '%s'", fourth.c_str(), paddedSum.c_str());
    }

    vector<int> letters = {
        digitAt(helloText, 0, "h"),
        digitAt(helloText, 1, "e"),
        digitAt(helloText, 2, "l"),
        digitAt(helloText, 3, "l"),
        digitAt(helloText, 4, "o"),
        digitAt(worldText, 0, "w"),
        digitAt(worldText, 1, "o"),
        digitAt(worldText, 2, "r"),
        digitAt(worldText, 3, "l"),
        digitAt(worldText, 4, "d"),
    };

    int h = letters[0];
    int e = letters[1];
    int l1 = letters[2];
    int l2 = letters[3];
    int o1 = letters[4];
    int w = letters[5];
    int o2 = letters[6];
    int r = letters[7];
    int l3 = letters[8];
    int d = letters[9];

    if (h == 0 || w == 0) {
        stream.quitf(_wa, "h and w must be nonzero");
    }
    if (l1 != l2 || l1 != l3) {
        stream.quitf(_wa, "all l positions must use the same digit");
    }
    if (o1 != o2) {
        stream.quitf(_wa, "all o positions must use the same digit");
    }

    vector<int> used(10, 0);
    for (int value : {d, e, h, l1, o1, r, w}) {
        if (used[value]) {
            stream.quitf(_wa, "letters must use distinct digits");
        }
        used[value] = 1;
    }

    long long hello = stoll(helloText);
    long long world = stoll(worldText);
    if (hello + world != n) {
        stream.quitf(_wa, "hello + world is %lld, expected %lld", hello + world, n);
    }

    return {false, hello, world};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    long long n = inf.readLong(1, 2147483647LL, "N");
    inf.readEoln();
    inf.readEof();

    Answer jury = readAnswer(ans, n);
    Answer participant = readAnswer(ouf, n);

    if (jury.noAnswer && participant.noAnswer) {
        quitf(_ok, "no answer");
    }
    if (jury.noAnswer && !participant.noAnswer) {
        quitf(_fail, "participant found a valid answer while jury says No Answer");
    }
    if (!jury.noAnswer && participant.noAnswer) {
        quitf(_wa, "jury has an answer but participant printed No Answer");
    }

    quitf(_ok, "hello=%lld world=%lld", participant.hello, participant.world);
}
