# ModularUtilityAIForUnrealEngine5

This is the backbone code for creating a video game Utility AI written in vanilla C++.  
It is intended to be used as a starting point and adapted for implementation in an Unreal Engine 5 project. However, they way it is written allows for easy protability to other frameworks if desired.   
The same backbone but written for the Unreal framework will be available [here] at some point.  

It is written for modularity and scalability.  
For low level breakdown of how the system works I suggest to refer to the creator of the architecture - Dave Mark.  
The following two talks provide good insight:  
https://www.gdcvault.com/play/1012410/Improving-AI-Decision-Modeling-Through  
https://www.gdcvault.com/play/1021848/Building-a-Better-Centaur-AI  

## What is Utility AI
*High level*  

Utility AI is a decision making system for NPCs in video games and simulations. It is more advanced than state machines and behavioural trees and similar to GOAP.  
Each NPC has a set of **Behaviours** they can exhibit and can choose their **active behaviour** based on some user defined environmental factors.  
Each behaviour has a set of possible **Actions** that the NPC can choose to take based on which is best in the currecnt situation i. e. has the highest score.  
To get a score each action has a set of **Considerations** which get evaluated.  
Each consideration resides in an **Axis** which stores the value of the consideration and has data on how to convert and score of that value from 0 to 1.  
The conversion happens by passing the input trough a **Response Curve** which can be linear, polynomial, logistic or logit.

## Implementation Specifics
This utility AI architecture makes use of **structs** instead of an inheritance based approach in an attempt to make it easier for someone with little to no knowledge of Utility AI
to adapt and implement the code for their particular use case. If you are alraedy familiar with the AI structure and plan to use it between different projects on the same framework (Unreal Engine)
it makes more sense to use classes, though the current architecture will do the job of portability just as well.

To get started with this AI, you will need to build out the behaviours your NPC will exhibit. For this code I imagine a hypothetical example of a *lion* as the decision making AI trying to get *food* (from a carcass) 
that is being guarded by *hyenas*. My lion has the behaviours of *satiated*, *content*, *hangry*.  
In `enum EBehaviourPatterns` add in the names of your behaviours.  
To build out the `std::vector<Behaviour> AllBehaviours`, you will need to fill them with `std::vector<ActionSet> Actions`. My lion can do the actions *attack*, *sneak*, *flee*.  
In `enum EActions` add in the names of your actions.  
Behaviour: Actions

> Satiated: Sneak, Flee  
> Content: Attack, Sneak, Flee  
> Hangry: Attack, Sneak

To define the `struct ActionSet` you need to give it `std::vector<Axis> Axes`. The main component of the axis is the *consideration*. My lion has the *distance to target*, *targets in range*, *time since last meal*.
In `enum EConsiderations` add in the names of your considerations.
In `struct Axis` pair a consideration with properties for the response curve.  
Behaviour: Action [consideration (CurveType, UpperLimit)]  

> Staiated:  
> Sneak [TargetsInRange (LinearFall, 3), DistanceToTarget(PolyFall, 200), TimeSinceLastMeal (LinearRise, 60]  
> Flee  [TargetsInRange (LinearRise, 6), DistanceToTarget(PolyRise, 200), TimeSinceLastMeal (LinearFall, 60]  
 
To break this down, the lion has eaten recently, but might attempt to sneak in and snatch a piece of meat if there aren't too many hyenas and they arent too far away.
The flee action has basically the same considerations, but in reverse. So sneak scores high when flee scores low and vice versa.  

> 'Content:  
> Attack [TargetsInRange (LinearFall, 3), DistanceToTarget(PolyFall, 200), TimeSinceLastMeal (LinearRise, 600]  
> Sneak  [TargetsInRange (LinearFall, 6), DistanceToTarget(PolyFall, 500), TimeSinceLastMeal (LinearRise, 600]  
> Flee   [TargetsInRange (LinearRise, 9), DistanceToTarget(PolyRise, 500), TimeSinceLastMeal (LinearFall, 600]  

It's been a while since his last meal, but the lion isn't hungry quite yet. He might attack into a favourable position, might attempt to sneak into an unfavourable position (to snatch a piece of meat while the hyenas are distracted) or else flee and try another spot.

> 'Hangry:  
> Attack [TargetsInRange (LinearFall, 6), DistanceToTarget(PolyFall, 600), TimeSinceLastMeal (LinearRise, 1440]  
> Sneak  [TargetsInRange (LinearFall, 9), DistanceToTarget(PolyFall, 700), TimeSinceLastMeal (LinearRise, 1440]  

The lion is starving and aggressive. He is ready to attack into an unfavourable position and will try to sneak into any spot where he knows he cannot win. 

