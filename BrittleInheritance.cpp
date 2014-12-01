/* Couse:    CS371p Objected Oriented Programming
 * Lecturer: Prof. Glenn Downing
 * Lecture:  12.01.2014
 * Topic:    The brittleness and limitations of inheritance in C++.
 */

#include <iostream>
using namespace std;

struct A {
    virtual void a() final {
        cout << "A::a()" << endl;
    }

    virtual void f(int) const {
        cout << "A::f()" << endl;
    }

    void f(long) {
        cout << "A::f(long)" << endl;
    }

    virtual void f(int) {
        cout << "A::f()" << endl;
    }
};

struct B : A {
    // error: declaration of 'a' overrides a 'final' function
    // virtual void a() {
    //     cout << "B::a()" << endl;
    // }

    virtual void f(std::string) {
        cout << "B::f()" << endl;
    }
};

struct C {
    virtual void f(string) {
        cout << "C::f(string)" << endl;
    }
};

struct D : C {
    virtual void f(int) {
        cout << "D::f(int)" << endl;
    }
};

struct E : C {
    using C::f;

    virtual void f(int) {
        cout << "E::f(int)" << endl;
    }
};

int main(void) {
    {
        cout << "A *a = new B();" << endl;
        A *a = new B();

        cout << "a->a():                      ";
        a->a();

        cout << "a->f(2l):                    ";
        a->f(2l);

        cout << "a->f(2):                     ";
        a->f(2);

        cout << "a->(f\"2\"):                   error: no matching member function for call to 'f'" << endl;
        // a->f("2");

        cout << "dynamic_cast<B*>(a)->f(\"2\"): ";
        dynamic_cast<B*>(a)->f("2");
    }

    {
        cout << endl;
        cout << "C *c = new D();" << endl;
        C *c = new D();
        cout << "c->f(2):                     error: no viable conversion from 'int' to 'string'" << endl;
        // c->f(2);

        cout << "dynamic_cast<D*>(c)->f(2):   ";
        dynamic_cast<D*>(c)->f(2); // solution to above
        c->f("2");

        cout << endl;
        cout << "D *d = new D();" << endl;
        D *d = new D();
        cout << "d->f(2)                      ";
        d->f(2);

        cout << "d->(f\"2\"):                   error: cannot initialize a parameter of type 'int'" << endl
             << "                                    with an lvalue of type 'const char [2]'" << endl;
        // d->f("2");

        cout << "d->C::f(\"2\"):                ";
        d->C::f("2"); // solution to above
    }

    {
        cout << endl;
        cout << "C *c = new E();" << endl;
        C *c = new E();
        cout << "c->f(2):                     error: no viable conversion from 'int' to 'string'" << endl;
        // c->f(2);

        cout << "dynamic_cast<E*>(c)->f(2):   ";
        dynamic_cast<E*>(c)->f(2); // solution to above

        cout << "c->f(\"2\"):                   ";
        c->f("2");

        cout << endl;
        cout << "E *e = new E(); " << endl;
        E *e = new E();

        cout << "e->f(2):                     ";
        e->f(2);

        cout << "e->f(\"2\"):                   ";
        e->f("2"); // no longer have to scope!
    }

    return 0;
}

/*
    Output:

    A *a = new B();
    a->a():                      A::a()
    a->f(2l):                    A::f(long)
    a->f(2):                     A::f()
    a->(f"2"):                   error: no matching member function for call to 'f'
    dynamic_cast<B*>(a)->f("2"): B::f()

    C *c = new D();
    c->f(2):                     error: no viable conversion from 'int' to 'string'
    dynamic_cast<D*>(c)->f(2):   D::f(int)
    C::f(string)

    D *d = new D();
    d->f(2)                      D::f(int)
    d->(f"2"):                   error: cannot initialize a parameter of type 'int'
                                        with an lvalue of type 'const char [2]'
    d->C::f("2"):                C::f(string)

    C *c = new E();
    c->f(2):                     error: no viable conversion from 'int' to 'string'
    dynamic_cast<E*>(c)->f(2):   E::f(int)
    c->f("2"):                   C::f(string)

    E *e = new E(); 
    e->f(2):                     E::f(int)
    e->f("2"):                   C::f(string)
*/
