#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* prev;
};

class CircularDoublyLinkedList {
public:
    CircularDoublyLinkedList() {
        head = new Node();
        head->next = head;
        head->prev = head;
    }

    void append(int value) {
        Node* newNode = new Node{value, head, head->prev};
        head->prev->next = newNode;
        head->prev = newNode;
    }

    void processSequence() {
        if (isSorted()) {
            removePrimes();
            duplicateMultiplesOf12();
        } else {
            sortByFirstDigit();
        }
    }

    void display() {
        Node* current = head->next;
        while (current != head) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

private:
    Node* head;

    bool isSorted() {
        bool nonDecreasing = true, nonIncreasing = true;
        Node* current = head->next;
        int prev = current->data;
        current = current->next;

        while (current != head) {
            if (prev % 10 < current->data % 10) nonIncreasing = false;
            if (prev % 10 > current->data % 10) nonDecreasing = false;
            prev = current->data;
            current = current->next;
        }
        return nonDecreasing || nonIncreasing;
    }

    bool isPrime(int num) {
        if (num < 2) return false;
        for (int i = 2; i * i <= num; i++) {
            if (num % i == 0) return false;
        }
        return true;
    }

    void removePrimes() {
        Node* current = head->next;
        while (current != head) {
            Node* nextNode = current->next;
            if (isPrime(current->data)) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
                delete current;
            }
            current = nextNode;
        }
    }

    void duplicateMultiplesOf12() {
        Node* current = head->next;
        while (current != head) {
            if (current->data % 12 == 0) {
                Node* newNode = new Node{current->data, current->next, current};
                current->next->prev = newNode;
                current->next = newNode;
                current = newNode; // переходим к новому узлу
            }
            current = current->next;
        }
    }

    void sortByFirstDigit() {
        // Простая сортировка по первой цифре
        // Для простоты реализуем пузырьковую сортировку
        bool swapped;
        do {
            swapped = false;
            Node* current = head->next;
            while (current->next != head) {
                int firstDigit1 = getFirstDigit(current->data);
                int firstDigit2 = getFirstDigit(current->next->data);
                if (firstDigit1 > firstDigit2) {
                    std::swap(current->data, current->next->data);
                    swapped = true;
                }
                current = current->next;
            }
        } while (swapped);
    }

    int getFirstDigit(int num) {
        while (num >= 10) num /= 10;
        return num;
    }
};

int main() {
    CircularDoublyLinkedList list;
    int n, value;

    std::cout << "Введите количество натуральных чисел: ";
    std::cin >> n;

    std::cout << "Введите числа: ";
    for (int i = 0; i < n; ++i) {
        std::cin >> value;
        list.append(value);
    }

    list.processSequence();
    std::cout << "Результат: ";
    list.display();

    return 0;
}

