// Lab4.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <map>
#include <random>
#include <string>
#include <vector>
using namespace std;


//===============================================EXERCISE 1=========================================================
map<string, pair<char, int>> hash_ex1;
int multiplier;                         // множитель для вычисления хэша

string getHash(int i) {                         // вычисление хэш-кода буквы
    string res = to_string(i * multiplier);
    while (res.size() < 8) res += "0";          // хэш-код должен быть фиксированной длины. мной была выбрана длина 8
    return res;
}

void init_table_ex1() {
    multiplier = rand() % 1000;
    for (int i = 'a'; i <= 'z'; i++) hash_ex1[getHash(i)] = make_pair((char)i, 0);          // добавление строчных букв в таблицу
    for (int i = 'A'; i <= 'Z'; i++) hash_ex1[getHash(i)] = make_pair((char)i, 0);          // добавление прописных букв в таблицу
}

void enterString(string s) {                                    // подсчет количества букв в строке
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ' || s[i] == '.' || s[i] == ',' || s[i] == '\n' || s[i] == '-' || s[i] == '!' || s[i] == '?' || s[i] == ':') continue; // пробел, знаки и тире препинания не обрабатываются
        if (s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z') {   // если найдена буква или символ не из английского алфавита
            cout << "not all letters are english in this string" << endl;       // то добавление прекращается
            return;
        }
        hash_ex1[getHash(s[i])].second++;
    }
}

void getInfOfLetter() {                                                                 // получение информации о букве
    cout << "enter any english letter for getting information about it" << endl;
    char c; cin >> c;
    if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z') {
        cout << "it isn't an english letter" << endl;
        return;
    }

    string hash = getHash(c);
    pair<char, int> temp = hash_ex1[hash];
    cout << "hash: " << hash << "; letter: " << temp.first << "; count: " << temp.second << endl;
}

void outputTable_ex_1() {                       // вывод таблицы
    cout << "hash-table:" << endl;
    int idx = 1;
    for (map<string, pair<char, int>>::iterator i = hash_ex1.begin(); i != hash_ex1.end(); i++, idx++) {
        cout << idx << ") hash: " << (*i).first << "; letter: " << (*i).second.first << "; count: " << (*i).second.second << endl;
    }
}

void ex_1() {
    init_table_ex1();

    char cmd; string s;
    while (9)
    {
        cout << "enter 0 to clear hash-table and back to main menu" << endl
            << "enter 1 for starting enter of a string" << endl
            << "enter 2 to clear hash-table" << endl
            << "enter 3 for getting information about a letter from hash-table" << endl
            << "enter 4 to output hash-table" << endl;

        cin >> cmd;
        switch ((int)(cmd - '0'))
        {
        case 0:
            return;
        case 1:
            cout << "enter any string which consists of only english letters" << endl;
            getline(cin, s, '.');
            enterString(s);
            cout << "string was added" << endl;
            break;
        case 2:
            hash_ex1.clear();
            init_table_ex1();
            cout << "hash-table was cleared" << endl;
            break;
        case 3:
            getInfOfLetter();
            break;
        case 4:
            outputTable_ex_1();
            break;
        default:
            cout << "no such command" << endl << endl;
        }
    }
}
//============================================================================================================
//==================================================EXERCISE 2================================================

int len;
vector<vector<string>> hash_ex2;

int getHash_ex2(string s) {                     // вычисление хэша слова
    if (s.size() <= 0) return -1;

    int res = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ' || s[i] == '.' || s[i] == ',' || s[i] == '\n' || s[i] == '-' || s[i] == '!' || s[i] == '?' || s[i] == ':') continue; // пробел, знаки и тире препинания не обрабатываются
        if (s[i] < 'A' || (s[i] > 'Z' && s[i] < 'a') || s[i] > 'z') return -1; // если найдена буква или символ не из английского алфавита, то ввод прекращается
        res += s[i];
    }
    return res % len;
}

bool enterText() {                      // ввод текста
    string word;
    int hash;
    while (7) {
        cin >> word;
        if (word._Equal("ENDTEXT")) break;
        hash = getHash_ex2(word);
        if (hash < 0) {
            cout << "not all letters are english in this string" << endl;
            return false;
        }
        hash_ex2[hash].push_back(word);
    }
    return true;
}

void outTable_ex2() {                   // вывод таблицы
    cout << "hash-table:" << endl;
    for (int i = 0; i < len; i++) {
        cout << i << ") ";
        if (hash_ex2[i].size() <= 0) cout << "__EMPTY__";
        else for (int j = 0; j < hash_ex2[i].size(); j++) {
            cout << hash_ex2[i][j];
            if (j < hash_ex2[i].size() - 1) cout << ", ";
        }
        cout << endl;
    }
}

void searchWord(string s) {                 // поиск слова в таблице
    int hash = getHash_ex2(s);
    if (hash < 0) {
        cout << "no such word" << endl;
        return;
    }

    for (int i = 0; i < hash_ex2[hash].size(); i++) {
        if (hash_ex2[hash][i]._Equal(s)) {
            cout << "the word \"" << s << "\" has hash [" << hash << "; " << i << "]" << endl;
            return;
        }
    }
    cout << "no such word" << endl;
}

void deleteWordsStartingWith(char s) {                               // удаление слов, начинающихся на определенную букву
    vector<string> temp;
    for (int i = 0; i < hash_ex2.size(); i++) {
        for (vector<string>::iterator j = hash_ex2[i].begin(); j != hash_ex2[i].end(); j++) {
            if ((*j)[0] != s) temp.push_back(*j);
        }
        hash_ex2[i] = temp;
        temp.clear();
    }
    outTable_ex2();
}

void ex_2() {

    cout << "set size of hash-table by entering a number" << endl;
    cin >> len;
    if (len <= 0) {
        cout << "ERROR: size <= 0 !!!" << endl;
        return;
    }
    hash_ex2.resize(len);

    cout << "enter a text which cosist of only english letters" << endl;
    cout << "for finishing of entering to enter ENDTEXT on next line" << endl;

    if (!enterText()) return;

    char cmd; string s;
    while (9) {
        cout << "enter 0 to clear hash-table and back to main menu" << endl
            << "enter 1 to output hash-table" << endl
            << "enter 2 to searching a word" << endl
            << "enter 3 to delete words" << endl;
        cin >> cmd;
        switch ((int)(cmd - '0')) {
        case 0:
            return;
            break;
        case 1:
            outTable_ex2();
            break;
        case 2:
            cout << "enter a word" << endl;
            cin >> s;
            searchWord(s);
            break;
        case 3:
            cout << "enter a letter. All words starting with this letter was deleted" << endl;
            cin >> cmd;
            deleteWordsStartingWith(cmd);
            break;
        default:
            cout << "no such command" << endl << endl;
        }
    }
}

//=========================================================================================================================
//================================================================ EXERCISE 3 =============================================

int multiplier_ex3;
map<string, long long> hash_ex3;

string getHash_ex_3(long long val) {                    // вычисление хэш-кода числа        
    bool isMines;
    if (val < 0) isMines = true;
    else isMines = false;

    val = abs(val);
    long long res = 0;
    long long pos = 1;

    while (val > 0) {
        int a = val % 10;
        res += (pos * a);        // каждая цифра числа домножается на номер позиции(начиная от правого конца) и прибавляется к хэш-сумме
        pos++;
        val /= 10;
        ;
    }
    res *= multiplier_ex3;          // затем хш-сумма домножается на случайный множитель с целью усложнить определение исходного значения по хэш-коду
    return to_string(res) + (isMines == true ? "-" : "");
}

void addValue(long long val) {                                          // добавление значения в таблицу
    hash_ex3[getHash_ex_3(val)] = val;
    cout << "values was added" << endl;
}

void searchValue(long long val) {                                       // поиск значения в таблице
    map<string, long long>::iterator it = hash_ex3.find(getHash_ex_3(val));
    if (it == hash_ex3.end()) cout << "No such value" << endl;
    else cout << "value: " << (*it).second << " has hash-code: " << (*it).first << endl;
}

void outputHash_ex3() {
    cout << "hash-table:" << endl;
    if (hash_ex3.size() <= 0) cout << "hash-table is empty" << endl;
    int idx = 1;
    for (map<string, long long>::iterator it = hash_ex3.begin(); it != hash_ex3.end(); it++, idx++) {
        cout << idx << ") value = " << (*it).second << "; hash-code = " << (*it).first << endl;
    }
}

void ex_3() {
    multiplier_ex3 = rand() % 1000;        // случайное значение, используемое при вычислении хэш-кода
    char cmd;
    long long value;
    while (9) {

        cout << "enter 0 to clear hash - table and back to main menu" << endl
            << "enter 1 to add a value" << endl
            << "enter 2 to searching a value" << endl
            << "enter 3 to output hash-table" << endl;

        cin >> cmd;
        switch ((int)(cmd - '0')) {
        case 0:
            return;
        case 1:
            cout << "enter a value for adding" << endl;
            cin >> value;
            addValue(value);
            break;
        case 2:
            cout << "enter a value for searching" << endl;
            cin >> value;
            searchValue(value);
            break;
        case 3:
            outputHash_ex3();
            break;
        default:
            cout << "No such command" << endl;
        }
    }
}

//=========================================================================================================================

int main()
{
    char cmd;
    while (9) {
        cout << "enter 0 for finishing execution this program" << endl;
        cout << "enter 1 to start checking ex. 1" << endl
            << "enter 2 to start checking ex. 2" << endl
            << "enter 3 to start checking ex. 3" << endl;
        cin >> cmd;
        switch ((int)(cmd - '0'))
        {
        case 0:
            cout << "Good bye!";
            return 0;
        case 1:
            ex_1();
            break;
        case 2:
            ex_2();
            break;
        case 3:
            ex_3();
            break;
        default:
            cout << "no such command" << endl << endl;
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
