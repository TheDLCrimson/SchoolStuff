import random
import sys

sys.stdout = open("LeftShift32_test.txt", "w")

print("B[32] Sa[5] Cin C[32]")

NUMBER_OF_TEST = 200

print("#Left Shift 32")
for test_case in range(NUMBER_OF_TEST):
    b = random.randint(0, 2**32 - 1)
    sa = random.randint(0, 31)
    cin = random.randint(0, 1)
    carrybits = cin * ((1 << sa) - 1)
    c = ((b << sa) & (2**32 - 1)) | carrybits
    print(f"{b} {sa} {cin} {c}")
