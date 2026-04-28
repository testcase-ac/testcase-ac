import asyncio, re

croatian_chars = ['c='
,'c-'
,'dz='
,'d-'
,'lj'
,'nj'
,'s='
,'z=']

word = input().rstrip()

async def substitute(char):
	global word
	word = re.sub(char, '*', word)

futures = [substitute(char) for char in croatian_chars]

loop = asyncio.get_event_loop()
loop.run_until_complete(asyncio.wait(futures))

print(len(word))