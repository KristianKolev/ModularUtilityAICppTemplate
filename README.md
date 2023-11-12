# ModularUtilityAIForUnrealEngine5

This is the backbone code for creating a video game Utility AI written in vanilla C++.  
It is intended to be used as a starting point and adapted for implementation in an Unreal Engine 5 project.  
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
