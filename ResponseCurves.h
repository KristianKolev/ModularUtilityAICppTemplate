#ifndef RESPONSECURVES_H
#define RESPONSECURVES_H

// Not exposed to the Editor
// Transforms the value from the knowledge map into a score from 0 to 1
class ResponseCurve 
{
    protected:
    double input {};
    double Mslope {};
    double Kexponent {};
    double Xshift {};
    double Yshift {};
    double score {};

    public:
    ResponseCurve () {}
    // input needs to be normalized with the clamp of its value. receive clamps in constructor and normalize in calculateCurve?
    // or do this like I have it implemented in blueprints currently, outside of the response curve
    ResponseCurve (double I, double M, double K, double X, double Y) : input (I), Mslope (M), Kexponent(K), Xshift(X), Yshift(Y) {}
    virtual ~ResponseCurve() {}
    virtual double CalculateCurve() = 0;
    // Consider a Function to build a graph in the UE editor
    void PrintGraph (int dataPoints);
};

// Formula for linear/polynomial graph.
class PolyCurve: public ResponseCurve 
{
    public:
    using ResponseCurve::ResponseCurve;
    double CalculateCurve();
};

// Formula for logistic graph. A logistic curve is a common S-shaped curve (sigmoid curve).
// It might be worth it to look into the derivatives of the logistic function.
class LogisticCurve: public ResponseCurve 
{
    public:
    using ResponseCurve::ResponseCurve;
    double CalculateCurve();
};

// Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
class LogitCurve: public ResponseCurve 
{
    public:
    using ResponseCurve::ResponseCurve;
    double CalculateCurve();
};

#endif
