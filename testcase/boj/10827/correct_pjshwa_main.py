import sys
a,b=sys.stdin.readline().split()
b = int(b)
floats = 0
if '.' not in a: print(int(a)**b)
else:
    ai,af=a.split('.')
    floats=len(af)*b
    a=int(''.join((ai,af)))
    result=str(a**b)
    l_r = len(result)
    if l_r<floats+1: result='0'*(floats+1-l_r)+result
    rresult="{}.{}".format(result[:-floats],result[-floats:])
    print(rresult)