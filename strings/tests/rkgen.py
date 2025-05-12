import random

TEXT_LENGTHS = [1_000_000, 2_000_000, 4_000_000, 8_000_000, 16_000_000]
PATTERN_LENGTHS = [3, 10, 30, 1_000, 100_000]
ALPHABET_SIZES = [26, 2, 5, 1, 1]

ALPHABET = ''.join([chr(i) for i in range(ord('a'), ord('z') + 1)])

def print_random_string(length, alphabet_size):
    alphabet = ALPHABET[:alphabet_size]
    print(''.join(random.choice(alphabet) for _ in range(length)))

REPETITION = 4
TEST_CASES = REPETITION * len(TEXT_LENGTHS)
print(TEST_CASES)
for _ in range(REPETITION):
    for t in range(len(TEXT_LENGTHS)):
        print_random_string(TEXT_LENGTHS[t], ALPHABET_SIZES[t]) # text
        print_random_string(PATTERN_LENGTHS[t], ALPHABET_SIZES[t]) # pattern