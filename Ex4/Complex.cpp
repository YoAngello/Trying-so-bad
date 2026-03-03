#include "complex.h"
#include <cmath>
#include <sstream>

using std::stringstream;

Complex::Complex() : re(0), im(0) {}
Complex::Complex(double x, double y) : re(x), im(y) {}

void Complex::set_re(double re) {
	this->re = re;
}

void Complex::set_im(double im) {
	this->im = im;
}

double Complex::get_re() const {
	return re;
}

double Complex::get_im() const {
	return im;
}

double Complex::arg() const {
    if (re > 0 && im > 0 || re > 0 && im < 0)
        return atan(im / re);
    else if (re < 0 && im > 0 || re < 0 && im < 0)
        return atan(im / re) + M_PI;
    else if (re == 0 && im > 0)
        return M_PI / 2;
    else if (re == 0 && im < 0)
        return -M_PI / 2;
    else if (re > 0 && im == 0)
        return 0;
    else  
        return M_PI;
}

string Complex::to_string() const {
    stringstream ss;

    ss << re;

    if (im != 0) {
        if (im > 0)
            ss << " + i*" << im;
        else
            ss << " - i*" << -im;
    }

    return ss.str();
}

string Complex::to_string_trig() const {
    stringstream ss;
    double phi = arg();

    ss << "cos(" << phi << ") + i*sin(" << phi << ")";

    return ss.str();
}

string Complex::to_string_exp() const {
    stringstream ss;
    double phi = arg();
    double ro = abs();

    ss << ro << "*e^(";
    if (phi >= 0)
        ss << "i*" << phi;
    else
        ss << "-i*" << -phi;
    ss << ")";

    return ss.str();
}

Complex Complex::add(const Complex& z) const {
    return Complex(re + z.get_re(), im + z.get_im());
}

Complex Complex::sub(const Complex& z) const {
    return Complex(re - z.get_re(), im - z.get_im());
}

Complex Complex::mult(const Complex& z) const {
    return Complex(
        re * z.re - im * z.im,
        re * z.im + im * z.re
    );
}

Complex Complex::div(const Complex& z) const {
    double denominator = z.re * z.re + z.im * z.im;

    return Complex(
        (re * z.re + im * z.im) / denominator,
        (-re * z.im + im * z.re) / denominator
    );
}