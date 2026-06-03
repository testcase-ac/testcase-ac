#include "testlib.h"

#include <string>
#include <utility>
#include <vector>

using namespace std;

string seatName(pair<int, int> seat) {
    return string(1, static_cast<char>('A' + seat.first)) + toString(seat.second + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> allSeats;
    vector<pair<int, int>> seats;
    for (int row = 0; row < 10; ++row) {
        for (int col = 0; col < 20; ++col) {
            allSeats.push_back({row, col});
        }
    }

    int mode = rnd.next(5);
    if (mode == 0) {
        shuffle(allSeats.begin(), allSeats.end());
        int n = rnd.next(1, 8);
        seats.assign(allSeats.begin(), allSeats.begin() + n);
    } else if (mode == 1) {
        int row = rnd.next(10);
        int n = rnd.next(1, 20);
        vector<int> cols;
        for (int col = 0; col < 20; ++col) {
            cols.push_back(col);
        }
        shuffle(cols.begin(), cols.end());
        for (int i = 0; i < n; ++i) {
            seats.push_back({row, cols[i]});
        }
    } else if (mode == 2) {
        int col = rnd.next(20);
        int n = rnd.next(1, 10);
        vector<int> rows;
        for (int row = 0; row < 10; ++row) {
            rows.push_back(row);
        }
        shuffle(rows.begin(), rows.end());
        for (int i = 0; i < n; ++i) {
            seats.push_back({rows[i], col});
        }
    } else if (mode == 3) {
        vector<pair<int, int>> edgeSeats;
        for (auto seat : allSeats) {
            if (seat.first == 0 || seat.first == 9 || seat.second == 0 || seat.second == 19) {
                edgeSeats.push_back(seat);
            }
        }
        shuffle(edgeSeats.begin(), edgeSeats.end());
        int n = rnd.next(1, static_cast<int>(edgeSeats.size()));
        seats.assign(edgeSeats.begin(), edgeSeats.begin() + n);
    } else {
        shuffle(allSeats.begin(), allSeats.end());
        int n = rnd.next(120, 200);
        seats.assign(allSeats.begin(), allSeats.begin() + n);
    }

    shuffle(seats.begin(), seats.end());
    println(static_cast<int>(seats.size()));
    for (auto seat : seats) {
        println(seatName(seat));
    }

    return 0;
}
