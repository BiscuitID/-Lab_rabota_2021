// Lab2_v2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
using namespace std;
//=============================================================LIST=====================================================================

struct Car {
    const int      price_per_liter_of_gasoline = 10; //цена за литр бензина
    const int      price_for_filling_oil = 15; //цена за заливку масла
    int       engine_power; // мощность двигателя
    string    _2sd_name;  //фамилия
    string    car_model; // марка автомобиля
    string    gasoline_brand; // марка бензина
    int       volume_of_the_tank; //объем бака
    int       gasoline_residue; //остаток бензина
    int       oil_volume; //объем масла
    int       date_of_inspection[3]; // дата техосмотра
    long long sum;                      // будем хранить также дату в виде суммы дней, для удобства сортировки и поиска
    Car* next = NULL;
};

Car* carList = NULL;

bool compareString(string s1, string s2) {                              // компаратор для строковых параметров при сортировке
    for (int i = 0; i < min(s1.length(), s2.length()); i++) {
        if (s1[i] < s2[i]) return true;
        if (s1[i] > s2[i]) return false;
    }
    return true;
}

bool comparator(Car* a, Car* b) {                                 // компаратор для сортировки списка
    if (a->engine_power != b->engine_power) return a->engine_power < b->engine_power;
    if (a->date_of_inspection != b->date_of_inspection) return a->date_of_inspection < b->date_of_inspection;
    return compareString(a->_2sd_name, b->_2sd_name);
}

void print(Car* prsn) {                                      // вывод информации о машине
    if (prsn == NULL) return;
    cout << "surname: " << prsn->_2sd_name << endl;
    cout << "car model: " << prsn->car_model << endl;
    cout << "engine power: " << prsn->engine_power << endl;
    cout << "gasoline brand: " << prsn->gasoline_brand << endl;
    cout << "date of inspection: " << prsn->date_of_inspection[0] <<                            // вывод даты в формате чч.мм.гггг
        "." << prsn->date_of_inspection[1] << "." << prsn->date_of_inspection[2] << endl;
    cout << "volume of the tank: " << prsn->volume_of_the_tank << endl;
    cout << "gasoline residue: " << prsn->gasoline_residue << endl;
    cout << "oil volume: " << prsn->oil_volume << endl;
    cout << "price per liter of gasoline: " << prsn->price_per_liter_of_gasoline << endl;
    cout << "price for filling oil: " << prsn->price_for_filling_oil << endl;
}

void find(int dep_num, long long date_empl, string srnm) {              // поиск информации о машине по параметрам
    if (carList == NULL) {
        cout << "List is empty" << endl;
        return;
    }
    Car* current = carList;
    while (current != NULL) {
        if (current->_2sd_name._Equal(srnm) && current->engine_power == dep_num && current->sum == date_empl) break;
        current = current->next;
    }
    if (current != NULL) print(current);                         // и вывод информации в консоль
    else cout << "There is no such machine :(" << endl;
}

long long dateToInt(string date, Car* prsn = NULL) {       // приведение даты к числовому типу и вычисление суммы дней даты
    char c; long long res = 0; int temp, idx = -1, tmp[3];
    for (short i = 0; i < 3; i++) {
        temp = 0; idx++;
        while (idx < date.size()) {
            c = date[idx];
            if (c == '.' || c == '\n') break;
            if (c < '0' || c > '9') return -1;
            temp += (c - 48); temp *= 10; idx++;
        }
        if (i < 2 && c != '.') return -1;
        if (prsn != NULL) prsn->date_of_inspection[i] = temp / 10;
        tmp[i] = temp / 10;
    }
    res = tmp[0] + tmp[1] * 31 + tmp[2] * 365;
    if (prsn != NULL) prsn->sum = res;
    return res;
}

bool addPerson() {              // добавление нового профиля в список и сортировка
    Car* prsn = new Car[1]; long long tmp;
    string temp;
    cout << "enter person' surname" << endl;
    cin >> prsn->_2sd_name;

    cout << "enter car' car model" << endl;
    cin >> prsn->car_model;

    cout << "enter car' engine power (for eaxmple 500)" << endl;
    cin >> prsn->engine_power;

    cout << "enter car' gasoline brand (for eaxmple 95)" << endl;
    cin >> prsn->gasoline_brand;

    cout << "enter car' date of employment dd.mm.yyyy" << endl;
    cin >> temp; tmp = dateToInt(temp, prsn);
    if (tmp < 0) return false;

    cout << "enter car' volume of the tank (for example 50)" << endl;
    cin >> prsn->volume_of_the_tank;

    cout << "enter car' gasoline residue (for example 15)" << endl;
    cin >> prsn->gasoline_residue;

    cout << "enter car' oil volume (for example 5)" << endl;
    cin >> prsn->oil_volume;

    if (carList == NULL) {
        carList = prsn;
        return true;
    }

    Car* current = carList, * prev = NULL;
    while (current->next != NULL) {
        if (comparator(prsn, current->next)) break;
        prev = current;
        current = current->next;
    }

    if (current->next == NULL) {
        if (comparator(prsn, current)) {
            if (current == carList) {
                carList = prsn;
                carList->next = current;
            }
            else {
                prev->next = prsn;
                prev->next->next = current;
            }
        }
        else current->next = prsn;
    }
    else {
        Car* tmp = current->next;
        current->next = prsn;
        prsn->next = tmp;
    }

    return true;
}

void printAll() {                               // вывод всего списка
    if (carList == NULL) {
        cout << "List is empty" << endl;
        return;
    }
    cout << "================================================" << endl;
    Car* current = carList;
    while (current != NULL) {
        print(current);
        cout << "================================================" << endl;
        current = current->next;
    }
}

void list() {
    string s;                                       // командная строка
    string srnm, sDt; int dp_nm; long long dt;
    while (7) {
        cout << "enter any command from list for working with LIST:\n";
        cout << "ADD for adding new car in list" << endl;                    // данные сортируются при добавлении
        cout << "FIND for searching a car in list" << endl;
        cout << "PRINT_ALL for outputing list" << endl;
        cout << "BACK for comming back to main menu" << endl;

        cin >> s;
        if (s._Equal("BACK")) return;
        else if (s._Equal("PRINT_ALL")) printAll();
        else if (s._Equal("FIND")) {
            cout << "enter person' surname " << endl;
            cin >> srnm;
            cout << "enter car' engine power" << endl;
            cin >> dp_nm;
            cout << "enter car' date of inspection dd.mm.yyyy" << endl;
            cin >> sDt;
            dt = dateToInt(sDt);
            if (dt < 0) {
                cout << "incorrect format of date" << endl;
                continue;
            }
            find(dp_nm, dt, srnm);
        }
        else if (s._Equal("ADD")) {
            if (!addPerson()) cout << "incorrect data" << endl;
            else cout << "car' profile was added successfully" << endl;
        }
        else cout << "no such command" << endl;
    }
}
//===============================================END OF LIST===================================================================================

//===================================================STACK==============================================================================

struct node {
    node* prev = NULL;                          // ссылка на предыдущий элемент
    long long value;                            // значение текущей ячейки стека
};

node* Stack = NULL;
long long buffer;

bool add(long long a) {                         // добавление элемента в стек
    if (Stack == NULL) Stack = new node[1];
    else {
        node* temp = new node[1];
        if (temp == NULL) return false;
        temp->prev = Stack;
        Stack = temp;
    }
    Stack->value = a;
    return true;
}

bool pop() {                                // получить верхний элемент из стека, удалив его                        
    if (Stack == NULL) return false;
    buffer = Stack->value;
    Stack = Stack->prev;
    return true;
}

void clear() {                              // очистить стек, выводя его элементы в консоль
    if (Stack == NULL) {
        return;
    }
    cout << "elements of stack:" << endl;
    while (Stack != NULL) {
        cout << Stack->value << " ";
        Stack = Stack->prev;
    }
    cout << endl;
}

void calc() {                                       // считаем сумму нечетных чисел в стеке, очищая его
    long long res = 0;
    long long verh = 0;
    long long niz = 0;
    cout << "elements of stack:" << endl;
    while (Stack != NULL) {
        if (Stack->value = Stack->value) verh += Stack->value;
        niz += 1;
        cout << Stack->value << " ";
        Stack = Stack->prev;
    }
    res = verh / niz;
    cout << endl;
    add(res);
    cout << "elements of stack:" << endl;
    while (Stack != NULL) {
        cout << Stack->value << " ";
        Stack = Stack->prev;
    }
    cout << endl;
    cout << "result was added in stack" << endl;
}

void stack() {
    string s;               // командная строка
    while (6) {
        cout << "enter any command from list for working with stack:\n";
        cout << "PUSH N to add new value in stack (for example: push 5)" << endl;
        cout << "POP to delete value from head of stack and print it in console" << endl;
        cout << "CLEAR for clearing stack" << endl;
        cout << "CALC - this function calculates arithmetic mean of numbers by clearing stack and adds result in Stack" << endl;
        cout << "BACK for coming back to main menu" << endl;

        cin >> s;                               // считывем команду, затем обрабатываем ее
        if (s._Equal("POP")) {
            if (pop()) cout << "Element " << buffer << " was deleted successfully" << endl;
            else cout << "stack is empty" << endl;
        }
        else if (s._Equal("CLEAR")) clear(), cout << "stack was cleared" << endl;
        else if (s._Equal("CALC")) calc();
        else if (s._Equal("BACK")) return;
        else if (s._Equal("PUSH")) {
            cin >> buffer;
            if (add(buffer)) cout << "value was added successfully" << endl;
        }
        else cout << "incorrect command" << endl << endl;
    }
}

//============================================================END OF STACK==============================================================

int main()
{
    cout << "Ostroverkh Danil KE-203 Variant 14, lab2\n";
    while (3) {
        cout << "=========================================================================" << endl;
        cout << "for checking list exercise enter 0\nfor checking stack exercise enter 1\n";
        cout << "enter 2 for finishing\n";
        string s; cin >> s;
        switch ((int)s[0] - 48)
        {
        case 0:
            list();
            break;
        case 1:
            stack();
            break;
        case 2:
            return 0;
        default:
            cout << "no such command\n";
        }
    }

}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
