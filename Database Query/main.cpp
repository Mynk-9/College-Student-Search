#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <windows.h>
#include <chrono>

#include "Data Def.h"

using namespace std;

vector < vector <string> > a (11472, vector <string> (ATTRIBUTES));

void change_case_toupper (string& a)
{
    for_each (a.begin(), a.end(), [](char& c){
                c = toupper(c);
              }
    );
}
vector <string> split (string& s)
{
    vector <string> a;
    string b = "";
    for (auto i = s.begin(); i != s.end(); i++)
    {
        if (*i == '|')// && (b != "" || b != " "))
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
bool compare_check (string what, string with)
{
    /*if (what.size() != with.size())
        return false;
    else
    {
        for (unsigned int i = 0; i < with.size(); i++)
        {
            if (what.at(i) != '_' && what.at(i) != with.at(i))
                return false;
        }
    }*/ // changed to add the * feature
    if (what.size() > with.size())
        return false;
    else
    {
        for (unsigned int i = 0; i < what.size(); i++)
        {
            if (what.at(i) == '*')
                return true;
            else if (what.at(i) != with.at(i) && what.at(i) != '_')
                return false;
        }
    }
    return true;
}

void load_data ()
{
    //a.resize(11471, vector <string> (ATTRIBUTES));
    ifstream fin;
    fin.open("processed_data");
    string entry;
    int i = 0;
    while (fin)
    {
        getline(fin, entry);
        vector <string> data = split(entry);
        a[i][ID] = data[ID];
        a[i][FNAME] = data[FNAME];
        a[i][MNAME] = data[MNAME];
        a[i][LNAME] = data[LNAME];
        a[i][HOSTEL] = data[HOSTEL];
        a[i][ROOM] = data[ROOM];
        a[i][DATASM] = data[DATASM];
        a[i][DATAIMG] = data[DATAIMG];
        i++;
    }

    fin.close();
}
void initialize ()
{
    cout << "\t\tWelcome to the Versatile Student Search by Mayank.\n" << endl;
    cout << " > Starting service...\n";
    load_data();
    cout << " > Service started." << endl;
}

void get_result (vector <string>& q)
{
    auto time_start = chrono::high_resolution_clock::now();

    ofstream fout;
    fout.open("result.js");

    vector < vector <string> > results (0, vector <string> (ATTRIBUTES));

    bool trip;
    for (int i = 0; i < a.size(); i++)
    {
        trip = true;
        for (int j = 0; j < ATTRIBUTES && trip; j++)
        {
            if (q[j] != "*")
            {
                if (!compare_check(q[j], a[i][j]))
                    trip = false;
            }
        }
        if (trip)
            results.push_back(a[i]);
    }

    auto time_stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast <chrono::microseconds> (time_stop - time_start);

    /*fout << "Total results: " << results.size() << "\n";
    fout << "Time Taken: " << duration.count() << " microseconds" << "\n";
    fout << "\n=======================================================\n";

    for (int i = 0; i < results.size(); i++)
    {
        fout << "Name: \t\t" << results[i][FNAME] << " " << results[i][MNAME]
            << " " << results[i][LNAME];
        fout << "\nID No.:\t\t" << results[i][ID];
        fout << "\nHostel/PS/Graduate:\t\t" << results[i][HOSTEL];
        fout << "\nRoom Number/PS Company:\t\t" << results[i][ROOM];
        fout << "\nSocial Media Data:\t\t" << (results[i][DATASM] == "" ? "N/A" : results[i][DATASM]);
        fout << "\nImage:\t\t" << (results[i][DATAIMG] == "" ? "N/A" : results[i][DATAIMG]);
        fout << "\n-----------------------------------------------------------\n";
    }

    if (results.size() == 0)
        fout << "Nothing matched the parameters.";*/

    fout << "var query_results = '{ \"qresults\": [";
    for (int i = 0; i < results.size(); i++)
    {
        /*fout << "Name: \t\t" << results[i][FNAME] << " " << results[i][MNAME]
            << " " << results[i][LNAME];
        fout << "\nID No.:\t\t" << results[i][ID];
        fout << "\nHostel/PS/Graduate:\t\t" << results[i][HOSTEL];
        fout << "\nRoom Number/PS Company:\t\t" << results[i][ROOM];
        fout << "\nSocial Media Data:\t\t" << (results[i][DATASM] == "" ? "N/A" : results[i][DATASM]);
        fout << "\nImage:\t\t" << (results[i][DATAIMG] == "" ? "N/A" : results[i][DATAIMG]);
        fout << "\n-----------------------------------------------------------\n";*/
        fout << "{";
        fout << "\"N\": " << "\"" << results[i][FNAME] << " " << results[i][MNAME]
            << " " << results[i][LNAME] << "\", ";
        fout << "\"ID\": " << "\"" << results[i][ID] << "\", ";
        fout << "\"H\": " << "\"" << results[i][HOSTEL] << "\", ";
        fout << "\"R\": " << "\"" << results[i][ROOM] << "\", ";
        fout << "\"SM\": " << "\"" << results[i][DATASM] << "\", ";
        fout << "\"IMG\": " << "\"" << results[i][DATAIMG] << "\" ";
        fout << "}";
        if (i != results.size() - 1)
            fout << ", ";
    }
    fout << "]}';";

    fout.close();

    //system ("result.html");
    ShellExecute(NULL, "open", "result.html", NULL, NULL, SW_SHOWDEFAULT);
}
void query ()
{
    vector <string> q (ATTRIBUTES);

    cout << "Query > \n";
    cout << "      > ID                     > ";
    getline(cin, q[ID]);
    cout << "      > First Name             > ";
    getline(cin, q[FNAME]);
    cout << "      > Middle Name            > ";
    getline(cin, q[MNAME]);
    cout << "      > Last Name              > ";
    getline(cin, q[LNAME]);
    cout << "      > Hostel/PS/Graduate     > ";
    getline(cin, q[HOSTEL]);
    cout << "      > Room Number/PS Company > ";
    getline(cin, q[ROOM]);
    cout << "      > Social Media           > ";
    getline(cin, q[DATASM]);

    for (int i = 0; i < ATTRIBUTES; i++)
    {
        if (q[i] == "")
            q[i] = "*";
        change_case_toupper(q[i]);
        //cout << "\t\t\t\t" << q[i] << "\n";
    }
    get_result(q);
}
void puthelp ()
{
    cout << "help > " << "Type query for query, help for help, quit to exit.\n";
    cout << "help > " << "While in query * means anything in that field, _ means anything on that position.\n";
}
int main()
{
    initialize();

    string q;

    while (q != "quit")
    {
        cout << "Command > ";
        getline(cin, q);

        if (q == "query")
        {
            query();
            cout << "Results are available in results.html file." << endl;
        }
        else if (q == "help")
            puthelp();
        else if (q == "quit")
        {
            cout << "\n\t\tBye.\n\n";
            cout << "Press any key.";
            getchar();
        }
        else
            cout << "Not recognized." << endl;
    }

    return 0;
}
