#include "testlib.h"

#include <algorithm>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

namespace {

struct City {
    string name;
    int lat;
    char ns;
    int lon;
    char ew;
};

string cityName(int index) {
    if (index < 26) {
        return string(1, char('A' + index));
    }
    return "City" + to_string(index);
}

City makeCity(int index, int count, int mode) {
    City city;
    city.name = cityName(index);

    if (mode == 0) {
        city.lat = 0;
        city.ns = (index % 2 == 0 ? 'N' : 'S');
        city.lon = (count == 1 ? 0 : index * 180 / (count - 1));
        city.ew = rnd.next(2) == 0 ? 'E' : 'W';
    } else if (mode == 1) {
        int signedLat = -80 + (count == 1 ? 0 : index * 160 / (count - 1));
        city.lat = abs(signedLat);
        city.ns = (signedLat < 0 ? 'S' : 'N');
        city.lon = rnd.next(0, 180);
        city.ew = (index % 2 == 0 ? 'E' : 'W');
    } else {
        city.lat = rnd.next(0, 80);
        city.ns = rnd.next(2) == 0 ? 'N' : 'S';
        city.lon = rnd.next(0, 180);
        city.ew = rnd.next(2) == 0 ? 'E' : 'W';
    }

    return city;
}

bool samePoint(const City& a, const City& b) {
    int signedLatA = a.ns == 'N' ? a.lat : -a.lat;
    int signedLatB = b.ns == 'N' ? b.lat : -b.lat;
    if (abs(signedLatA) == 90 && abs(signedLatB) == 90) {
        return signedLatA == signedLatB;
    }

    int signedLonA = a.ew == 'E' ? a.lon : -a.lon;
    int signedLonB = b.ew == 'E' ? b.lon : -b.lon;
    if (a.lon == 180) {
        signedLonA = 180;
    }
    if (b.lon == 180) {
        signedLonB = 180;
    }
    return signedLatA == signedLatB && signedLonA == signedLonB;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 4);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int x = rnd.next(2, 10);
        int mode = rnd.next(0, 2);

        vector<City> cities;
        for (int i = 0; i < x; ++i) {
            City city;
            do {
                city = makeCity(i, x, mode);
            } while (i > 0 && samePoint(cities.back(), city));
            cities.push_back(city);
        }

        if (rnd.next(2) == 0) {
            reverse(cities.begin(), cities.end());
        }

        println(x, x - 1);
        for (const City& city : cities) {
            println(city.name, city.lat, city.ns, city.lon, city.ew);
        }

        for (int i = 0; i + 1 < x; ++i) {
            if (rnd.next(2) == 0) {
                println(cities[i].name, cities[i + 1].name);
            } else {
                println(cities[i + 1].name, cities[i].name);
            }
        }
    }

    return 0;
}
