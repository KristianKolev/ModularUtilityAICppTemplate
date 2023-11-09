#include "UtilityAIComponent.h"
#include <algorithm>
#include <vector>

// Exposed to the editor
// UOBJECT - Component
//UFUONCTION(BlueprintReadWrite)
bool UtilityAIComponent::SwitchBehaviour(EBehaviourPatterns InBehaviour) {
    bool bBehaviourChanged = false;

    for (auto& ObservedBehaviour : AllBehaviours) 
    {
        if ( ObservedBehaviour.behaviourPattern == InBehaviour)
        {
            ActiveBehaviour = ObservedBehaviour;
            bBehaviourChanged = true;
            return bBehaviourChanged;
        }
    }
    return bBehaviourChanged;
}

double UtilityAIComponent::CompensationFactorActionScore(double InScore, int NumberOfConsiderations)
{
        InScore = (((1 - (1.0/NumberOfConsiderations)) * (1.0 - InScore)) * InScore) + InScore;
        return InScore;
}

double UtilityAIComponent::TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis)
{
    //Consider whether to put this here or inside ResponseCurve Constructor
    // this gets replaced by FMath::GetMappedRangeValueClamped in UE
    double ClampedInput = std::clamp(InputMap.at(Axis.Consideration), Axis.CurveProperty.LowerClamp, Axis.CurveProperty.UpperClamp);
    double NormalizedInput = ClampedInput/Axis.CurveProperty.UpperClamp;
    ResponseCurve TransformCurve { NormalizedInput };
    if (Axis.bUsePresetCurve == true)
    {
        TransformCurve.setCurveProperties(Axis.CurvePropertiesPerest);
    }
    else 
    {
        TransformCurve.setCurveProperties(Axis.CurveProperty);
    }
    switch (Axis.CurveType)
    {
        case Poly:
            return TransformCurve.CalculatePolyCurve();
        case Logistic:
            return TransformCurve.CalculateLogisticCurve();
        case Logit:
            return TransformCurve.CalculateLogitCurve();
        default:
            return TransformCurve.CalculatePolyCurve();
    }
}
//UFUONCTION(BlueprintCallable)
double UtilityAIComponent::ScoreConsiderations(std::vector<Axis> InConsiderations)
{
    double ActionScore{ 1.0 };
    for (auto& ObservedConsideration : InConsiderations)
    {
        ActionScore *= TransformInputToScore(KnowledgeMap, ObservedConsideration);
        if (ActionScore == 0)
            return ActionScore;
    }
    return ActionScore;
}

std::vector<double> UtilityAIComponent::ScoreActions()
{
    std::vector<double> ActionScores{};
    
    for (auto& ObservedAction : ActiveBehaviour.Actions)
    {
        double AdjustedActionScore {0.0};
        double ActionScore = ScoreConsiderations(ObservedAction.Axes);
        if (ActionScore != 0)
        {
            int NumberOfConsiderations = static_cast<int> (ObservedAction.Axes.size());
            AdjustedActionScore = CompensationFactorActionScore(ActionScore, NumberOfConsiderations);
        }
        ActionScores.push_back(AdjustedActionScore);

    }
    return ActionScores;
}

EActions UtilityAIComponent::PickBestAction(std::vector<double> InScores)
{
    int TopScorePosition{0};
    for (int i = 0; i < InScores.size(); i++)
    {
        if (InScores[i] > InScores[TopScorePosition])
        TopScorePosition = i;
    }
    return ActiveBehaviour.Actions.at(TopScorePosition).Action;
}
//calls function logic on the npc controller
void UtilityAIComponent::ExecuteAction(NPCController InController, EActions InAction)
{
    
    switch (InAction)
    {
    case Attack: 
        InController.RunActionAttack();
        break;
    case Sneak:
        InController.RunActionSneak();
        break;
    case Flee:
        InController.RunActionFlee();
        break;
    default:
        InController.RunActionIdle();
        break;
    }
}
void UtilityAIComponent::ScorePickAndExecuteAction(NPCController InController)
{
    std::vector<double> ActionScores = ScoreActions();
    EActions BestAction = PickBestAction(ActionScores);
    ExecuteAction(InController, BestAction);
}
void NPCController::RunActionAttack()
{
    std::cout << "I am attacking!";
}
void NPCController::RunActionSneak()
{
    std::cout << "I am sneaking!";
}
void NPCController::RunActionFlee()
{
    std::cout << "I am fleeing!";
}
void NPCController::RunActionIdle()
{
    std::cout << "I do nothing!";
}
