#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>


struct Pot {
   int iz_vozlisca, v_vozlisce, cena;
   std::vector<bool> mnozica;
};

// Variables
unsigned int steviloVozlisc;
std::vector<int> matrikaSosednosti;
std::vector<Vozlisce> vozlisca;
bool running = true;



void napaka(const std::string& what = "") {
    std::cout << "***** NAPAKA: " << what;
}


bool beriIzDatoteke(const std::string& pot) {
    unsigned int cena;
    std::ifstream f("/home/alex/CLionProjects/APS/naloga11/graf1.txt");
    if (!f.is_open()) return false;

    f >> steviloVozlisc;
    vozlisca.reserve(steviloVozlisc);
    matrikaSosednosti.reserve(steviloVozlisc * steviloVozlisc - 1);

    for (unsigned int i = 0; i < steviloVozlisc; i++) {
        Vozlisce tmp = {i + 1, -1, 0};
        vozlisca.push_back(tmp);
    }
    while (f >> cena) {
        matrikaSosednosti.push_back(cena);
    }
    return true;
}


void meni() {
    int choice, input, zacetnoVozlisce, koncnoVozlisce, cena;
    std::string potDoDatoteke;

    std::cout << "Trgovski potnik - izbira\n\n";
    std::cout << "1) Preberi matriko\n";
    std::cout << "2) Resi problem trgovskega potnika\n";
    std::cout << "3) Izpisi dobljen seznam nivojev\n";
    std::cout << "4) Rekonstrukcija poti\n";
    std::cout << "5) Izhod\n\n";
    std::cout << "Izbira: "; 
    std::cin >> choice;
    std::cout << "\n";

    switch(choice) {
        case 1:
            // std::cout << "Vpisi pot do datoteke: ";
            // std::cin >> potDoDatoteke;
            if (!beriIzDatoteke(potDoDatoteke)) {
                napaka("Datoteka ne obstaja!");
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            std::cout << "Program se je zakljucil.";
            running = false;
            break;
        default:
            napaka("Napačna izbira");
            break;
    }
    std::cout << "\n\n";
}


int main() {

    while (running) {
        meni();
    }
    return 0;
}
