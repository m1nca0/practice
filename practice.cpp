#include <iostream>
#include <string>
#include <vector>
#include <gtest/gtest.h>
using namespace std;

string checkMusor(string str)
{
    bool p = true;
    int i = 0;
    while (p) //проверка на мусор
    {
        if (!(isdigit(str[i]) || str[i] == '+' || str[i] == '-' ||
            str[i] == '(' || str[i] == ')' || str[i] == '/' || str[i] == '*' || str[i] == '.' || str[i] == ','))
        {
            str.erase(i, 1);
            i = 0;
        }
        else
        {
            i++;
        }
        if (i == str.size())
        {
            p = false;
        }

    }
    return str;
}

bool checkSyntax(string str)
{
    bool a = true;
    if (str[0] == '/' || str[0] == '*' || str[0] == ')')//проверка на начало 
    {
        a = false;
    }
    if (str[str.size() - 1] != ')' && !isdigit(str[str.size() - 1]))//проверка на начало
    {
        a = false;
    }
    vector<int> pravSkobok;
    vector<int> levSkobok;
    for (int i = 0; i < str.size(); i++) //проверка синтаксис
    {
        if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-')
        {
            if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '+')
            {

                a = false;
            }
        }
        if (str.find("--") != -1)
        {
            a = false;
        }
        if (str[i] == '(')
        {
            levSkobok.push_back(i);
        }
        if (str[i] == ')')
        {
            pravSkobok.push_back(i);
        }
    }
    if (levSkobok.size() != pravSkobok.size()) //проверка на кол-во скобок
    {
        a = false;
    }
    else
    {
        if (levSkobok.size() > 0)
        {
            int min;
            int index = 999;
            bool p = true;
            while (p)
            {
                for (int j = 0; j < pravSkobok.size(); j++)
                {
                    if (pravSkobok[0] - levSkobok[j] < index && pravSkobok[0] - levSkobok[j] > 0)
                    {
                        index = pravSkobok[0] - levSkobok[j]; // )()()(
                        min = j;

                    }
                }
                levSkobok.erase(levSkobok.begin() + min);
                pravSkobok.erase(pravSkobok.begin());
                min = 0;
                if (levSkobok.empty())
                {
                    p = false;
                }

            }
            if (!(pravSkobok.empty() && levSkobok.empty()))
            {
                a = false;
            }
        }
    }
    return a;
}

void usl(string& perem, string copyStr, int& i, string& znak, string dest)
{
    znak = dest;
    if (copyStr[i + 1] == '-')
    {
        perem = "-";
        i++;
    }
}

double resSkobok(string copyStr)
{
    double perRes;
    string znak = "";
    string perem;
    copyStr.push_back('!');
    if (copyStr[0] == '-')
    {
        perem += '-';
        copyStr.erase(0, 1);
    }
    for (int i = 0; i < copyStr.size(); i++)
    {

        if (isdigit(copyStr[i]) || copyStr[i] == '.' || copyStr[i] == ',')
        {
            perem += copyStr[i];
        }
        else
        {
            if (znak == "") perRes = stod(perem);
            else if (znak == "*") {
                perRes = perRes * stod(perem);
                znak = "";
            }
            else if (znak == "/") {
                perRes = perRes / stod(perem);
                znak = "";
            }
            else if (znak == "+") {
                perRes = perRes + stod(perem);
                znak = "";
            }
            else if (znak == "-") {
                perRes = perRes - stod(perem);
                znak = "";
            }
            perem = "";
        }

        if (copyStr[i] == '*') {
            usl(perem, copyStr, i, znak, "*");
        }
        else if (copyStr[i] == '/') {
            usl(perem, copyStr, i, znak, "/");
        }
        else if (copyStr[i] == '-')
        {
            usl(perem, copyStr, i, znak, "-");
        }
        else if (copyStr[i] == '+') {
            usl(perem, copyStr, i, znak, "+");
        }
    }
    return perRes;
}


string resDelumn(string copyStr)
{
    string umn = "";
    string perRes;
    int nachalo = 0;
    int konec = 0;
    for (int i = 0; i < copyStr.size(); i++)
    {
        if (copyStr[i] == '*' || copyStr[i] == '/')
        {
            for (int k = i + 1; k < copyStr.size() + 1; k++)
            {
                if (isdigit(copyStr[k]) || copyStr[k] == '.' || copyStr[k] == ',' || copyStr[k] == '-')
                {
                    umn = umn + copyStr[k];
                }
                else
                {
                    konec = k;
                    k = copyStr.size();
                }
            }
            umn = copyStr[i] + umn;
            for (int k = i - 1; k >= 0; k--)
            {
                if (isdigit(copyStr[k]) || copyStr[k] == '.' || copyStr[k] == ',')
                {
                    umn = copyStr[k] + umn;
                }
                else
                {
                    nachalo = k + 1;
                    k = 0;
                }
            }
        }
        if (umn != "")
        {
            int znakPos = 0;
            for (int k = 0; k < umn.size() + 1; k++)
            {
                if (umn[k] == '/')
                {
                    znakPos = k;
                    k = umn.size();
                }
            }
            if (umn[znakPos + 1] == '0' && umn[znakPos] == '/')
            {
                cout << "Деление на 0 невозможно!\n";
                cout << "Один из этапов вычисления: " << umn << endl;
                return "null";
            }
            copyStr.erase(nachalo, konec - nachalo);
            copyStr.insert(nachalo, to_string(resSkobok(umn)));
            umn = "";
            i = 0;
        }
    }
    return copyStr;
}




string logic(string str, vector<int>& pravSkobok, vector<int>& levSkobok)
{
    str = '(' + str + ')';
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(') levSkobok.push_back(i);
        if (str[i] == ')') pravSkobok.push_back(i);
    }
    int min;
    int index = 999;
    bool p = true;
    while (p)
    {
        for (int j = 0; j < pravSkobok.size(); j++)
        {
            if (pravSkobok[0] - levSkobok[j] < index && pravSkobok[0] - levSkobok[j] > 0)
            {
                index = pravSkobok[0] - levSkobok[j];
                min = levSkobok[j];
            }
        }

        string copyStr = ""; //((34564) + ()  )
        for (int k = min + 1; k < pravSkobok[0]; k++)
        {
            copyStr += str[k];
        }

        if (resDelumn(copyStr) == "null")
        {
            return " ";
        }
        double skobka = resSkobok(resDelumn(copyStr));
        str.erase(min, pravSkobok[0] - min + 1);
        str.insert(min, to_string(skobka));
        levSkobok.clear();
        pravSkobok.clear();
        for (int l = 0; l < str.size(); l++)
        {
            if (str[l] == '(') levSkobok.push_back(l);
            if (str[l] == ')') pravSkobok.push_back(l);
        }
        index = 999;
        if (levSkobok.size() == 0)
        {
            p = false;
        }
    }
    return str;
}

void testLogic()
{
    string str = "(10+5)*100";
    vector<int> pravSkobok;
    vector<int> levSkobok;
    double result = (10 + 5) * 100;
    double resultFromStr;
    cout << "Вводимые данные:" << str << endl;
    cout << "Ожидаемый результат:" << result << endl;
    resultFromStr = stod(logic(str, pravSkobok, levSkobok));
    if (resultFromStr == result)
    {
        cout << "Тест #1 пройден" << endl;
    }
    else
    {
        cout << "Тест #1 не пройден" << endl;
    }
}


void runTests() {
    int fake_argc = 1;
    char fake_argv0[] = "program_name";
    char* fake_argv[] = { fake_argv0, nullptr };
    testing::InitGoogleTest(&fake_argc, fake_argv);
    RUN_ALL_TESTS();
}

// Тесты для функции checkMusor
TEST(CalculatorTest, CheckMusorTest) {
    EXPECT_EQ(checkMusor("5+2*3"), "5+2*3");
    EXPECT_EQ(checkMusor("a5+b2*c3"), "5+2*3");
    EXPECT_EQ(checkMusor("(1.5 + 2.5)"), "(1.5+2.5)");
    EXPECT_EQ(checkMusor("test123"), "123");
}

// Тесты для функции checkSyntax
TEST(CalculatorTest, CheckSyntaxTest) {
    EXPECT_TRUE(checkSyntax("5+2*3"));
    EXPECT_TRUE(checkSyntax("(5+2)*3"));
    EXPECT_FALSE(checkSyntax("5++3"));
    EXPECT_FALSE(checkSyntax("(5+2"));
    EXPECT_FALSE(checkSyntax("5+2)"));
    EXPECT_FALSE(checkSyntax("*5+2"));
}

// Тесты для функции resSkobok
TEST(CalculatorTest, ResSkobokTest) {
    EXPECT_DOUBLE_EQ(resSkobok("2+3"), 5.0);
    EXPECT_DOUBLE_EQ(resSkobok("2*3"), 6.0);
    EXPECT_DOUBLE_EQ(resSkobok("6/2"), 3.0);
    EXPECT_DOUBLE_EQ(resSkobok("2,5+3,5"), 6.0);
    EXPECT_DOUBLE_EQ(resSkobok("-2+5"), 3.0);
}

// Тесты для функции resDelumn
TEST(CalculatorTest, ResDelumnTest) {
    EXPECT_EQ(resDelumn("2+3"), "2+3");
    EXPECT_EQ(resDelumn("2*3+4"), "6,000000+4");
    EXPECT_EQ(resDelumn("10/2*3"), "15,000000");
    EXPECT_EQ(resDelumn("10/0"), "null");
}

// Тесты для функции logic
TEST(CalculatorTest, LogicTest) {
    vector<int> prav, lev;
    EXPECT_EQ(logic("2+3", prav, lev), "5,000000");
    EXPECT_EQ(logic("(2+3)*4", prav, lev), "20,000000");
    EXPECT_EQ(logic("2*(3+4)", prav, lev), "14,000000");
    EXPECT_EQ(logic("10/(5-5)", prav, lev), " ");
}




// -(10 / 5) + (10 * (98 - 140 * 50) + (150 - 93.3))
int main()
{
    setlocale(LC_ALL, "Rus");
    vector<int> pravSkobok;
    vector<int> levSkobok;
    string str;
    while (true)
    {
        cout << "Пользователь вводит с клавиатуры некоторое арифметическое выражение. Выражение может содержать: Начальный уровень: +, -, *, /. Например, если пользователь ввел: 5+2*2. Результат: 9.Средний уровень: (), +, -, *, /. Приложение рассчитывает результат выражения с учетом скобок, приоритетов операторов. " << endl;
        cout << "====МЕНЮ====" << endl;
        cout << "1.Ввод выражения" << endl;
        cout << "2.Вывод результата " << endl;
        cout << "3.Результаты тестирования " << endl;
        cout << "4.Выход " << endl;
        int viborMenu;
        cout << "Ваш выбор: ";
        cin >> viborMenu;
        if (viborMenu == 1)
        {
            cout << "Введите выражение: ";
            cin >> str;
            str = checkMusor(str);
            if (checkSyntax(str) == false)
            {
                cout << "Ошибка синтаксиса\n";
                str.clear();
            }
        }
        else if (viborMenu == 2)
        {
            cout << "Выражение: " << str << endl;
            cout << "Результат: " << logic(str, pravSkobok, levSkobok) << endl;
        }
        else if (viborMenu == 3)
        {
            /*testLogic();*/
            runTests();
        }
        else if (viborMenu == 4)
        {
            break;
        }
    }
    return 0;
}