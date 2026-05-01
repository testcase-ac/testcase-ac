# Generate the maximum test case
# N = maximum days, M = maximum subjects
N = 200_000
M = 200_000

print(N, M)
# All a_i = 1 (minimum starting score), so you can raise each up to 100.
print(" ".join(["1"] * M))
# All b_i = 100 (maximum per-hour gain), so each subject takes exactly 1 hour to hit the cap.
print(" ".join(["100"] * M))
