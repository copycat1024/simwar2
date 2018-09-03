#include <iostream>
#include "combi.h"

using std::string;
using std::cout;
using std::endl;

int base32d(char c){
	if (c>='a' && c<='z') return c-'a';
	if (c>='A' && c<='Z') return c-'A';
	if (c>='2' && c<='7') return c-'2'+26;
	throw std::exception();
}

char base32e(int n){
	if (n<26){
		return 'A'+n;
	} else if (n<32){
		return '2'+n-26;
	}
	throw std::exception();
}

int factorial(int n){
	int res = 1;
	for (int i=1; i<n+1; i++){
		res *= i;
	}
	return res;
}

int combination(int n, int k){
	if (n<k) return 0;
	return factorial(n)/factorial(k)/factorial(n-k);
}

namespace simwar {

	Array5 intToFormation(int r){
		Array5 res;
		const int k = 5;
		int i, p;

		++r; // start from 1
		for (i=k; i>0; i--){
			p = i;
			while (combination(p, i) < r)
				p++;
			r -= combination(p-1, i);
			res[i-1] = p-1;
		}

		return res;
	}

	int formationToInt(const Array5& r){
		int res = 0;
		const int k = 5;
		int i, p;

		for (i=k-1; i>-1; i--){
			res += combination(r[i], i+1);
		}

		return res;
	}

	TeamSetup stampToSetup(string stamp){
		TeamSetup res;

		// extract heroes data
		if (stamp.size()%5 != 2) throw std::exception();
		int hs = stamp.size()/5;
		for (int i=0; i<5; i++){
			int h = 0;
			int off = 2 + i*hs;
			for (int j=0; j<hs; j++){
				h *= 32;
				h += base32d(stamp[off+j]);
			}
			res.heroes[i] = h;
		}

		// extract formation data
		int form = base32d(stamp[0])*32 + base32d(stamp[1]);
		if (form > 125) throw std::exception();
		res.formation = intToFormation(form);

		return res;
	}

	string setupToStamp(TeamSetup setup){
		string res;

		// compress heroes data
		int max = 0, len = 1, i;
		for (auto h: setup.heroes){
			if (h>max) max = h;
		}
		while (max>31){
			len++;
			max /= 32;
		}
		res = string(len*5+2, 'a');
		for (i=0; i<5; i++){
			int h = setup.heroes[i], off = len;
			while (h>0){
				char c = base32e(h%32);
				if (c>='A' && c<='Z') c += 'a'-'A';
				res[len*i+off+1] = c;
				off--;
				h /= 32;
			}
		}

		// extract formation data
		int form = formationToInt(setup.formation);
		res[0] = base32e(form/32);
		res[1] = base32e(form%32);

		return res;
	}

	void printForm(const Array5& arr){
		for (auto n: arr){
			cout << n;
		}
	}

	void printArr(const Array5& arr){
		int i;
		for (i=4; i>-1; i--){
			cout << arr[i];
		}
	}

}
