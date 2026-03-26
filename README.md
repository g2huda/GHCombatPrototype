# GHCombatPrototype

## Overview
This project implements a simple multiplayer spell system using Unreal Engine 5 and the Gameplay Ability System (GAS). Players can cast a projectile-based spell that damages enemies, with all gameplay and effects properly replicated.

---

## Setup & How to Run
- Open the project in Unreal Engine 5  
- Open **Lvl_ThirdPerson.umap**_
- Play using **2 players (Listen Server)**  
- Press **Right Mouse Button or X** to cast the spell  

---

## Architecture

- Implemented a base class `GHCharacterBase` that contains the **AbilitySystemComponent** and **AttributeSet**  
- Both **player `GHCombatPrototypeCharacter` and enemy `GHEnemey` classes inherit from `GHCharacterBase`** to reuse GAS setup and shared functionality  
- Attributes (Health) are defined in `GHAttributeSet` and replicated using GAS  

---

## Gameplay Flow

1. Ability is granted on possession  
2. Player activates ability via input  
3. Ability spawns a **server-authoritative projectile**  
4. Projectile replicates to clients  
5. On hit:
   - Applies a **Gameplay Effect (`GE_Damage`)** to the target  
   - Triggers a **Gameplay Cue (`GameplayCue.Spell.Impact`)**  
6. Enemy health updates and death is handled on the server  

---

## Replication Notes

- Projectile is **spawned on the server** and uses replicated movement  
- Damage is applied **server-side through GAS**  
- Health is replicated via `FGameplayAttributeData`  
- Impact VFX is triggered using **Gameplay Cues**  

---

## Design Decisions

- Used a shared `GHCharacterBase` base class to reduce duplication between player and enemy  
- Chose a simple, data-driven GAS setup focused on clarity and correctness  
- Used `GameplayCueNotify_Static` for impact VFX since it is a one-shot event  
- Kept systems minimal to focus on **replication and GAS integration**  

---

## If I Had More Time

- Add UI for health display  
- Improve projectile targeting and feedback  
- Expand ability system for multiple abilities 
- Use pool behaviour for projectiles to optimize performance
