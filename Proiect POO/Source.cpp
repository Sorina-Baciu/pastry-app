/**
 * Baciu Sorina Stefania -- 1048
 * Compilator: Visual Studio 2022 - Windows
 */

 /// -------------------------   CERINTA   -------------------------

 /*
     Aplicatie pentru gestiunea costurilor produselor la
     o patiserie unde se produc diferite produse, pentru
     care se consuma diferite materiale (cod material,
     denumire, preț unitar, cantitate). Aplicația permite
     calculul pretului de cost pentru fiecare produs,
     determinarea produsului cu costul cel mai mare, respectiv cel mai mic.
 */

 /// -------------------------   IMPORT DE LIBRARII   -------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <exception>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

/// -------------------------   ENUM TipProdus   -------------------------

enum TipProdus
{
    Refrigerat,
    Proaspat,
    AltTip
};

TipProdus convertToTipProdus(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = char(toupper(str[i]));
        i++;
    }

    if (strcmp(str, "REFRIGERAT") == 0)
        return TipProdus::Refrigerat;

    if (strcmp(str, "PROASPAT") == 0)
        return TipProdus::Proaspat;

    return TipProdus::AltTip;
}

string convertToChar(TipProdus tipProdus)
{
    switch (tipProdus)
    {
    case TipProdus::Proaspat:
        return "PROASPAT";
        break;
    case TipProdus::Refrigerat:
        return "REFRIGERAT";
        break;
    default:
        return "AltTipProdus";
        break;
    }
}

/// -------------------------   ENUM CATEGORIE   -------------------------

enum Categorie
{
    Prajituri,
    Rulade,
    Foietaje,
    AltaCategorie
};

Categorie convertToCategorie(char* str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        str[i] = char(toupper(str[i]));
        i++;
    }

    if (strcmp(str, "PRAJITURI") == 0)
        return Categorie::Prajituri;

    if (strcmp(str, "PATISERIE") == 0)
        return Categorie::Foietaje;

    if (strcmp(str, "RULADE") == 0)
        return Categorie::Rulade;

    return Categorie::AltaCategorie;
}

string convertToChar(Categorie categorie)
{
    switch (categorie)
    {
    case Categorie::Rulade:
        return "RULADE";
        break;
    case Categorie::Foietaje:
        return "PATISERIE";
        break;
    case Categorie::Prajituri:
        return "PRAJITURI";
        break;
    default:
        return "AltaCategorie";
        break;
    }
}

/// -------------------------   CLASA IO PENTRU CITIRE/AFISARE   -------------------------

// O clasa abstracta care implementeaza functiile de citire si de afisare

class IO
{
public:
    IO() = default;

    virtual ~IO() = default;

    friend istream& operator>>(istream& in, IO& ob)
    {
        ob.read(in);
        return in;
    }

    friend ostream& operator<<(ostream& out, const IO& ob)
    {
        ob.write(out);
        return out;
    }

    virtual void read(istream& in) = 0;

    virtual void write(ostream& out) const = 0;
};

/// -------------------------   CLASA CHECKER   -------------------------

// O clasa de tip template cu care verific diverse variabile

template <class T>
class Checker
{
public:
    Checker() = default;

    virtual ~Checker() = default;

    static void throwIfNotPositive(T);

    static void throwIfNotStrictPositive(T);

    static void throwIfNotInRange(T, T, T, string = "Numarul");

    static void throwIfGreaterThan(T, T, string = "Numarul");

    static void throwIfLowerThan(T, T, string = "Numarul");
};

template <class T>
void Checker<T>::throwIfNotPositive(T value)
{
    if (value < 0)
    {
        throw runtime_error("Numarul trebuie sa fie pozitiv!");
    }
}

template <class T>
void Checker<T>::throwIfNotStrictPositive(T value)
{
    if (value <= 0)
    {
        throw runtime_error("Numarul trebuie sa fie strict pozitiv!");
    }
}

template <class T>
void Checker<T>::throwIfNotInRange(T value, T a, T b, string ob_name)
{
    if (value < a || value > b)
    {
        throw runtime_error(ob_name + " trebuie sa fie in intervaulul [" + to_string(a) + ", " + to_string(b) + "]");
    }
}

template <class T>
void Checker<T>::throwIfGreaterThan(T value, T a, string ob_name)
{
    if (value > a)
    {
        throw runtime_error(ob_name + " trebuie sa fie < " + to_string(a));
    }
}

template <class T>
void Checker<T>::throwIfLowerThan(T value, T a, string ob_name)
{
    if (value < a)
    {
        throw runtime_error(ob_name + " trebuie sa fie > " + to_string(a));
    }
}

/// -------------------------   CLASA DATA   -------------------------

class Data : public virtual IO
{
    int zi, luna, an;

    static Data data_default;

public:
    static void init_data_default(int zi, int luna, int an);

    Data();

    Data(int, int, int);

    Data(const Data&);

    ~Data() = default;

    int getZi() const;

    void setZi(int zi);

    int getLuna() const;

    void setLuna(int luna);

    int getAn() const;

    void setAn(int an);

    Data& operator=(const Data&);

    Data& operator++();

    Data& operator--();

    Data& operator+(int);

    Data& operator++(int);

    Data& operator--(int);

    Data& operator-=(int);

    Data& operator+=(int);

    bool operator==(const Data&);

    bool operator!=(const Data&);

    bool operator<(const Data&);

    bool operator>(const Data&);

    bool operator<=(const Data&);

    bool operator>=(const Data&);

    void read(istream&) override;

    void write(ostream&) const override;
};

void Data::init_data_default(int zi, int luna, int an)
{
    data_default = Data(zi, luna, an);
}

Data::Data()
{
    zi = data_default.zi;
    luna = data_default.luna;
    an = data_default.an;
}

Data::Data(int ziua, int luna2, int anul)
{
    Checker<int>::throwIfNotInRange(ziua, 1, 31, "Ziua");
    Checker<int>::throwIfNotInRange(luna2, 1, 12, "Luna");
    Checker<int>::throwIfLowerThan(anul, 2000, "Anul");
    zi = ziua;
    luna = luna2;
    an = anul;
}

Data::Data(const Data& d)
{
    this->zi = d.zi;
    this->luna = d.luna;
    this->an = d.an;
}

void Data::read(istream& in)
{
    cout << "Introduceti ziua (int : 1-31) :";
    do
    {
        in >> zi;
        if (zi < 1 || zi > 31)
            cout << "Gresit ! Ziua trebuie sa fie intre 1 si 31. Reintroduceti : ";
    } while (zi < 1 || zi > 31);

    cout << "Introduceti luna (int : 1-12) :";
    do
    {
        in >> luna;
        if (luna < 1 || luna > 12)
            cout << "Gresit ! Luna trebuie sa fie intre 1 si 12. Reintroduceti : ";
    } while (luna < 1 || luna > 12);

    cout << "Introduceti anul (int : >=2000) :";
    do
    {
        in >> an;
        if (an < 2000)
            cout << "Gresit ! Anul trebuie sa fie >= 2000. Reintroduceti : ";
    } while (an < 2000);
}

void Data::write(ostream& out) const
{
    out << "Data{zi=" << zi;
    out << ", luna=" << luna;
    out << ", an=" << an << "}";
}

int Data::getZi() const
{
    return zi;
}

void Data::setZi(int zi)
{
    Data::zi = zi;
}

int Data::getLuna() const
{
    return luna;
}

void Data::setLuna(int luna)
{
    Data::luna = luna;
}

int Data::getAn() const
{
    return an;
}

void Data::setAn(int an)
{
    Data::an = an;
}

Data& Data::operator=(const Data& d)
{
    this->zi = d.zi;
    this->luna = d.luna;
    this->an = d.an;
    return *this;
}

Data& Data::operator++()
{
    int rest = 0;
    this->zi++;
    rest = int(this->zi / 31);
    this->zi %= 31;

    this->luna += rest;
    rest = int(this->luna / 12);
    this->luna %= 12;

    this->an += rest;

    return *this;
}

Data& Data::operator--()
{
    this->zi--;
    if (this->zi <= 0)
    {
        this->zi += 31;
        this->luna -= 1;
        if (this->luna <= 0)
        {
            this->luna += 12;
            this->an -= 1;
        }
    }
    return *this;
}

Data& Data::operator+(int x)
{
    for (int i = 0; i < x; i++)
        this->operator++();
    return *this;
}

Data& Data::operator++(int)
{
    this->operator++();
    return *this;
}

Data& Data::operator--(int)
{
    this->operator--();
    return *this;
}

Data& Data::operator-=(int x)
{
    for (int i = 0; i < x; i++)
        this->operator--();
    return *this;
}

Data& Data::operator+=(int x)
{
    for (int i = 0; i < x; i++)
        this->operator++();
    return *this;
}

bool Data::operator==(const Data& s)
{
    return this->an == s.an && this->luna == s.luna && this->zi == s.zi;
}

bool Data::operator!=(const Data& s)
{
    return !this->operator==(s);
}

bool Data::operator<(const Data& m)
{
    if (this->an < m.an)
        return true;
    else if (this->an > m.an)
        return false;
    else
    {
        if (this->luna < m.luna)
            return true;
        else if (this->luna > m.luna)
            return false;
        else
        {
            if (this->zi < m.zi)
                return true;
            else
                return false;
        }
    }
}

bool Data::operator>(const Data& m)
{
    if (!this->operator==(m) and !this->operator<(m))
        return true;
    return false;
}

bool Data::operator<=(const Data& m)
{
    if (this->operator<(m) || this->operator==(m))
        return true;
    return false;
}

bool Data::operator>=(const Data& m)
{
    if (this->operator>(m) || this->operator==(m))
        return true;
    return false;
}

/// -------------------------   CLASA MATERIAL   -------------------------

class Material : public virtual IO
{
protected:
    const int idMaterial;
    char* numeMaterial;
    char* unitateDeMasura;
    Data dataExpirare;
    float pretUnitar;
    int cantitate;
    static int nrTotalMateriale;

public:
    Material();

    Material(const char*, const char*, float, int, int, int, int);

    Material(const char*, const char*, float, int, Data);

    Material(const Material&);

    const int getIdMaterial() const;

    char* getNumeMaterial() const;

    void setNumeMaterial(char* numeMaterial);

    char* getUnitateDeMasura() const;

    void setUnitateDeMasura(char* unitateDeMasura);

    const Data& getDataExpirare() const;

    void setDataExpirare(const Data& dataExpirare);

    float getPretUnitar() const;

    int getCantitate() const;

    static int getNrTotalMateriale();

    static void setNrTotalMateriale(int nrTotalMateriale);

    Material& operator=(const Material&);

    Material& operator+(float);

    virtual Material& operator++();

    virtual Material& operator--();

    virtual Material& operator++(int)
    {
        this->operator++();
        return *this;
    }

    virtual Material& operator--(int)
    {
        this->operator--();
        return *this;
    }

    virtual Material& operator-=(float x)
    {
        this->pretUnitar -= x;
        return *this;
    }

    Material& operator+=(float x)
    {
        this->pretUnitar += x;
        return *this;
    }

    bool operator!=(Material& s)
    {
        if (strcmp(this->numeMaterial, s.numeMaterial) != 0)
            return true;
        return false;
    }

    bool operator<(const Material& m) const
    {
        return this->cantitate < m.cantitate;
    }

    bool operator>(const Material& m) const
    {
        return this->cantitate > m.cantitate;
    }

    bool operator<=(const Material& m) const
    {
        return this->cantitate <= m.cantitate;
    }

    bool operator>=(const Material& m) const
    {
        return this->cantitate >= m.cantitate;
    }

    bool operator==(const Material& m)
    {
        return strcmp(this->unitateDeMasura, m.unitateDeMasura) == 0 and this->cantitate == m.cantitate and
            this->pretUnitar == m.pretUnitar;
    }

    void read(istream&) override;

    void write(ostream&) const override;

    virtual ~Material()
    {
        if (this->numeMaterial != nullptr)
            delete[] this->numeMaterial;
        if (this->unitateDeMasura != nullptr)
            delete[] this->unitateDeMasura;
    }
};

Material::Material() : idMaterial(nrTotalMateriale++)
{
    numeMaterial = new char[4];
    strcpy(numeMaterial, "N/A");
    unitateDeMasura = new char[4];
    strcpy(unitateDeMasura, "N/A");
}

Material::Material(const char* nume, const char* unitate, float pretU, int cant, int zi, int luna, int an) : idMaterial(nrTotalMateriale++), dataExpirare(zi, luna, an)
{
    this->numeMaterial = new char[strlen(nume) + 1];
    strcpy(this->numeMaterial, nume);
    this->unitateDeMasura = new char[strlen(unitate) + 1];
    strcpy(this->unitateDeMasura, unitate);
    pretUnitar = pretU;
    cantitate = cant;
}

Material::Material(const char* nume, const char* unitate, float pretU, int cant, Data dateExpirare) : idMaterial(nrTotalMateriale++), dataExpirare(dateExpirare)
{
    this->numeMaterial = new char[strlen(nume) + 1];
    strcpy(this->numeMaterial, nume);
    this->unitateDeMasura = new char[strlen(unitate) + 1];
    strcpy(this->unitateDeMasura, unitate);
    pretUnitar = pretU;
    cantitate = cant;
}

Material::Material(const Material& m) : idMaterial(m.getIdMaterial())
{
    if (m.numeMaterial == nullptr)
        this->numeMaterial = nullptr;
    else
    {
        this->numeMaterial = new char[strlen(m.numeMaterial) + 1];
        strcpy(this->numeMaterial, m.numeMaterial);
    }
    if (m.unitateDeMasura == nullptr)
        this->unitateDeMasura = nullptr;
    else
    {
        this->unitateDeMasura = new char[strlen(m.unitateDeMasura) + 1];
        strcpy(this->unitateDeMasura, m.unitateDeMasura);
    }
    this->dataExpirare = m.dataExpirare;
    this->pretUnitar = m.pretUnitar;
    this->cantitate = m.cantitate;
}

Material& Material::operator=(const Material& m)
{
    if (&m == this)
        return *this;

    if (m.numeMaterial != nullptr)
    {
        if (this->numeMaterial != nullptr)
            delete[] this->numeMaterial;
    }
    this->numeMaterial = new char[strlen(m.numeMaterial) + 1];
    strcpy(this->numeMaterial, m.numeMaterial);

    if (m.unitateDeMasura != nullptr)
    {
        if (this->unitateDeMasura != nullptr)
            delete[] this->unitateDeMasura;
    }
    this->unitateDeMasura = new char[strlen(m.unitateDeMasura) + 1];
    strcpy(this->unitateDeMasura, m.unitateDeMasura);

    this->dataExpirare = m.dataExpirare;
    this->pretUnitar = m.pretUnitar;
    this->cantitate = m.cantitate;

    return *this;
}

Material& Material::operator+(const float x)
{
    this->pretUnitar += x;
    return *this;
}

Material& Material::operator++()
{
    this->pretUnitar += 1.0;
    return *this;
}

Material& Material::operator--()
{
    this->pretUnitar -= 1.0;
    return *this;
}

const int Material::getIdMaterial() const
{
    return idMaterial;
}

char* Material::getNumeMaterial() const
{
    return numeMaterial;
}

void Material::setNumeMaterial(char* numeMaterial)
{
    Material::numeMaterial = numeMaterial;
}

char* Material::getUnitateDeMasura() const
{
    return unitateDeMasura;
}

void Material::setUnitateDeMasura(char* unitateDeMasura)
{
    Material::unitateDeMasura = unitateDeMasura;
}

const Data& Material::getDataExpirare() const
{
    return dataExpirare;
}

void Material::setDataExpirare(const Data& dataExpirare)
{
    Material::dataExpirare = dataExpirare;
}

int Material::getNrTotalMateriale()
{
    return nrTotalMateriale;
}

void Material::setNrTotalMateriale(int nrTotalMateriale)
{
    Material::nrTotalMateriale = nrTotalMateriale;
}

float Material::getPretUnitar() const
{
    return pretUnitar;
}

int Material::getCantitate() const
{
    return cantitate;
}

void Material::read(istream& in)
{
    cout << "Introduceti numele materialului (char*, maxim 25 caractere) :";
    this->numeMaterial = new char[25];
    in.get(this->numeMaterial, 25);
    in.get();
    cout << "Introduceti unitatea de masura (char*, maxim 25 caractere) :";
    this->unitateDeMasura = new char[25];
    in.get(this->unitateDeMasura, 25);
    in.get();
    cout << "Introduceti data de expirare :";
    dataExpirare.read(in);

    cout << "Introduceti pretul unitar (float, pozitiv) :";
    do
    {
        in >> this->pretUnitar;
        if (this->pretUnitar < 0.0)
            cout << "Gresit ! Pretul trebuie sa fie pozitiv. Reintroduceti :";
    } while (this->pretUnitar < 0.0);

    cout << "Introduceti cantitatea (int, pozitiv) :";
    do
    {
        in >> this->cantitate;
        if (this->cantitate < 0)
            cout << "Gresit ! Cantitatea trebuie sa fie pozitiva. Reintroduceti :";
    } while (this->cantitate < 0);
}

void Material::write(ostream& out) const
{
    out << "Material{id=";
    out << this->idMaterial << ", nume=";
    out << this->numeMaterial;
    out << ", unitate de masura=" << this->unitateDeMasura;
    out << ", dataExpirare=";
    dataExpirare.write(out);
    out << ", pret=" << this->pretUnitar;
    out << ", cantitate=" << this->cantitate;
    out << "}";
}

/// -------------------------   CLASA PRODUS   -------------------------

class Produs : public virtual IO
{
protected:
    const int idProdus;
    char* denumireProdus;
    Data dataExpirare;
    bool esteDePost;
    bool perisabil;
    int gramaj;
    float pret;
    Categorie categorie;
    TipProdus tipProdus;
    map<string, int> materialeFolosite;

    static int nrTotalProduse;

public:
    Produs();

    Produs(const char*, int, int, int, bool, bool, int, char*, char*);

    Produs(char*, Data, bool, bool, int, Categorie, TipProdus, float);

    Produs(const Produs&);

    const int getIdProdus() const;

    bool addMaterial(Material&, int);

    bool removeMaterial(Material&);

    char* getDenumireProdus() const;

    void setDenumireProdus(char* denumireProdus);

    float getPret() const;

    void setPret(float pret);

    const Data& getDataExpirare() const;

    void setDataExpirare(const Data& dataExpirare);

    bool isEsteDePost() const;

    void setEsteDePost(bool esteDePost);

    bool isPerisabil() const;

    void setPerisabil(bool perisabil);

    int getGramaj() const;

    void setGramaj(int gramaj);

    Categorie getCategorie() const;

    void setCategorie(Categorie categorie);

    TipProdus getTipProdus() const;

    void setTipProdus(TipProdus tipProdus);

    map<string, int> getMaterialeFolosite() const;

    void setMaterialeFolosite(map<string, int> materialeFolosite);

    Produs& operator=(const Produs&);

    Produs& operator+(int);

    virtual Produs& operator++();

    virtual Produs& operator--();

    virtual Produs& operator++(int)
    {
        this->operator++();
        return *this;
    }

    virtual Produs& operator--(int)
    {
        this->operator--();
        return *this;
    }

    virtual Produs& operator-=(float x)
    {
        this->gramaj -= x;
        return *this;
    }

    Produs& operator+=(float x)
    {
        this->gramaj += x;
        return *this;
    }

    bool operator!=(Produs& s)
    {
        if (strcmp(this->denumireProdus, s.denumireProdus) != 0)
            return true;
        return false;
    }

    bool operator<(const Produs& m) const
    {
        return this->gramaj < m.gramaj;
    }

    bool operator>(const Produs& m) const
    {
        return this->gramaj > m.gramaj;
    }

    bool operator<=(const Produs& m) const
    {
        return this->gramaj <= m.gramaj;
    }

    bool operator>=(const Produs& m) const
    {
        return this->gramaj >= m.gramaj;
    }

    bool operator==(const Produs& m)
    {
        return strcmp(this->denumireProdus, m.denumireProdus) == 0 and this->gramaj == m.gramaj and
            this->esteDePost == m.esteDePost and this->perisabil == m.perisabil;
    }

    void read(istream&) override;

    void write(ostream&) const override;

    virtual ~Produs()
    {
        if (denumireProdus != nullptr)
            delete[] denumireProdus;
    }
};

Produs::Produs() : idProdus(nrTotalProduse++)
{
    denumireProdus = new char[4];
    strcpy(denumireProdus, "N/A");
    esteDePost = true;
    perisabil = true;
    gramaj = 0;
    tipProdus = TipProdus::AltTip;
    categorie = Categorie::AltaCategorie;
    pret = 0;
}

Produs::Produs(const char* denumireProdus, int zi, int luna, int an, bool esteDePost, bool perisabil, int gramaj,
    char* categorie, char* tipProdus) : idProdus(nrTotalProduse++), dataExpirare(zi, luna, an)
{
    Checker<int>::throwIfNotPositive(gramaj);

    this->denumireProdus = new char[strlen(denumireProdus) + 1];
    strcpy(this->denumireProdus, denumireProdus);
    this->esteDePost = esteDePost;
    this->perisabil = perisabil;
    this->gramaj = gramaj;
    this->categorie = convertToCategorie(categorie);
    this->tipProdus = convertToTipProdus(tipProdus);
    this->pret = 0;
}

Produs::Produs(char* denumireProdus, Data dataExpirare, bool esteDePost, bool perisabil, int gramaj, Categorie categorie,
    TipProdus tipProdus, float pret) : idProdus(nrTotalProduse++), dataExpirare(dataExpirare)
{
    Checker<int>::throwIfNotPositive(gramaj);

    this->denumireProdus = new char[strlen(denumireProdus) + 1];
    strcpy(this->denumireProdus, denumireProdus);
    this->esteDePost = esteDePost;
    this->perisabil = perisabil;
    this->gramaj = gramaj;
    this->categorie = categorie;
    this->tipProdus = tipProdus;
    this->pret = pret;
}

Produs::Produs(const Produs& m) : idProdus(nrTotalProduse++), dataExpirare(m.dataExpirare)
{
    this->denumireProdus = new char[strlen(m.denumireProdus) + 1];
    strcpy(this->denumireProdus, m.denumireProdus);
    this->esteDePost = m.esteDePost;
    this->perisabil = m.perisabil;
    this->gramaj = m.gramaj;
    this->categorie = m.categorie;
    this->tipProdus = m.tipProdus;
    this->materialeFolosite = m.materialeFolosite;
    this->pret = m.pret;
}

Produs& Produs::operator=(const Produs& m)
{
    if (&m == this)
        return *this;

    if (m.denumireProdus != nullptr)
    {
        if (this->denumireProdus != nullptr)
            delete[] this->denumireProdus;
    }
    this->denumireProdus = new char[strlen(m.denumireProdus) + 1];
    strcpy(this->denumireProdus, m.denumireProdus);

    this->dataExpirare = m.dataExpirare;
    this->esteDePost = m.esteDePost;
    this->perisabil = m.perisabil;
    this->categorie = m.categorie;
    this->tipProdus = m.tipProdus;
    this->materialeFolosite = m.materialeFolosite;
    this->pret = m.pret;

    return *this;
}

Produs& Produs::operator+(const int x)
{
    this->gramaj += x;
    return *this;
}

Produs& Produs::operator++()
{
    this->gramaj += 1;
    return *this;
}

Produs& Produs::operator--()
{
    this->gramaj -= 1;
    return *this;
}

void Produs::read(istream& in)
{
    char* s = new char[25];
    int x;

    cout << "Introduceti denumirea produsului (char*, maxim 25 caractere) : ";
    this->denumireProdus = new char[25];
    in.getline(this->denumireProdus, 25);

    cout << "Introduceti pretul produsului (float) :";
    in >> this->pret;

    cout << "Este de post ? (bool : 1/0) :";
    do
    {
        in >> x;
        if (x < 0 || x > 1)
            cout << "Gresit ! Trebuie sa fie 1/0. Reintroduceti :";
        else
            this->esteDePost = x;
    } while (x < 0 || x > 1);

    cout << "Este perisabil ? (bool : 1/0) :";
    do
    {
        in >> x;
        if (x < 0 || x > 1)
            cout << "Gresit ! Trebuie sa fie 1/0. Reintroduceti :";
        else
            this->perisabil = x;
    } while (x < 0 || x > 1);

    cout << "Introduceti gramajul (int : pozitiv) :";
    do
    {
        in >> this->gramaj;
        if (this->gramaj < 0)
            cout << "Gresit ! Gramajul trebuie sa fie pozitiv. Reintroduceti :";
    } while (this->gramaj < 0);

    cout << "Introduceti data de expirare :";
    dataExpirare.read(in);
    in.get();

    cout << "Introduceti tipul de produs (enum : REFRIGERAT / PROASPAT) :";
    do
    {
        in.getline(s, 25);
        this->tipProdus = convertToTipProdus(s);
        if (this->tipProdus == TipProdus::AltTip)
            cout << "Gresit ! Tipul de produs trebuie sa fie REFRIGERAT / PROASPAT. Reintroduceti : ";
    } while (this->tipProdus == TipProdus::AltTip);

    cout << "Introduceti tipul de de produs (enum : RULADE / PATISERIE / PRAJITURI) :";
    do
    {
        in.get(s, 25);
        this->categorie = convertToCategorie(s);
        if (this->categorie == Categorie::AltaCategorie)
            cout << "Gresit ! Tipul de produs trebuie sa fie RULADE / PATISERIE / PRAJITURI. Reintroduceti : ";
    } while (this->categorie == Categorie::AltaCategorie);
    in.get();

    cout << "Introduceti numarul de materiale necesar pentru acest produs (int, pozitiv) : ";
    int nr;
    do
    {
        in >> nr;
        if (nr < 0)
            cout << "Gresit ! Numarul trebuie sa fie pozitiv. Reintroduceti :";
    } while (nr < 0);

    string temp;
    int cant;
    in.get();
    for (int i = 0; i < nr; i++)
    {
        cout << "Introduceti numele materialului numarul " << i << " : ";
        in >> temp;
        cout << " Introduceti numarul de unitati ale acestui tip de material (int, pozitiv) :";
        in >> cant;
        materialeFolosite.insert({ temp, cant });
    }
}

void Produs::write(ostream& out) const
{
    out << "Produs{denumireProdus=" << this->denumireProdus;
    out << ", dataExpirare=";
    dataExpirare.write(out);
    out << ", pret=" << this->pret << " RON";
    out << ", esteDePost=" << this->esteDePost;
    out << ", perisabil=" << this->perisabil;
    out << ", gramaj=" << this->gramaj;
    out << ", categorie=" << convertToChar(categorie);
    out << ", tipProdus=" << convertToChar(tipProdus);
    out << ", materialeFolosite={";
    for (auto& x : materialeFolosite)
    {
        out << " material=" << x.first << ", cantitate=" << x.second << ";";
    }
    out << "}}";
}

bool Produs::addMaterial(Material& material, int cant)
{
    // daca exista deja in map materialul pe care incerc sa il adaug, returnez false
    string nume = material.getNumeMaterial();
    if (materialeFolosite.find(nume) != materialeFolosite.end())
        return false;
    materialeFolosite.insert({ nume, cant });
    return true;
}

bool Produs::removeMaterial(Material& material)
{
    // daca nu exista in map materialul pe care incerc sa il sterg, returnez false
    string nume = material.getNumeMaterial();
    if (materialeFolosite.find(nume) == materialeFolosite.end())
        return false;
    materialeFolosite.erase(nume);
    return true;
}

char* Produs::getDenumireProdus() const
{
    return denumireProdus;
}

void Produs::setDenumireProdus(char* denumireProdus)
{
    Produs::denumireProdus = denumireProdus;
}

float Produs::getPret() const
{
    return pret;
}

void Produs::setPret(float pret)
{
    Produs::pret = pret;
}

const Data& Produs::getDataExpirare() const
{
    return dataExpirare;
}

void Produs::setDataExpirare(const Data& dataExpirare)
{
    Produs::dataExpirare = dataExpirare;
}

bool Produs::isEsteDePost() const
{
    return esteDePost;
}

void Produs::setEsteDePost(bool esteDePost)
{
    Produs::esteDePost = esteDePost;
}

bool Produs::isPerisabil() const
{
    return perisabil;
}

void Produs::setPerisabil(bool perisabil)
{
    Produs::perisabil = perisabil;
}

int Produs::getGramaj() const
{
    return gramaj;
}

void Produs::setGramaj(int gramaj)
{
    Produs::gramaj = gramaj;
}

Categorie Produs::getCategorie() const
{
    return categorie;
}

void Produs::setCategorie(Categorie categorie)
{
    Produs::categorie = categorie;
}

TipProdus Produs::getTipProdus() const
{
    return tipProdus;
}

void Produs::setTipProdus(TipProdus tipProdus)
{
    Produs::tipProdus = tipProdus;
}

const int Produs::getIdProdus() const
{
    return idProdus;
}

map<string, int> Produs::getMaterialeFolosite() const
{
    return materialeFolosite;
}

void Produs::setMaterialeFolosite(map<string, int> materialeFolosite)
{
    Produs::materialeFolosite = materialeFolosite;
}

/// -------------------------   CLASA PATISERIE   -------------------------

class Patiserie : public IO
{
protected:
    const int idPatiserie;
    string numePatiserie;
    Data dataInfiintere;
    int nrProduse;
    string adresa;
    map<Produs, int> produse;

    static int nrTotalPatiserii;

public:
    Patiserie();

    Patiserie(string, Data, string, int);

    Patiserie(const Patiserie&);

    const string& getNumePatiserie() const;
    void setNumePatiserie(const string& numePatiserie);

    Data getDataInfiintare() const;
    void setDataInfiintare(Data dataInfiintare);

    const string& getAdresa() const;
    void setAdresa(const string& adresa);

    int getNrProduse() const;
    void setNrProduse(int nrProduse);

    const map<Produs, int>& getProduse() const;
    void setProduse(const map<Produs, int>& produse);

    const int& getIdPatiserie() const;
    static int getNrTotalPatiserii();

    void adaugareProdus(Produs, int);
    void stergereProdus(Produs);
    void stergereProdusCuNume(string);
    void afisareProduse();

    void read(istream&) override;

    void write(ostream&) const override;

    Patiserie& operator=(const Patiserie&);

    ~Patiserie();
};

Patiserie::Patiserie() : idPatiserie(++nrTotalPatiserii)
{
    this->numePatiserie = "Necunoscut";
    this->dataInfiintere = Data();
    this->nrProduse = 0;
    this->produse = map<Produs, int>();
}

Patiserie::Patiserie(string numePatiserie, Data dataInfiintere, string adresa, int nrProduse) : idPatiserie(++nrTotalPatiserii)
{
    this->numePatiserie = numePatiserie;
    this->dataInfiintere = dataInfiintere;
    this->adresa = adresa;
    this->nrProduse = nrProduse;
    this->produse = map<Produs, int>();
}

Patiserie::Patiserie(const Patiserie& patiserie) : idPatiserie(++nrTotalPatiserii)
{
    this->numePatiserie = patiserie.numePatiserie;
    this->dataInfiintere = patiserie.dataInfiintere;
    this->adresa = patiserie.adresa;
    this->nrProduse = patiserie.nrProduse;
    this->produse = patiserie.produse;
}

const string& Patiserie::getNumePatiserie() const
{
    return numePatiserie;
}

void Patiserie::setNumePatiserie(const string& numePatiserie)
{
    Patiserie::numePatiserie = numePatiserie;
}

Data Patiserie::getDataInfiintare() const
{
    return dataInfiintere;
}

void Patiserie::setDataInfiintare(Data dataInfiintare)
{
    Patiserie::dataInfiintere = dataInfiintare;
}

int Patiserie::getNrProduse() const
{
    return nrProduse;
}

void Patiserie::setNrProduse(int nrProduse)
{
    Patiserie::nrProduse = nrProduse;
}

const map<Produs, int>& Patiserie::getProduse() const
{
    return produse;
}

void Patiserie::setProduse(const map<Produs, int>& produse)
{
    Patiserie::produse = produse;
}

const int& Patiserie::getIdPatiserie() const
{
    return idPatiserie;
}

int Patiserie::getNrTotalPatiserii()
{
    return nrTotalPatiserii;
}

const string& Patiserie::getAdresa() const
{
    return adresa;
}

void Patiserie::setAdresa(const string& adresa)
{
    Patiserie::adresa = adresa;
}

void Patiserie::adaugareProdus(Produs produs, int cantitate)
{
    this->produse.insert(pair<Produs, int>(produs, cantitate));
    this->nrProduse++;
}

void Patiserie::stergereProdus(Produs produs)
{
    this->produse.erase(produs);
    this->nrProduse--;
}

void Patiserie::stergereProdusCuNume(string numeProdus)
{
    for (auto it = this->produse.begin(); it != this->produse.end(); it++)
    {
        if (it->first.getDenumireProdus() == numeProdus)
        {
            this->produse.erase(it);
            this->nrProduse--;
            break;
        }
    }
}

void Patiserie::afisareProduse()
{
    cout << "Produsele sunt: " << endl;
    for (auto it = this->produse.begin(); it != this->produse.end(); it++)
    {
        cout << "Produsul: " << it->first.getDenumireProdus() << " cu pretul: " << it->first.getPret() << " si cantitatea: " << it->second << endl;
    }
}

void Patiserie::read(istream& in)
{
    cout << "Numele patiseriei este: ";
    in >> this->numePatiserie;
    cout << "Data infiintarii este: ";
    in >> this->dataInfiintere;
    cout << "Numarul de produse este: ";
    in >> this->nrProduse;
    cout << "Produsele sunt: ";
    for (int i = 0; i < this->nrProduse; i++)
    {
        Produs produs;
        in >> produs;
        this->produse.insert(pair<Produs, int>(produs, 0));
    }
}

void Patiserie::write(ostream& out) const
{
    out << "Numele patiseriei este: " << this->numePatiserie << endl;
    out << "Data infiintarii este: " << this->dataInfiintere << endl;
    out << "Numarul de produse este: " << this->nrProduse << endl;
}

Patiserie& Patiserie::operator=(const Patiserie& patiserie)
{
    this->numePatiserie = patiserie.numePatiserie;
    this->nrProduse = patiserie.nrProduse;
    this->produse = patiserie.produse;
    return *this;
}

Patiserie::~Patiserie()
{
    this->numePatiserie = "";
    this->nrProduse = 0;
    this->produse.clear();
}

/// -------------------------   Template pentru vectori specifici   -------------------------

template <class T>
class Gestiune : public IO
{
    vector<T> obiecte;

public:
    Gestiune() = default;

    ~Gestiune() = default;

    int get_nr_obiecte();

    vector<T>& getVector();

    void afis_pozitia_i(int x);

    Gestiune& operator+=(const T&);

    Gestiune& operator-=(const T&);

    void read(istream&) override;

    void write(ostream&) const override;
};

template <class T>
void Gestiune<T>::read(istream& in)
{
    cout << "Numarul de obiecte pe care vreti sa le cititi este (int, pozitiv) :";
    int x;
    in >> x;
    for (int i = 0; i < x; i++)
    {
        T object;
        in >> object;
        obiecte.push_back(object);
    }
}

template <class T>
void Gestiune<T>::write(ostream& out) const
{
    for (auto& x : obiecte)
        out << x << endl;
}

template <class T>
int Gestiune<T>::get_nr_obiecte()
{
    return this->obiecte.size();
}

template <class T>
vector<T>& Gestiune<T>::getVector()
{
    return obiecte;
}

template <class T>
void Gestiune<T>::afis_pozitia_i(int x)
{
    cout << obiecte[x];
}

template <class T>
Gestiune<T>& Gestiune<T>::operator+=(const T& g)
{
    this->obiecte.push_back(g);
    return (*this);
}

template <class T>
Gestiune<T>& Gestiune<T>::operator-=(const T& g)
{
    for (int i = 0; i < this->obiecte.size(); i++)
    {
        if (this->obiecte[i] == g)
        {
            this->obiecte.erase(this->obiecte.begin() + i);
            break;
        }
    }
    return (*this);
}

/// -------------------------   SINGLETON PT MENIU INTERACTIV   -------------------------

class Meniu
{
private:
    Gestiune<Material> materiale;
    Gestiune<Produs> produse;
    Patiserie patiserie;

    vector<pair<string, function<void()>>> menu;

    static Meniu* instanta;

public:
    Meniu();

    Meniu(const Meniu&) = delete;

    Meniu& operator=(const Meniu&) = delete;

    Material getMatreialByDenumire(const string denumire)
    {
        for (auto& x : materiale.getVector())
        {
            if (x.getNumeMaterial() == denumire)
                return x;
        }
        return Material();
    }

    ~Meniu();

    void run();

    const Gestiune<Material>& getMateriale() const;

    const Gestiune<Produs>& getProduse() const;

    const Patiserie getPatiserii() const;

    void citireFisierPatiserie();
    void citireFisierMateriale();
    void citireFisierProduse();

    pair<string, string> citireLinie(string str);
    string tipFisier(string str);
    Data citireData(string str);
    map<string, int> citireMateriale(string str);
    Material getMaterialByDenumire(string denumire);
};

Material Meniu::getMaterialByDenumire(string denumire)
{
    for (auto& x : materiale.getVector())
    {
        if (x.getNumeMaterial() == denumire)
            return x;
    }
    return Material();
}

pair<string, string> Meniu::citireLinie(string str)
{
    char aux[1000000];
    strcpy(aux, str.c_str());
    char* ptr = strtok(aux, ":");
    bool fieldOcupat = false;
    pair<string, string> rezultat;
    rezultat = make_pair("", "");
    while (ptr != NULL)
    {
        if (fieldOcupat)
        {
            rezultat.second = ptr;
        }
        else
        {
            rezultat.first = ptr;
        }
        ptr = strtok(NULL, ":");
        fieldOcupat = true;
    }
    if (rezultat.second[0] == ' ')
        rezultat.second = rezultat.second.substr(1, rezultat.second.length() - 1);
    return rezultat;
}

string Meniu::tipFisier(string str)
{
    string rezultat = "";
    for (size_t i = str.length() - 1; i >= 0; --i)
    {
        if (str[i] == '.')
            break;
        rezultat += str[i];
    }
    reverse(rezultat.begin(), rezultat.end());
    return rezultat;
}

Data Meniu::citireData(string str)
{
    vector<string> rezultat;
    char aux[1000000];
    strcpy(aux, str.c_str());
    char* ptr = strtok(aux, "./");
    while (ptr != NULL)
    {
        rezultat.push_back(ptr);
        ptr = strtok(NULL, "./");
    }
    Data data(stoi(rezultat[0]), stoi(rezultat[1]), stoi(rezultat[2]));
    return data;
}

map<string, int> Meniu::citireMateriale(string str)
{
    map<string, int> rezultat;
    char aux[1000000];
    strcpy(aux, str.c_str());
    char* ptr = strtok(aux, ",-");
    while (ptr != NULL)
    {
        if (ptr[0] == ' ')
            ptr = ptr + 1;
        pair<string, string> produs;
        produs.first = ptr;
        ptr = strtok(NULL, ",-");
        produs.second = ptr;
        ptr = strtok(NULL, ",-");
        // Material material = getMaterialByDenumire(produs.first);
        string material = produs.first;
        int cantitate = stoi(produs.second.size() == 0 ? "0" : produs.second);
        rezultat[material] = cantitate;
    }
    return rezultat;
}

void Meniu::citireFisierMateriale()
{
    bool fisierValid = false;
    while (!fisierValid)
    {
        cout << "Introduceti numele fisierului: ";
        string numeFisier = "";
        getline(cin, numeFisier);
        if ([](string str) -> bool
            { transform(str.begin(), str.end(), str.begin(), ::tolower); return str == "back"; }(numeFisier))
        {
            break;
        }
        ifstream fisier(numeFisier);
        if (fisier.is_open())
        {
            fisierValid = true;
            cout << "Fisierul a fost deschis cu succes!" << endl;
            if (tipFisier(numeFisier) == "txt")
            {
                string linie;
                map<string, string> date;
                while (getline(fisier, linie))
                {
                    pair<string, string> pereche = citireLinie(linie);
                    date[pereche.first] = pereche.second;
                    if (date.size() == 5)
                    {
                        char* numeMaterial = new char[date["Nume Material"].length() + 1];
                        strcpy(numeMaterial, date["Nume Material"].c_str());
                        char* unitateDeMasura = new char[date["Unitate De Masura"].length() + 1];
                        strcpy(unitateDeMasura, date["Unitate De Masura"].c_str());
                        Data dataExpirare = citireData(date["Data Expirare"].size() ? date["Data Expirare"] : "1/1/2000");
                        float pretUnitar = stof(date["Pret Unitar"].size() ? date["Pret Unitar"] : "0");
                        int cantitate = stoi(date["Cantitate"].size() ? date["Cantitate"] : "0");
                        Material material(numeMaterial, unitateDeMasura, pretUnitar, cantitate, dataExpirare);
                        materiale += material;
                        date.clear();
                        getline(fisier, linie);
                    }
                }
            }
            else
            {
                cout << "Fisierul nu este valid!" << endl;
            }
        }
        else
        {
            cout << "Fisierul nu a putut fi deschis!" << endl;
        }
    }
}

void Meniu::citireFisierPatiserie()
{

    bool fisierValid = false;
    string linie;
    map<string, string> date;
    while (!fisierValid)
    {
        cout << "Introduceti numele fisierului: ";
        string numeFisier = "";
        getline(cin, numeFisier);
        if ([](string str) -> bool
            { transform(str.begin(), str.end(), str.begin(), ::tolower); return str == "back"; }(numeFisier))
        {
            break;
        }
        ifstream fisier(numeFisier);
        if (fisier.is_open())
        {
            fisierValid = true;
            cout << "Fisierul a fost deschis cu succes!" << endl;
            if (tipFisier(numeFisier) == "txt")
            {
                while (getline(fisier, linie))
                {
                    pair<string, string> rezultat = citireLinie(linie);
                    date[rezultat.first] = rezultat.second;
                    if (date.size() == 4)
                    {
                        string numePatiserie = date["Nume Patiserie"];
                        Data dataInfiintare = citireData(date["Data"]);
                        string adresa = date["Adresa"];
                        int nrProduse = std::stoi(date["Numar Produse"].size() ? date["Numar Produse"] : "0");
                        Patiserie p(numePatiserie, dataInfiintare, adresa, nrProduse);
                        patiserie = p;
                        date.clear();
                    }
                }
            }
            else
            {
                cout << "Fisierul nu este suportat!" << endl;
            }
            // banci[0].setBanci(banci, nrBanci);

            fisier.close();
        }
        else
        {
            cout << "Fisierul nu a putut fi deschis! \nIncercati din nou, ori tastati back pentru a reveni la meniul anterior" << endl;
        }
    }
}

void Meniu::citireFisierProduse()
{
    bool fisierValid = false;
    string linie;
    map<string, string> date;
    while (!fisierValid)
    {
        cout << "Introduceti numele fisierului: ";
        string numeFisier = "";
        getline(cin, numeFisier);
        if ([](string str) -> bool
            { transform(str.begin(), str.end(), str.begin(), ::tolower); return str == "back"; }(numeFisier))
        {
            break;
        }
        ifstream fisier(numeFisier);
        if (fisier.is_open())
        {
            fisierValid = true;
            cout << "Fisierul a fost deschis cu succes!" << endl;
            if (tipFisier(numeFisier) == "txt")
            {
                while (getline(fisier, linie))
                {
                    pair<string, string> rezultat = citireLinie(linie);
                    date[rezultat.first] = rezultat.second;
                    if (date.size() == 10)
                    {
                        char* denumireProdus = new char[date["Denumire"].length() + 1];
                        strcpy(denumireProdus, date["Denumire"].c_str());
                        Data dataExpirare = citireData(date["Data Expirare"]);
                        bool esteDePost = date["Este de post"] == "Da" ? true : false;
                        bool perisabil = date["Perisabil"] == "Da" ? true : false;
                        char* stringCategorie = new char[date["Categorie"].length() + 1];
                        strcpy(stringCategorie, date["Categorie"].c_str());
                        Categorie categorie = convertToCategorie(stringCategorie);
                        char* stringTipProdus = new char[date["Tip Produs"].length() + 1];
                        strcpy(stringTipProdus, date["Tip Produs"].c_str());
                        TipProdus tipProdus = convertToTipProdus(stringTipProdus);
                        int gramaj = stoi(date["Gramaj"].size() ? date["Gramaj"] : "0");
                        int cantitate = stoi(date["Cantitate"].size() ? date["Cantitate"] : "0");
                        float pret = stof(date["Pret"].size() ? date["Pret"] : "0");
                        Produs produs(denumireProdus, dataExpirare, esteDePost, perisabil, gramaj, categorie, tipProdus, pret);
                        map<string, int> materiale;
                        materiale = citireMateriale(date["Materiale"]);
                        produs.setMaterialeFolosite(materiale);
                        patiserie.adaugareProdus(produs, cantitate);
                        getline(fisier, linie);
                        date.clear();
                    }
                }
            }
            else
            {
                cout << "Fisierul nu este suportat!" << endl;
            }
            // banci[0].setBanci(banci, nrBanci);

            fisier.close();
        }
        else
        {
            cout << "Fisierul nu a putut fi deschis! \nIncercati din nou, ori tastati back pentru a reveni la meniul anterior" << endl;
        }
    }
}

Meniu::Meniu()
{

    menu.push_back(make_pair("Citirea datelor din fisier", [&]()
        {
            do {
                cout << "Ce doriti sa cititi din fisier?\n";
                cout << "1.Citirea datelor despre Patiserie\n";
                cout << "2.Citirea datelor despre Materiale\n";
                cout << "3.Citirea datelor despre Produse\n";
                cout << "4.Revenire la meniul anterior\n";
                try {
                    int optiune;
                    cout << "Optiunea dumneavoastra este: ";
                    cin >> optiune;
                    cin.ignore();
                    switch (optiune)
                    {
                    case 1:
                        citireFisierPatiserie();
                        break;
                    case 2:
                        citireFisierMateriale();
                        break;
                    case 3:
                        citireFisierProduse();
                        break;
                    case 4:
                        return;
                    default:
                        cout << "Optiunea nu este valida! Incercati din nou" << endl;
                        break;
                    }
                }
                catch (exception e)
                {
                    cout << "Optiunea nu este valida! Incercati din nou" << endl;
                }
            } while (true); }));

    menu.push_back(make_pair("Meniu Materiale", [&]()
        {
            int optiune;
            do {
                cout << "Ce doriti sa faceti cu Materialele din aplicatie?\n";
                cout << "1.Afisarea tuturor Materialelor\n";
                cout << "2.Afisarea unui Material in functie de numarul de ordine\n";
                cout << "3.Afisarea costului unui Material in functie de numarul de ordine\n";
                cout << "4.Afisarea Materialelor ce au unitate de masura KG\n";
                cout << "5.Adaugarea unui nou Material\n";
                cout << "6.Stergerea unui Material\n";
                cout << "7.Revenire la meniul anterior\n";
                try {
                    cout << "Optiunea dumneavoastra este: ";
                    cin >> optiune;
                    if (optiune < 1 || optiune > 7)
                        throw optiune;
                    switch (optiune) {
                    case 1: {
                        cout << materiale;
                        break;
                    }
                    case 2: {
                        try {
                            if (materiale.get_nr_obiecte() <= 0)
                                throw 1;
                            int opt;
                            cout
                                << "\nNumarul de ordine al materialului pe care doriti sa il afisati este ....( acesta trebuie sa fie intre 0 si "
                                << materiale.get_nr_obiecte() - 1 << " ) : ";
                            do {
                                cin >> opt;
                            } while (opt < 0 || opt >= materiale.get_nr_obiecte());
                            materiale.afis_pozitia_i(opt);
                        }
                        catch (int x) {
                            cout << "Nu exista niciun material!\n";
                        }

                        break;
                    }
                    case 3: {
                        try {
                            if (materiale.get_nr_obiecte() <= 0)
                                throw 1;
                            int opt;
                            cout
                                << "\nNumarul de ordine al materialului al carui cost doriti sa il afisati este ....( acesta trebuie sa fie intre 0 si "
                                << materiale.get_nr_obiecte() - 1 << " ) : ";
                            do {
                                cin >> opt;
                            } while (opt < 0 || opt >= materiale.get_nr_obiecte());
                            cout << "Costul materialului este : " << materiale.getVector()[opt].getPretUnitar();
                        }
                        catch (int x) {
                            cout << "Nu exista niciun material!\n";
                        }

                        break;
                    }
                    case 4: {
                        // afisare materiale cu unit de masura=kg
                        try {
                            if (materiale.get_nr_obiecte() <= 0)
                                throw 1;
                            bool ok = false;
                            cout << "Se incepe cautarea materialelor ce au unitatea de masura KG : \n";
                            for (auto& x : materiale.getVector()) {
                                string unit(x.getUnitateDeMasura());
                                transform(unit.begin(), unit.end(), unit.begin(), ::toupper);
                                if (unit == "KG") {
                                    ok = true;
                                    cout << x << endl;
                                }
                            }
                            if (!ok)
                                cout << "Niciun material nu are KG ca si unitate de masura !";
                        }
                        catch (int x) {
                            cout << "Nu exista niciun material!\n";
                        }

                        break;
                    }
                    case 5: {
                        cin.get();
                        Material obiect_temporar;
                        cin >> obiect_temporar;
                        materiale += obiect_temporar;
                        break;
                    }
                    case 6:
                    {
                        try {
                            if (materiale.get_nr_obiecte() <= 0)
                                throw 1;
                            int opt;
                            cout
                                << "\nNumarul de ordine al materialului pe care doriti sa il stergeti este ....( acesta trebuie sa fie intre 0 si "
                                << materiale.get_nr_obiecte() - 1 << " ) : ";
                            do {
                                cin >> opt;
                            } while (opt < 0 || opt >= materiale.get_nr_obiecte());
                            materiale -= materiale.getVector()[opt];
                        }
                        catch (int x) {
                            cout << "Nu exista niciun material!\n";
                        }

                        break;
                    }
                    case 7: {
                        break;
                    }
                    }
                }
                catch (int x) {
                    cout << "Optiunea dumneavoastra nu se afla intre 1 si 7 . EROARE!!!\n";
                    return;
                }
            } while (optiune != 7); }));

    menu.push_back(make_pair("Meniu Produse", [&]()
        {
            int optiune;
            do {
                cout << "Ce doriti sa faceti cu Produsele din aplicatie?\n";
                cout << "1.Afisarea tuturor Produselor\n";
                cout << "2.Afisarea unui Produs in functie de numarul de ordine\n";
                cout << "3.Afisarea costului unui Produs in functie de numarul de ordine\n";
                cout << "4.Afisarea Produsului care are costul maxim\n";
                cout << "5.Afisarea Produsului care are costul minim\n";
                cout << "6.Afisarea Produsului care este perisabil si are costul maxim\n";
                cout << "7.Afisarea unui Produs care este de post\n";
                cout << "8.Adaugarea unui nou Produs\n";
                cout << "9.Revenire la meniul anterior.\n";
                try {
                    cin >> optiune;
                    if (optiune < 1 || optiune > 9)
                        throw optiune;
                    switch (optiune) {
                    case 1: {
                        cout << produse;
                        break;
                    }
                    case 2: {
                        try {
                            if (produse.get_nr_obiecte() <= 0)
                                throw 1;
                            int opt;
                            cout
                                << "\nNumarul de ordine al produsului pe care doriti sa il afisati este ....( acesta trebuie sa fie intre 0 si "
                                << produse.get_nr_obiecte() - 1 << " ) : ";
                            do {
                                cin >> opt;
                            } while (opt < 0 || opt >= produse.get_nr_obiecte());
                            produse.afis_pozitia_i(opt);
                        }
                        catch (int x) {
                            cout << "Nu exista niciun produs!\n";
                        }
                        break;
                    }
                    case 3: {
                        try {
                            if (produse.get_nr_obiecte() <= 0)
                                throw 1;
                            int opt;
                            cout
                                << "\nNumarul de ordine al produsului al carui cost doriti sa il afisati este ....( acesta trebuie sa fie intre 0 si "
                                << produse.get_nr_obiecte() - 1 << " ) : ";
                            do {
                                cin >> opt;
                            } while (opt < 0 || opt >= produse.get_nr_obiecte());
                            // cout << "Costul produsului este : "
                            //     << produse.getVector()[opt].get_cost_produs();
                        }
                        catch (int x) {
                            cout << "Nu exista niciun produs!\n";
                        }
                        break;
                    }
                    case 4: {
                        // calcul prod maxim
                        try {
                            if (produse.get_nr_obiecte() <= 0)
                                throw 1;
                            int poz = -1;
                            float maxim = 0.0;
                            // for (int i = 0; i < produse.get_nr_obiecte(); i++) {
                            //     auto& x = produse.getVector()[i];
                            //     float cost = x.get_cost_produs();
                            //     if (cost > maxim) {
                            //         maxim = cost;
                            //         poz = i;
                            //     }
                            // }
                            if (poz >= 0)
                                cout << "Produsul " << produse.getVector()[poz] << " are costul maxim de " << maxim
                                << endl;
                        }
                        catch (int x) {
                            cout << "Nu exista niciun produs!\n";
                        }
                        break;
                    }
                    case 5: {
                        //calcul prod minim
                        try {
                            if (produse.get_nr_obiecte() <= 0)
                                throw 1;
                            int poz = -1;
                            float minim = (float)INT_MAX;
                            // for (int i = 0; i < produse.get_nr_obiecte(); i++) {
                            //     auto& x = produse.getVector()[i];
                            //     float cost = x.get_cost_produs();
                            //     if (cost < minim) {
                            //         minim = cost;
                            //         poz = i;
                            //     }
                            // }
                            if (poz >= 0)
                                cout << "Produsul " << produse.getVector()[poz] << " are costul minim de " << minim
                                << endl;
                        }
                        catch (int x) {
                            cout << "Nu exista niciun produs!\n";
                        }
                        break;
                    }
                    case 6: {
                        //perisabil si are costul maxim
                        try {
                            if (produse.get_nr_obiecte() <= 0)
                                throw 1;
                            int poz = -1;
                            float maxim = 0.0;
                            // for (int i = 0; i < produse.get_nr_obiecte(); i++) {
                            //     auto& x = produse.getVector()[i];
                            //     float cost = x.get_cost_produs();
                            //     if (cost > maxim and x.isPerisabil()) {
                            //         maxim = cost;
                            //         poz = i;
                            //     }
                            // }
                            if (poz >= 0)
                                cout << "Produsul perisabil " << produse.getVector()[poz] << " are costul maxim de "
                                << maxim << endl;
                        }
                        catch (int x) {
                            cout << "Nu exista niciun produs!\n";
                        }
                        break;
                    }
                    case 7: {
                        //de post
                        try {
                            if (produse.get_nr_obiecte() <= 0)
                                throw 1;
                            bool ok = false;
                            for (auto& x : produse.getVector()) {
                                if (x.isEsteDePost()) {
                                    ok = true;
                                    cout << "Produs de post = " << x << endl;
                                    break;
                                }
                            }
                            if (!ok)
                                cout << "Nu exista niciun produs de post !";
                        }
                        catch (int x) {
                            cout << "Nu exista niciun produs!\n";
                        }
                        break;
                    }
                    case 8: {
                        cin.get();
                        Produs obiect_temporar;
                        cin >> obiect_temporar;
                        produse += obiect_temporar;
                        break;
                    }
                    case 9:
                        break;
                    }
                }
                catch (int x) {
                    cout << "Optiunea dumneavoastra nu se afla intre 1 si 7 . EROARE!!!\n";
                    return;
                }
            } while (optiune != 9); }));

    menu.push_back(make_pair("Meniu Patiserie", [&]()
        {
            int optiune;
            do {
                cout << "Ce doriti sa faceti cu Patiseriile din aplicatie?\n";
                cout << "1.Afisarea datelor Patiseriei\n";
                cout << "2.Modificarea datelor Patiseriei\n";
                cout << "3.Revenire la meniul principal\n";

                cout << "Optiunea dumneavoastra este : ";
                cin >> optiune;
                try {
                    if (optiune < 1 || optiune > 3)
                        throw 1;
                    switch (optiune) {
                    case 1: {
                        cout << "Patiseria este : " << patiserie << endl;
                        break;
                    }
                    case 2: {
                        cin.get();
                        string numeData;
                        cout << "Introduceti tipul de data pe care doriti sa o modificati(Nume, Data infiintarii, Comision, Adresa) : ";
                        getline(cin, numeData);
                        if (numeData == "Nume") {
                            string nume;
                            cout << "Introduceti numele nou : ";
                            getline(cin, nume);
                            patiserie.setNumePatiserie(nume);
                        }
                        else if (numeData == "Data infiintarii") {
                            string str;
                            cout << "Introduceti data noua : ";
                            getline(cin, str);
                            Data data = citireData(str);
                            patiserie.setDataInfiintare(data);
                        }
                        else if (numeData == "Adresa") {
                            string locatie;
                            cout << "Introduceti locatia noua : ";
                            getline(cin, locatie);
                            patiserie.setAdresa(locatie);
                        }
                        else
                            cout << "Nu exista aceasta data!\n";
                        break;
                    }
                    case 3:
                        break;
                    }
                }
                catch (int x) {
                    cout << "Optiunea dumneavoastra nu se afla intre 1 si 3 . EROARE!!!\n";
                    return;
                }

            } while (optiune != 4); }));
}

Meniu::~Meniu()
{
    menu.clear();
}

void Meniu::run()
{
    bool ok = true;
    while (ok)
    {
        try
        {
            int optiune, i;
            cout << "Alege operatia" << endl;
            for (i = 0; i < menu.size(); i++)
                cout << i << ") " << menu[i].first << endl;
            cout << menu.size() << ") Inchidere" << endl;

            cout << "Optiunea dumneavoastra este : ";
            cin >> optiune;
            if (optiune < 0 || optiune > menu.size())
                throw runtime_error("Optiune invalida");

            if (optiune == menu.size())
            {
                ok = false;
                return;
            }

            menu[optiune].second();
        }
        catch (const exception& e)
        {
            cout << "Am intampinat o problema: " << e.what() << endl;
        }
    }
}

const Gestiune<Material>& Meniu::getMateriale() const
{
    return materiale;
}

const Gestiune<Produs>& Meniu::getProduse() const
{
    return produse;
}

const Patiserie Meniu::getPatiserii() const
{
    return patiserie;
}

/// -------------------------   VARIABILE STATICE DIN CLASE   -------------------------

int Material::nrTotalMateriale = 100;
int Produs::nrTotalProduse = 10;
int Patiserie::nrTotalPatiserii = 1000;

Meniu* Meniu::instanta = nullptr;

Data Data::data_default(20, 1, 2023);

/// -------------------------   MAIN   -------------------------

int main()
{
    Meniu meniu;
    meniu.run();
    cout << "O ZI BUNA!";
    return 0;
}