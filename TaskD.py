import sys
import tty
import termios

def input_password(prompt='Password: '):
    sys.stdout.write(prompt)
    sys.stdout.flush()
    password = ""
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        while True:
            ch = sys.stdin.read(1)
            if ch in ('\n', '\r'):
                print()
                break
            elif ch == '\x7f':  
                if len(password) > 0:
                    password = password[:-1]
                    sys.stdout.write('\b \b')
                    sys.stdout.flush()
            else:
                password += ch
                sys.stdout.write('*')
                sys.stdout.flush()
    finally:
        termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
    return password

correct_password = "admin123"
max_attempts = 3
attempts = 0

while attempts < max_attempts:
    user_input = input_password("Enter password: ")
    if user_input == correct_password:
        print("Login successful")
        break
    else:
        attempts += 1
        attempts_left = max_attempts - attempts
        if attempts_left > 0:
            print(f"Incorrect password. Attempts left: {attempts_left}")
        else:
            print("Access denied")
