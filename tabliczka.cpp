#include <iostream>
using namespace std;

int main() {
	int a, b;
	
	cout << "podaj zakres\n";
	
	if ((cin >> a >> b)&&(a <= b)) {

		for (int i = a; i <= b; i++) {
			for (int j = a; j <= b; j++) {
				cout << i*j<<"\t";
			}
			cout << endl;
		}

	}
	else {
		cout << "niepoprawne dane\n";
	}
	system("pause");
	return 0;
}