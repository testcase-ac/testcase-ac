from datetime import date
a,b = [int(i) for i in input().split()]
d = date(2009, b, a).weekday()
s = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
print(s[d])
