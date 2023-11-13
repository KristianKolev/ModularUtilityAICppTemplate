#include "UtilityAIComponent.h"
#include <algorithm>
#include <vector>

// Exposed to the editor
// UOBJECT - Component
//UFUONCTION(BlueprintReadWrite)

double UtilityAIComponent::TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis)
{
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

double UtilityAIComponent::CompensationFactorActionScore(double InScore, int NumberOfConsiderations)
{
    InScore = (((1 - (1.0 / NumberOfConsiderations)) * (1.0 - InScore)) * InScore) + InScore;
    return InScore;
}
//UFUONCTION(BlueprintCallable)
double UtilityAIComponent::ScoreConsiderations(std::vector<Axis> InConsiderations)
{
    double AdjustedActionScore{ 0.0 };
    double ActionScore{ 1.0 };
    for (auto& ObservedConsideration : InConsiderations)
    {
        ActionScore *= TransformInputToScore(KnowledgeMap, ObservedConsideration);
        if (ActionScore == 0)
            return ActionScore;
    }
    int NumberOfConsiderations = static_cast<int> (InConsiderations.size());
    AdjustedActionScore = CompensationFactorActionScore(ActionScore, NumberOfConsiderations);
    return AdjustedActionScore;
}
// rework to score and pick best target. Do this inside the loop instead of new loop in new function
double UtilityAIComponent::ScoreTargets(std::vector<NPCTarget> InTargets, std::vector<Axis> InConsiderations, NPCTarget* OutTarget)
{
    std::vector<double> TargetScores{};
    double BestScore{ 0.0 };
    for (auto& ObservedTarget : InTargets)
    {
        double TargetScore = ScoreConsiderations(InConsiderations);
        TargetScores.push_back(TargetScore);
        if (BestScore < TargetScore)
        {
            BestScore = TargetScore;
            ObservedTarget = *OutTarget;
        }
    }
    return BestScore;
}
// rework to score and pick best action. Do this inside the loop instead of new loop in new function
std::vector<double> UtilityAIComponent::ScoreActions(std::vector<ActionSet> InActions)
{
    std::vector<double> ActionScores{};
    
    for (auto& ObservedAction : InActions)
    {
        if (ObservedAction.bTargeted = true)
        {
            /*
            std::vector<double> TargetScores = ScoreTargets(PossibleTargets, ObservedAction.Axes, BestTarget);
            ActionScores.insert(end(ActionScores), begin(TargetScores), end(TargetScores));
            */
            double TargetScores = ScoreTargets(PossibleTargets, ObservedAction.Axes, BestTarget);
            ActionScores.push_back(TargetScores);
        }
        else 
        {
            double ActionScore = ScoreConsiderations(ObservedAction.Axes);
            ActionScores.push_back(ActionScore);
        }
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

void UtilityAIComponent::ExecuteAction(NPCController InController, EActions InAction)
{
    
    switch (InAction)
    {
    case Attack: 
        InController.RunActionAttack(BestTarget);
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

void UtilityAIComponent::UpdateKnowledgeMap(std::map<EConsiderations, double> OutKnowledgeMap)
{
    OutKnowledgeMap[TargetsInRange] = 3;
}

void UtilityAIComponent::ScorePickAndExecuteAction(NPCController InController)
{
    UpdateKnowledgeMap(KnowledgeMap);
    std::vector<double> ActionScores = ScoreActions(ActiveBehaviour.Actions);
    EActions BestAction = PickBestAction(ActionScores);
    ExecuteAction(InController, BestAction);
}
void NPCController::RunActionAttack(NPCTarget* InTarget)
{
    std::cout << "I am attacking" << InTarget->Name << "!";
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

bool UtilityAIComponent::SwitchBehaviour(EBehaviourPatterns InBehaviour) {
    bool bBehaviourChanged = false;
    if (ActiveBehaviour.behaviourPattern != InBehaviour)
    {
        for (auto& ObservedBehaviour : AllBehaviours)
        {
            if (ObservedBehaviour.behaviourPattern == InBehaviour)
            {
                ActiveBehaviour = ObservedBehaviour;
                bBehaviourChanged = true;
                return bBehaviourChanged;

            }
        }
        return bBehaviourChanged;
    }
    else
    {
        return bBehaviourChanged;
    }
}

int main()
{
    ResponseCurve TestCurve{ 0.5, PolySlowRise };
    TestCurve.PrintGraph(10, Poly);

    return 0;
}
