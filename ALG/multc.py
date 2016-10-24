import sys
import time

def MultiplicaEnterosLargos (n1, n2):
    aux = 0
    resto = 0
    res = 0
    filas = []
    sol = []
    i = 0

    for x in reversed(n2):
        filas.append([])
        # insertamos tantos ceros al inicio como sea 
        # necesario
        for y in range(0,i):
            filas[i].insert(0,0)

        for y in reversed(n1):
            aux = (x*y)+resto
            resto = int(aux/10)
            res = aux%10
            filas[i].insert(0, res)

        if resto > 0:
            filas[i].insert(0, resto)
        resto = 0
        i += 1

    # insertamos tantos ceros al final como sea necesario
    max_tam = len(filas[-1])
    for f in reversed(filas):
        tam = len(f)
        while (tam < max_tam):
            f.insert(0, 0)
            tam += 1

    aux = 0
    resto = 0
    res = 0

    if len(n2) > 1:
        # sumamos las dos primeras filas
        # for x in range(0, len(filas[0])):
        for x, y in zip(reversed(filas[0]), reversed(filas[1])):
            aux = x + y + resto
            resto = int(aux/10)
            res = aux%10
            sol.insert(0,res);

        # sumamos el resto de filas
        aux = 0
        resto = 0
        res = 0
        i = 1

        for j in range(2, len(n2)):
            for x, y in zip(reversed(sol), reversed(filas[j])):
                aux = y + x + resto
                resto = int(aux/10)
                res = aux%10
                sol[-i] = res
                i = (i+1)%len(sol)

    else:
        sol = filas[0]

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
        sol = MultiplicaEnterosLargos(num1, num2)
        despues = time.time()

        tiempo = despues - antes

        print (str(n1)+" * "+str(n2)+" == "+(''.join(str(n) for n in sol)))
        print ("Tiempo: "+str(tiempo))
        