# cs_300
//1. Rock–Paper–Scissors Game
The computer picks a random choice:
0 = Rock
1 = Paper
2 = Scissors
You enter your choice (0, 1, or 2).
The program compares both choices and tells you if you win, lose, or if it’s a tie.
Uses rand() to generate the computer’s random choice.
2. FizzBuzz
You enter a number n (up to 50).
The program prints numbers from 1 to n.
For each number:
Prints "Fizz" if divisible by 3
Prints "Buzz" if divisible by 5
Prints "FizzBuzz" if divisible by both 3 and 5
Otherwise, prints the number itself.
3. Guess the Number Game
The secret number is 7.
You try to guess it.
The program tells you if your guess is too small, too big, or correct.
You keep guessing until you get it right.
4. Fraction Operations
Defines a Fraction struct with numerator and denominator.
Supports 4 operations on fractions:
Addition (add)
Subtraction (subtract)
Multiplication (multiply)
Division (divide)
Also has a print function to show the fraction as numerator/denominator.
You enter two fractions.
The program performs all four operations and prints the results.
Main Menu
Shows options for the 4 programs and an exit option.
Lets you select which program to run.
Keeps showing the menu after each program finishes until you choose to exit.
How to Use
Run the program.
Enter the number for the option you want.
Follow the on-screen instructions.
To exit, choose option 5.
Technical Notes
#include <iostream> for input/output.
#include <cstdlib> and #include <ctime> for random number generation in Rock–Paper–Scissors.
Uses srand(time(0)) to seed the random number generator.
Uses simple loops, conditionals (if/else) and functions to organize code.
The Fraction struct implements methods instead of operator overloading for simplicity.