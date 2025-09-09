import random
import sys

sys.stdout = open("Add32_test.txt", "w")

print("A[32] B[32] Cin C[32] V")

NUMBER_OF_TEST = 200

print("# Add 32")
for test_case in range(NUMBER_OF_TEST):
    a = random.randint(-(2**31), 2**31 - 1)
    b = random.randint(-(2**31), 2**31 - 1)
    cin = random.randint(0, 1)
    v = 0
    c = a + b + cin
    if c >= 2**31:
        v = 1
        c = c - 2**32
    elif c < -(2**31):
        v = 1
        c = c + 2**32
    print(a, b, cin, c, v)
