import random

VARIABLES = [chr(ord('a') + i) for i in range(26)] 
def make_assignment():
    var = random.choice(VARIABLES)
    expr = []

    num_terms = random.randint(1, 3)
    for i in range(num_terms):
        op = random.choice(['+', '-']) if i != 0 else ''
        const = random.choice(['', str(random.randint(1, 5))])
        var2 = random.choice(VARIABLES)
        expr.append(f"{op} {const}{var2}".strip())
    
    return f"{var} = {' '.join(expr)}"

def make_repeat_block(depth=1):
    indent = '   ' * depth
    block = []
    repeat_times = random.randint(2, 5)
    block.append(f"{indent}REPEAT {repeat_times}")
    for _ in range(random.randint(2, 4)):
        if random.random() < 0.4 and depth < 2:
            block.extend(make_repeat_block(depth + 1))
        else:
            block.append(f"{indent}   {make_assignment()}")
            if random.random() < 0.5:
                block.append(f"{indent}   PRINT {random.choice(VARIABLES)}")
    block.append(f"{indent}STOP")
    return block

def generate_testcase():
    program = ["BEGIN"]
    for _ in range(random.randint(2, 4)):
        program.append(f"   {make_assignment()}")
    
    for _ in range(random.randint(1, 2)):
        program.extend(make_repeat_block())
    
    program.append("STOP")
    return "\n".join(program)

print(generate_testcase())
