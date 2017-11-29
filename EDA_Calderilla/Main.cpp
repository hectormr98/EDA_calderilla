#include<iostream>
#include<vector>

using namespace std;

int pideDato() {
	int dato;
	cin >> dato;
	return dato;
}

int Imax(int& deuda, int val[8], int cal[8]) {
	int imax = 7;

	while (cal[imax] == 0 || val[imax] > deuda)
		imax--;
	return imax+1;
}


bool es_solucion(int& ActVal, int& MaxVal) {
	return ActVal == MaxVal;
}

bool es_completable(int& ActVal, int& MaxVal) {
	return ActVal < MaxVal;
}


bool CalcCalderilla(int money[8], int used[8], int values[8], int& deuda, int& ActualMoney, int CoinType, int& TopCoinType) {
	bool solution = false;
	if (CoinType < TopCoinType) {
		int CoinsToUse = money[CoinType];
		int AuxValue;
		while (CoinsToUse >= 0 && !solution) {
			used[CoinType] = CoinsToUse;
			AuxValue = ActualMoney + values[CoinType] * CoinsToUse;
			CoinsToUse--;
			if (!es_solucion(AuxValue, deuda)) {
				if (es_completable(AuxValue, deuda)) {
					if (CalcCalderilla(money, used, values, deuda, AuxValue, CoinType + 1, TopCoinType))
						solution = true;
				}
			}
			else solution = true;
			//ef
			//sjfbeu
		}
	}
	return solution;
}

void calderilla() {
	int NumberCases = pideDato();
	if (NumberCases > 0) {
		int money[8];
		int used[8]{};
		int values[8]{ 1,2,5,10,20,50,100,200 };
		int deuda = 0;
		int ActualMoney = 0;
		int NumberOfCoins = 0;

		for (int i = 0; i < NumberCases; i++) {
			deuda = pideDato();
			if (deuda >= 0) {
				if (deuda == 0)
					cout << "0" << endl;
				else {
					for (int a = 0; a < 8; a++) {
						money[a] = pideDato();
					}
					int MaxCoinType = Imax(deuda, values, money);
					if (CalcCalderilla(money, used, values, deuda, ActualMoney, 0, MaxCoinType)) {
						for (int j = 0; j < 7; j++)
							NumberOfCoins += used[j];
						cout << NumberOfCoins << endl;
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