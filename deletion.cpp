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
     void addPolynomial(const Polynomial& other) {
        Term* current = other.head;
        while (current != nullptr) {
            insertTerm(current->coefficient, current->exponent);
            current = current->next;
        }
    }
    void deleteTerm(int exp) {
        if (head == nullptr) {
            std::cout << "Polynomial is empty. Cannot delete." << std::endl;
            return;
        }

        if (head->exponent == exp) {
            Term* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Term with exponent " << exp << " deleted." << std::endl;
            return;
        }

        Term* current = head;
        while (current->next != nullptr && current->next->exponent != exp) {
            current = current->next;
        }

        if (current->next != nullptr) {
            Term* temp = current->next;
            current->next = current->next->next;
            delete temp;
            std::cout << "Term with exponent " << exp << " deleted." << std::endl;
        } else {
            std::cout << "Term with exponent " << exp << " not found in the polynomial." << std::endl;
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
    std::cout << "Enter the exponent of the term to delete: ";
    std::cin >> exp;
    poly.deleteTerm(exp);

    std::cout << "Modified Polynomial: ";
    poly.display();

    int x;
    std::cout << "Enter value of x to evaluate polynomial: ";
    std::cin >> x;
    int result = poly.evaluate(x);
    std::cout << "Value of the polynomial for x = " << x << " is " << result << std::endl;

    std::cout<<"Thanks for checking our product";
    return 0;
}
