s = input()
a, b = s.count(':-)'), s.count(':-(')
if not a and not b:
    print('none')
elif a > b:
    print('happy')
elif a < b:
    print('sad')
else:
    print('unsure')
