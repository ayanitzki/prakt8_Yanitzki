#include <iostream>
#include <string>
using namespace std;
struct Process
{
	int pid;
	char name[50];
	int memory;
};
struct Node
{
	Process data;
	Node* next;
	Node* prev;
};
struct HeadTailList
{
	Node* head = nullptr;
	Node* tail = nullptr;
};
void push_front(HeadTailList& list, Process process)
{
    Node* newNode = new Node;
    newNode->data = process;
    newNode->next = list.head;
    newNode->prev = nullptr;

    if (list.head == nullptr)
    {
        list.tail = newNode;
    }
    else
    {
        list.head->prev = newNode;
    }
    list.head = newNode;
}
void push_back(HeadTailList& list, Process process)
{
    Node* newNode = new Node;
    newNode->data = process;
    newNode->next = nullptr;
    newNode->prev = list.tail;

    if (list.tail == nullptr)
    {
        list.head = newNode;
    }
    else
    {
        list.tail->next = newNode;
    }
    list.tail = newNode;
}
void pop_front(HeadTailList& list)
{
    if (list.head == nullptr)
    {
        cout << "Список пуст!" << endl;
        return;
    }

    Node* temp = list.head;
    list.head = list.head->next;
    if (list.head == nullptr)
    {
        list.tail = nullptr;
    }
    else
    {
        list.head->prev = nullptr;
    }
    delete temp;
    cout << "Первый узел удален" << endl;
}
void pop_back(HeadTailList& list)
{
    if (list.head == nullptr)
    {
        cout << "Список пуст!" << endl;
        return;
    }

    Node* temp = list.tail;
    list.tail = list.tail->prev;
    if (list.tail == nullptr)
    {
        list.head = nullptr;
    }
    else
    {
        list.tail->next = nullptr;
    }
    delete temp;
    cout << "Последний узел удален" << endl;
}
void PrintProcess(Process process)
{
    cout << "Идентификационный код процесса: " << process.pid << " " << "|" << " " << "Название процесса: " << process.name << " " << "|" << " " << "Занимаемая память процессом: " << process.memory << "\n";
}
void display_forward(HeadTailList& list)
{
    if (list.head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }

    Node* current = list.head;
    while (current != nullptr)
    {
        PrintProcess(current->data);
        current = current->next;
    }
}
void display_backward(HeadTailList& list)
{
    if (list.tail == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }

    Node* current = list.tail;
    while (current != nullptr)
    {
        PrintProcess(current->data);
        current = current->prev;
    }
}
void find(HeadTailList& list, int pid)
{
    if (list.head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }

    Node* current = list.head;
    while (current != nullptr)
    {
        if (current->data.pid == pid)
        {
            cout << "Найденный элемент:" << endl;
            PrintProcess(current->data);
            cout << "Удалить этот элемент?(Y/N)" << endl;
            string choice = "";
            cin >> choice;
            if (choice == "Y")
            {
                if (current->prev != nullptr)
                {
                    current->prev->next = current->next;
                }
                else
                {
                    list.head = current->next;
                }
                if (current->next != nullptr)
                {
                    current->next->prev = current->prev;
                }

                delete current;
                cout << "Найденый узел удален" << endl;
                return;
            }
        }
        current = current->next;
    }
}
void clear(HeadTailList& list)
{
    Node* current = list.head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    list.head = nullptr;
    list.tail = nullptr;
}
Node* findMaxProcess(HeadTailList& list)
{
    if (list.head == nullptr)
    {
        cout << "Список пуст" << endl;
        return nullptr;
    }

    Node* maxNode = list.head;
    Node* current = list.head->next;
    while (current != nullptr)
    {
        if (current->data.memory > maxNode->data.memory)
        {
            maxNode = current;
        }
        current = current->next;
    }
    return maxNode;
}
void deleteLowMemory(HeadTailList& list, int limit)
{
    if (list.head == nullptr)
    {
        cout << "Список пуст" << endl;
        return;
    }

    Node* current = list.head;

    while (current != nullptr)
    {
        Node* nextNode = current->next;

        if (current->data.memory < limit)
        {
            if (current->prev != nullptr)
            {
                current->prev->next = current->next;
            }
            else
            {
                list.head = current->next;
            }
            if (current->next != nullptr)
            {
                current->next->prev = current->prev;
            }
            delete current;
        }
        current = nextNode;
    }
}
void moveMaxProcess(HeadTailList& list)
{
    Node* maxNode = findMaxProcess(list);

    if (maxNode == nullptr || maxNode == list.head)
    {
        return;
    }

    if (maxNode->prev != nullptr)
    {
        maxNode->prev->next = maxNode->next;
    }
    if (maxNode->next != nullptr)
    {
        maxNode->next->prev = maxNode->prev;
    }

    maxNode->next = list.head;
    maxNode->prev = nullptr;
    list.head->prev = maxNode;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    HeadTailList list;
    int choice = 0;
    while(true)
    {
        cout << "---МЕНЮ---" << endl;
        cout << "1. Добавить элемент в начало" << endl;
        cout << "2. Добавить элемент в конец" << endl;
        cout << "3. Удалить первый элемент" << endl;
        cout << "4. Удалить последний элемент" << endl;
        cout << "5. Вывести список" << endl;
        cout << "6. Вывсти список в обратном порядке" << endl;
        cout << "7. Найти элемент" << endl;
        cout << "8. Найти процесс, использующий больше всего памяти" << endl;
        cout << "9. Удалить процессы, использующие меньше заданного количества памяти" << endl;
        cout << "10. Переместить самый ресурсоёмкий процесс в начало списка" << endl;
        cout << "11. Очистить список" << endl;
        cout << "12. Выход" << endl;
        cin >> choice;

        if (choice == 12)
        {
            break;
        }
        else if (choice == 1)
        {
            Process process;
            cout << "Введите идентификационный номер процесса: ";
            cin >> process.pid;
            cin.ignore();
            cout << "Введите название процесса: ";
            cin.getline(process.name, 50);
            cout << "Введите кол-во памяти которое занимает процесс: ";
            cin >> process.memory;
            push_front(list, process);
        }
        else if (choice == 2)
        {
            Process process;
            cout << "Введите идентификационный номер процесса: ";
            cin >> process.pid;
            cin.ignore();
            cout << "Введите название процесса: ";
            cin.getline(process.name, 50);
            cout << "Введите кол-во памяти которое занимает процесс: ";
            cin >> process.memory;
            push_back(list, process);
        }
        else if (choice == 3)
        {
            pop_front(list);
        }
        else if (choice == 4)
        {
            pop_back(list);
        }
        else if (choice == 5)
        {
            display_forward(list);
        }
        else if (choice == 6)
        {
            display_backward(list);
        }
        else if (choice == 7)
        {
            cout << "Введите pid для поиска процесса: ";
            int pid;
            cin >> pid;
            find(list, pid);
            cout << "Найденный процесс:" << endl;
        }
        else if (choice == 8)
        {
            Node* maxNode;
            maxNode = findMaxProcess(list);
            cout << "Процесс использующий больше всего памяти:" << endl;
            PrintProcess(maxNode->data);
        }
        else if (choice == 9)
        {
            cout << "Укажите минимальный лимит памяти: ";
            int limit;
            cin >> limit;
            deleteLowMemory(list, limit);
        }
        else if (choice == 10)
        {
            moveMaxProcess(list);
        }
        else if (choice == 11)
        {
            clear(list);
            cout << "СПИСОК ОЧИЩЕН" << endl;
        }
        else
        {
            cout << "Неверный пункт меню." << endl;
        }
    }
}
