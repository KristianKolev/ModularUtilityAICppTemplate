#include <iostream>
#include <vector>
#include "CurveProperties.h"
// Exposed to the editor
//UPROPERTY(BlueprintReadWrite)
// enum is to be replaced by the user with their own set of custom enums

// What factors do I need to consider?
enum EConsiderations {                           // replaced by user, values are placeholder examples
        DistanceToTarget, 
        TargetsInRange, 
        TimeSinceLastMeal
};    

// See ResponseCruves.cpp
enum EResponseCurveType { Poly, Logistic, Logit };

// The consideration together with data needed to score it
struct Axis {
    EConsiderations consideration {};
    EResponseCurveType CurveType {};  
    CurveProperties CurveProperty {};
    bool bUsePresetCurve {};
    CurvePresets {};
};

// What are the actions I can take?
enum EActions {                                  // replaced by user, values are placeholder examples
    Attack,
    Sneak,
    Flee
};                               

// Implemented as an array. 
// What is my behaviour based on the set of actions I can choose from?
struct ActionSet {                              // this could be a map
    EActions Action {};
    std::vector<Axis> Axes {};
};

// The different types of behaviour I can exhibit.
enum EBehaviourPatterns {                        // replaced by user, values are placeholder examples
    Satietad,
    Content,
    Hangry
};                     

struct BehaviourSet {                           // this could be a map
    EBehaviourPatterns behaviourPattern {};
    std::vector<ActionSet> Actions {};
};

std::vector<BehaviourSet> AllBehaviours {};
BehaviourSet ActiveBehaviour {};

/* 
This could be a good spot for the knowledge map. Need to consider how to implement it as it is 
mostly define by the use case and hard to generalize. Each game will have it's own method and data set
that need to be aggregated and monitored.
*/
