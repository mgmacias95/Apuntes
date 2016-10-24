import sys
import time

def Resta (n1, n2):
    num1 = int(''.join(map(str,n1)))
    num2 = int(''.join(map(str,n2)))
    resta = num1 - num2
    r = str(resta)
    return [int(x.strip()) for x in r.split(',')]

def Suma (n1, n2):
    num1 = int(''.join(map(str,n1)))
    num2 = int(''.join(map(str,n2)))
    suma = num1 + num2
    s = str(suma)
    return [int(x.strip()) for x in s.split(',')]

def MultiplicaEnterosLargosDYV (n1, n2):

    if len(n1) == 1:
        num1 = int(''.join(map(str,n1)))
        num2 = int(''.join(map(str,n2)))
        mult = num1 * num2
        s = str(mult)
        sol = [int(x.strip()) for x in s.split(',')]

    else:
        if len(n1) % 2 != 0:
            n1.insert(0, 0)

        if len(n2) % 2 != 0:
            n2.insert(0, 0)

        w = []
        x = []
        y = []
        z = []

        # dividimos los numeros
        tam = len(n1)
        mitad = tam/2
        for k, i in zip(n1, range(0,tam)):
            if i < mitad:
                w.append(k)
            else:
                x.append(k)

        tam = len(n2)
        mitad = int(tam/2)
        for k, i in zip(n2, range(0,tam)):
            if i < mitad:
                y.append(k)
            else:
                z.append(k)

        r1 = Resta(w, x)
        r2 = Resta(z, y)

        m1 = MultiplicaEnterosLargosDYV(w, y)
        m2 = MultiplicaEnterosLargosDYV(x, z)
        m3 = MultiplicaEnterosLargosDYV(r1, r2)

        suma = Suma(m1, m2)
        suma = Suma(m3, suma)

        m1.extend(0 for i in range(tam))
        suma.extend(0 for i in range(mitad))

        sol = Suma(m1, suma)
        sol = Suma(m2, sol)
    
    return sol

if __name__ == '__main__':
    if len(sys.argv) < 3:
        print("Numero de argumentos incorrecto")

    else:
        n1 = sys.argv[1]
        num1 = []
        for n in n1:
            num1.append(int(n))

        n2 = sys.argv[2]
        num2 = []
        for n in n2:
            num2.append(int(n))

        antes = time.time()
        sol = MultiplicaEnterosLargosDYV(num1, num2)
        despues = time.time()

        tiempo = despues - antes

        print (str(n1)+" * "+str(n2)+" == "+(''.join(str(n) for n in sol)))
        print ("Tiempo: "+str(tiempo))
        