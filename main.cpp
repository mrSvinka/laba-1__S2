/*
Ввести последовательность натуральных чисел. Если последовательность упорядочена по неубыванию или по невозрастанию последней цифры,
 удалить из последовательности простые числа, и продублировать числа кратные 12.
  В противном случае упорядочить последовательность по неубыванию первой цифры.
  Последовательность хранить в двусвязном циклическом списке с фиктивным элементом
*/


#include <iostream>
//делаем 2связ список
struct Node 
{
    int data;
    Node* next;
    Node* prev;
};
//цыклическая структура


class L_List 
{
    Node* sent;

public:
    L_List() 
    {
        sent = new Node();
        sent->next = sent;
        sent->prev = sent;
    }


//создание новой чати списка и добовление в конеец
    void insert(int value) 
    {
        Node* newNode = new Node{value, sent, sent->prev};
        sent->prev->next = newNode;
        sent->prev = newNode;
    }


// сортированнасть
    bool isSorted() 
    {
        Node* temp = sent->next;
        bool vozr = true, ybiv = true;

        while (temp != sent) 
        {
            if (temp->next != sent) 
            {
                if (temp->data > temp->next->data) vozr = false;
                if (temp->data < temp->next->data) ybiv = false;
            }
            temp = temp->next;
        }
        return vozr || ybiv;
    }


//простые числша
    bool isPrime(int num) 
    {
        if (num <= 1) return false;
        for (int i = 2; i * i <= num; i++)
            if (num % i == 0) return false;
        return true;
    }


    int F_Digit(int num) 
    {
        while (num >= 10) num /= 10;
        return num;
    }

//сорт про возростанию
    void F_Digit() 
    {


        Node* current = sent->next;
        while (current != sent) 
        {
            Node* nextNode = current->next;
            while (nextNode != sent) 
            {
                if (F_Digit(current->data) > F_Digit(nextNode->data)) 
                {
                    std::swap(current->data, nextNode->data);
                }
                nextNode = nextNode->next;
            }
            current = current->next;
        }
    }


    void processList() 
    {
        if (isSorted()) 
        {
            Node* current = sent->next;
            while (current != sent) 
            {
                if (isPrime(current->data)) 
                {
                    Node* toDelete = current;
                    current->prev->next = current->next;
                    current->next->prev = current->prev;
                    current = current->next;
                    delete toDelete;
                } 
                else if (current->data % 12 == 0) 
                {
                    insert(current->data); // дубляж
                    current = current->next;
                } 
                else 
                {
                    current = current->next;
                }
            }
        } 
        else 
        {
            // Упорядочить по возрост.
            F_Digit();
        }
    }


    void display() 
    {
        Node* temp = sent->next;
        while (temp != sent) 
        {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

};

int main() 
{
    L_List list;
    int n, value;
//данные


    std::cout << "количество чисел: ";
    std::cin >> n;
    std::cout << "числа: \n";

    for (int i = 0; i < n; ++i) 
    {
        std::cin >> value;
        list.insert(value);
    }


//результат
    list.processList();
    std::cout << "результат: ";
    list.display();

    return 0;
}
