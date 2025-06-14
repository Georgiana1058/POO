#include <iostream>
#include<string.h>
#include<fstream>
#include<vector>
using namespace std;
class Animal {
public:
    char* nume;
    char* specie;
    int varsta;
    int greutate;
    //Constructor cu parametri
    Animal(const char* nume, const char* specie, int varsta, int greutate)
    {
        this->nume = new char[strlen(nume) + 1];
        strcpy_s(this->nume, strlen(nume) + 1, nume);
        this->specie = new char[strlen(specie) + 1];
        strcpy_s(this->specie, strlen(specie) + 1, specie);
        this->varsta = varsta;
        this->greutate = greutate;

    }
    //Construtor fara parametri
    Animal() :nume(nullptr), specie(nullptr), varsta(0), greutate(0) {
        nume = new char[1];
        nume[0] = '\0';
        specie = new char[1];
        specie[0] = '\0';


    };
    //Constructor de copiere
    Animal(const Animal& p) : nume(nullptr), specie(nullptr)
    {
        this->nume = new char[strlen(p.nume) + 1];
        strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
        this->specie = new char[strlen(p.specie) + 1];
        strcpy_s(this->specie, strlen(p.specie) + 1, p.specie);
        this->varsta = p.varsta;
        this->greutate = p.greutate;
    }
    //Destructor
    ~Animal()
    {
        delete[] nume;
        delete[]specie;
    };
    //Subraincarcarea operatorului =
    Animal& operator=(const Animal& p)
    {
        delete[] nume;
        delete[] specie;
        this->nume = new char[strlen(p.nume) + 1];
        strcpy_s(this->nume, strlen(p.nume) + 1, p.nume);
        this->specie = new char[strlen(p.specie) + 1];
        strcpy_s(this->specie, strlen(p.specie) + 1, p.specie);
        this->varsta = p.varsta;
        this->greutate = p.greutate;
        return *this;
    }

    //Metode de acces pentru toate campurile
    const char* getNume() const
    {
        return this->nume;

    }
    void setNume(const char* nume)
    {
        delete[] this->nume;
        this->nume = new char[strlen(nume) + 1];
        strcpy_s(this->nume, strlen(nume) + 1, nume);
    }

    const char* getSpecie() const
    {

        return this->specie;

    }
    void setSpecie(const char* specie)
    {
        delete[] this->specie;
        this->specie = new char[strlen(specie) + 1];
        strcpy_s(this->specie, strlen(specie) + 1, specie);
    }
    int getVarsta() const
    {
        return this->varsta;
    }
    void setVarsta(int varsta)
    {
        this->varsta = varsta;

    }
    int getGreutate() const
    {
        return this->greutate;
    }
    void setGreutate(int greutate)
    {
        this->greutate = greutate;

    }
    friend istream& operator>>(istream& is, Animal& p)
    {
        is.ignore();
        cout << "Introduce-ti nume Animal: ";
        is.getline(p.nume, 100);
        cout << "Introduce-ti specie Animal: ";
        is.getline(p.specie, 100);
        cout << "Introduce-ti varsta Animal: ";
        is >> p.varsta;
        cout << "Introduce-ti greutate Animal: ";
        is >> p.greutate;
        is.ignore();  // Consumă newline-ul rămas în buffer
        return is;
    }
    friend ostream& operator << (ostream& os, const Animal& p);
    // Serializare in fisier binar pentru clasa Animal
    virtual void serialize(ostream& os) const {
        os.write(nume, strlen(nume) + 1);
        os.write(specie, strlen(specie) + 1);
        os.write(reinterpret_cast<const char*>(&varsta), sizeof(varsta));
        os.write(reinterpret_cast<const char*>(&greutate), sizeof(greutate));
    }

    // Deserializare din fisier binar pentru clasa Animal
    virtual void deserialize(istream& is) {
        is.read(nume, 100);
        is.read(specie, 100);
        is.read(reinterpret_cast<char*>(&varsta), sizeof(varsta));
        is.read(reinterpret_cast<char*>(&greutate), sizeof(greutate));
    }

};
ostream& operator <<(ostream& os, const Animal& p)
{
    os << "Nume: " << p.nume << endl;
    os << "Specie:" << p.specie << endl;
    os << "Varsta:" << p.varsta << endl;
    os << "Greutate:" << p.greutate << endl;
    return os;


};
class Reptila : public Animal
{
private:
    float marime_reptila;
    bool veninos;

public:
    // Constructor cu parametri
    Reptila(const char* nume, const char* specie, int varsta, int greutate, float marime_reptila, bool veninos)
        : Animal(nume, specie, varsta, greutate), marime_reptila(marime_reptila), veninos(veninos) {}

    // Constructor fara parametri
    Reptila() : Animal(), marime_reptila(0.0), veninos(false) {}

    // Constructor de copiere
    Reptila(const Reptila& r) : Animal(r), marime_reptila(r.marime_reptila), veninos(r.veninos) {}

    // Destructor
    ~Reptila() {}

    // Supraincarcare operator de atribuire =
    Reptila& operator=(const Reptila& r)
    {
        if (this != &r)
        {
            Animal::operator=(r);
            this->marime_reptila = r.marime_reptila;
            this->veninos = r.veninos;
        }
        return *this;
    }

    // Functii de acces
    const float getMarimeReptila() const
    {
        return this->marime_reptila;
    }

    void setMarimeReptila(float marime_reptila)
    {
        this->marime_reptila = marime_reptila;
    }

    const bool getVeninos() const
    {
        return this->veninos;
    }

    void setVeninos(bool veninos)
    {
        this->veninos = veninos;
    }

    // Operatorul de citire
    friend istream& operator>>(istream& is, Reptila& r)
    {
        is >> dynamic_cast<Animal&>(r);
        cout << "Introduce-ti marimea reptilei: ";
        is >> r.marime_reptila;
        is.ignore();
        cout << "Reptila este veninoasa: ";
        is >> r.veninos;
        is.ignore();
        return is;
    }
    friend istream& operator>>(istream& is, Reptila& r);


};

class Pasare : public Animal
{
private:
    bool zboara;
    char* culoare_penaj;

public:
    // Constructor cu parametri
    Pasare(const char* nume, const char* specie, int varsta, int greutate, bool zboara, const char* culoare_penaj)
        : Animal(nume, specie, varsta, greutate), zboara(zboara)
    {
        this->culoare_penaj = new char[strlen(culoare_penaj) + 1];
        strcpy_s(this->culoare_penaj, strlen(culoare_penaj) + 1, culoare_penaj);
    }

    // Constructor fara parametri
    Pasare() : Animal(), zboara(false), culoare_penaj(nullptr) {}

    // Constructor de copiere
    Pasare(const Pasare& p) : Animal(p)
    {
        this->culoare_penaj = new char[strlen(p.culoare_penaj) + 1];
        strcpy_s(this->culoare_penaj, strlen(p.culoare_penaj) + 1, p.culoare_penaj);
        this->zboara = p.zboara;
    }

    // Destructor
    ~Pasare()
    {
        delete[] culoare_penaj;
    }

    // Supraincarcare operatorului de atribuire =
    Pasare& operator=(const Pasare& p)
    {
        if (this != &p)
        {
            Animal::operator=(p);
            delete[] culoare_penaj;
            this->culoare_penaj = new char[strlen(p.culoare_penaj) + 1];
            strcpy_s(this->culoare_penaj, strlen(p.culoare_penaj) + 1, p.culoare_penaj);
            this->zboara = p.zboara;
        }
        return *this;
    }
    // Functiile de accesare
    const bool getZboara() const
    {
        return this->zboara;
    }

    void setZboara(bool zboara)
    {
        this->zboara = zboara;
    }

    const char* getCuloarePenaj() const
    {
        return this->culoare_penaj;
    }

    void setCuloarePenaj(const char* culoare_penaj)
    {
        delete[] this->culoare_penaj;
        this->culoare_penaj = new char[strlen(culoare_penaj) + 1];
        strcpy_s(this->culoare_penaj, strlen(culoare_penaj) + 1, culoare_penaj);
    }

    // Incarcare operator de citire

    friend  istream& operator >>(istream& is, Pasare& p) {
        // Apelam operatorul de citire al clasei de baza (Animal)
        is >> dynamic_cast<Animal&>(p);

        // Alte citiri specifice pentru Pasare
        cout << "Zboara: ";
        is >> p.zboara;

        // Citirea culorii penajului
        cout << "Culoare Penaj: ";
        char temp[100];
        is.ignore();  // Ignoram newline-ul ramas in buffer
        is.getline(temp, 100);

        // Alocam memorie pentru culoare_penaj si copiem continutul
        delete[] p.culoare_penaj;
        p.culoare_penaj = new char[strlen(temp) + 1];
        strcpy_s(p.culoare_penaj, strlen(temp) + 1, temp);

        return is;
    }
    // Operatorul de afisare
    friend ostream& operator<<(ostream& os, const Pasare& p)
    {
        os << dynamic_cast<const Animal&>(p);
        os << "Culoare Penaj:  " << p.culoare_penaj << endl;
        os << "Zboara : " << p.zboara << endl;
        return os;
    }
    friend istream& operator>>(istream& is, Pasare& p);
};

class Gradina_Zoologica {
private:
    vector<Animal*> animale;

public:
    // Constructori
    Gradina_Zoologica() {}

    Gradina_Zoologica(const vector<Animal*>& animale) : animale(animale) {}

    Gradina_Zoologica(const Gradina_Zoologica& gz) {
        for (const Animal* animal : gz.animale) {
            this->animale.push_back(new Animal(*animal));
        }
    }

    // Destructor
    ~Gradina_Zoologica() {
        for (Animal* animal : animale) {
            delete animal;
        }
    }

    // Supraincarcarea operatorului de atribuire
    Gradina_Zoologica& operator=(const Gradina_Zoologica& gz) {
        if (this != &gz) {
            // Stergere animalele curente
            for (Animal* animal : animale) {
                delete animal;
            }
            animale.clear();

            // Copiere animale din gz
            for (const Animal* animal : gz.animale) {
                this->animale.push_back(new Animal(*animal));
            }
        }
        return *this;
    }

    // Metode de acces pentru campurile private
    const vector<Animal*>& getAnimale() const {
        return this->animale;
    }

    // Supraincarcarea operatorilor de citire 
    friend istream& operator>>(istream& is, Gradina_Zoologica& gz) {
        int numarAnimale;
        cout << "Introduceti numarul de animale: ";
        is >> numarAnimale;

        for (int i = 0; i < numarAnimale; ++i) {
            int tipAnimal;
            cout << "Introduceti tipul animalului (1 - Reptila, 2 - Pasare): ";
            is >> tipAnimal;

            Animal* animal = nullptr;

            switch (tipAnimal) {
            case 1:
                animal = new Reptila();
                break;
            case 2:
                animal = new Pasare();
                break;
            default:
                cout << "Tip de animal invalid.\n";
                continue;
            }

            is >> *animal;
            gz.animale.push_back(animal);
        }

        return is;
    }
    //Supraincrcare operator de afisare
    friend ostream& operator<<(ostream& os, const Gradina_Zoologica& gz) {
        for (const Animal* animal : gz.animale) {
            os << *animal << "\n";
        }
        return os;
    }

    // Supraincarcarea operatorului +=
    Gradina_Zoologica& operator+=(Animal* animal) {
        animale.push_back(animal);
        return *this;
    }
    // Supraincarcarea operatorului -=
    void operator-=(int index) {
        if (index >= 0 && index < animale.size()) {
            delete animale[index];
            animale.erase(animale.begin() + index);
        }
    }
    // Operatorul de acces pe baza de index
    Animal* operator[](int index) const {
        if (index >= 0 && index < animale.size()) {
            return animale[index];
        }
        return nullptr;
    }
    // Serializare in fisier binar
    void serialize(const char* fileName) const {
        ofstream file(fileName, ios::binary | ios::trunc);
        if (file.is_open()) {
            size_t numarAnimale = animale.size();
            file.write(reinterpret_cast<const char*>(&numarAnimale), sizeof(numarAnimale));

            for (const Animal* animal : animale) {
                animal->serialize(file);
            }

            file.close();
        }
        else {
            cout << "Eroare la deschiderea fisierului pentru serializare.\n";
        }
    }

    // Deserializare din fisier binar
    void deserialize(const char* fileName) {
        ifstream file(fileName, ios::binary);
        if (file.is_open()) {
            size_t numarAnimale;
            file.read(reinterpret_cast<char*>(&numarAnimale), sizeof(numarAnimale));

            for (size_t i = 0; i < numarAnimale; ++i) {
                int tipAnimal;
                file.read(reinterpret_cast<char*>(&tipAnimal), sizeof(tipAnimal));

                Animal* animal = nullptr;

                switch (tipAnimal) {
                case 1:
                    animal = new Reptila();
                    break;
                case 2:
                    animal = new Pasare();
                    break;
                default:
                    cout << "Tip de animal invalid la deserializare.\n";
                    continue;
                }

                animal->deserialize(file);
                animale.push_back(animal);
            }

            file.close();
        }
        else {
            cout << "Eroare la deschiderea fisierului pentru deserializare.\n";
        }
    }
};

int main()
{
    // Test constructor cu parametri
    Animal animal1("Ionel", "Mamifer", 5, 150);
    cout << "Informatii despre animal1:\n" << animal1 << endl;

    // Test constructor fara parametri
    Animal animal2;
    cout << "Informatii despre animal2 (initializat cu constructorul fara parametri):\n" << animal2 << endl;

    // Test constructor de copiere cu parametri
    Animal animal3 = animal1;
    cout << "Informatii despre animal3 (copia obiectului animal1):\n" << animal3 << endl;

    // Test constructor de copiere fara parametri
    Animal animal4(animal2);
    cout << "Informatii despre animal4 (copia obiectului animal2):\n" << animal4 << endl;

    // Test operator de atribuire
    animal2 = animal1;
    cout << "Informatii despre animal2 dupa atribuire de la animal1:\n" << animal2 << endl;

    // Test metode de acces
    cout << "Test metode de acces:\n";
    cout << "Nume animal1: " << animal1.getNume() << endl;
    cout << "Specie animal1: " << animal1.getSpecie() << endl;
    cout << "Varsta animal1: " << animal1.getVarsta() << endl;
    cout << "Greutate animal1: " << animal1.getGreutate() << endl;

    // Test metode de modificare
    cout << "Modificare varsta animal1:\n";
    int newVarsta;
    cout << "Introduceti noua varsta: ";
    cin >> newVarsta;
    animal1.setVarsta(newVarsta);

    cout << "Informatii actualizate despre animal1:\n" << animal1 << endl;
    // Exemplu pentru Reptila
    Reptila reptila("Sarpe", "Boa constrictor", 5, 10, 5, true);

    cout << "Informatii despre reptila:\n" << reptila << endl;

    // Exemplu pentru Pasare
    Pasare pasare("Vultur", "Aquila", 3, 5, true, "Maro");
    cout << "Informatii despre pasare:\n" << pasare << endl;

    return 0;
}

