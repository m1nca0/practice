#include <iostream>
#include <string>
#include <vector>


using namespace std;

string checkMusor(string str)
{
    for (int i = 0;i < str.size();i++) //проверка на мусор
    {
        if (isdigit(str[i]) || str[i] == '+' || str[i] == '-' || 
        str[i] == '(' || str[i] == ')' || str[i] == '/' || str[i] == '*' || str[i] == '.')    
        {
            continue;
        }
        else
        {
            str.erase(i,1);
        }
    }
    return str;
}

bool checkSyntax(string str)
{
    bool a = true;
    if (str[0] == '/' || str[0] == '*' || str[0] == ')')//проверка на начало 
    {
        cout<<"START";
        a = false;
    }
    if (str[str.size() - 1] != ')' && !isdigit(str[str.size() - 1]))//проверка на начало
    {
        cout<<"FIN";
        a = false;
    }
    int levSkobka = 0;
    int pravSkobka = 0;
    for (int i = 0;i < str.size();i++) //проверка синтаксис
    {
        if (str[i] =='*' || str[i] =='/' || str[i] =='+' || str[i] =='-')
        {
            if(str[i + 1] =='*' || str[i + 1] =='/' || str[i + 1] =='+')
            {
                cout<<"LOL";
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
    
    for (int i = 0;i < str.size();i++) //проверка на порядок скобок
    {
        
        if (str.find_first_of('(', i) > str.find_first_of(')', i)) a = false;
        else i = str.find_first_of(')', i);
        if (levSkobka == 0) i = str.size();
    }
    
    return a;
}

double resSkobok(string &str, string &copyStr, string finalStr)
{
    
    double perRes;
    double perRes2;
    string znak;
    string perem;
    
    copyStr.push_back('.');

    //1/-4

    for (int i = 0;i < copyStr.size();i++)
    {
        if (isdigit(copyStr[i]))
        {
            perem += copyStr[i];
        }
        else
        {
            if (znak == "") perRes = stoi(perem);
            else if(znak == "*") {
                perRes = perRes * stoi(perem);
                znak = "";
            }
            else if(znak == "/"){
                perRes = perRes / stoi(perem);
                znak = "";
            }
            else if(znak == "+"){ 
                perRes = perRes + stoi(perem);
                znak = "";
            }
            else if(znak == "-") {
                perRes = perRes - stoi(perem);
                znak = "";
            }
            perem = "";
        }

        if (copyStr[i] == '*') {
            znak = "*";
            if (copyStr[i+1] == '-')
            {
                perem = "-";
                i++;
            }
        }
        else if (copyStr[i] == '/'){
            znak = "/";
            if (copyStr[i+1] == '-')
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

void logic(string str,vector<int> &pravSkobok,vector<int> &levSkobok,string &finalStr)
{
    for (int i = 0;i<str.size();i++)
    {
        if (str[i] == '(') levSkobok.push_back(i);
        if (str[i] == ')') pravSkobok.push_back(i);
    }

    int min = 999;

    for (int i = 0;i<str.size();i++)
    {
        for (int j = 0;j<str.size();j++)
        {
            if (pravSkobok[i] - levSkobok[j] < min && pravSkobok[i] - levSkobok[j] > 0)
            {
                min = levSkobok[j];
            }
        } 
        string copyStr = "";
        for (int k = min;k < pravSkobok[i];k++)
        {
            copyStr += str[k];
        }
        resSkobok(str,copyStr,finalStr);

    }

}

// -(10 / 5) + (10 * (98 - 140 * 50) + (150 - 93.3))
int main()
{
    int i = -1;

    vector<int> pravSkobok;
    vector<int> levSkobok;

    double res;
    
    string str = "1/-4";
    
    string finalStr = str;

    str = checkMusor(str);

    string copyStr = str;
 
    cout<<resSkobok(str,copyStr,finalStr);
    
    if (checkSyntax(str))
    {
        cout<<"good";
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