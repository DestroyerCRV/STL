#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;
struct atributeProblema {
    string problema;
    string specialitateNecesara;
    int durata;
    int prioritate;
    int oraSosire;

    bool operator<(const atributeProblema& b) const {
        if (oraSosire != b.oraSosire)
            return oraSosire > b.oraSosire;
        return prioritate < b.prioritate;
    }
};

struct atributeDoctor {
    string nume;
    int inceput = 9;
    int sfarsit = 17;
    int nrSpecializari;
    vector<pair<string, int>> problemeRezolvate;
    vector<string> listaSpecializari;
};


void problemeRezolvateDeDoctori(vector<atributeDoctor>& doctori)
{
    for (auto& doctorCurent : doctori)
    {
        if (!doctorCurent.problemeRezolvate.empty())
        {
            cout << doctorCurent.nume << " " << doctorCurent.problemeRezolvate.size() << " ";
            for (auto& problemaRezolvataCurenta : doctorCurent.problemeRezolvate)
            {
                cout << problemaRezolvataCurenta.first << " " << problemaRezolvataCurenta.second << " ";
            }
            cout << '\n';
        }
    }
}

void gasesteDoctorPotrivit(vector<atributeDoctor>& doctori, const atributeProblema& Problema)
{
    auto it = find_if(doctori.begin(), doctori.end(), [&](atributeDoctor& doctorCurent) {
        for (auto& specializareCurenta : doctorCurent.listaSpecializari)
        {
            if (specializareCurenta == Problema.specialitateNecesara && doctorCurent.inceput + Problema.durata <= doctorCurent.sfarsit && doctorCurent.inceput <= Problema.oraSosire)
            {
                doctorCurent.inceput = Problema.oraSosire + Problema.durata;
                doctorCurent.problemeRezolvate.push_back({ Problema.problema, Problema.oraSosire });
                return true;
            }
        }
        return false;
        });
}

void citireProbleme(int no_problems, ifstream& inFile, string& name, string& tipProblema, int& ora, int& duration, int& priority, priority_queue<atributeProblema>& probleme)
{
    for (int i = 0; i < no_problems; i++)
    {
        inFile >> name;
        inFile >> tipProblema;
        inFile >> ora;
        inFile >> duration;
        inFile >> priority;
        atributeProblema problema;
        problema.durata = duration;
        problema.prioritate = priority;
        problema.specialitateNecesara = tipProblema;
        problema.problema = name;
        problema.oraSosire = ora;
        probleme.push(problema);
    }
}

void citireDoctori(int no_doctors, ifstream& inFile, string& name, int& numarProblemeDoctorCurent, string& speciality, vector<atributeDoctor>& doctori)
{
    for (int i = 0; i < no_doctors; i++)
    {
        inFile >> name;
        inFile >> numarProblemeDoctorCurent;
        for (int j = 0; j < numarProblemeDoctorCurent; j++)
        {
            inFile >> speciality;
            doctori[i].listaSpecializari.emplace_back(speciality);
        }

        doctori[i].nume = name;
    }
}

int main()
{
    ifstream inFile("input4_bonus.txt");

    int numarProbleme, numarDoctori;
    string numePersoana, specialitate;
    int durata, prioritate, ora;
    priority_queue<atributeProblema> pacienti;
    inFile >> numarProbleme;
    
    citireProbleme(numarProbleme, inFile, numePersoana, specialitate, ora, durata, prioritate, pacienti);

    inFile >> numarDoctori;
    int numarProblemeDoctorCurent;
    vector<atributeDoctor> doctori(numarDoctori);

    citireDoctori(numarDoctori, inFile, numePersoana, numarProblemeDoctorCurent, specialitate, doctori);

    while (!pacienti.empty())
    {
        atributeProblema Problema = pacienti.top();
        pacienti.pop();

        gasesteDoctorPotrivit(doctori, Problema);
    }

    problemeRezolvateDeDoctori(doctori);

    return 0;
}