#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
using namespace std;

int parseTime(const string& s) {
    int hour = stoi(s.substr(0, 2));
    int minute = stoi(s.substr(3, 2));
    if (s.size() == 5) {
        return hour * 3600 + minute * 60;
    }
    int second = stoi(s.substr(6, 2));
    return hour * 3600 + minute * 60 + second;
}

int parseStation(const string& s) {
    return stoi(s.substr(1));
}

int travelSecondsFrom(int station) {
    if (station == 210 || station == 222 || station == 225 ||
        station == 238 || station == 250 || station == 256 ||
        station == 266) {
        return 180;
    }
    if (station == 220 || station == 221 || station == 245 ||
        station == 249) {
        return 240;
    }
    if (station == 247) {
        return 300;
    }
    return 120;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string arrival = inf.readToken("[0-2][0-9]:[0-5][0-9]:[0-5][0-9]", "arrival_time");
    ensuref(arrival[0] < '2' || arrival[1] <= '3',
            "arrival hour is outside [00, 23]: %s", arrival.c_str());
    inf.readEoln();

    int n = inf.readInt(1, 400, "n");
    inf.readEoln();

    const vector<int> allowedStations = {210, 233, 246, 258, 272};
    vector<vector<pair<int, int>>> occupancy(273);
    vector<pair<int, int>> departuresAtStation[273];

    for (int i = 0; i < n; ++i) {
        string startToken = inf.readToken("K[0-9][0-9][0-9]", "start_station");
        inf.readSpace();
        string endToken = inf.readToken("K[0-9][0-9][0-9]", "end_station");
        inf.readSpace();
        string departureToken = inf.readToken("[0-2][0-9]:[0-5][0-9]", "departure_time");
        ensuref(departureToken[0] < '2' || departureToken[1] <= '3',
                "departure hour is outside [00, 23]: %s", departureToken.c_str());
        inf.readEoln();

        int startStation = parseStation(startToken);
        int endStation = parseStation(endToken);
        ensuref(find(allowedStations.begin(), allowedStations.end(), startStation) != allowedStations.end(),
                "invalid start station at train %d: %s", i + 1, startToken.c_str());
        ensuref(find(allowedStations.begin(), allowedStations.end(), endStation) != allowedStations.end(),
                "invalid end station at train %d: %s", i + 1, endToken.c_str());
        ensuref(startStation < endStation,
                "start station must be before end station at train %d: %s %s",
                i + 1, startToken.c_str(), endToken.c_str());

        int departure = parseTime(departureToken);
        // CHECK: The Korean statement says departures are after 04:45 and before
        // 23:45; accept exactly 23:45 as the less restrictive boundary reading.
        ensuref(4 * 3600 + 45 * 60 <= departure && departure <= 23 * 3600 + 45 * 60,
                "departure time outside [04:45, 23:45] at train %d: %s",
                i + 1, departureToken.c_str());

        for (const auto& existing : departuresAtStation[startStation]) {
            ensuref(existing.first != departure,
                    "multiple trains depart station K%03d at %02d:%02d",
                    startStation, departure / 3600, (departure / 60) % 60);
        }
        departuresAtStation[startStation].push_back({departure, i + 1});

        int current = departure;
        for (int station = startStation; station < endStation; ++station) {
            current += travelSecondsFrom(station);
            int stopStation = station + 1;
            occupancy[stopStation].push_back({current, current + 20});
            if (stopStation != endStation) {
                current += 20;
            }
        }
    }

    for (int station = 210; station <= 272; ++station) {
        sort(occupancy[station].begin(), occupancy[station].end());
        for (int i = 1; i < (int)occupancy[station].size(); ++i) {
            ensuref(occupancy[station][i - 1].second <= occupancy[station][i].first,
                    "two trains occupy station K%03d at overlapping times", station);
        }
    }

    inf.readEof();
}
