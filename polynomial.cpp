#include <iostream>
#include <cmath>

// Structure to represent a term in the polynomial
struct Term {
    int coefficient;
    int exponent;
    Term* next;

    Term(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};

// Class to represent a polynomial using a linked list of terms
class Polynomial {
private:
    Term* head; // Pointer to the first term in the polynomial

public:
    Polynomial() : head(nullptr) {}

    // Function to insert a new term into the polynomial
    void insertTerm(int coeff, int exp) {
        Term* newTerm = new Term(coeff, exp);
        if (head == nullptr || exp > head->exponent) {
            newTerm->next = head;
            head = newTerm;
        } else {
            Term* current = head;
            while (current->next != nullptr && exp < current->next->exponent) {
                current = current->next;
            }
            newTerm->next = current->next;
            current->next = newTerm;
        }
    }

    // Function to display the polynomial
    void display() {
        if (head == nullptr) {
            std::cout << "0" << std::endl;
            return;
        }

        Term* current = head;
        while (current != nullptr) {
            if (current->coefficient > 0)
                std::cout << " + " << current->coefficient << "x^" << current->exponent;
            else
                std::cout << " - " << -current->coefficient << "x^" << current->exponent;
            current = current->next;
        }
        std::cout << std::endl;
    }

    // Function to evaluate the polynomial for a given value of x
    int evaluate(int x) {
        int result = 0;
        Term* current = head;
        while (current != nullptr) {
            result += current->coefficient * pow(x, current->exponent);
            current = current->next;
        }
        return result;
    }
};

int main() {
    Polynomial poly;

    // Take input from the user for coefficients and exponents
    int coeff, exp;
    while (true) {
        std::cout << "Enter coefficient (or 0 to stop): ";
        std::cin >> coeff;
        if (coeff == 0) {
            break;
        }
        std::cout << "Enter exponent: ";
        std::cin >> exp;
        poly.insertTerm(coeff, exp);
    }

    // Display the polynomial
    std::cout << "Polynomial: ";
    poly.display();

    // Evaluate the polynomial for a user-specified value of x
    int x;
    std::cout << "Enter the value of x to evaluate the polynomial: ";
    std::cin >> x;
    int result = poly.evaluate(x);
    std::cout << "Value of the polynomial for x = " << x << " is " << result << std::endl;

    return 0;
}