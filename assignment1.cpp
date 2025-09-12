#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Rock Paper Scissors 
void rockPaperScissors() {
    srand(time(0));
    int compChoice = rand() % 3;
    int playerChoice;

    cout << "Enter 0 (Rock), 1 (Paper), or 2 (Scissors): ";
    cin >> playerChoice;

    cout << "Computer chose: " << compChoice << endl;

    if (playerChoiceChoice == compChoice) {
        cout << "It's a tie!" << endl;
    } else if ((playerChoice == 0 && compChoice == 2) ||
               (playerChoice == 1 && compChoice == 0) ||
               (playerChoice == 2 && compChoice == 1)) {
        cout << "You win!" << endl;
    } else {
        cout << "You lose!" << endl;
    }
}

// FizzBuzz 
void fizzBuzz() {
    int n;
    cout << "Enter value for n (up to 50): ";
    cin >> n;

    if (n > 50) {
        cout << "Number too big!" << endl;
        return;
    }

    for (int i = 1; i <= n; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            cout << "FizzBuzz ";
        } else if (i % 3 == 0) {
            cout << "Fizz ";
        } else if (i % 5 == 0) {
            cout << "Buzz ";
        } else {
            cout << i << " ";
        }
    }
    cout << endl;
}

// Guess the Number 
void guessTheNumber() {
    int secretNumber = 7;
    int guess;

    while (true) {
        cout << "Guess the number: ";
        cin >> guess;

        if (guess < secretNumber) {
            cout << "Too small" << endl;
        } else if (guess > secretNumber) {
            cout << "Too big" << endl;
        } else {
            cout << "Correct!" << endl;
            break;
        }
    }
}

// Fraction Struct
struct Fraction {
    int numerator;
    int denominator;

    Fraction add(Fraction other) {
        Fraction result;
        result.numerator = numerator * other.denominator + other.numerator * denominator;
        result.denominator = denominator * other.denominator;
        return result;
    }

    Fraction subtract(Fraction other) {
        Fraction result;
        result.numerator = numerator * other.denominator - other.numerator * denominator;
        result.denominator = denominator * other.denominator;
        return result;
    }

    Fraction multiply(Fraction other) {
        Fraction result;
        result.numerator = numerator * other.numerator;
        result.denominator = denominator * other.denominator;
        return result;
    }

    Fraction divide(Fraction other) {
        Fraction result;
        result.numerator = numerator * other.denominator;
        result.denominator = denominator * other.numerator;
        return result;
    }

    void print() {
        cout << numerator << "/" << denominator;
    }
};

void fractionDemo() {
    Fraction a, b;

    cout << "Enter numerator and denominator for first fraction: ";
    cin >> a.numerator >> a.denominator;

    cout << "Enter numerator and denominator for second fraction: ";
    cin >> b.numerator >> b.denominator;

    cout << "\na = ";
    a.print();
    cout << "\nb = ";
    b.print();

    cout << "\na + b = ";
    a.add(b).print();

    cout << "\na - b = ";
    a.subtract(b).print();

    cout << "\na * b = ";
    a.multiply(b).print();

    cout << "\na / b = ";
    a.divide(b).print();

    cout << endl;
}

// Main Menu 
int main() {
    int choice;

    while (true) {
        cout << "\n=== Main Menu ===" << endl;
        cout << "1. Rock–Paper–Scissors" << endl;
        cout << "2. FizzBuzz" << endl;
        cout << "3. Guess the Number" << endl;
        cout << "4. Fraction Operations" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        if (choice == 1) {
            rockPaperScissors();
        } else if (choice == 2) {
            fizzBuzz();
        } else if (choice == 3) {
            guessTheNumber();
        } else if (choice == 4) {
            fractionDemo();
        } else if (choice == 5) {
            cout << "Goodbye!" << endl;
            break;
        } else {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}
