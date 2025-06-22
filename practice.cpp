#include <iostream>
#include <string>
#include <vector>


using namespace std;

string checkMusor(string str)
{
    for (int i = 0; i < str.size(); i++) //проверка на мусор
    {
        if (isdigit(str[i]) || str[i] == '+' || str[i] == '-' ||
            str[i] == '(' || str[i] == ')' || str[i] == '/' || str[i] == '*' || str[i] == '.')
        {
            continue;
        }
        else
        {
            str.erase(i, 1);
        }
    }
    return str;
}

bool checkSyntax(string str)
{
    bool a = true;
    if (str[0] == '/' || str[0] == '*' || str[0] == ')')//проверка на начало 
    {
        cout << "START";
        a = false;
    }
    if (str[str.size() - 1] != ')' && !isdigit(str[str.size() - 1]))//проверка на начало
    {
        cout << "FIN";
        a = false;
    }
    int levSkobka = 0;
    int pravSkobka = 0;
    for (int i = 0; i < str.size(); i++) //проверка синтаксис
    {
        if (str[i] == '*' || str[i] == '/' || str[i] == '+' || str[i] == '-')
        {
            if (str[i + 1] == '*' || str[i + 1] == '/' || str[i + 1] == '+')
            {
                cout << "LOL";
                a = false;
            }
        }
        if (str[i] == '(')
        {
            levSkobka++;
        }
        if (str[i] == ')')
        {
            pravSkobka++;
        }
    }
    if (levSkobka != pravSkobka) //проверка на кол-во скобок
    {
        a = false;
    }

    for (int i = 0; i < str.size(); i++) //проверка на порядок скобок
    {

        if (str.find_first_of('(', i) > str.find_first_of(')', i)) a = false;
        else i = str.find_first_of(')', i);
        if (levSkobka == 0) i = str.size();
    }

    return a;
}



double resSkobok(string copyStr)
{
    double perRes;
    string znak;
    string perem;

    copyStr.push_back('!');


    for (int i = 0; i < copyStr.size(); i++)
    {
        if (isdigit(copyStr[i]) || copyStr[i] == '.')
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
            znak = "*";
            if (copyStr[i + 1] == '-')
            {
                perem = "-";
                i++;
            }
        }
        else if (copyStr[i] == '/') {
            znak = "/";
            if (copyStr[i + 1] == '-')
            {
                perem = "-";
                i++;
            }
        }
        else if (copyStr[i] == '-') znak = "-";
        else if (copyStr[i] == '+') znak = "+";

    }
    return perRes;
}


string resDelumn(string copyStr)
{
    int j = 0;
    string umn = "";
    string perRes;
    int nachalo = 0;
    int konec = 0;
    for (int i = 0; i < copyStr.size(); i++)
    {
        if (copyStr[i] == '*' || copyStr[i] == '/')
        {
            j = i;
            for (int k = j + 1; k < copyStr.size() + 1; k++)
            {
                if (isdigit(copyStr[k]) || copyStr[k] == '.')
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
            for (int k = j - 1; k >= 0; k--)
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
    int razmer;
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '(') levSkobok.push_back(i);
        if (str[i] == ')') pravSkobok.push_back(i);
    }
    razmer = levSkobok.size();
    int min;
    int index = 999;
    for (int i = 0; i < levSkobok.size(); i++)
    {
        for (int j = 0; j < pravSkobok.size(); j++)
        {
            if (pravSkobok[i] - levSkobok[j] < index && pravSkobok[i] - levSkobok[j] > 0)
            {
                index = pravSkobok[i] - levSkobok[j];
                min = levSkobok[j];
            }
        }

        string copyStr = ""; //((34564) + ()  )
        for (int k = min + 1; k < pravSkobok[i]; k++)
        {
            copyStr += str[k];
        }

        double skobka = resSkobok(resDelumn(copyStr));
        str.erase(min, pravSkobok[i] - min + 1);
        str.insert(min, to_string(skobka));
        levSkobok.clear();
        pravSkobok.clear();
        for (int l = 0; l < str.size(); l++)
        {
            if (str[l] == '(') levSkobok.push_back(l);
            if (str[l] == ')') pravSkobok.push_back(l);
        }
        if (levSkobok.size() == 1)
        {
            str.erase(0, 1);
            str.erase(str.size() - 1, 1);
            skobka = resSkobok(resDelumn(str));
            str = to_string(skobka);
        }
    }
    return str;
}


// -(10 / 5) + (10 * (98 - 140 * 50) + (150 - 93.3))
int main()
{
    int i = -1;

    vector<int> pravSkobok;
    vector<int> levSkobok;



    string str = "((15 + 450)/10";

    str = checkMusor(str);
    if (checkSyntax(str) != 1)
    {
        cout << "Ошибка";
    }
    else
    {
        cout << logic(str, pravSkobok, levSkobok);
    }
    return 0;
}
// в функции resSkobok вызываем функцию resDelUmn 
// которая будет отдельно искать умножение или деление 
// решать его, и возвращать результат 
// пример
// исходная -(10 / 5) + (10 * (98 - 140 * 50) + (150 - 93.3))
// которая пойдет в resSkobok (98 - 140 * 50) 
// которая пойдет в resdelumn 140 * 50
// вернет в эту же строку (98 - 7000)

// *** в функции resdelumn вызывать снова функцию resSkobok