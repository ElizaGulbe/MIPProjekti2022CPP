#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Employee {
    string Name;
    int Age;
    float Salary;
};

int main(){
    vector<Employee> data = {
        {"Andris",25,1105.75},
        {"Elza", 35,805.27},
        {"Vitauts",19,1305.22},
        {"Liene",61,5005.21},
        {"Talvaldis",81,705.28},
        {"Mariss",43,905.22},
        {"Rainers", 33, 1105.42},
        {"Judite",17,1205.29}
    };

auto printAllEmployees = [](Employee employeeData){cout << employeeData.Name << endl;};
auto printOver50 = [](Employee employeeData){if(employeeData.Age > 50) cout << employeeData.Name << endl;};
auto printUnder25 = [](Employee employeeData){if(employeeData.Age < 25) cout << employeeData.Name << endl;};
auto countSalaryOver1000Eval = [](Employee employeeData){return employeeData.Salary > 1000;};
auto countOver500Eval = [](Employee employeeData){return employeeData.Salary > 500;};
auto allOver15Eval = [](Employee employeeData){return employeeData.Age > 15;};
auto compare = [](Employee employeeData1, Employee employeeData2 ){ return (employeeData1.Salary < employeeData2.Salary);};

auto minSalary = min_element(data.begin(), data.end(), compare);
auto maxSalary = max_element(data.begin(), data.end(), compare);
cout << "Darbinieks, kurš saņem vislielāko algu: " << data[distance(data.begin(), maxSalary)].Name  <<endl;
cout << "\nDarbinieks, kurš saņem vismazāko algu: " << data[distance(data.begin(), minSalary)].Name  <<endl;
// darbinieki, kuri ir vecāki par 50 gadiem
cout << "\nDarbinieki, kuri vecāki par 50: " << endl;
for_each(data.begin(),data.end(),printOver50);
// darbinieki, kuri ir jaunāki par 25 gadiem
cout << "\nDarbinieki, kuri ir jaunāki par 25: " << endl;
for_each(data.begin(),data.end(),printUnder25);
// darbinieku skaits, kuri saņem vairāk par 1000
int countSalaryOver1000 = count_if(data.begin(), data.end(),countSalaryOver1000Eval);
cout << "\nDarbinieku skaits, kuri saņem vairāk par 1000: " << countSalaryOver1000 << endl;
//  Vai visi darbinieki saņem vairāk par 500 Eur
bool countOver500 = all_of(data.begin(), data.end(),countOver500Eval);
if(countOver500){
    cout << "\nVisi darbinieki saņem vairāk par 500 Eur" << endl;
} else {
    cout << "\nNe visi darbinieki saņem vairāk par 500 Eur" << endl;
}
bool allOver15 = all_of(data.begin(), data.end(),allOver15Eval);
if(allOver15){
    cout << "\nVisi darbinieki ir vecāki par 15 gadien" << endl;
} else {
    cout << "\nNe visi darbinieki ir vecāki par 15 gadien" << endl;
}
// Izprintēt visus darbiniekus uz ekrāna
cout << "\nVisu darbinieku vārdi: " << endl;
for_each(data.begin(),data.end(),printAllEmployees);
}
/**
■ Darbinieks, kurš saņem vislielāko algu
■ Darbinieks, kurš saņem vismazāko algu
■ Darbinieki, kuri ir vecāki par 50 gadiem
■ Darbinieki, kuri ir jaunāki par 25 gadiem
■ Darbinieku skaitu, kuri saņem vairāk par 1000 Eur
■ Vai visi darbinieki saņem vairāk par 500 Eur
■ Vai ir kāds darbinieks, kurš ir jaunāks par 15 gadiem
■ Visus darbiniekus uz ekrāna
 * 
 */