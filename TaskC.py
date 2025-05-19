import sys
import getpass

def input_password(prompt='Password: '):
    import sys
    import tty
    import termios
  
    sys.stdout.write(prompt)
    sys.stdout.flush()
    password = ""
    fd = sys.stdin.fileno()
    old_settings = termios.tcgetattr(fd)
    try:
        tty.setraw(fd)
        while True:
            ch = sys.stdin.read(1)
            if ch == '\n' or ch == '\r':
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
  
correct_password = "default123"

while True:
    user_input = input_password("Enter password: ")
    if user_input == correct_password:
        print("Access granted")
        break
    else:
        print("Incorrect password, try again.")
