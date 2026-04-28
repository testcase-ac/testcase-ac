input()
s = input().rstrip()
if len(s) <= 25:
  print(s)
else:
  ss = s[11:-11]
  if ss.count('.') == 0 or (ss.count('.') == 1 and ss[-1] == '.'):
    print(s[0:11] + '...' + s[-11:])
  else:
    print(s[0:9] + '......' + s[-10:])
