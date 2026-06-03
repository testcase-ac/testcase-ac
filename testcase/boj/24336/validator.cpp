#include "testlib.h"
#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Station {
    string name;
    bool required;
};

int parseTime(const string& token, const char* fieldName, int row) {
    ensuref(token.size() == 5 && token[2] == ':',
            "%s at row %d must have hh:mm format", fieldName, row);
    ensuref('0' <= token[0] && token[0] <= '9' &&
                    '0' <= token[1] && token[1] <= '9' &&
                    '0' <= token[3] && token[3] <= '9' &&
                    '0' <= token[4] && token[4] <= '9',
            "%s at row %d must contain only digits around ':'", fieldName, row);

    int hour = (token[0] - '0') * 10 + (token[1] - '0');
    int minute = (token[3] - '0') * 10 + (token[4] - '0');
    ensuref(0 <= hour && hour <= 23, "%s hour out of range at row %d: %d", fieldName, row, hour);
    ensuref(0 <= minute && minute <= 59, "%s minute out of range at row %d: %d", fieldName, row, minute);
    return hour * 60 + minute;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const vector<Station> stations = {
            {"Seoul", true},        {"Yeongdeungpo", true}, {"Anyang", false},
            {"Suwon", true},        {"Osan", false},        {"Seojeongri", false},
            {"Pyeongtaek", true},   {"Seonghwan", false},   {"Cheonan", true},
            {"Sojeongni", false},   {"Jeonui", false},      {"Jochiwon", true},
            {"Bugang", false},      {"Sintanjin", false},   {"Daejeon", true},
            {"Okcheon", false},     {"Iwon", false},        {"Jitan", false},
            {"Simcheon", false},    {"Gakgye", false},      {"Yeongdong", true},
            {"Hwanggan", false},    {"Chupungnyeong", false}, {"Gimcheon", true},
            {"Gumi", true},         {"Sagok", false},       {"Yangmok", false},
            {"Waegwan", true},      {"Sindong", false},     {"Daegu", true},
            {"Dongdaegu", true},    {"Gyeongsan", false},   {"Namseonghyeon", false},
            {"Cheongdo", false},    {"Sangdong", false},    {"Miryang", true},
            {"Samnangjin", false},  {"Wondong", false},     {"Mulgeum", false},
            {"Hwamyeong", false},   {"Gupo", true},         {"Sasang", false},
            {"Busan", true},
    };

    map<string, int> stationIndex;
    for (int i = 0; i < int(stations.size()); ++i) {
        stationIndex[stations[i].name] = i;
    }
    const set<string> terminalStations = {"Seoul", "Daejeon", "Dongdaegu", "Busan"};

    int n = inf.readInt(2, 43, "N");
    inf.readSpace();
    int q = inf.readInt(1, n * (n - 1) / 2, "Q");
    inf.readEoln();

    vector<string> routeNames(n);
    vector<int> route(n);
    vector<int> eventTimes;
    eventTimes.reserve(2 * n - 2);

    for (int i = 0; i < n; ++i) {
        string name = inf.readToken("[A-Za-z]{1,20}", "station");
        ensuref(stationIndex.count(name), "unknown station at row %d: %s", i + 1, name.c_str());
        inf.readSpace();
        string arrival = inf.readToken("-:-|[0-9]{2}:[0-9]{2}", "arrival");
        inf.readSpace();
        string departure = inf.readToken("-:-|[0-9]{2}:[0-9]{2}", "departure");
        inf.readEoln();

        routeNames[i] = name;
        route[i] = stationIndex[name];
        if (i == 0) {
            ensuref(arrival == "-:-", "origin arrival must be -:-");
            ensuref(departure != "-:-", "origin departure must be a time");
            eventTimes.push_back(parseTime(departure, "departure", i + 1));
        } else if (i == n - 1) {
            ensuref(arrival != "-:-", "terminal arrival must be a time");
            ensuref(departure == "-:-", "terminal departure must be -:-");
            eventTimes.push_back(parseTime(arrival, "arrival", i + 1));
        } else {
            ensuref(arrival != "-:-", "intermediate arrival must be a time at row %d", i + 1);
            ensuref(departure != "-:-", "intermediate departure must be a time at row %d", i + 1);
            eventTimes.push_back(parseTime(arrival, "arrival", i + 1));
            eventTimes.push_back(parseTime(departure, "departure", i + 1));
        }
    }

    ensuref(terminalStations.count(routeNames.front()), "origin must be one of Seoul, Daejeon, Dongdaegu, Busan");
    ensuref(terminalStations.count(routeNames.back()), "terminal must be one of Seoul, Daejeon, Dongdaegu, Busan");
    ensuref(route.front() != route.back(), "origin and terminal must be different");

    int direction = route.back() > route.front() ? 1 : -1;
    set<int> stoppedStations;
    for (int i = 0; i < n; ++i) {
        ensuref(stoppedStations.insert(route[i]).second,
                "station appears more than once: %s", routeNames[i].c_str());
        if (i > 0) {
            ensuref((route[i] - route[i - 1]) * direction > 0,
                    "route changes direction or repeats around row %d", i + 1);
        }
    }

    for (int idx = route.front(); idx != route.back() + direction; idx += direction) {
        ensuref(!stations[idx].required || stoppedStations.count(idx),
                "required station is missing: %s", stations[idx].name.c_str());
    }

    vector<int> absoluteEventTimes(eventTimes.size());
    absoluteEventTimes[0] = eventTimes[0];
    for (int i = 1; i < int(eventTimes.size()); ++i) {
        absoluteEventTimes[i] = eventTimes[i];
        while (absoluteEventTimes[i] <= absoluteEventTimes[i - 1]) {
            absoluteEventTimes[i] += 24 * 60;
        }
    }
    int elapsed = absoluteEventTimes.back() - absoluteEventTimes.front();
    ensuref(60 <= elapsed && elapsed <= 360,
            "total service time must be between 1 and 6 hours, got %d minutes", elapsed);

    for (int i = 0; i < q; ++i) {
        string from = inf.readToken("[A-Za-z]{1,20}", "station_1");
        ensuref(stationIndex.count(from), "unknown query station_1 at query %d: %s", i + 1, from.c_str());
        inf.readSpace();
        string to = inf.readToken("[A-Za-z]{1,20}", "station_2");
        ensuref(stationIndex.count(to), "unknown query station_2 at query %d: %s", i + 1, to.c_str());
        inf.readEoln();

        int fromIndex = stationIndex[from];
        int toIndex = stationIndex[to];
        ensuref(fromIndex != toIndex, "query %d uses the same station twice", i + 1);
        ensuref(stoppedStations.count(fromIndex), "query %d station_1 is not stopped: %s", i + 1, from.c_str());
        ensuref(stoppedStations.count(toIndex), "query %d station_2 is not stopped: %s", i + 1, to.c_str());
        ensuref((toIndex - fromIndex) * direction > 0,
                "query %d direction does not match train direction", i + 1);
    }

    inf.readEof();
    return 0;
}
