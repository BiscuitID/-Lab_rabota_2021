// Lab5.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>


using namespace std;


int num; // размер массива
vector<int> mas1 ;
vector<int> chet;
vector<int> nechet;

 void NEW() {
    mas1.clear();
    cout << "Enter the size of the array: ";
    cin >> num; // получение от пользователя размера массива

    int b;
    for (int i = 0; i < num; i++) {
        // Заполнение массива и вывод значений его элементов
        cout << "Enter integer value: ";
        cin >> b;
        mas1.push_back(b);
        cout << "Value of " << i << " element is " << mas1[i] << endl;
    }
    return;
}

void PRINT() {               //выводим все элементы массива
    cout << "\narray: ";

    for (int i = 0; i < num; i++) {
        cout << mas1[i] << " ";
    }
    cout << endl;
    return ;
}

void sort_vibor() {
    // Перебираем каждый элемент массива 
    for (int startIndex = 0; startIndex < mas1.size()-1; ++startIndex)
    {
        if (startIndex % 2 == 0) {
            // В переменной smallestIndex хранится индекс наименьшего значения, которое мы нашли в этой итерации.
            // Начинаем с того, что наименьший элемент в этой итерации - это первый элемент (индекс 0)
            int smallestIndex = startIndex;

            // Затем ищем элемент поменьше в остальной части массива
            for (int currentIndex = startIndex + 1; currentIndex < mas1.size(); ++currentIndex)
            {
                if (currentIndex % 2 == 0) {
                    // Если мы нашли элемент, который меньше нашего наименьшего элемента,
                    if (mas1[currentIndex] < mas1[smallestIndex])
                        // то запоминаем его
                        smallestIndex = currentIndex;
                }
            }

            // smallestIndex теперь наименьший элемент. 
                    // Меняем местами наше начальное наименьшее число с тем, которое мы обнаружили
            std::swap(mas1[startIndex], mas1[smallestIndex]);
        }
    }
    cout << "array sorted" << endl;
}

void sort_bin_vklucheniem() {
    short x;
    short left;
    short right;
    short sred;
    for (short i = 1; i < num; i++)
        if (mas1[i - 1] > mas1[i]) {
            x = mas1[i];
            left = 0;
            right = i - 1;
            do {
                sred = (left + right) / 2;
                if (mas1[sred] < x) left = sred + 1;
                else  right = sred - 1;
            } while (left <= right);
            for (short j = i - 1; j >= left; j--)
                mas1[j + 1] = mas1[j];
            mas1[left] = x;
        }
    cout << "array sorted" << endl;
}

int main()
{
    string s;               // командная строка
    while (6) {
        cout << "enter any command from list for working with array:\n";
        cout << "NEW creating a new array" << endl; 
        cout << "PRINT all elements" << endl;
        cout << "S1 - sort vibor" << endl;
        cout << "S2 - sort binarnim vklucheniem" << endl;

        cin >> s;                               // считывем команду, затем обрабатываем ее
        if (s._Equal("NEW")) NEW();
        else if (s._Equal("S2")) sort_bin_vklucheniem();
        else if (s._Equal("S1")) sort_vibor();
        else if (s._Equal("PRINT")) PRINT();

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
