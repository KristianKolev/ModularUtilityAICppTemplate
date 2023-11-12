#include <math.h>
#include <algorithm>
#include <iostream>
#include "ResponseCurves.h"
//#include "Math/UnrealMathUtility.h"

// Not exposed to the Editor
// Transforms the value from the knowledge map into a Score from 0 to 1

/* // normalize and clamp Input
void ResponseCurve::ResponseCurve(double Input, CurveProperties& CurveProperty)
{
        double NormalizedInput = FMath::GetMappedRangeValueClamped
        (FVector2D(CurveProperty.lowerClamp, CurveProperty.upperClamp), FVector2D(0.0f, 1.0f), Input)
}
*/

// prints Curve points to terminal for debugging
void ResponseCurve::PrintGraph(int DataPoints, EResponseCurveType CurveType)
{
    // Consider a Function to build a graph in the UE editor
    std::cout << "Input" << '\t' << "Score" << '\n';
    for (double i = 0; i <= DataPoints; i++)
    {
        Input = i / DataPoints;
        switch (CurveType)
        {
        case Poly:
            std::cout << Input << '\t' << CalculatePolyCurve() << '\n';
            break;
        case Logistic:
            std::cout << Input << '\t' << CalculateLogisticCurve() << '\n';
            break;
        case Logit:
            std::cout << Input << '\t' << CalculateLogitCurve() << '\n';
            break;

        default:
            std::cout << Input << '\t' << CalculatePolyCurve() << '\n';
            break;
        }
    }
};

void ResponseCurve::setCurveProperties(ECurvePresetTypes InCurvePresetType)
{
    CurveProperty = CurvePresets.at(InCurvePresetType);
};
void ResponseCurve::setCurveProperties(CurveProperties InCurveProperty)
{
    CurveProperty = InCurveProperty;
};
// Formula for linear/polynomial graph.
double ResponseCurve::CalculatePolyCurve()
{
    Score = CurveProperty.Slope * pow((Input - CurveProperty.XShift), CurveProperty.Exponent) + CurveProperty.YShift;
    Score = std::clamp(Score, 0.0, 1.0);
    return Score;
};

// Formula for logistic graph. A logistic Curve is a common S-shaped Curve (sigmoid Curve).
// It might be worth it to look into the derivatives of the logistic function.
double ResponseCurve::CalculateLogisticCurve()
{
    Score = CurveProperty.Slope / (1 + exp(-10 * CurveProperty.Exponent * (Input - 0.5 - CurveProperty.XShift))) + CurveProperty.YShift;
    Score = std::clamp(Score, 0.0, 1.0);
    return Score;
};

// Formula for logit graph. Mathematically, the logit is the inverse of the standard logistic function
double ResponseCurve::CalculateLogitCurve()
{
    // to avoid log10(0)
    if (Input == 0.0 && CurveProperty.Slope == 1.0)
        return 0.0;
    else if (Input == 0.0 && CurveProperty.Slope == -1.0)
        return 1.0;
    // to avoid 1/0
    if (Input == 1.0 && CurveProperty.Slope == 1.0)
        return 1.0;
    else if (Input == 1.0 && CurveProperty.Slope == -1.0)
        return 0.0;

    Score = (CurveProperty.Slope * log10((Input - CurveProperty.XShift) / (1 - (Input - CurveProperty.XShift)))) / 5 + 0.5 + CurveProperty.YShift;
    Score = std::clamp(Score, 0.0, 1.0);
    return Score;
};
