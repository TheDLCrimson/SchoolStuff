import random
import sys

sys.stdout = open("ALU32_test.txt", "w")

print("Op[4] A[32] B[32] Sa[5] C[32] V")

NUMBER_OF_TEST = 50

print("# and")
for test_case in range(NUMBER_OF_TEST):
    a, b, c = "", "", ""
    for _ in range(32):
        a_bit = random.randint(0, 1)
        b_bit = random.randint(0, 1)
        a += str(a_bit)
        b += str(b_bit)
        c += str(a_bit & b_bit)
    op = "0100"
    v = 0
    sa = "00000"
    print(op, a, b, sa, c, v)

print("# or")
for test_case in range(NUMBER_OF_TEST):
    a, b, c = "", "", ""
    for _ in range(32):
        a_bit = random.randint(0, 1)
        b_bit = random.randint(0, 1)
        a += str(a_bit)
        b += str(b_bit)
        c += str(a_bit | b_bit)
    op = "0101"
    v = 0
    sa = "00000"
    print(op, a, b, sa, c, v)

print("# shift left logical")
for test_case in range(NUMBER_OF_TEST):
    b = random.randint(-(2**31), 2**31 - 1)
    sa = random.randint(0, 31)
    c = (b << sa) & (2**32 - 1)
    op = "0000" if random.random() <= 0.5 else "0001"
    v = 0
    a = random.randint(-(2**31), 2**31 - 1)
    print(op, a, b, sa, c, v)

print("# xor")
for test_case in range(NUMBER_OF_TEST):
    a, b, c = "", "", ""
    for _ in range(32):
        a_bit = random.randint(0, 1)
        b_bit = random.randint(0, 1)
        a += str(a_bit)
        b += str(b_bit)
        c += str(a_bit ^ b_bit)
    op = "1010"
    v = 0
    sa = "00000"
    print(op, a, b, sa, c, v)

print("# nor")
for test_case in range(NUMBER_OF_TEST):
    a, b, c = "", "", ""
    for _ in range(32):
        a_bit = random.randint(0, 1)
        b_bit = random.randint(0, 1)
        a += str(a_bit)
        b += str(b_bit)
        c += "1" if (a_bit | b_bit) == 0 else "0"
    op = "1011"
    v = 0
    sa = "00000"
    print(op, a, b, sa, c, v)

print("# shift right logical")
for test_case in range(NUMBER_OF_TEST):
    b = random.randint(-(2**31), 2**31 - 1)
    sa = random.randint(0, 31)
    if b < 0:
        b += 2**32
    c = b >> sa
    op = "1100"
    v = 0
    a = random.randint(-(2**31), 2**31 - 1)
    print(op, a, b, sa, c, v)

print("# shift right arithmetic")
for test_case in range(NUMBER_OF_TEST):
    b = random.randint(-(2**31), 2**31 - 1)
    sa = random.randint(0, 31)
    c = b >> sa
    op = "1101"
    v = 0
    a = random.randint(-(2**31), 2**31 - 1)
    print(op, a, b, sa, c, v)

print("# ne")
for test_case in range(NUMBER_OF_TEST):
    a = random.randint(-(2**31), 2**31 - 1)
    b = random.randint(-(2**31), 2**31 - 1)
    b = a if random.random() <= 0.5 else b
    c = 1 if a != b else 0
    op = "1000"
    v = 0
    sa = "00000"
    print(op, a, b, sa, c, v)

print("# eq")
for test_case in range(NUMBER_OF_TEST):
    a = random.randint(-(2**31), 2**31 - 1)
    b = random.randint(-(2**31), 2**31 - 1)
    b = a if random.random() <= 0.5 else b
    c = 1 if a == b else 0
    op = "1001"
    v = 0
    sa = "00000"
    print(op, a, b, sa, c, v)

print("# le")
for test_case in range(NUMBER_OF_TEST):
    a = random.randint(-(2**31), 2**31 - 1)
    c = 1 if a <= 0 else 0
    op = "1110"
    v = 0
    sa = "00000"
    b = random.randint(-(2**31), 2**31 - 1)
    print(op, a, b, sa, c, v)

print("# gt")
for test_case in range(NUMBER_OF_TEST):
    a = random.randint(-(2**31), 2**31 - 1)
    c = 1 if a > 0 else 0
    op = "1111"
    v = 0
    sa = "00000"
    b = random.randint(-(2**31), 2**31 - 1)
    print(op, a, b, sa, c, v)

print("# subtract")
for test_case in range(NUMBER_OF_TEST):
    a = random.randint(-(2**31), 2**31 - 1)
    b = random.randint(-(2**31), 2**31 - 1)
    op = "0110" if random.random() <= 0.5 else "0111"
    c = a - b
    v = 0
    if c >= 2**31:
        v = 1
        c -= 2**32
    elif c < -(2**31):
        v = 1
        c += 2**32
    sa = "00000"
    print(op, a, b, sa, c, v)

print("# add")
for test_case in range(NUMBER_OF_TEST):
    a = random.randint(-(2**31), 2**31 - 1)
    b = random.randint(-(2**31), 2**31 - 1)
    op = "0010" if random.random() <= 0.5 else "0011"
    c = a + b
    v = 0
    if c >= 2**31:
        v = 1
        c -= 2**32
    elif c < -(2**31):
        v = 1
        c += 2**32
    sa = "00000"
    print(op, a, b, sa, c, v)
