#include "testlib.h"

#include <string>

using namespace std;

struct DateOutput {
    int year;
    string month;
    string day;
};

DateOutput readDate(InStream& stream) {
    int year = stream.readInt(0, 9999, "year");
    stream.readEoln();

    string month = stream.readToken("[0-9]{2}", "month");
    stream.readEoln();

    string day = stream.readToken("[0-9]{2}", "day");
    stream.readEoln();
    stream.readEof();

    int monthValue = stoi(month);
    int dayValue = stoi(day);
    if (monthValue < 1 || monthValue > 12) {
        stream.quitf(_wa, "month must be in [01, 12], found %s", month.c_str());
    }
    if (dayValue < 1 || dayValue > 31) {
        stream.quitf(_wa, "day must be in [01, 31], found %s", day.c_str());
    }

    return {year, month, day};
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    DateOutput jury = readDate(ans);
    DateOutput participant = readDate(ouf);

    if (participant.year != jury.year || participant.month != jury.month || participant.day != jury.day) {
        quitf(_wa,
              "expected %04d-%s-%s, found %04d-%s-%s",
              jury.year,
              jury.month.c_str(),
              jury.day.c_str(),
              participant.year,
              participant.month.c_str(),
              participant.day.c_str());
    }

    quitf(_ok, "date %04d-%s-%s", participant.year, participant.month.c_str(), participant.day.c_str());
}
