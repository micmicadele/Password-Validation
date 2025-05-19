# Password Tasks - Implementation Overview

## Task C - Continuous Password Prompt

In this task, the program repeatedly asks the user to enter a password until the correct one is entered.

- **Python:**  
  Utilized the `getpass` module’s `getpass()` function to securely hide user input. This method disables echoing typed characters but does not show any masking (no `*` characters appear). This provides simple, secure input across platforms without extra code. The program loops indefinitely until the correct password (`default123`) is entered.

- **C:**  
  Used POSIX terminal control (`termios`) to disable input echo and switch the terminal to raw mode. This enabled capturing each character typed without displaying it directly. The program manually prints `*` for each entered character to visually mask the password. Backspace handling was implemented to allow users to delete characters. The loop continues until the entered password matches `default123`.

---

## Task D - Login System with Maximum Attempts

This task simulates a login with a limited number of password attempts (3 maximum).

- **Python:**  
  Again used the `getpass.getpass()` function to hide password input during typing. The program tracks the number of attempts, decrementing after each incorrect input. It informs the user how many attempts remain after each failure. If the correct password (`admin123`) is entered within three tries, it prints "Login successful" and exits. Otherwise, it prints "Access denied" after all attempts are used.

- **C:**  
  Similar to Task C, terminal echo is disabled using `termios` and each input character is masked by printing `*`. The program tracks the number of remaining attempts and provides real-time feedback on attempts left after each failure. Backspace functionality is supported to allow editing input. If the user enters the correct password within three attempts, the program prints "Login successful" and exits; otherwise, it prints "Access denied."

---

## Summary

- Python’s `getpass` module provides easy and portable password hiding but does not support displaying masking characters like `*`. It handles input securely with minimal code.  
- C allows low-level terminal control enabling visible password masking with asterisks and precise input handling such as backspace support, but requires more complex code and works primarily on Unix-like systems.  
- Both implementations highlight core concepts of user authentication loops, input privacy, and limited attempt logic for login systems.

