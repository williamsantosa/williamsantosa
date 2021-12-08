#include "mathlib.h"

#include <math.h>

#define EPSILON 1e-14 // 1 x 10^(-14) / From Eugene's Lab Section

// Basically, if x < 0 then return -x, else return x
static inline double Abs(double x) { // Included within asgn2 document
    return x < 0 ? -x : x;
}

// Square root of value. Initializes first term to 1 and old to 0. Within while loop it sets the old term to x_n and then updates
// x_n using Newton's method. 0.5 represents 1/2 and is multiplied by (x_k plus (y/x_k), where x_k = x_n and y is y.
double Sqrt(double y) { // Included within asgn2 document
    double x_n = 1.0;
    double old = 0.0;
    while (Abs(x_n - old) > EPSILON) {
        old = x_n;
        x_n = 0.5 * (x_n + y / x_n);
    }
    return x_n;
}

// Sin of x value.
double Sin(double
        x) { // Included within "Numerical Computation" slides, altered using pseudocode from Eugene's lab 1/19/21

    x = fmod(x, 2.0 * M_PI); // Normalize to be within -2pi to 2pi inclusive, from piazza note@34
    double sum = x; // Will be the end value returned, also the starting value in taylor series
    double numerator = x; // Numerator (x^2k+1)
    double denominator = 1.0; // Denominator (2k+1)!
    for (double k = 3.0; Abs(numerator / denominator) > EPSILON;
         k += 2.0) { // Makes more accurate using taylor series
        numerator
            *= -x
               * x; // Numerator switches sign, multiplies by itself twice because 2k in numerator
        denominator
            *= k
               * (k
                   - 1.0); // This one just multiplies the next two terms in factorial (8, 9, 10) to previous
        sum += numerator / denominator; // Adds terms to sum to be more accurate
    }
    return sum;
}

// Cos of x value.
double Cos(double x) { // Altered from Sin function
    x = fmod(x, 2.0 * M_PI); // Normalize to be within -2pi to 2pi inclusive, from piazza note@34
    double sum = 1.0; // Will be the end value returned, also the starting value in taylor series
    double numerator = 1.0; // Numerator (x^2k+1)
    double denominator = 1.0; // Denominator (2k+1)!
    for (double k = 2.0; Abs(numerator / denominator) > EPSILON;
         k += 2.0) { // Makes more accurate using taylor series
        numerator
            *= -x
               * x; // Numerator switches sign, multiplies by itself twice because 2k in numerator
        denominator
            *= k
               * (k
                   - 1.0); // This one just multiplies the next two terms in factorial (8, 9, 10) to previous
        sum += numerator / denominator; // Adds terms to sum to be more accurate
    }
    return sum;
}

// Tan of x value.
double Tan(double x) {
    return Sin(x) / Cos(x);
}

// e to the power of x value.
double Exp(double x) { // Included within "Numerical Computation" slides
    double term = 1.0; // Starting number, will also determine when to stop iterations
    double sum = term; // Returned variable
    for (double k = 1.0; Abs(term) > EPSILON; k += 1.0) {
        term = x / k * term; // Term multiplied by x/k, as defined within the taylor series for e^x
        sum += term; // Adds to the term to the total
    }
    return sum;
}
// log_e(x)
double Log(double x) { // Included within "Numerical Computation" slides
    double y = 1.0; // Return variable
    double p = Exp(y); // Previous number, will be changed
    while (Abs(p - x) > EPSILON) { // If margin is less than epsilon then it breaks
        y += (x - p) / p; // Changes return to be more accurate
        p = Exp(y);
    }
    return y;
}
