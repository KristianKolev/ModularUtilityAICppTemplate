#pragma once
#include <iostream>
#include <vector>
#include "CurveProperties.h"

// Exposed to the editor
//UPROPERTY(BlueprintReadWrite)
// enum is implementation dependant, to be replaced by the user with their own set of custom enums

// What factors do I need to consider?
enum EConsiderations {                           // implementation dependant, replaced by user
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
    ECurvePresetTypes CurvePropertiesPerest {};
};

// What are the actions I can take?
enum EActions {                                  // implementation dependant, replaced by user
    Attack,
    Sneak,
    Flee
};                               

// Implemented as an array. 
// What is my behaviour based on the set of actions I can choose from?
struct ActionSet {                              
    EActions Action {};
    std::vector<Axis> Axes {};
};

// The different types of behaviour I can exhibit.
enum EBehaviourPatterns {                        // implementation dependant, replaced by user
    Satietad,
    Content,
    Hangry
};                     

struct Behaviour {                           
    EBehaviourPatterns behaviourPattern {};
    std::vector<ActionSet> Actions {};
};
