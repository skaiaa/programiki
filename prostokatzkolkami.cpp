#include <iostream>
using namespace std;

int main() {
	int x, y,s;
	cout <<  "podaj wymiary\n";
	if (cin >> x >> y >> s) {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < y; j++) {
				if (i >= x - s&&j >= y - s) {
					cout << "o";
				}
				else {
					cout << "*";
				}
			}
			cout << endl;
		}
		
	}
	else {
		cout << "niepoprawne dane";
	}
	system("pause");
	return 0;
}