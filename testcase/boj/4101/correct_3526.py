import sys;[exit() if l=="0 0\n" else print('Yes') if list(map(int,l.split()))[0]>list(map(int,l.split()))[1] else print('No') for l in sys.stdin]
