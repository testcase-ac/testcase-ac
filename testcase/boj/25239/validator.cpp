#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int parseClockMinutes(const string& token) {
    int hh = (token[0] - '0') * 10 + (token[1] - '0');
    int mm = (token[3] - '0') * 10 + (token[4] - '0');
    ensuref(0 <= hh && hh <= 11, "hh out of range: %d", hh);
    ensuref(0 <= mm && mm <= 59, "mm out of range: %d", mm);
    ensuref(mm % 10 != 0, "mm must not be a multiple of 10: %d", mm);
    return hh * 60 + mm;
}

int parseEventMilliseconds(const string& token) {
    int dot = -1;
    for (int i = 0; i < (int)token.size(); ++i) {
        if (token[i] == '.') dot = i;
    }

    string secondsPart = token.substr(0, dot);
    ensuref(secondsPart == "0" || secondsPart[0] != '0',
            "event seconds has a leading zero: %s", token.c_str());

    int seconds = 0;
    for (char ch : secondsPart) seconds = seconds * 10 + (ch - '0');

    int millis = (token[dot + 1] - '0') * 100 +
                 (token[dot + 2] - '0') * 10 +
                 (token[dot + 3] - '0');
    int total = seconds * 1000 + millis;
    ensuref(total < 60000, "event time must be before 60.000 seconds: %s", token.c_str());
    return total;
}

int itemDeltaMinutes(const string& event) {
    if (event == "10MIN") return 10;
    if (event == "30MIN") return 30;
    if (event == "50MIN") return 50;
    if (event == "2HOUR") return 120;
    if (event == "4HOUR") return 240;
    if (event == "9HOUR") return 540;
    return -1;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int clockMinutes = parseClockMinutes(inf.readToken("[0-9]{2}:[0-9]{2}", "hh:mm"));
    inf.readEoln();

    vector<int> values(6);
    for (int i = 0; i < 6; ++i) {
        if (i > 0) inf.readSpace();
        values[i] = inf.readInt(1, 100, "value");
        ensuref(values[i] == 1 || values[i] == 10 || values[i] == 100,
                "cell value %d must be one of 1, 10, 100: %d", i + 1, values[i]);
    }
    inf.readEoln();

    int l = inf.readInt(1, 150, "L");
    inf.readEoln();

    vector<bool> sealed(6, false);
    int sealedCount = 0;
    int previousTime = -1;
    bool patternEnded = false;

    for (int i = 0; i < l; ++i) {
        ensuref(!patternEnded, "event %d occurs after all areas were sealed", i + 1);

        string timeToken = inf.readToken("[0-9]{1,2}[.][0-9]{3}", "s.T");
        int eventTime = parseEventMilliseconds(timeToken);
        ensuref(previousTime < eventTime,
                "event times must be strictly increasing at event %d", i + 1);
        previousTime = eventTime;

        inf.readSpace();
        string event = inf.readToken("[0-9A-Z^]{1,5}", "event");
        ensuref(event == "^" || itemDeltaMinutes(event) != -1,
                "unknown event at event %d: %s", i + 1, event.c_str());
        inf.readEoln();

        if (event == "^") {
            int area = clockMinutes / 120;
            if (!sealed[area]) {
                sealed[area] = true;
                ++sealedCount;
                if (sealedCount == 6) patternEnded = true;
            }
        } else {
            clockMinutes = (clockMinutes + itemDeltaMinutes(event)) % 720;
        }
    }

    inf.readEof();
}
