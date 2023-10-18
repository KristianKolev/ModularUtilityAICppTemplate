#include <math.h>
#include <algorithm>
#include <iostream>

// Transforms the value from the knowledge map into a score from 0 to 1
class ResponseCurve 
{
    public:
    double input {};
    double Mslope {};
    double Kexponent {};
    double Xshift {};
    double Yshift {};
    double score {};

    ResponseCurve () {}
    ResponseCurve (double I, double M, double K, double X, double Y) : input (I), Mslope (M), Kexponent(K), Xshift(X), Yshift(Y) {}
   
    virtual ~ResponseCurve() {}

    virtual double CalculateCurve() = 0;
    void PrintGraph (int dataPoints) 
    {
        std::cout << "Input" << '\t' << "Score" << '\n';
        for (double i = 0; i < dataPoints; i++)
        {
            std::cout << input << '\t' << CalculateCurve() << '\n';
            input =  i/dataPoints;

        }
    }    
};

// Formula for linear/polynomial graph.
class PolyCurve: public ResponseCurve 
{
    public:
    using ResponseCurve::ResponseCurve;
    double CalculateCurve() 
    {
       
        score = Mslope * pow((input - Xshift), Kexponent) + Yshift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
    }
};

// Formula for logistic graph. A logistic curve is a common S-shaped curve (sigmoid curve).
// It might be worth it to look into the derivatives of the logistic function.
class LogisticCurve: public ResponseCurve 
{
    public:
    using ResponseCurve::ResponseCurve;
    double CalculateCurve() 
    {
       
        score = 
        // Mslope * pow((input - Xshift), Kexponent) + Yshift;
        score = std::clamp(score, 0.0, 1.0);
        return score;
    }
};

// Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
class LogitCurve: public ResponseCurve 
{
    public:
    using ResponseCurve::ResponseCurve;
    double CalculateCurve() 
    {
        //examine that 5 + 0.5 term
        score = ((Mslope * ( log10 ((input - Xshift)/(1 - input - Xshift)) )) / (5 + 0.5 + Yshift));
        score = std::clamp(score, 0.0, 1.0);
        return score;
    }
};

int main ()
{
    PolyCurve TestCurve(-100.0, -1.0, 1.0, 0.0, 1.15);
    TestCurve.PrintGraph(10);
    return 0;
}
