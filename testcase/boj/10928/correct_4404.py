from hashlib import sha1
print(sha1(input().encode('utf-8')).hexdigest())
