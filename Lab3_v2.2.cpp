// Lab3_v2.2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include < queue >

using namespace std;

queue<int> q1, q2;
 void print() {                                       //вывод всех элементов очереди
     for (int i = q1.size(); i > 0; i -=1 ) {
         cout << q1.front();
         cout << " ";
         q2.push(q1.front());
         q1.pop();
         
     }      
     for (int i = q2.size(); i > 0; i -= 1) {
         q1.push(q2.front());
         q2.pop();

     }
     cout << " " << endl;
     cout << "--------------------------" << endl;
  }

void add() {                                // добавляем в очередь элемент
    cout << "Enter the number: " << endl;
    int i;
    cin >> i;
    q1.push(i);  
    cout << "value was added successfully" << endl;
}
void del() {
    if (q1.size() == 0) {
        cout << "The queue is empty" << endl;
        return;
    }
    else {
        q1.pop();
        cout << "value was delete successfully" << endl;
    }
}

void empty(){
    if (!q1.empty()) cout << "The queue is not empty\n";  // проверяем пуста ли очередь 
    else cout << "The queue is empty\n";
}

void calc() {
    int MAX = -2000000000;

    for (int i = q1.size(); i > 0; i -= 1) {
        q2.push(q1.front());
        if (q1.front() > MAX) MAX = q1.front();          //находим максимальный элемент
        q1.pop();
    }

    if (q2.front() != MAX) {                        //переносим в первую очередь все элементы между первым и максимальным
        q2.pop();
        if (q2.front() == MAX) {
            cout << "There are no items between the first and maximum queue items" << endl;
            cout << "--------------------------" << endl;
            for (int i = q2.size(); i > 0; i -= 1) {
                q2.pop();
            }
            return;
        }
        if (q2.front() != MAX) {
            while (q2.front() < MAX) q1.push(q2.front()), q2.pop();
            for (int i = q2.size(); i > 0; i -= 1) {
                q2.pop();
            }
            cout << "Elements are displayed" << endl;
            cout << "--------------------------" << endl;
            return;
        }
    }
    if (q2.front() == MAX){
        cout << "The first element of the queue was the maximum" << endl;
        cout << "--------------------------" << endl;
        for (int i = q2.size(); i > 0; i -= 1) {           
            q2.pop();
        }
        return;

    }
}

int main()
{
    string s;               // командная строка
    while (6) {
        cout << "enter any command from list for working with queue:\n";
        cout << "ADD new value in queue" << endl;
        cout << "DEL first value in queue" << endl;
        cout << "EMPTY checks if the queue is empty" << endl;
        cout << "PRINT all elements" << endl;
        cout << "CALC - this function transfers all items between the first and maximum to the new queue" << endl;

        cin >> s;                               // считывем команду, затем обрабатываем ее
        if (s._Equal("EMPTY")) empty();
        else if (s._Equal("ADD")) add();
        else if (s._Equal("DEL")) del();
        else if (s._Equal("CALC")) calc();
        else if (s._Equal("PRINT")) print();

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
