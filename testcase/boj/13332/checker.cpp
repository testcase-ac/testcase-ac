#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <string>

using namespace std;

struct VacationPlan {
    int di;
    int ri;
    int ri_prime;
};

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input data from the input file (inf)
    int m = inf.readInt(1, 100, "m");
    int n = inf.readInt(1, 100, "n");
    int p = inf.readInt(1, n, "p");
    int p_prime = inf.readInt(p, n, "p'");

    vector<int> qi(n + 1);
    vector<int> qi_prime(n + 1);

    for (int i = 1; i <= n; ++i) {
        qi[i] = inf.readInt(1, m, format("qi[%d]", i).c_str());
        qi_prime[i] = inf.readInt(qi[i], m, format("qi'[%d]", i).c_str());
    }

    vector<vector<VacationPlan>> vacationPlans(m + 1); // Member indices from 1 to m

    for (int j = 1; j <= m; ++j) {
        int k = inf.readInt(0, 20, format("k[%d]", j).c_str());
        vector<VacationPlan> plans;
        int last_ri = -1;

        for (int idx = 0; idx < k; ++idx) {
            int di = inf.readInt(1, n, format("d[%d][%d]", j, idx + 1).c_str());
            int ri = inf.readInt(1, n, format("r[%d][%d]", j, idx + 1).c_str());
            int ri_prime = inf.readInt(ri, n, format("r'[%d][%d]", j, idx + 1).c_str());

            if (ri <= last_ri) {
                quitf(_fail, "Invalid input: vacation periods not in increasing order for member %d", j);
            }
            last_ri = ri;

            if (di > ri_prime - ri + 1) {
                quitf(_fail, "Invalid input: di > ri' - ri + 1 for member %d, plan %d", j, idx + 1);
            }

            plans.push_back({di, ri, ri_prime});
        }
        vacationPlans[j] = plans;
    }

    // Read the jury's answer
    int ansAns = ans.readInt(-1, 1, "ansAns");

    // Read the participant's answer
    int oufAns = ouf.readInt(-1, 1, "participantAns");

    if (oufAns == -1) {
        if (ansAns == -1) {
            quitf(_ok, "Both participant and jury say impossible");
        } else {
            quitf(_wa, "Participant says impossible, but a solution exists");
        }
    }

    if (oufAns == 1) {
        if (ansAns == -1) {
            quitf(_wa, "Participant found a solution, but jury says impossible");
        }

        // Read and validate participant's vacation schedules
        vector<set<int>> participantVacations(m + 1); // Member indices from 1 to m

        for (int j = 1; j <= m; ++j) {
            int vj = ouf.readInt(0, n, format("vj[%d]", j).c_str());
            set<int> vacationDays;

            int last_day = 0;
            for (int k = 0; k < vj; ++k) {
                int day = ouf.readInt(1, n, format("vacationDay[%d][%d]", j, k + 1).c_str());

                if (day < last_day) {
                    quitf(_wa, "Vacation days for member %d not in ascending order", j);
                }
                if (vacationDays.count(day)) {
                    quitf(_wa, "Duplicate vacation day %d for member %d", day, j);
                }
                vacationDays.insert(day);
                last_day = day;
            }
            participantVacations[j] = vacationDays;
        }

        // Validate the participant's schedule against the constraints
        for (int j = 1; j <= m; ++j) {
            vector<VacationPlan>& plans = vacationPlans[j];
            set<int>& vacationDays = participantVacations[j];

            // Collect all days in the union of [ri, ri']
            set<int> union_ri;
            for (auto& plan : plans) {
                for (int d = plan.ri; d <= plan.ri_prime; ++d) {
                    union_ri.insert(d);
                }
            }

            // Check vacation plans
            for (auto& plan : plans) {
                int count_di = 0;
                for (int d = plan.ri; d <= plan.ri_prime; ++d) {
                    if (vacationDays.count(d)) {
                        count_di++;
                    }
                }
                if (count_di < plan.di) {
                    quitf(_wa, "Member %d does not take enough vacation days in plan [%d,%d]", j, plan.ri, plan.ri_prime);
                }
            }

            // Check that member works on at least one day outside of vacation periods
            bool works_outside_union = false;
            for (int d = 1; d <= n; ++d) {
                if (vacationDays.count(d) == 0 && union_ri.count(d) == 0) {
                    works_outside_union = true;
                    break;
                }
            }
            if (!works_outside_union) {
                quitf(_wa, "Member %d does not work on any day outside of vacation periods", j);
            }

            // Check total working days
            int working_days = n - vacationDays.size();
            if (working_days < p || working_days > p_prime) {
                quitf(_wa, "Member %d works %d days, which is outside of [%d, %d]", j, working_days, p, p_prime);
            }
        }

        // Check the number of members working each day
        for (int i = 1; i <= n; ++i) {
            int working_members = 0;
            for (int j = 1; j <= m; ++j) {
                if (participantVacations[j].count(i) == 0) {
                    working_members++;
                }
            }
            if (working_members < qi[i] || working_members > qi_prime[i]) {
                quitf(_wa, "On day %d, %d members are working, which is outside of [%d, %d]", i, working_members, qi[i], qi_prime[i]);
            }
        }

        // If all checks pass, accept the participant's answer
        quitf(_ok, "Participant's schedule is valid");
    }

    // Unexpected case
    quitf(_fail, "Unexpected case encountered");

    return 0;
}
