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

// The consideration together with data needed to builds the scoring curve
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
// Which actions come together to define a behaviour
struct ActionSet {                              
    EActions Action {};
    std::vector<Axis> Axes {};
    bool bTargeted {};
};

// The different types of behaviours I can exhibit.
enum EBehaviourPatterns {                        // implementation dependant, replaced by user
    Satietad,
    Content,
    Hangry
};                     
// A pairing of a behaviour to a set of actions.
struct Behaviour {                           
    EBehaviourPatterns behaviourPattern {};
    std::vector<ActionSet> Actions {};
};
