#pragma once

#include <cmath>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

class Complex {
    double re;
    double im;

public:
    Complex() {}

    Complex(double x, double y) {};

    void set_re(double re) {};
    void set_im(double im) {};

    double get_re() {};
    double get_im() {};

    double abs() {};
    double arg() {};

    string to_string() {};
    string to_string_trig() const;
    string to_string_exp() {};

    Complex add(const Complex& z) const;
    Complex sub(const Complex& z) const;
    Complex mult(const Complex& z) const;
    Complex div(const Complex& z) const;
};