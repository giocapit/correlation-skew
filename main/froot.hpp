#ifndef froot_hpp
#define froot_hpp
#include "Functional.hpp"

double froot(Functional* f,double x_lower,double x_upper);

double bisection(Functional* f, double x_lower, double x_upper);

double corde(Functional* f, double x_lower, double x_upper, double xtol);

double corde(Functional* f, double x_lower, double x_upper);

#endif
