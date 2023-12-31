#pragma once    
#include "ResponseCurves.h"
#include "BehavioursAndActions.h"
#include "CurveProperties.h"

//get reference to this from project. Exists here for testing purposes
//NPCController = AAIController ;

class NPCController
{
public:
    std::string Name = "MySelf";
    void RunActionAttack(NPCTarget* InTarget);
    void RunActionSneak();
    void RunActionFlee();
    void RunActionIdle();
    std::map<EConsiderations, double> KnowledgeMap{};
};
//get reference to this from project. Exists here for testing purposes
class NPCTarget
{
public:
    std::string Name = "MyTarget";
    std::map<EConsiderations, double> KnowledgeMap{};
};

// Exposed to the editor
// UOBJECT - Component
class UtilityAIComponent 
{
private:
    // UPROPERTY(BlueprintReadWrite)
    std::vector<Behaviour> AllBehaviours {};
    Behaviour ActiveBehaviour {};
    std::vector<NPCTarget> PossibleTargets{};
    //This is something that should maybe be held inside the knowledge map
    NPCTarget* BestTarget{};


public:
    /* 
    Need to consider how to implement map as it is mostly defined by the use case and hard to generalize. 
    Each game will have it's own method and data set that need to be aggregated and monitored.
    Each actor has his own knowledge map with values.
    Values of the map should be updated before ScorePickAndExecuteAction() is called.
    In a per implementaion based method, fill the Utility knowledge map with values from the actors knowledgemap.
    */
    // UPROPERTY(BlueprintReadWrite)
    std::map<EConsiderations, double> KnowledgeMap {}; 
    //Runs the input from the knowledge map trough a response curve to generate a score
    double TransformInputToScore(std::map<EConsiderations, double> InputMap, Axis Axis);
    //To remove the penalty from multiplying many fractional values together
    double CompensationFactorActionScore(double InScore, int NumberOfActions);
    // Multiplies the scores for all considerations inside an action and apply a compensation factor
    double ScoreConsiderations(std::vector<Axis> InConsiderations);
    double ScoreTargets(std::vector<NPCTarget> InTargets, std::vector<Axis> InConsiderations, NPCTarget* OutTarget);
    // modify to work with targets - same action evaluated multiple times for each target (external array of possible targets)
    // maybe trough if statement that checks target == NULL?
    //Collects the adjusted scores for all actions
    std::vector<double> ScoreActions(std::vector<ActionSet> InActions);
    //Picks the highest scoring action from the array of all actions.
    EActions PickBestAction(std::vector<double> AllScores);
    //calls function logic on the npc controller
    void ExecuteAction(NPCController InController, EActions InAction);
    //logic replaced based on custom implementation
    void UpdateKnowledgeMap(std::map<EConsiderations, double> OutKnowledgeMap);
    //Combines the other methods together 
    void ScorePickAndExecuteAction(NPCController InController);
    bool SwitchBehaviour(EBehaviourPatterns InBehaviour);                           //Logic and conditions to switch are implementation dependant.
};
