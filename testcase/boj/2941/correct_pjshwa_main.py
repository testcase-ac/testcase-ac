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

loop = asyncio.new_event_loop()
asyncio.set_event_loop(loop)
futures = [loop.create_task(substitute(char)) for char in croatian_chars]
loop.run_until_complete(asyncio.wait(futures))

print(len(word))
