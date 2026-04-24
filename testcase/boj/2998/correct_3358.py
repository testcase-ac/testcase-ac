a = input()
if len(a)%3:
    a = '0'*(3-len(a)%3) + a
mp = {'000': 0, '001': 1, '010': 2, '011': 3, '100': 4, '101': 5, '110': 6, '111': 7}
print(''.join(str(mp[a[i:i+3]]) for i in range(0, len(a), 3)))
        
