/* Couse:    CS371p Objected Oriented Programming
 * Lecturer: Prof. Glenn Downing
 * Lecture:  ??
 * Topic:    Access Control & Inheritance
 * 
 * This short program explores the changes when different privacy accessors
 * are used when inheriting from another class.

 * Information derived from:
 * http://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm

   +----------------+-----------+-----------+-----------+
   | Access 		| public	| protected	| private	|
   +----------------+-----------+-----------+-----------+
   | Same class 	| yes		| yes		| yes		|
   +----------------+-----------+-----------+-----------+
   | Derived class 	| yes		| yes		| no		|
   +----------------+-----------+-----------+-----------+
   | Outside class 	| yes		| no		| no		|
   +----------------+-----------+-----------+-----------+

 * A derived class inherits all base class methods with the following exceptions:
 	1. Constructors, destructors and copy constructors of the base class.
  	2. Overloaded operators of the base class.
  	3. The friend functions of the base class.
*/

#include <iostream>

using namespace std;

// -------
// Class A
// -------

class A {
public:
	char _a1;
	char _a2;

	A() {
		cout << "A(_a1, _a2)";
		_a1 = 'A';
		_a2 = 'A';
	}
};

// -------
// Class B
// -------

/* B is capable of accessing all of A's public and protected members
 * Places a "protected" restriction on these members, which keeps them open to
 * child classes but closed to outside classes.
 */
class B : protected A {
public: 
	char _b1;

	B() {
		cout << " -> B(_a1, _a2, _b1)";
		_a1 = 'B';
		_a2 = 'B';
		_b1 = 'B';
	}
};

// -------
// Class C
// -------

/* C is capable of accessing all of A's public and protected members
 * But restricts these members to private for outside and child classes
 */
class C : private A {
public:
	char _c1;

	C() {
		cout << " -> C(_a1, _a2, _c1)";

		// A's members become private, restricted to C
		_a1 = 'C';
		_a2 = 'C';

		_c1 = 'C';
	}
};

// -------
// Class D
// -------

class D : public B {
public:
	char _d1;

	D() {
		cout << " -> D(_a1, _a2, _b1, _d1)";

		// B made these variables protected, which allows D to use them, still,
		// but restricts this access to subclasses
		_a1 = 'D';
		_a2 = 'D';

		// Free to access B's public data
		_b1 = 'D';

		_d1 = 'D';
	}
};

// -------
// Class E
// -------

/* C has made all of A's members private, so E as a derived class does not 
 * inherit A's members. C has been declared public, so all C's members are
 * accessible by E and outside classes.
 */
class E : public C {
public:
	char _e1;

	E() {
		cout << " -> E(_c1, _e1)";

		// Unable to access A's public data
		// _a1 = 'E'; // doesn't compile
		// _a2 = 'E'; // doesn't compile

		// Can access C's public data
		_c1 = 'E';

		_e1 = 'E';
	}
};

// -------
// Class F
// -------

/* This syntax is implicitly converted to 
 * 		class F : private A
 * and follows the same rules.
 */
class F : A {
public:
	char _f1;

	F() {
		cout << " -> F(_a1, _a2, _f1)";

		// A's members become private, restricted to F
		_a1 = 'F';
		_a2 = 'F';

		_f1 = 'F';
	}
};

int main() {
	A a;
	cout << endl;
	cout << "a._a1: " << a._a1 << endl;
	cout << "a._a2: " << a._a2 << endl;
	cout << endl;

	B b;
	cout << endl;
	cout << "b._a1: error: '_a1' is a protected member of 'A'" << endl;
	cout << "b._a2: error: '_a2' is a protected member of 'A'" << endl;
	cout << "b._b1: " << b._b1 << endl;
	cout << endl;

	C c;
	cout << endl;
	cout << "c._a1: error: '_a1' is a private member of 'A'" << endl;
	cout << "c._a2: error: '_a2' is a private member of 'A'" << endl;
	cout << "c._c1: " << c._c1 << endl;
	cout << endl;

	D d;
	cout << endl;
	cout << "d._a1: error: '_a1' is a protected member of 'A'" << endl;
	cout << "d._a2: error: '_a2' is a protected member of 'A'" << endl;
	cout << "d._b1: " << d._b1 << endl;
	cout << "d._d1: " << d._d1 << endl;
	cout << endl;

	E e;
	cout << endl;
	cout << "e._a1: error: '_a1' is a private member of 'A'" << endl;
	cout << "e._a2: error: '_a2' is a private member of 'A'" << endl;
	cout << "e._c1: " << e._c1 << endl;
	cout << "e._e1: " << e._e1 << endl;
	cout << endl;

	F f;
	cout << endl;
	cout << "f._a1: error: '_a1' is a private member of 'A'" << endl;
	cout << "f._a2: error: '_a2' is a private member of 'A'" << endl;
	cout << "f._b1: " << f._f1 << endl;
	cout << endl;

	return 0;
}

/* Output
 A(_a1, _a2)
 a._a1: A
 a._a2: A

 A(_a1, _a2) -> B(_a1, _a2, _b1)
 b._a1: error: '_a1' is a protected member of 'A'
 b._a2: error: '_a2' is a protected member of 'A'
 b._b1: B

 A(_a1, _a2) -> C(_a1, _a2, _c1)
 c._a1: error: '_a1' is a private member of 'A'
 c._a2: error: '_a2' is a private member of 'A'
 c._c1: C

 A(_a1, _a2) -> B(_a1, _a2, _b1) -> D(_a1, _a2, _b1, _d1)
 d._a1: error: '_a1' is a protected member of 'A'
 d._a2: error: '_a2' is a protected member of 'A'
 d._b1: D
 d._d1: D

 A(_a1, _a2) -> C(_a1, _a2, _c1) -> E(_c1, _e1)
 e._a1: error: '_a1' is a private member of 'A'
 e._a2: error: '_a2' is a private member of 'A'
 e._c1: E
 e._e1: E

 A(_a1, _a2) -> F(_a1, _a2, _f1)
 f._a1: error: '_a1' is a private member of 'A'
 f._a2: error: '_a2' is a private member of 'A'
 f._b1: F
*/
 