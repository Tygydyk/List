#include <sstream>
#include <iostream>
#include <string>
#include <fcntl.h>
#include <locale.h>
using namespace std;

struct List {
        int value;
        List* next;
};

List* create(int value) { // Создать список
        List* res = new List;
        res->value = value;
        res->next = 0;
        return res;
}

List * add(List* l, int value) { // Добавить элемент
        List* n = new List;
        n->value = value;
        n->next = 0;

        List* it = l;
        if (l == 0) {
                return n;
        }
        while (it->next != 0)
                it = it->next;
        it->next = n;
        return l;
}

bool find(List* l, int value, int* out, int counter=0) {
        if (l == 0)
                return false;
        if (l->value == value) {
                *out = counter;
                return true;
        }
        return find(l->next, value, out, counter + 1);
}

void printfind(List* l, int value, int counter = 0) { // Поиск позиций элемента
        if (l == 0) {
                wcout << "Список пуст";
                }
        else
        if (l->value == value) {
                wcout << counter << L" ";
        }
        printfind(l->next, value, counter + 1);
}

List* del(List*l, int value) { // Удаление элемента
        if (l == 0) {
                wcout << L"Элемент"  << value << L"отсутствует";
                return l;
        }
        if (l->value == value) {
                List* res = l->next;
                delete l;
                return res;
        }
        List* it = l;
        while (it->next != 0) {
                if (it->next->value == value) {
                        List* res = it->next;
                        it->next = res->next;
                        delete res;
                        return l;
                }
                it = it->next;
        }
        wcout << L"Элемент " << value << L" отсутствует";
	 return l;
}

void set(List*l, int index, int value) {// Установка эл-та
        if (l == 0){ 
        wcout << "List empty\n";
        }
        else { 
        if  (index == 0) {
                l->value = value;
                return;
                }
        set(l->next, index - 1, value);
        }
}


void print(List* l) {
        if (l == 0) {
                wcout << "List empty\n";
        }
        else {
                while (true) {
                        wcout << l->value;
                        l = l->next;
                        if (l == 0)
                                return;
                        wcout << "->";
                }
        }
}

void find_minimum(List* l,int* outindex, int*outvalue) {
        int min = l->value;
        int minindex = 0;
        int i = 0;
        while (l != 0) {
                if (l->value < min) {
                        min = l->value;
                        minindex = i;
                }
                l = l->next;
		     }
        *outindex = minindex;
        *outvalue = min;
}

List* sort(List* head) { // Сортировака вставками
        List* l = 0;

        while (head != 0) {
                int minindex, minvalue;
                find_minimum(head, &minindex, &minvalue);
                l = add(l, minvalue);
                head = del(head, minvalue);
        }
        return l;
}

int main(int argc, char *argv[]) {
setlocale(LC_CTYPE, "");
        List* l = 0;
	 for (int i = 1; i < argc; i++) { // Считываем аргументы
                int value;
                istringstream ss(argv[i]); // Превращаем строку в поток
                ss >> value;
                l = add(l, value); // Добавляет в список
        }

        while (true) { // Бесконечно предлагаем варианты меню
                wcout << L"\n1. Распечатать список\n2. Добавить элементы в список\n3. Удалить элемент\n4. Найти $
                wcout << L"5. Заменить элемент на другой\n6. Отсортировать элементы списка\n7. Завершить работу $
                int cmd;
                cin >> cmd; // Считываем команду

                if (cmd == 1) {
                        print(l); // Распечатать список
                }
                else if (cmd == 2) {
                        wcout << L"Введите элементы:\n";
                        int c;
                        string line;
                        getline(cin, line); // Пропускаем перевод строки
                        getline(cin, line); // Считываем строку
                        istringstream iss(line);
                        while (iss >> c) {
                                l = add(l, c); // Добавляем в список
                        }
                }
		 else if (cmd == 3) {
                        wcout << L"Введите значение элемента :\n";
                        int elem;
                        cin >> elem; // Считываем элемент
                        l = del(l, elem); // Удаляем
                }
                else if (cmd == 4) {
                        wcout << L"Введите значение элемента :\n";
                        int elem;
                        cin >> elem; // Считываем элемент
                        printfind(l, elem); // Ищем позиции
                }
                else if (cmd == 5) {
                        wcout << L"Введите позицию и новое значение:\n";
                        int elem, value;
                        cin >> elem >> value; // Считываем позицию и значение
                        set(l, elem, value); // Устанавливаем
                }
                else if (cmd == 6) {
                        l = sort(l); // Сортировка
                }
		  else if (cmd == 7) {
                        wcout << L"Вы хотите выйти из программы ? (y, n) :\n";
                        string yN;
                        cin >> yN;
                        if (yN == "y" || yN == "Y" || yN == "Yes" || yN == "yes" )
                                return 0;
                }

        }
        return 0;
}

