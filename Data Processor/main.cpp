/* Copyright (c) 2019 Mayank Mathur under MIT License */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>

#include "Data Def.h"

using namespace std;

const string pd = "processed_data";

void clearStringVec (vector <string> & a)
{
    for (int i = 0; i < a.size(); i++)
        a[i] = "";
}
string trim(const string& str)
{
    size_t first = str.find_first_not_of(' ');
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
vector <string> split (string& s)
{
    vector <string> a;
    string b = "";
    for (auto i = s.begin(); i != s.end(); i++)
    {
        if (*i == ' ' && (b != "" || b != " "))
        {
            a.push_back(b);
            b = "";
        }
        else
            b += *i;
    }
    a.push_back(b);
    return a;
}

void process (string name, string path)
{
    ifstream fin;
    ofstream fout;

    string entry;

    fin.open(path + "\\" + name);
    fout.open(path + "\\" + pd);

    int n, z1, z2;
    z1 = z2 = 0;    /// iterators for 'a' vector
    vector <string> s (ATTRIBUTES);
    vector < vector <string> > a (11471, vector <string> (ATTRIBUTES));

    while (fin)
    {
        clearStringVec(s);
        z2 = n = 0;

        getline(fin, entry);
        for (auto i = entry.begin(); i != entry.end(); i++)
        {
            if ((char)(*i) != '|')
                s[n] += *i;
            else
                n++;
        }

        for (int i = 0; i <= n; i++)
        {
            s[i] = trim(s[i]);
            if (i == FNAME)
            {
                vector <string> full_name = split(s[i]);
                switch (full_name.size())
                {
                case 1:
                    a[z1][FNAME] = full_name[0];
                    break;
                case 2:
                    a[z1][FNAME] = full_name[0];
                    a[z1][LNAME] = full_name[1];
                    break;
                case 3:
                    a[z1][FNAME] = full_name[0];
                    a[z1][MNAME] = full_name[1];
                    a[z1][LNAME] = full_name[2];
                    break;
                default:
                    a[z1][FNAME] = full_name[0];
                }
                z2 = LNAME + 1;
            }
            else
                a[z1][z2++] = s[i];
        }

        z1++;
    }

    sort (a.begin(), a.end(),
          [](vector <string> a, vector <string> b){
            return (a[0] < b[0]);
            }
    );

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = 0; j < a[i].size(); j++)
        {
            fout << a[i][j] << "|";
        }
        fout << "\n";
    }

    fout.close();
    fin.close();
}

int main()
{
    string name, path;
    cout << "Enter file name > ";
    cin >> name;
    path = "D:\\Projects\\Cpp\\Versatile Student Search - SWD";

    process(name, path);

    return 0;
}
