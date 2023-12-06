#include <iostream>
#include <string>
#include <cstdlib> // Для генерации случайных значений
#include <ctime>   // Для инициализации генератора случайных чисел

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
};

template <typename T>
class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

public:
    // Конструкторы и деструктор
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    LinkedList(const LinkedList& other);

    LinkedList(size_t count);
    size_t getSize() const;
    ~LinkedList();

    // Операция присваивания
    LinkedList& operator=(const LinkedList& other);

    // Методы для добавления элементов
    void push_tail(const T& value);

    void push_tail(const LinkedList& other);

    void push_head(const T& value);

    void push_head(const LinkedList& other);

    // Методы для удаления элементов
    void pop_head();

    void pop_tail();

    void delete_node(const T& value);

    // Операция доступа по индексу
    T& operator[](size_t index);

    const T& operator[](size_t index) const;

    // Метод для вывода списка на экран
    void print() const;
};

// Реализация методов класса LinkedList
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), size(0) {
    Node<T>* current = other.head;
    while (current != nullptr) {
        push_tail(current->data);
        current = current->next;
    }
}

template <typename T>
LinkedList<T>::LinkedList(size_t count) : head(nullptr), tail(nullptr), size(0) {
    // Инициализация генератора случайных чисел
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    for (size_t i = 0; i < count; ++i) {
        T randomValue = static_cast<T>(std::rand() % 100); // Генерация случайного значения
        push_tail(randomValue);
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    while (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        // Очистка текущего списка
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;

        // Копирование элементов из другого списка
        Node<T>* current = other.head;
        while (current != nullptr) {
            push_tail(current->data);
            current = current->next;
        }
    }
    return *this;
}

template <typename T>
void LinkedList<T>::push_tail(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (tail == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    ++size;
}

template <typename T>
void LinkedList<T>::push_tail(const LinkedList& other) {
    Node<T>* current = other.head;
    while (current != nullptr) {
        push_tail(current->data);
        current = current->next;
    }
}

template <typename T>
void LinkedList<T>::push_head(const T& value) {
    Node<T>* newNode = new Node<T>(value);
    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    ++size;
}

template <typename T>
void LinkedList<T>::push_head(const LinkedList& other) {
    LinkedList<T> temp;

    Node<T>* current = other.head;
    // перебираем список other и вставляем элементы во временный список temp
    while (current != nullptr) {
        temp.push_head(current->data);
        current = current->next;
    }
    current = temp.head;
    // перебираем временный список и вставляем элементы в текущий список в правильном порядке
    while (current != nullptr) {
        push_head(current->data);
        current = current->next;
    }
}

template <typename T>
void LinkedList<T>::pop_head() {
    if (head != nullptr) {
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }
        delete temp;
        --size;
    }
}

template <typename T>
void LinkedList<T>::pop_tail() {
    if (tail != nullptr) {
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }
        delete temp;
        --size;
    }
}

template <typename T>
void LinkedList<T>::delete_node(const T& value) {
    Node<T>* current = head; // начинаем сначала списка
    while (current != nullptr) {
        // проверяем, содержит ли текущий узел значение для удаления
        if (current->data == value) {
            // если у текущего узла есть предыдущий узел, обновляем указатель next
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            }
            // если текущий узел является головой списка, обновляем указатель head
            else {
                head = current->next;   
            }
            // если у текущего узла есть следующий узел, обновляем указатель prev
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            }
            // если текущий узел является концом списка, обновляем указатель tail
            else {
                tail = current->prev;
            }
            // удаляем текущий узел
            delete current;
            --size;
            break;
        }
        current = current->next;
    }
}

template <typename T>
T& LinkedList<T>::operator[](size_t index) {
    if (index >= 0 && index < size) {
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
const T& LinkedList<T>::operator[](size_t index) const {
    if (index >= 0 && index < size) {
        Node<T>* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
void LinkedList<T>::print() const {
    Node<T>* current = head;
    while (current != nullptr) {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << std::endl;
}
template <typename T>
size_t LinkedList<T>::getSize() const {
    return size;
}
// Пример использования

int main() {
    LinkedList<std::string> studentList;

    // Добавление элементов в список
    studentList.push_tail("Ivanov Ivan 3 85");
    studentList.push_tail("Petrov Petr 2 78");
    studentList.push_tail("Sidorov Sidr 1 90");
    studentList.push_tail("Ivanov Ivan 3 85"); // Дубликат
    studentList.push_tail("Smirnov Smit 4 92");
    studentList.push_tail("Petrov Petr 2 78"); // Дубликат

    std::cout << "Original list:" << std::endl;
    studentList.print();

    std::cout << "\nSize of the list: " << studentList.getSize() << std::endl;

    // Удаление дубликатов
    for (size_t i = 0; i < studentList.getSize(); ++i) {
        for (size_t j = i + 1; j < studentList.getSize(); ++j) {
            if (studentList[i] == studentList[j]) {
                studentList.delete_node(studentList[j]);
                --j; // Перепроверяем элемент j, так как после удаления список сдвинулся
            }
        }
    }

    std::cout << "\nList after removing duplicates:" << std::endl;
    studentList.print();
    std::cout << "\nSize of the list after removing duplicates: " << studentList.getSize() << std::endl;

    return 0;
}
