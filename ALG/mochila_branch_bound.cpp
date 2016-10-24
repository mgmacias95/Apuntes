#include <vector>           // para los objetos que de
#include <iostream>
#include <cstdlib>          // para el atoi
#include <cmath>
#include <set>
#include <limits>           // para el infinito
#include <queue>            // para la lista de nodos vivos (priority_queue)
using namespace std;

struct Elemento {
    double peso;
    double beneficio;
    double b_unidad_p;
    Elemento (int b, int p) {
        beneficio = b;
        peso = p;
        b_unidad_p = beneficio/peso;
    }

    bool operator < (const Elemento & elem1) const {
        return (((*this).b_unidad_p) < (elem1.b_unidad_p));
    }

    bool operator > (const Elemento & elem1) const {
        return (((*this).b_unidad_p) > (elem1.b_unidad_p));
    }

    bool operator <= (const Elemento & elem1) const {
        return (((*this).b_unidad_p) <= (elem1.b_unidad_p));
    }

    bool operator >= (const Elemento & elem1) const {
        return (((*this).b_unidad_p) >= (elem1.b_unidad_p));
    }

    bool operator == (const Elemento & elem1) const {
        return (*this).peso == elem1.peso && (*this).beneficio == elem1.beneficio;
    }

    bool operator != (const Elemento & elem1) const {
        return !((*this) == elem1);
    }
};

struct Nodo {
    double CI;
    double CS;
    double BE;
    int nivel;
    double valor_actual;
    double peso_actual;
    vector<bool> tupla;
    Nodo (double cota_i, double cota_s, double ben_e, int n,
        double vact, double pact, vector<bool> & t) {
        CI = cota_i;
        CS = cota_s;
        BE = ben_e;
        nivel = n;
        valor_actual = vact;
        peso_actual = pact;
        tupla = t;
    }
   
    bool operator > (const Nodo & n1)const {
        return (*this).BE > n1.BE;
    }

    bool operator < (const Nodo & n1)const {
        return (*this).BE < n1.BE;
    }

    bool operator >= (const Nodo & n1)const {
        return (*this).BE >= n1.BE;
    }

    bool operator <= (const Nodo & n1)const {
        return (*this).BE <= n1.BE;
    }

     bool operator == (const Nodo & n1)const {
        return (*this).BE >= n1.BE;
    }
     
    bool operator != (const Nodo & n1)const {
        return !((*this) == n1);
    }
};

ostream & operator << (ostream & os, const multiset<Elemento> & m){
    multiset<Elemento>::const_iterator it;
    for(it = m.cbegin(); it != m.end(); it++)
        os << "Beneficio="<< (*it).beneficio << " Peso=" << (*it).peso << endl;

    return os;
}

double GreedyFraccional(const double lim_peso, const multiset<Elemento> & objetos){
    double pesoact = 0, beneficio = 0;

    multiset<Elemento>::const_reverse_iterator it;

    for(it = objetos.rbegin(); it != objetos.rend() && pesoact < lim_peso; ++it){
        if((pesoact + (*it).peso) <= lim_peso){
            beneficio += (*it).beneficio;
            pesoact += (*it).peso;
        }
        else {
            double fraccion = (lim_peso-pesoact)/(*it).peso;
            beneficio += fraccion * (*it).beneficio;
            pesoact = lim_peso;
        }
    }

    return beneficio;
}

double Greedy01(const multiset<Elemento> & objetos, const double pesoM){
    double pesoact = 0, beneficio = 0;

    multiset<Elemento>::const_reverse_iterator it;

    for(it = objetos.rbegin(); it != objetos.rend() && pesoact < pesoM; ++it)
        if((pesoact + (*it).peso) <= pesoM){
            beneficio += (*it).beneficio;
            pesoact += (*it).peso;
        }

    return beneficio;
}

Nodo NodoInicial(const multiset<Elemento> & objs, const double pesoM){
    double  cota_s = GreedyFraccional(pesoM, objs),
            ben_e = Greedy01(objs, pesoM);

    vector<bool> tupla(objs.size(),false);
    Nodo inicial(0, cota_s, ben_e, -1, 0, 0, tupla);

    return inicial;
}

Nodo Generar(Nodo & actual, bool eleccion, double pesoM, 
    const multiset<Elemento> & Originalobjs){

    Nodo res = Nodo(0, 0, 0, actual.nivel+1, 0, 0, actual.tupla);
    multiset<Elemento> objs(Originalobjs);
    multiset<Elemento>::const_reverse_iterator obj_it = Originalobjs.crbegin();
    multiset<Elemento>::iterator otro;
    
    for (int k=0; k<=res.nivel && obj_it != objs.crend(); k++){        
        otro = objs.end();--otro;
        // esto va borrando elementos hasta que nos 
        objs.erase(otro);
        ++obj_it;
    }   
    
    --obj_it;
    res.tupla.at(res.nivel) = eleccion;
    
    if (!eleccion) {
        res.valor_actual = actual.valor_actual;
        res.peso_actual = actual.peso_actual;
    }

    else{
        res.valor_actual = actual.valor_actual + (*obj_it).beneficio;
        res.peso_actual = actual.peso_actual + (*obj_it).peso;
    }
    res.CI =res.BE = res.valor_actual+Greedy01(objs, (pesoM - res.peso_actual));
    res.CS = res.valor_actual+ceil(GreedyFraccional((pesoM - res.peso_actual), objs));
  
    if (res.peso_actual > pesoM) {
        res.CI = numeric_limits<double>::min();
        res.CS = numeric_limits<double>::min();
        res.BE = numeric_limits<double>::min();
        res.valor_actual = res.BE;
    }

    return res;
}

vector<bool> Mochila(const multiset<Elemento> & elementos, double m) {
    Nodo inic = NodoInicial(elementos, m);
    double C = Greedy01(elementos,m);
    priority_queue<Nodo> LNV;
    LNV.push(inic);
    double s = numeric_limits<double>::min();
    vector<bool> resultado;

    multiset<Elemento>::const_reverse_iterator raux = elementos.rbegin();

    while (!LNV.empty()) {
        Nodo x = (LNV.top());
        LNV.pop();
        if (x.CS >= C) {
            for (unsigned k = 0; k < 2; k++) {
                bool elec = (k==0) ? true : false;
                Nodo y = Generar(x, elec, m,elementos);
                if (y.nivel == elementos.size()-1 && y.valor_actual > s) {
                    s = y.valor_actual;
                    C = (C >= s) ? C : s;
                    resultado = y.tupla;
                }

                else if (y.nivel < elementos.size()-1 && y.CS >= C){
                    C = (C >= y.CI) ? C : y.CI;
                    LNV.push(y);
                }
            }
        }
        ++raux;
    }
    return resultado;
}


int main(int argc, char const *argv[]) {
    if (argc < 2) {
        cerr << "ERROR: falta la multiseta de beneficios-pesos" <<
            " y el peso de la mochila" << endl;
        exit(1);
    }

    if (argc%2 != 0) {
        cerr << "ERROR: argumentos incorrectos: beneficio-peso pesomochi" << endl;
        exit(2);
    }

    multiset<Elemento> candidatos;
    for (int i=1; i<argc-1; i+=2) {
        double b = atoi(argv[i]); double p = atoi(argv[i+1]);
        Elemento obj (b, p);
        candidatos.insert(obj);
    }

    cout << candidatos << endl;

    double pesomochi = strtod(argv[argc-1], NULL);
    cout << "PesoMochila="<<pesomochi << endl;

    double ncgt;
    struct timespec cgt1, cgt2;
    clock_gettime(CLOCK_REALTIME,&cgt1);
    vector<bool> mochi = Mochila(candidatos, pesomochi);
    clock_gettime(CLOCK_REALTIME,&cgt2);

    ncgt=(double)(cgt2.tv_sec-cgt1.tv_sec)+
        (double)((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

    multiset<Elemento>::reverse_iterator it = candidatos.rbegin();

    cout << "Los objetos utilizados son: " << endl;
    for (unsigned i=0; i<mochi.size(); i++) {
        if (mochi.at(i))
            cout << "Usamos el objeto [" << (*it).beneficio << 
                ',' << (*it).peso << ']' << endl;
        ++it;
    }

    printf("\nTiempo (seg.) = %11.9f\n", ncgt);

    return 0;
}
