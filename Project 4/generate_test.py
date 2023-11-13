import random
import string

def generate_random_string(length):
    return ''.join(random.choice(string.ascii_lowercase) for _ in range(length))

def generate_test_data(file_path, num_lines):
    with open(file_path, 'w') as file:
        for _ in range(num_lines):
            random_string = generate_random_string(1024*1024)
            file.write(random_string)

if __name__ == "__main__":
    generate_test_data('test.txt',128)