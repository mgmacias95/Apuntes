#include <iostream>
#include <list>
#include <iomanip>

using namespace std;

struct Objeto{
	double beneficio;
	double peso;
	double beneficio_unidad_peso;
	bool operator < (const Objeto & o)const{
		return (beneficio_unidad_peso) < (o.beneficio_unidad_peso);
	}
	bool operator > (const Objeto & o)const{
		return (beneficio_unidad_peso) > (o.beneficio_unidad_peso);
	}

	bool operator <= (const Objeto & o)const{
		return (beneficio_unidad_peso) <= (o.beneficio_unidad_peso);
	}
	bool operator >= (const Objeto & o)const{
		return (beneficio_unidad_peso) >= (o.beneficio_unidad_peso);
	}

	bool operator == (const Objeto & o)const{
		return beneficio == o.beneficio && peso = o.peso;
	}

	bool operator != (const Objeto & otro)const{
		return !(*this == otro);
	}

	Objeto (){};

	Objeto(double b, double p) : beneficio(b), peso(p){
		beneficio_unidad_peso = beneficio/peso;
	}
};

struct Opcion{
	Objeto o;
	double porcentaje = 0;
};

ostream & operator << (ostream & os, const list<Objeto> & l){
	list<Objeto>::const_iterator it;
	os << setw(10) << "BENEFICIO" << setw(15) << "PESOS" << endl;
	for(it = l.cbegin(); it != l.cend(); ++it)
		os << setw(10) << (*it).beneficio << setw(10) << (*it).peso << endl;

	os << endl;

	return os;
}

ostream & operator << (ostream & os, const list<Opcion> & l){
	list<Opcion>::const_iterator it;
	os << setw(10) << "BENEFICIO" << setw(10) 
		<< "PESOS" << setw(15) << "PORCENTAJE" << endl;
	for(it = l.cbegin(); it != l.cend(); ++it)
		os << setw(10) << (*it).o.beneficio << setw(10)
			<< (*it).o.peso << setw(10) << (*it).porcentaje << endl;

	os << endl;

	return os;
}

// PRE: la lista que se le pasa por parámetro a la función,
// está ordenada previamente

list<Opcion> voraz(double capacidad_M, const list<Objeto> & conjunto_inicial){
	list<Objeto> aux = conjunto_inicial;
	list<Opcion> solucion;
	Objeto p;
	double peso_actual = 0;
	Opcion opt;

	while(peso_actual < capacidad_M && !aux.empty()){
		p = aux.back();
		if((peso_actual + p.peso) <= capacidad_M){
			opt.o = p;
			opt.porcentaje = 1;
			solucion.push_front(opt);
			peso_actual += p.peso;
		}
		else{
			opt.o = p;
			opt.porcentaje = (capacidad_M-peso_actual)/p.peso;
			peso_actual = capacidad_M;
			solucion.push_front(opt);
		}
		aux.pop_back();
	}

	return solucion;
}

double Total(const list<Opcion> & l){
	list<Opcion>::const_iterator it;
	double suma = 0;
	for(it = l.cbegin(); it != l.cend(); ++it)
		suma += (*it).o.beneficio * (*it).porcentaje;

	return suma;
}

int main(int argc, char ** argv){
	
	if(argc % 2 != 0){
		cerr << "ERROR: Hay que meter argumentos impares" << endl;
		exit(-1);
	}

	list<Objeto> conjunto_inicial;

	for(int i = 1; i < argc - 2; i+=2)
		conjunto_inicial.push_back(Objeto(strtod(argv[i],NULL), 
			strtod(argv[i+1],NULL)));

	double mochila = strtod(argv[argc-1], NULL);

	conjunto_inicial.sort();

	cout << "Capacidad de la mochila = " << mochila << "kg." << endl;

	cout << conjunto_inicial;

	double ncgt;
    struct timespec cgt1, cgt2;
    clock_gettime(CLOCK_REALTIME,&cgt1);

	list<Opcion> sol = voraz(mochila, conjunto_inicial);

	clock_gettime(CLOCK_REALTIME,&cgt2);

    ncgt=(double)(cgt2.tv_sec-cgt1.tv_sec)+
        (double)((cgt2.tv_nsec-cgt1.tv_nsec)/(1.e+9));

	cout << sol;

	cout << endl << "Beneficio total = " << Total(sol) << endl;

	printf("\nTiempo (seg.) = %11.9f\n", ncgt);
	
	return 0;
}
