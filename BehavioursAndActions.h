#pragma once
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

// The consideration together with data needed to score it
struct Axis {
    EConsiderations Consideration {};
    EResponseCurveType CurveType {};  
    CurveProperties CurveProperty {};
    bool bUsePresetCurve {};
    CurvePresetTypes CurvePropertiesPerest {};
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

struct Behaviour {                           // this could be a map
    EBehaviourPatterns behaviourPattern {};
    std::vector<ActionSet> Actions {};
};
