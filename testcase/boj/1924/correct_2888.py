from datetime import date
a,b = [int(i) for i in input().split()]
d = date(2007, a, b).weekday()
s = ["MON", "TUE", "WED", "THU", "FRI", "SAT","SUN"]
print(s[d])
