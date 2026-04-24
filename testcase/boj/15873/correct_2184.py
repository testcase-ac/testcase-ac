s = input()
if len(s) == 4:
    print(20)
elif len(s) == 3:
    print(int(s[2])+10 if s[:2] == '10' else int(s[0])+10)
else:
    print(int(s[0])+int(s[1]))
