s = input().split(" (")
print(f"{s[0]}\n{"-" if len(s) == 1 else s[1][:-1]}")
