#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

struct Elemento{
    double peso;
    double beneficio;
    bool operator < (const Elemento & b){
        return (*this).beneficio < b.beneficio && (*this).peso < b.peso;
    }
    bool operator > (const Elemento & b){
        return !((*this)<b);
    }
    bool operator == (const Elemento & b){
        return (*this).beneficio == b.beneficio && (*this).peso == b.peso;
    }
    bool operator != (const Elemento & b){
        return !((*this)==b);
    }
    Elemento operator = ( const Elemento & b){
        (*this).peso = b.peso;
        (*this).beneficio = b.beneficio;
        return *this;
    }
};

ostream & operator << (ostream & os, const vector< vector<int> > & v){
    os << "-------------------------------" << endl;
    os << 'v' << setw(2) << '|';
    for(unsigned i = 0; i < v[0].size(); i++)
        os << setw(2) << i << setw(2) << '|';
    os << endl << "-------------------------------" << endl;
    for(unsigned i = 0; i < v.size(); i++){
        os << i << setw(2) << '|';
        for(unsigned j = 0; j < v[i].size(); j++)
            os << setw(2) << v[i][j] << setw(2) << '|';

        os << endl << "-------------------------------" << endl;
    }
    os << endl;
    return os;
}

ostream & operator << (ostream & os, const vector<Elemento> & v){
    for(unsigned i = 0; i < v.size(); i++)
        os << setw(4) << "Peso=" << v[i].peso 
            << " Beneficio=" << v[i].beneficio << endl;
    os << endl;

    return os;
}

ostream & operator << (ostream & os, const Elemento & v){
    os << '[' << v.peso << ", " << v.beneficio << ']';
    return os;
}

ostream & operator << (ostream & os, const vector<int> & v){
    for(unsigned i = 0; i < v.size(); i++)
        os << setw(4) << v[i];

    os << endl;

    return os;
}

int max(int i, int j){
    if(i > j)
        return i;
    else
        return j;
}

void Mochila(vector< vector <int> > & tabla, const vector<Elemento> & elementos){
    for(unsigned i = 1; i < tabla.size(); i++)
        for(unsigned j = 1; j < tabla[i].size(); j++){
            Elemento k_i = elementos[i -1];
            if(j - k_i.peso < 0)
              tabla[i][j] = tabla[i-1][j];
            else
                tabla[i][j] = max(tabla[i-1][j], 
                    k_i.beneficio + tabla[i-1][j-k_i.peso]);
        } 
}

void recomponer(const vector< vector <int> > & tabla, const vector<Elemento> & elementos,
    vector<int> & sol){
    unsigned j = tabla[0].size()-1;
    for(unsigned i = tabla.size()-1; i>=1; i--)
        if(tabla[i][j] == tabla[i-1][j])
            sol[i-1] = 0;       // tabla[i][j] == tabla[i-1][j-p_i + b]
        else{
            sol[i-1] = 1;
            j -= elementos[i-1].peso;
        }
}


int main(int argc, char **argv){

    int num_objetos = 3,
        peso_mochila = 6;

    vector<Elemento> elementos(num_objetos);
    elementos[0].peso = 2; elementos[0].beneficio = 1;
    elementos[1].peso = 3; elementos[1].beneficio = 2;
    elementos[2].peso = 4; elementos[2].beneficio = 5;

    cout << "Elementos a escoger" << endl;
    cout << elementos;
    cout << "Peso de la mochila " << peso_mochila << endl;
    cout << endl << "Tabla:" << endl << endl;

    vector< vector <int> > tabla((num_objetos+1));

    for(int i = 0; i < num_objetos + 1; i++){
        tabla[i].resize(peso_mochila + 1);
        tabla[i][0] = tabla[0][i] = 0;  
    }
    Mochila(tabla, elementos);
    vector<int> sol(num_objetos,0);

    cout << tabla;
    recomponer(tabla, elementos, sol);
    cout << "Elementos escogidos: " << setw(5);
    for(unsigned i = 0; i < elementos.size(); i++){
        if(sol[i] == 1)
            cout << elementos[i] << setw(5);
    }

    cout << endl;
    
    return 0;
}