m = int(input())
d = int(input())
if m == 2:
    print('Before' if d < 18 else 'After' if d > 18 else 'Special')
else:
    print('Before' if m == 1 else 'After')
