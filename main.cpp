#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>
using namespace std;
// this is the main function

struct problems {
    string problema;
    string specialitateNecesara;
    int durata;
    int prioritate;
    
};

struct doctors {
    string nume;
    string specializare;
    int inceput = 9;
    int sfarsit = 17;
    vector<string> problemeRezolvate;
};

struct comparator {
    bool operator()(problems& a, problems& b) const {
        return a.prioritate < b.prioritate;
    }
};

int main()
{
    ifstream inFile("input3.txt");

    int no_problems, no_doctors;
    string name, speciality;
    int duration, priority;

    inFile >> no_problems;
    priority_queue<problems, vector<problems>, comparator> probleme;
    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> duration;
        inFile >> priority;
        problems problema;
        problema.durata = duration;
        problema.prioritate = priority;
        problema.specialitateNecesara = speciality;
        problema.problema = name;
        probleme.push(problema);
    }

    inFile >> no_doctors;

    vector<doctors> doctori(no_doctors);

    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        doctori[i].nume = name;
        doctori[i].specializare = speciality;
    }

    while(!probleme.empty())
    {
        problems Problema = probleme.top();
        auto it = find_if(doctori.begin(), doctori.end(), [&](doctors& x) {
            if (x.specializare == Problema.specialitateNecesara && x.inceput + Problema.durata <= x.sfarsit)
            {
                x.problemeRezolvate.emplace_back(Problema.problema);
                return true;
            }
            return false;
            });

        if (it != doctori.end())
        {
            (*it).inceput += Problema.durata;
        }
        probleme.pop();
    }

    for (auto& i : doctori)
    {
        if (!i.problemeRezolvate.empty())
        {
            cout << i.nume << " " << i.problemeRezolvate.size() << " ";
            for (auto& j : i.problemeRezolvate)
            {
                cout << j << " ";
            }
            cout << '\n';
        }
    }

    return 0;
}