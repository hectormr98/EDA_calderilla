/*Grupo 19 de 2º GDV de la asignatura EDA
Integrantes : Alberto Casado Trapote , Héctor Marcos Rabadán

Algoritmo empleado para la resolución del ejercicio:
Al empezar, intentamos emplear el mayor numero de monedas (sin tener el cuenta el límite posible)
para alcanzar la cifra o deuda introducida (Si no cabe un numero exacto, se opta por añadir una
moneda extra, superando la deuda total). Si se ha empleado un numero de monedas dentro del rango
permitido para ello, no hay ningún problema. En caso contrario removemos de manera inmediata las
monedas sobrantes (coste constante) y pasamos a la moneda de valor inmediatamente mayor.
Eventualmente se igualara o superara la cantidad pedida. Si ha sido igualada, el ejercicio
finaliza, pues con este método la primera solución es la óptima al maximizar el número de monedas
de menor valor. Si la deuda ha sido superada, llamamos a otro metodo que se encarga de quitar las
monedas sobrantes, minimizando el numero de ellas que serán removidas.
*/


#include<iostream>
#include<vector>

using namespace std;


//metodo auxiliar de recogida de datos, para ahorrar lineas de codigo
int pideDato() {
	int dato;
	cin >> dato;
	return dato;
}

/*Metodo que halla la moneda a partir de la cual ya no tiene sentido
seguir analizando el problema ( por ejemplo, para una deuda de 14 cents
no tiene sentido analizar las monedas de 20cent y superiores*/
int Imax(int& deuda, int val[8], int cal[8]) {
	int imax = 7;

	while (cal[imax] == 0 || val[imax] > deuda)
		imax--;
	return imax + 1;
}

//Metodo auxiliar que remueve una moneda del vector de usadas, dado el tipo de moneda
void QuitaMoneda(int used[8], int type) {
	used[type]--;
}

/*Metodo empleado a la hora de remover las monedas sobrantes
con coste cuadratico O (imax * cantidad de monedas de cada tipo),
utilizando la imax hallada en el metodo superior*/
bool GetResto(int resto, int values[8], int used[8], int imax) {

	//variables auxiliares para el bucle
	int i = imax;
	bool bandera = false;

	//vamos a ir decrementando la i (y con ello el tipo de moneda que intentaremos quitar)
	while (!bandera && i >= 0) {
		//comprobamos si podemos quitar una moneda sin que el resto pase a ser negativo)
		if (values[i] <= resto) {
			//tambien debemos comprobar si hemos usado o no monedas de ese tipo
			if (used[i] != 0) {

				//de ser asi, quitamos una moneda del tipo en el que estemos
				//y actualizamos valores
				QuitaMoneda(used, i);
				resto -= values[i];

				//si todavia nos quedan monedas por quitar
				if (resto != 0)
					//llamamos al mismo metodo, pero esta vez el bucle empezara por el tipo de moneda que removimos
					return GetResto(resto, values, used, i);

				//si al quitar la moneda nos hemos quedado a 0, es que hemmos hallado la solucion
				else if (resto == 0)
					bandera = true;
			}
		}
		i--;
	}
	//true si hemos reducido la deuda a 0, false si el bucle bajo de 0 y no pudimos hacerlo
	return bandera;
}


//Metodo principal, explicado en el comentario inicial, que añade monedas hasta igualar o superar la deuda
//con coste cuadratico (inclu
bool FindCalderilla(int money[8], int used[8], int values[8], int deuda, int& ActMoney, int CoinType, int MaxCoinType) {

	//si hemos superado el limite (moneda de mayor valor) es que no hay solucion posible
	if (CoinType >= MaxCoinType)
		return false;

	//lo que nos queda por pagar
	int AuxMoney = deuda - ActMoney;

	//lo intentamos meter todo en el tipo de moneda
	used[CoinType] = AuxMoney / values[CoinType];

	//si no entra justo, aumentamos en uno y nos pasamos de lo que tenemos que pagar
	if (AuxMoney%values[CoinType] != 0) {
		used[CoinType]++;
	}

	ActMoney += used[CoinType] * values[CoinType];

	//si al habernos pasado seguimos estando en el rango posible, toca quitar monedas
	if (used[CoinType] <= money[CoinType]) {

		//es posible hayamos dado con una cantidad de monedas que es exactamente la deuda
		if (ActMoney == deuda)
			return true;

		//vamos a hallar por cuanto nos hemos pasado
		int resto = values[CoinType] - AuxMoney%values[CoinType];

		//y llamamos al metodo que quitara las monedas correspondientes, si se puede.
		return GetResto(resto, values, used, MaxCoinType);

	}

	else {

		//lo que nos queda por pagar, en la siguiente moneda
		int sobrante = (used[CoinType] - money[CoinType])*values[CoinType];

		//actualizamos el dinero que llevamos (lo que teniamos menos lo que sobra)
		ActMoney -= sobrante;

		//ajustamos las monedas usadas
		used[CoinType] = money[CoinType];

		//y llamamos a la siguiente moneda
		return FindCalderilla(money, used, values, deuda, ActMoney, CoinType + 1, MaxCoinType);
	}
}

//metodo de declaracion y asignacion de variables
//que permite dejar el main limpio
void calderilla() {
	int NumberCases = pideDato();
	if (NumberCases > 0) {
		//el numero de monedas
		int money[8];
		//las monedas que iremos usando, inicializado a 0
		int used[8]{};
		//los valores de las monedas
		int values[8]{ 1,2,5,10,20,50,100,200 };
		//cantidad a pagar
		int deuda = 0;
		//cantidad pagada
		int ActualMoney = 0;
		int NumberOfCoins = 0;

		for (int i = 0; i < NumberCases; i++) {
			deuda = pideDato();
			if (deuda >= 0) {
				for (int a = 0; a < 8; a++) {
					money[a] = pideDato();
				}
				//hallamos el valor maximo en el cual tiene sentido analizar
				int MaxCoinType = Imax(deuda, values, money);

				//pagamos 0 con 0 monedas
				if (deuda == 0)
					cout << "0" << endl;
				else {

					//si se puede encontrar un numero de monedas
					if (FindCalderilla(money, used, values, deuda, ActualMoney, 0, MaxCoinType)) {

						//recorremos el vector de monedas usadas
						for (int j = 0; j < 8; j++)
							NumberOfCoins += used[j];
						//e imprimimos el numero total de ellas
						cout << NumberOfCoins << endl;

						//reseteo del vector used para el siguiente caso
						for (int a = 0; a < 8; a++)
							used[a] = 0;
						ActualMoney = 0;
						NumberOfCoins = 0;
					}

					else cout << "IMPOSIBLE" << endl;
				}
			}
			else cout << "IMPOSIBLE" << endl;
		}
	}
}

int main() {
	calderilla();

	return 0;
}