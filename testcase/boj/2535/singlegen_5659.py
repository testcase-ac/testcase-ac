# Maximum testcase generator for the “medal awarding” problem
# N = 100 (maximum), two countries: country 1 has 98 students (highest scores),
# country 2 has 2 students. This ensures country 1 would occupy the top 3 scores,
# but can only get two medals, so the bronze goes to country 2.

N = 100
print(N)
# Country 1: 98 students, scores 1000 down to 903
for i in range(98):
    country = 1
    student_id = i + 1
    score = 1000 - i
    print(country, student_id, score)

# Country 2: 2 students, scores 902 and 901
print(2, 1, 902)
print(2, 2, 901)
