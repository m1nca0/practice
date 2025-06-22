#include <iostream>
#include <string>
#include <vector>

using namespace std;

string checkMusor(string str)
{
    for (int i = 0; i < str.size(); i++) 
    {
        if (!(isdigit(str[i]) || str[i] == '+' || str[i] == '-' ||
            str[i] == '(' || str[i] == ')' || str[i] == '/' || str[i] == '*' || str[i] == '.'))
        {
            str.erase(i, 1);
        }
    }
    return str;
}

bool checkSyntax(string str)
{
    bool a = true;
    if (str[0] == '/' || str[0] == '*' || str[0] == ')')
    {
        a = false;
    }
    if (str[str.size() - 1] != ')' && !isdigit(str[str.size() - 1]))
    {
        a = false;
    }
    vector<int> pravSkobok;
    vector<int> levSkobok;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-')
        {
            if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '+')
            {
                a = false;
            }
        }
        if (str.find_first_of('--') != -1)
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
    if (levSkobok.size() != pravSkobok.size())
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
                        index = pravSkobok[0] - levSkobok[j]; 
                        min = j;

                    }
                }
                levSkobok.erase(levSkobok.begin()+min);
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

void usl(string &perem,string copyStr,int &i,string &znak,string dest)
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
        
        if (isdigit(copyStr[i]) || copyStr[i] == '.' )
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
                // if (copyStr[i + 1] == '-')
                // {
                //     perem = "-";
                //     i++;
                // }
                znak = "";
            }
            else if (znak == "-") {
                perRes = perRes - stod(perem);
                znak = "";
            }
            perem = "";
        }

        if (copyStr[i] == '*') {
            usl(perem,copyStr,i,znak,"*");
        }
        else if (copyStr[i] == '/') {
            usl(perem,copyStr,i,znak,"/");
        }
        else if (copyStr[i] == '-')
        {
            usl(perem,copyStr,i,znak,"-");
        }
        else if (copyStr[i] == '+') {
            usl(perem,copyStr,i,znak,"+");
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
                if (isdigit(copyStr[k]) || copyStr[k] == '.' || copyStr[k] == '-')
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
                if (isdigit(copyStr[k]) || copyStr[k] == '.')
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
            if (umn[umn.size() - 1] == '0' && umn[umn.size() - 2] == '/')
            {
                cout<<"Деление на 0 невозможно!\n";
                cout<<"Один из этапов вычисления: "<<umn<<endl;
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
                index = pravSkobok[0]-levSkobok[j];
                min = levSkobok[j];
            }
        }
        
        string copyStr = ""; //((34564) + ()  )
        for (int k = min+1; k < pravSkobok[0]; k++)
        {
            copyStr += str[k];
        } 
        
        if (resDelumn(copyStr) == "null")
        {
            return " ";
        }
        double skobka=resSkobok(resDelumn(copyStr));
        str.erase(min, pravSkobok[0] - min+1);
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


// -(10 / 5) + (10 * (98 - 140 * 50) + (150 - 93.3))
int main()
{
    vector<int> pravSkobok;
    vector<int> levSkobok;
    string str;

    while (true)
    {
        cout << "Пользователь вводит с клавиатуры некоторое арифметическое выражение. Выражение может содержать: Начальный уровень: +, -, *, /. Например, если пользователь ввел: 5+2*2. Результат: 9.Средний уровень: (), +, -, *, /. Приложение рассчитывает результат выражения с учетом скобок, приоритетов операторов. "<< endl;
        cout<<"====МЕНЮ===="<<endl;
        cout << "1.Ввод выражения" << endl;
        cout << "2.Вывод результата " << endl;
        cout << "3.Результаты тестирования " << endl;
        cout << "4.Выход " << endl;
        int viborMenu;
        cout << "Ваш выбор: ";
        cin >> viborMenu;
        if (viborMenu == 1)
        {
            cout<<"Введите выражение: ";
            cin >> str;
            str = checkMusor(str);
            if (checkSyntax(str) == false)
            {
                cout << "Ошибка синтаксиса\n";
            }
        }
        else if (viborMenu == 2)
        {
            cout<<"Выражение: " << str<<endl;
            cout<<"Результат: " << logic(str,pravSkobok,levSkobok)<<endl;
        }
        else if (viborMenu == 3)
        {
            //тесты
        }
        else if (viborMenu == 4)
        {
            break;
        }
    }
    return 0;
}