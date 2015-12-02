#include "avltree.h"
#include <iostream>

using namespace std;

struct myint {
	myint(int i) : x(i) {}
	//~myint() { cout << "delete " << x << endl; }
	~myint() = default;
	myint(const myint &i) { ncopy++; x = i.x; }
	myint(myint &&) = default;
	myint &operator=(const myint &i) { ncopy++; x =i.x; return *this; }
	myint &operator=(myint &&) = default;

	operator int() const { return x; }

	bool operator<(const myint &i) {
		ncmp++;
		return x<i.x;
	}
	bool operator<=(const myint &i) {
		ncmp++;
		return x<=i.x;
	}
	bool operator>(const myint &i) {
		ncmp++;
		return x>i.x;
	}
	bool operator>=(const myint &i) {
		ncmp++;
		return x>=i.x;
	}
	bool operator==(const myint &i) {
		ncmp++;
		return x==i.x;
	}
	bool operator!=(const myint &i) {
		ncmp++;
		return x!=i.x;
	}

	int x;

	static void reset() {
		ncmp = ncopy = 0;
	}

	static void printstats() {
		cout << "number of copies = " << ncopy << endl;
		cout << "number of comparisons = " << ncmp << endl;
	}

	static int ncmp,ncopy;
};

int myint::ncmp = 0;
int myint::ncopy = 0;

int main(int argc, char **argv) {
	avltree<myint> t;

	while(1) {
		char c;
		cin >>  c;
		if (c=='q') break;
		if (c=='i' || c=='a') {
			int i; cin >> i;
			myint::reset();
			t.insert(i);
			myint::printstats();
		} else if (c=='r') {
			int i; cin >> i;
			myint::reset();
			t.remove(i);
			myint::printstats();
		} else if (c=='k') {
			int i; cin >> i;
			myint::reset();
			cout << t.kthsmallest(i) << endl;
			myint::printstats();
		} else if (c=='c') {
			int i; cin >> i;
			myint::reset();
			cout << t.contains(i) << endl;
			myint::printstats();
		} else if (c=='d') {
			t.print(cout);
		} else if (c=='b') {
			int i,j;
			cin >> i >> j;
			myint::reset();
			auto t2 = t.between(i,j);
			myint::printstats();
			t2.print(cout);
		}
	}
}
