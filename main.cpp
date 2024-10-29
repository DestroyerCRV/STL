#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
// this is the main function

struct problems {
    string problema;
    string specialitateNecesara;


};

struct doctors {
    string nume;
    string specializare;

};
int main()
{

    vector<problems> probleme;
    vector<doctors> doctori;
    ifstream inFile("input.txt");

    int no_problems, no_doctors;
    string name, speciality;
    
    inFile >> no_problems;

    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> speciality;
        probleme.emplace_back(name, speciality);
    }

    inFile >> no_doctors;



    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> speciality;
        doctori.emplace_back(name, speciality);
    }

    for (auto& i : probleme)
    {
        bool found = false;
        for (auto& j : doctori)
        {
            if (i.specialitateNecesara == j.specializare)
            {
                found = true;
                cout << i.problema << " " << "Acceptat\n";
                break;
            }
            
        }
        if(!found)
            cout << i.problema << " " << "Respins\n";
    }



    return 0;
}