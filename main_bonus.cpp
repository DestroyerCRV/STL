#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
using namespace std;
// this is the main function

struct problems {
    string problema;
    string specialitateNecesara;
    int durata;

};

struct doctors {
    string nume;
    string specializare;  
    int inceput = 9;
    int sfarsit = 17;
    vector<string> problemeRezolvate;
};

bool operator==(const problems& p,  const doctors& d)
{
    if (p.specialitateNecesara == d.specializare)
    {
        return true;     
    }       
}

int main()
{   
    ifstream inFile("input4_bonus.txt");

    int no_problems, no_doctors;
    string name, speciality;
    int duration;

    inFile >> no_problems;
    vector<problems> probleme(no_problems);
    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        inFile >> duration;
        probleme[i].problema = name;
        probleme[i].specialitateNecesara = speciality;
        probleme[i].durata = duration;      
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

    for (auto& i : probleme)
    {
        
        auto it = find_if(doctori.begin(), doctori.end(), [&](doctors &x) {
            if (x.specializare == i.specialitateNecesara && x.inceput + i.durata <= x.sfarsit)
            {
                x.problemeRezolvate.emplace_back(i.problema);              
                return true;
            }
            return false;
            });
        
        if (it != doctori.end())
        {
            (*it).inceput += i.durata;
        }
       
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