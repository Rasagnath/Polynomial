#include <iostream>
#include <cmath>
struct Term {
    int coefficient;
    int exponent;
    Term* next;

    Term(int coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};
class Polynomial {
private:
    Term* head;

public:
    Polynomial() : head(nullptr) {}
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
    std::cout << "Polynomial: ";
    poly.display();
    int x;
    std::cout << "Enter the value of x to evaluate the polynomial: ";
    std::cin >> x;
    int result = poly.evaluate(x);
    std::cout << "Value of the polynomial for x = " << x << " is " << result << std::endl;

    return 0;
}