#include "UtilityAIComponent.h"

//UFUONCTION(BlueprintReadWrite)
bool SwitchBehaviour (EBehaviourPatterns InBehaviour) {
    bool bBehaviourChanged = false;

    for (auto& i : AllBehaviours) 
    {
        if ( i.behaviourPattern == InBehaviour)
        {
            ActiveBehaviour = i;
            bBehaviourChanged = true;
            return bBehaviourChanged;
        }
    }
    return bBehaviourChanged;
}

double CompensationFactorActionScore (double InScore, int NumberOfActions)
{
    if (InScore == 0)
    {
        return 0;
    }
    else
    {
        InScore = (((1 - (1.0/NumberOfActions)) * (1.0 - InScore)) * InScore) + InScore 
        return InScore;
    }
}

double TransformToScore (std::map<EConsiderations, double> InputMap, Axis Axis)
{
    switch (EResponseCurveType)
    {
    case Poly:
        PolyCurve EvaluationCurve;
        break;
    case Logistic:
        LogisticCurve EvaluationCurve;
        break;
    case Logit:
        LogitCurve EvaluationCurve;
        break;
    
    default:
        break;
    }
}
//UFUONCTION(BlueprintReadWrite)
double ScoreActions (std::map<EConsiderations, double> KnowledgeMap, Behaviour )
{
    for (auto& ObservedAction : ActiveBehaviour.Actions)
    {
        for (auto& ObservedConsideration : ObservedAction.Axes)
        {
            double TransformToScore (std::map<EConsiderations, double> InputMap, Axis Axis);
        }
    }
    return 0;
}


int main () 
{
    
    return 0;
}
