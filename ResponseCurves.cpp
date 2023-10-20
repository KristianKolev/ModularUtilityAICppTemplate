#include <math.h>
#include <algorithm>
#include <iostream>
#include "ResponseCurves.h"

// Not exposed to the Editor

// Transforms the value from the knowledge map into a score from 0 to 1
void ResponseCurve::PrintGraph(int dataPoints ) {

    // Consider a Function to build a graph in the UE editor
        std::cout << "Input" << '\t' << "Score" << '\n';
        for (double i = 0; i <= dataPoints; i++)
        {
            input =  i/dataPoints;
            std::cout << input << '\t' << CalculateCurve() << '\n';
        }
};

// Formula for linear/polynomial graph.
double PolyCurve::CalculateCurve() {
       
        score = Mslope * pow((input - Xshift), Kexponent) + Yshift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

// Formula for logistic graph. A logistic curve is a common S-shaped curve (sigmoid curve).
// It might be worth it to look into the derivatives of the logistic function.
double LogisticCurve::CalculateCurve() {
       
        score = Mslope / (1 + exp(-10 * Kexponent * (input - 0.5 - Xshift))) + Yshift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

// Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
double LogitCurve::CalculateCurve() {
        //examine that 5 + 0.5 term
        score = ((Mslope * ( log10 ((input - Xshift)/(1 - input - Xshift)) )) / (5 + 0.5 + Yshift));
        score = std::clamp(score, 0.0, 1.0);
        return score;
};

int main ()
{
    LogisticCurve TestCurve(100, -1.0, 0.7, -0.05, 1.08);
    TestCurve.PrintGraph(10);
    return 0;
}
