#include "testlib.h"
#include <cmath>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

// Constants from the problem
const double BALL_DIAM = 20.0; // cm
const double BALL_RADIUS = BALL_DIAM / 2.0; // 10.0 cm
const double LANE_WIDTH = 105.0; // cm
const double PIN_DIAM = 12.0; // cm
const double PIN_RADIUS = PIN_DIAM / 2.0; // 6.0 cm

// Input constraints
const double T_MIN = 16.0;
const double T_MAX = 18.0;
const int X_MIN = 10;
const int X_MAX = 80;

// For floating point comparison
const double EPS = 1e-8;

// Helper: check if a double has at most 2 decimal digits
bool has_at_most_2_decimal_digits(const string& s) {
    size_t dot = s.find('.');
    if (dot == string::npos) return true;
    return s.size() - dot - 1 <= 2;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    for (int tc = 0; tc < N; ++tc) {
        // 2. Read T (double, 2 decimal places), X (int)
        string t_str = inf.readToken("[0-9]{1,2}\\.[0-9]{2}", "T");
        ensuref(has_at_most_2_decimal_digits(t_str), 
            "T must have at most 2 decimal digits, got '%s' at test case %d", t_str.c_str(), tc+1);
        double T = atof(t_str.c_str());
        ensuref(T >= T_MIN - EPS && T <= T_MAX + EPS, 
            "T out of bounds at test case %d: got %.10f, expected [%.2f, %.2f]", tc+1, T, T_MIN, T_MAX);

        inf.readSpace();

        int X = inf.readInt(X_MIN, X_MAX, "X");
        inf.readEoln();

        // 3. Simulate the ball's path to ensure the answer always exists (as per problem statement)
        // The ball is thrown from the center (x=0), at angle X degrees from the lane's axis (centered).
        // The ball bounces off bumpers elastically.

        // The ball's center can move between -W and +W, where W = (LANE_WIDTH/2 - BALL_RADIUS)
        const double W = (LANE_WIDTH / 2.0) - BALL_RADIUS; // 42.5 cm

        // The pin is at distance T meters = T*100 cm, at (0, T*100)
        double pin_y = T * 100.0;
        double pin_x = 0.0;

        // Ball starts at (0, 0), angle X degrees from the y-axis (centerline)
        // Positive X: to the right, negative: to the left (but X is always positive in [10,80])
        double angle_deg = X;
        double angle_rad = angle_deg * M_PI / 180.0;

        // The ball's velocity vector
        double vx = sin(angle_rad);
        double vy = cos(angle_rad);

        // Ball's current position
        double bx = 0.0, by = 0.0;

        // Simulate until by >= pin_y
        // At each step, compute time to next wall (left or right), or to pin_y
        // The ball's center must stay within [-W, W]

        // To avoid infinite loops, set a reasonable bounce limit
        int bounce_limit = 1000;
        int bounces = 0;
        bool reached = false;

        while (true) {
            // Time to reach pin_y
            double t_pin = (vy == 0) ? 1e18 : (pin_y - by) / vy;
            if (t_pin < -EPS) t_pin = 1e18; // Only forward

            // Time to hit left or right wall
            double t_wall = 1e18;
            if (vx > EPS) {
                // Right wall at x = W
                t_wall = (W - bx) / vx;
            } else if (vx < -EPS) {
                // Left wall at x = -W
                t_wall = (-W - bx) / vx;
            }
            if (t_wall < -EPS) t_wall = 1e18; // Only forward

            // Next event: wall or pin
            if (t_pin < t_wall + EPS) {
                // Reaches pin line before next wall
                bx += vx * t_pin;
                by += vy * t_pin;
                // Check if the ball's center is close enough to the pin's center
                double dist = fabs(bx - pin_x);
                // Ball hits pin if their centers are within (BALL_RADIUS + PIN_RADIUS)
                // But the problem only asks for answer existence, not to check here
                // We only need to ensure the simulation is valid (ball never leaves lane)
                ensuref(fabs(bx) <= W + EPS, 
                    "Ball center out of lane at pin line at test case %d: bx=%.10f, allowed [%.10f, %.10f]", 
                    tc+1, bx, -W, W);
                break;
            } else {
                // Hits wall first
                bx += vx * t_wall;
                by += vy * t_wall;
                // Reflect vx
                vx = -vx;
                ++bounces;
                ensuref(fabs(bx) <= W + EPS, 
                    "Ball center out of lane after bounce at test case %d: bx=%.10f, allowed [%.10f, %.10f]", 
                    tc+1, bx, -W, W);
                ensuref(bounces <= bounce_limit, 
                    "Too many bounces at test case %d, possible infinite loop", tc+1);
            }
        }
    }

    inf.readEof();
}
