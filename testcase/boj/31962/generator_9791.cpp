#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = (argc >= 3 ? atoi(argv[2]) : rnd.next(1, 7));

    int N = 0;
    int X = 0;
    vector<pair<int,int>> buses;

    switch (scenario) {
        case 1: {
            // N = 1, guaranteed feasible
            X = rnd.next(2, 200);
            int Smax = min(100, X - 1);
            if (Smax < 1) Smax = 1; // just in case
            int S = rnd.next(1, Smax);
            int Tmax = min(100, X - S);
            if (Tmax < 1) Tmax = 1;
            int T = rnd.next(1, Tmax);
            N = 1;
            buses.push_back({S, T});
            break;
        }
        case 2: {
            // N = 1, guaranteed infeasible (answer -1)
            int S = rnd.next(1, 100);
            int T = rnd.next(1, 100);
            if (S + T <= 2) {
                S = 2;
                T = 1;
            }
            int maxX = min(200, S + T - 1);
            if (maxX < 2) maxX = 2;
            X = rnd.next(2, maxX);
            N = 1;
            buses.push_back({S, T});
            break;
        }
        case 3: {
            // All buses arrive within X (subtask 2-style)
            N = rnd.next(2, 10);
            X = rnd.next(20, 200);
            for (int i = 0; i < N; i++) {
                int Smax = min(100, X - 1);
                if (Smax < 1) Smax = 1;
                int S = rnd.next(1, Smax);
                int Tmax = min(100, X - S);
                if (Tmax < 1) Tmax = 1;
                int T = rnd.next(1, Tmax);
                buses.push_back({S, T});
            }
            break;
        }
        case 4: {
            // All buses have T = 20 (subtask 3-style)
            N = rnd.next(1, 10);
            X = rnd.next(5, 200);
            for (int i = 0; i < N; i++) {
                int S = rnd.next(1, 100);
                int T = 20;
                buses.push_back({S, T});
            }
            break;
        }
        case 5: {
            // Mix of feasible and infeasible, guaranteed both exist
            N = rnd.next(3, 10);
            X = rnd.next(20, 150);

            // One feasible bus
            int Smax = min(100, X - 1);
            int S_f = rnd.next(1, Smax);
            int Tmax = min(100, X - S_f);
            if (Tmax < 1) Tmax = 1;
            int T_f = rnd.next(1, Tmax);
            buses.push_back({S_f, T_f});

            // One definitely infeasible bus
            int S_i, T_i;
            if (X <= 99) {
                S_i = X;
                T_i = 1; // S_i + T_i = X + 1 > X
            } else {
                S_i = 100;
                T_i = X - 100 + 1; // >=1 and <=51, S_i+T_i > X
            }
            buses.push_back({S_i, T_i});

            // Remaining buses random
            for (int i = 2; i < N; i++) {
                int S = rnd.next(1, 100);
                int T = rnd.next(1, 100);
                buses.push_back({S, T});
            }
            break;
        }
        case 6: {
            // Edge values: very small or very large X
            bool smallX = rnd.next(0, 1);
            if (smallX) {
                X = rnd.next(2, 10);
                N = rnd.next(1, 8);
                for (int i = 0; i < N; i++) {
                    if (i % 2 == 0) {
                        // Feasible bus
                        int Smax = min(100, X - 1);
                        if (Smax < 1) Smax = 1;
                        int S = rnd.next(1, Smax);
                        int Tmax = min(100, X - S);
                        if (Tmax < 1) Tmax = 1;
                        int T = rnd.next(1, Tmax);
                        buses.push_back({S, T});
                    } else {
                        // Infeasible bus: make S large enough
                        int S = rnd.next(X + 1, 100); // X+1..100, and X<=10
                        int T = rnd.next(1, 100);
                        buses.push_back({S, T});
                    }
                }
            } else {
                X = rnd.next(150, 200);
                N = rnd.next(5, 15);

                // Ensure at least one feasible bus
                int S_fe = rnd.next(1, min(100, X - 1));
                int Tmax_fe = min(100, X - S_fe);
                if (Tmax_fe < 1) Tmax_fe = 1;
                int T_fe = rnd.next(1, Tmax_fe);
                buses.push_back({S_fe, T_fe});

                // Others with S,T near 90..100
                for (int i = 1; i < N; i++) {
                    int S = rnd.next(90, 100);
                    int T = rnd.next(90, 100);
                    buses.push_back({S, T});
                }
            }
            break;
        }
        case 7: {
            // Tricky: best bus has largest S among feasible, not minimal arrival time
            X = rnd.next(10, 50);
            N = rnd.next(3, 7);

            int S_best = X - 1;
            int T_best = 1; // arrival exactly X
            buses.push_back({S_best, T_best}); // optimal bus

            // Another bus with earliest departure but same arrival time
            buses.push_back({1, X - 1});

            if (N >= 3) {
                // Another feasible bus with smaller S
                int S2 = rnd.next(1, X - 2);
                int Tmax2 = min(100, X - S2);
                if (Tmax2 < 1) Tmax2 = 1;
                int T2 = rnd.next(1, Tmax2);
                buses.push_back({S2, T2});
            }

            while ((int)buses.size() < N) {
                int choice = rnd.next(0, 1);
                if (choice == 0 && S_best > 2) {
                    // Extra feasible with smaller S
                    int S = rnd.next(1, S_best - 1);
                    int Tmax = min(100, X - S);
                    if (Tmax < 1) Tmax = 1;
                    int T = rnd.next(1, Tmax);
                    buses.push_back({S, T});
                } else {
                    // Infeasible, often with larger S
                    int S = rnd.next(S_best + 1, min(100, S_best + 10));
                    int T = rnd.next(1, 100);
                    if (S + T <= X) {
                        int need = X - (S + T) + 1;
                        if (T + need <= 100) T += need;
                        else if (S + need <= 100) S += need;
                        // With X <= 50 and S >= S_best+1 = X, this almost always works
                    }
                    buses.push_back({S, T});
                }
            }
            break;
        }
        default:
            break;
    }

    shuffle(buses.begin(), buses.end());

    println(N, X);
    for (int i = 0; i < N; i++) {
        println(buses[i].first, buses[i].second);
    }

    return 0;
}
