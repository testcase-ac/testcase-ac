#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Station {
    string name;
    bool required;
};

string formatTime(int minutes) {
    minutes %= 24 * 60;
    int hour = minutes / 60;
    int minute = minutes % 60;
    string result;
    result += char('0' + hour / 10);
    result += char('0' + hour % 10);
    result += ':';
    result += char('0' + minute / 10);
    result += char('0' + minute % 10);
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

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
    const vector<int> terminals = {0, 14, 30, 42};

    int origin = rnd.any(terminals);
    int terminal = rnd.any(terminals);
    while (terminal == origin) {
        terminal = rnd.any(terminals);
    }
    int direction = terminal > origin ? 1 : -1;

    int mode = rnd.next(4);
    int optionalPercent = 0;
    if (mode == 0) optionalPercent = rnd.next(0, 20);
    if (mode == 1) optionalPercent = rnd.next(35, 65);
    if (mode == 2) optionalPercent = rnd.next(80, 100);
    if (mode == 3) optionalPercent = rnd.next(0, 100);

    vector<int> route;
    for (int idx = origin; idx != terminal + direction; idx += direction) {
        if (idx == origin || idx == terminal || stations[idx].required ||
            rnd.next(100) < optionalPercent) {
            route.push_back(idx);
        }
    }

    int events = 2 * int(route.size()) - 2;
    int totalMinutes = rnd.next(max(60, events - 1), 360);
    vector<int> gaps(events - 1, 1);
    int extra = totalMinutes - int(gaps.size());
    vector<int> weights(gaps.size());
    for (int i = 0; i < int(gaps.size()); ++i) {
        bool travelGap = (i % 2 == 0);
        weights[i] = travelGap ? rnd.next(3, 12) : rnd.next(1, 4);
    }
    int weightSum = accumulate(weights.begin(), weights.end(), 0);
    for (int i = 0; i < int(gaps.size()); ++i) {
        int add = extra * weights[i] / weightSum;
        gaps[i] += add;
        extra -= add;
        weightSum -= weights[i];
    }

    int start = rnd.next(0, 23 * 60 + 59);
    vector<int> eventTimes(events);
    eventTimes[0] = start;
    for (int i = 1; i < events; ++i) {
        eventTimes[i] = eventTimes[i - 1] + gaps[i - 1];
    }

    vector<pair<int, int>> queryCandidates;
    for (int i = 0; i < int(route.size()); ++i) {
        for (int j = i + 1; j < int(route.size()); ++j) {
            queryCandidates.emplace_back(i, j);
        }
    }
    shuffle(queryCandidates.begin(), queryCandidates.end());
    int q = rnd.next(1, int(queryCandidates.size()));
    if (mode != 2) {
        q = min(q, rnd.next(1, min(12, int(queryCandidates.size()))));
    }

    println(int(route.size()), q);
    int eventIndex = 0;
    for (int i = 0; i < int(route.size()); ++i) {
        string arrival = "-:-";
        string departure = "-:-";
        if (i == 0) {
            departure = formatTime(eventTimes[eventIndex++]);
        } else if (i + 1 == int(route.size())) {
            arrival = formatTime(eventTimes[eventIndex++]);
        } else {
            arrival = formatTime(eventTimes[eventIndex++]);
            departure = formatTime(eventTimes[eventIndex++]);
        }
        println(stations[route[i]].name, arrival, departure);
    }

    for (int i = 0; i < q; ++i) {
        int from = queryCandidates[i].first;
        int to = queryCandidates[i].second;
        println(stations[route[from]].name, stations[route[to]].name);
    }

    return 0;
}
