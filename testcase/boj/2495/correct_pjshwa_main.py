for _ in range(3):
    string = input().rstrip()
    first_char = string[0]
    streak = 1
    max_streak = 1
    for char in string[1:]:
        if char == first_char:
            streak += 1
        else:
            first_char = char
            if max_streak < streak: max_streak = streak
            streak = 1
    if max_streak < streak: max_streak = streak
    print(max_streak)