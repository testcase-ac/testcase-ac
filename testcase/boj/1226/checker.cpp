#include "testlib.h"

#include <vector>

using namespace std;

int n;
vector<int> seats;
int totalSeats;

struct Answer {
    int seatSum;
    int parties;
};

Answer readAnswer(InStream& stream) {
    int k = stream.readInt(1, n, "k");
    stream.readEoln();

    vector<int> used(n + 1, 0);
    int sum = 0;
    for (int i = 0; i < k; ++i) {
        int party = stream.readInt(1, n, format("party[%d]", i + 1).c_str());
        if (used[party]) {
            stream.quitf(_wa, "party %d appears more than once", party);
        }
        used[party] = 1;
        sum += seats[party];
    }
    stream.readEoln();
    stream.readEof();

    if (sum * 2 <= totalSeats) {
        stream.quitf(_wa,
                     "coalition is not valid: coalition seats=%d total seats=%d",
                     sum,
                     totalSeats);
    }

    for (int party = 1; party <= n; ++party) {
        if (!used[party]) {
            continue;
        }
        if ((sum - seats[party]) * 2 > totalSeats) {
            stream.quitf(_wa,
                         "coalition is redundant: removing party %d leaves %d of %d seats",
                         party,
                         sum - seats[party],
                         totalSeats);
        }
    }

    return {sum, k};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    n = inf.readInt();
    seats.assign(n + 1, 0);
    totalSeats = 0;
    for (int i = 1; i <= n; ++i) {
        seats[i] = inf.readInt();
        totalSeats += seats[i];
    }

    Answer jury = readAnswer(ans);
    Answer participant = readAnswer(ouf);

    if (participant.seatSum < jury.seatSum) {
        quitf(_wa,
              "jury has better coalition: jury=%d participant=%d",
              jury.seatSum,
              participant.seatSum);
    }
    if (participant.seatSum > jury.seatSum) {
        quitf(_fail,
              "participant found better coalition: jury=%d participant=%d",
              jury.seatSum,
              participant.seatSum);
    }
    quitf(_ok, "coalition has %d seats using %d parties", participant.seatSum, participant.parties);
}
