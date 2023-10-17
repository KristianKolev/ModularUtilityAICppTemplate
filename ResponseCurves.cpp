#include <math.h>
#include <algorithm>
#include <iostream>

// Transforms the value from the knowledge map into a score from 0 to 1
class ResponseCurve 
{
    public:
    float Mslope {};
    float Kexponent {};
    float Xshift {};
    float Yshift {};
    float input {};
    float score {};

    ResponseCurve ();
    ResponseCurve (float I, float M, float K, float X, float Y) : input (I), Mslope (M), Kexponent(K), Xshift(X), Yshift(Y) {}

    virtual int CalculateCurve() = 0;
    float PrintGraph (int dataPoints) 
    {
        std::cout << "Input", '/t', "Score";
        for (i = 0, i < dataPoints, i++)
        {
            std::cout << input, '/t', CalculateCurve();
            input =  1/dataPoints;

        }
    }
        
}

// Formula for linear/polynomial graph.
class PolyCurve: public ResponseCurve {
    public:
    int CalculateCurve() 
    {
        //examine that 5 + 0.5 term
        score = ((Mslope * ( log10 ((input - Xshift)/(1 - input - Xshift)) )) / (5 + 0.5 + Yshift));
        score = std::clamp(score, 0, 1);
        return score;
    }
}

int main ()
{
    
    return 0;
}