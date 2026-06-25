#include "testlib.h"

#include <algorithm>
#include <iomanip>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Train {
    int start;
    int finish;
    int departure;
};

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

int departureOffset(int start, int station) {
    int offset = 0;
    for (int current = start; current < station; ++current) {
        offset += travelSecondsFrom(current) + 20;
    }
    return offset;
}

string stationToken(int station) {
    return "K" + to_string(station);
}

string clockToken(int seconds, bool includeSeconds) {
    int hour = seconds / 3600;
    int minute = (seconds % 3600) / 60;
    int second = seconds % 60;
    stringstream ss;
    ss << setfill('0') << setw(2) << hour << ':' << setw(2) << minute;
    if (includeSeconds) {
        ss << ':' << setw(2) << second;
    }
    return ss.str();
}

vector<pair<int, int>> occupancyIntervals(const Train& train) {
    vector<pair<int, int>> intervals;
    int current = train.departure;
    for (int station = train.start; station < train.finish; ++station) {
        current += travelSecondsFrom(station);
        intervals.push_back({current, current + 20});
        if (station + 1 != train.finish) {
            current += 20;
        }
    }
    return intervals;
}

bool canAddTrain(const vector<Train>& trains, const Train& candidate) {
    for (const Train& train : trains) {
        if (train.start == candidate.start && train.departure == candidate.departure) {
            return false;
        }
    }

    vector<vector<pair<int, int>>> byStation(273);
    for (const Train& train : trains) {
        vector<pair<int, int>> intervals = occupancyIntervals(train);
        for (int station = train.start + 1; station <= train.finish; ++station) {
            byStation[station].push_back(intervals[station - train.start - 1]);
        }
    }

    vector<pair<int, int>> intervals = occupancyIntervals(candidate);
    for (int station = candidate.start + 1; station <= candidate.finish; ++station) {
        pair<int, int> now = intervals[station - candidate.start - 1];
        for (pair<int, int> existing : byStation[station]) {
            if (max(existing.first, now.first) < min(existing.second, now.second)) {
                return false;
            }
        }
    }
    return true;
}

bool tryAddTrain(vector<Train>& trains, int start, int finish, int departure) {
    if (departure < 4 * 3600 + 45 * 60 || departure > 23 * 3600 + 45 * 60) {
        return false;
    }
    if (departure % 60 != 0) {
        return false;
    }
    Train train{start, finish, departure};
    if (!canAddTrain(trains, train)) {
        return false;
    }
    trains.push_back(train);
    return true;
}

void addRandomTrains(vector<Train>& trains, int count) {
    const vector<int> stations = {210, 233, 246, 258, 272};
    for (int attempt = 0; attempt < count * 80 && (int)trains.size() < count; ++attempt) {
        int startIndex = rnd.next(0, 3);
        int finishIndex = rnd.next(startIndex + 1, 4);
        int departure = rnd.next(4 * 60 + 45, 23 * 60 + 45) * 60;
        tryAddTrain(trains, stations[startIndex], stations[finishIndex], departure);
    }
}

void addChainNear(vector<Train>& trains, int gaheeArrival) {
    int desiredK225Departure = gaheeArrival + rnd.next(0, 45) * 60;
    int firstDeparture = desiredK225Departure - departureOffset(210, 225);
    firstDeparture = (firstDeparture / 60) * 60;
    if (!tryAddTrain(trains, 210, rnd.any(vector<int>{233, 246, 258, 272}), firstDeparture)) {
        return;
    }

    const vector<pair<int, int>> segments = {{233, 246}, {246, 258}, {258, 272}};
    int ready = firstDeparture + departureOffset(210, 233);
    for (pair<int, int> segment : segments) {
        int departure = ((ready + rnd.next(0, 35) * 60 + 59) / 60) * 60;
        if (!tryAddTrain(trains, segment.first, segment.second, departure)) {
            departure += rnd.next(5, 20) * 60;
            tryAddTrain(trains, segment.first, segment.second, departure);
        }
        ready = departure + departureOffset(segment.first, segment.second);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int arrival = rnd.next(0, 23 * 3600 + 59 * 60 + 59);
    vector<Train> trains;

    if (mode <= 2) {
        addChainNear(trains, arrival);
        addRandomTrains(trains, rnd.next(6, 18));
    } else if (mode == 3) {
        int directDeparture = rnd.next(4 * 60 + 45, 23 * 60 + 45) * 60;
        tryAddTrain(trains, 210, 272, directDeparture);
        addRandomTrains(trains, rnd.next(3, 12));
    } else if (mode == 4) {
        arrival = rnd.next(22 * 3600, 23 * 3600 + 59 * 60 + 59);
        addRandomTrains(trains, rnd.next(1, 8));
    } else {
        addRandomTrains(trains, rnd.next(20, 45));
    }

    while (trains.empty()) {
        addRandomTrains(trains, 1);
    }

    shuffle(trains.begin(), trains.end());

    println(clockToken(arrival, true));
    println((int)trains.size());
    for (const Train& train : trains) {
        println(stationToken(train.start), stationToken(train.finish),
                clockToken(train.departure, false));
    }

    return 0;
}
