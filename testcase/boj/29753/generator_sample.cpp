#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

struct Course {
    int credit;
    string grade;
};

const vector<pair<string, int>> GRADES = {
    {"A+", 450}, {"A0", 400}, {"B+", 350}, {"B0", 300}, {"C+", 250},
    {"C0", 200}, {"D+", 150}, {"D0", 100}, {"F", 0},
};

string formatGpa(int cents) {
    return to_string(cents / 100) + "." + string(1, char('0' + (cents / 10) % 10)) +
           string(1, char('0' + cents % 10));
}

void printCase(const vector<Course>& courses, int missingCredit, int threshold) {
    println(int(courses.size()) + 1, formatGpa(threshold));
    for (const Course& course : courses) {
        println(course.credit, course.grade);
    }
    println(missingCredit);
}

vector<Course> randomCourses(int knownCount, int gradeLo, int gradeHi) {
    vector<Course> courses;
    for (int i = 0; i < knownCount; ++i) {
        int gradeIndex = rnd.next(gradeLo, gradeHi);
        courses.push_back({rnd.next(1, 6), GRADES[gradeIndex].first});
    }
    return courses;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int knownCount = rnd.next(1, 23);
        printCase(randomCourses(knownCount, 0, 8), rnd.next(1, 6), rnd.next(0, 450));
        return 0;
    }

    if (mode == 1) {
        int knownCount = rnd.next(1, 10);
        printCase(randomCourses(knownCount, 5, 8), rnd.next(1, 6), rnd.next(390, 450));
        return 0;
    }

    if (mode == 2) {
        int knownCount = rnd.next(1, 12);
        printCase(randomCourses(knownCount, 0, 4), rnd.next(1, 6), rnd.next(0, 120));
        return 0;
    }

    for (int attempt = 0; attempt < 200; ++attempt) {
        int knownCount = rnd.next(1, 12);
        vector<Course> courses = randomCourses(knownCount, 0, 8);
        int missingCredit = rnd.next(1, 6);

        int creditSum = missingCredit;
        int weightedSum = 0;
        for (const Course& course : courses) {
            creditSum += course.credit;
            for (const auto& grade : GRADES) {
                if (grade.first == course.grade) {
                    weightedSum += course.credit * grade.second;
                    break;
                }
            }
        }

        vector<int> indices;
        for (int i = 0; i < int(GRADES.size()); ++i) {
            indices.push_back(i);
        }
        shuffle(indices.begin(), indices.end());

        for (int idx : indices) {
            int targetAvg = (weightedSum + missingCredit * GRADES[idx].second) / creditSum;
            if (targetAvg == 0) {
                continue;
            }

            int threshold = targetAvg - 1;
            bool lowerPasses = false;
            for (int j = idx + 1; j < int(GRADES.size()); ++j) {
                int lowerAvg = (weightedSum + missingCredit * GRADES[j].second) / creditSum;
                if (lowerAvg > threshold) {
                    lowerPasses = true;
                }
            }
            if (!lowerPasses) {
                printCase(courses, missingCredit, threshold);
                return 0;
            }
        }
    }

    printCase({{3, "B+"}, {2, "C0"}, {1, "A0"}}, 2, 299);
    return 0;
}
