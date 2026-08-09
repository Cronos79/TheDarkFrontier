# The Dark Frontier — Incremental Dependency-Driven Programming Method

## Purpose

This document defines the programming method used for **The Dark Frontier**.

The goal is to avoid premature architecture, placeholder-heavy systems, rigid sprint plans, and speculative code that later has to be removed or rewritten.

Development should move from the **final game vision** toward working gameplay one concrete dependency at a time.

The vision tells us **what the finished game should be**.

The codebase should only contain **what the current playable path actually requires**.

---

# Core Principle

> **Do not implement a system because the design says the game will eventually need it. Implement it when the next real gameplay step cannot work correctly without it.**

Every programming task begins with a concrete gameplay goal.

Example:

> The player should be able to build a Lumbermill.

Do not immediately create a complete construction system.

Instead ask:

> What is the first thing preventing the Lumbermill from being built correctly in the current codebase?

Then follow that dependency backward until reaching the deepest missing prerequisite.

Implement that prerequisite first.

---

# Vision First, Implementation Day by Day

The project should still have a strong final vision.

The vision may define things such as:

- physical resources;
- citizens;
- buildings;
- construction;
- hauling;
- jobs;
- housing;
- schedules;
- needs;
- town progression;
- professions;
- storage;
- production;
- roads;
- weather;
- combat;
- magic;
- dragons.

However, the vision does **not** determine the order in which those systems are programmed.

The implementation order is discovered by asking:

> **What must already exist for the next desired gameplay action to work correctly?**

No sprint should force a system into existence before the game is ready for it.

---

# Dependency-First Development

For every desired gameplay result:

1. State the visible gameplay goal.
2. Ask what that goal requires.
3. Inspect the current codebase.
4. Find the first required thing that does not really exist yet.
5. Stop working on the original goal.
6. Implement the missing prerequisite.
7. Test it.
8. Return to the original goal.
9. Repeat until the gameplay path works.

Do not continue downstream while an upstream dependency is fake, missing, or represented by placeholder logic.

---

# Example: Building a Lumbermill

Desired result:

> A citizen builds a Lumbermill.

Start walking backward.

## Question 1 — Can a citizen reach the construction site?

If citizens cannot move yet:

> Stop.

Implement citizen movement.

Do not build construction yet.

---

## Question 2 — Does the Lumbermill require materials?

The final vision says construction uses physical resources.

Therefore the Lumbermill cannot simply consume a magical city-wide resource number.

If the Lumbermill needs 10 logs, ask:

> Where are the 10 logs physically located?

Suppose they are in the starting wagon.

---

## Question 3 — Can a citizen carry logs?

If not:

> Stop construction work.

The next required system is carrying.

But before implementing carrying, ask:

> How many logs can the citizen carry?

That requires resource weight.

---

## Question 4 — Do logs have weight?

If resource definitions do not contain weight:

> Stop.

Add real resource weight data.

For example:

- Log weight = 10 lb
- Citizen carrying capacity = 50 lb

Now the citizen may carry 5 logs.

Do not invent a temporary "carry 5 items" rule if the final game uses weight.

---

## Question 5 — Can the construction site receive materials?

The citizen can carry 5 logs, but the Lumbermill needs 10.

The site therefore needs real material storage.

If construction-site inventory does not exist:

> Stop hauling work.

Add inventory/storage to the construction site.

Now the real sequence becomes:

1. Citizen goes to wagon.
2. Citizen picks up 5 logs.
3. Citizen walks to Lumbermill site.
4. Citizen delivers 5 logs.
5. Citizen returns to wagon.
6. Citizen picks up the remaining 5 logs.
7. Citizen delivers them.
8. Construction site now contains all 10 required logs.
9. Construction may begin.

Only now should actual construction work be implemented.

---

# The Important Rule

At every point:

> **If the next gameplay action requires data or behavior that does not exist, stop and build that dependency first.**

Do not fake the dependency just to keep moving.

Do not write the downstream code around a placeholder assumption.

---

# Small Data Objects Are Good

A class should begin with only the information the game currently requires.

Example:

## Building — First Version

```text
Building
    ID
```

That is enough to create six different building records.

No construction state.

No inventory.

No worker slots.

No health.

No production.

No upgrade tier.

No storage.

No building effects.

Those fields are added only when gameplay reaches a point where they are required.

---

## Building — Later

When construction becomes necessary:

```text
Building
    ID
    State
```

Example state:

```text
Unbuilt
Built
```

If that is all current gameplay requires, stop there.

Do not immediately add:

```text
Placement
Foundation
Construction
Finished
Damaged
Destroyed
Upgrading
Repairing
Disabled
```

unless the current game actually needs those states.

---

# Citizen Example

Start with:

```text
Citizen
    ID
```

Create five citizens.

They do not need:

- Hunger
- Thirst
- Happiness
- Entertainment
- Sleep
- Warmth
- Skills
- Traits
- Schedules
- Jobs
- Housing
- Religion
- Social needs
- Medical state

until gameplay reaches a point that actually requires those systems.

---

## Citizen Movement

When the next gameplay requirement is:

> A citizen must walk to the construction site.

Add only what is required to make the citizen move correctly.

Now the citizen may be:

```text
Citizen
    ID
```

while the world actor knows how to move.

Do not add hunger because citizens will eventually need food.

That is not today's problem.

---

## Citizen Carrying

When the next requirement becomes:

> The citizen must transport logs.

Now carrying capacity becomes necessary.

Add it.

```text
Citizen
    ID
    CarryCapacity
```

If inventory is needed to know what the citizen is physically carrying, add the minimum real inventory representation required.

That code exists because the current gameplay path requires it.

---

# Avoid Placeholder Systems

Placeholder code is especially dangerous when other systems begin depending on it.

Example:

```cpp
bool CanCitizenPerformConstruction() const
{
    return true;
}
```

If five other classes begin calling that method, replacing it later may require changes across the entire codebase.

Worse, downstream code may have been designed around assumptions that are no longer true.

This creates cascading refactors.

---

# Production Rule vs Placeholder Rule

There is an important distinction.

## Placeholder

```cpp
return true;
```

because:

> "We will make construction rules later."

This is speculative and temporary.

---

## Valid Incremental Production Rule

Suppose the only implemented settlement stage currently allows all unemployed adult citizens to construct.

Then this is a real rule:

```text
Adult
AND
No permanent job
    =>
May perform construction
```

That is not placeholder code.

When Builder Huts and Town Hall Tier 2 actually become part of playable gameplay, the rule expands.

The earlier implementation was still correct for the game that existed at that time.

---

# Do Not Build Future Systems Early

Do not create:

- a complete hunger system before food exists;
- a sleep system before homes exist;
- a hauling system before physical resources exist;
- job scheduling before jobs actually need schedules;
- town tiers before gameplay reaches progression that requires tiers;
- builder professions before Builder Huts exist;
- complex AI intent systems before citizens need those behaviors;
- generalized inventories before something genuinely needs inventory.

A future feature in the vision is **not enough reason to create code today**.

---

# Brainstorm More, Code Less

Before writing code, ask questions.

For construction:

- Where do materials physically exist?
- Who owns them?
- Can they be reserved?
- Can multiple citizens deliver them?
- When are they consumed?
- What happens if the site is cancelled?
- What happens to delivered resources?
- What happens if materials run out?
- Does construction wait?
- Where does the citizen stand?
- Can multiple citizens build simultaneously?
- What determines carrying capacity?
- What determines resource weight?

The purpose is not to implement every answer immediately.

The purpose is to discover which answer the **next line of code depends on**.

---

# Never Skip a Missing Dependency

If today's goal is:

> Produce logs at a Lumbermill.

and the Lumbermill does not exist yet:

> Stop.

Make the Lumbermill.

If creating the Lumbermill correctly requires construction:

> Stop.

Work backward into construction.

If construction requires physical materials:

> Stop.

Work backward into resources.

If moving resources requires citizens to carry them:

> Stop.

Work backward into carrying.

If carrying requires resource weight:

> Stop.

Add resource weight.

Then move forward again.

---

# Working Forward Again

Once the deepest dependency works, climb the dependency chain forward.

Example:

```text
Resource Weight
    ↓
Citizen Carry Capacity
    ↓
Citizen Inventory
    ↓
Wagon Inventory
    ↓
Construction-Site Inventory
    ↓
Material Delivery
    ↓
Construction Work
    ↓
Finished Lumbermill
    ↓
Lumbermill Worker
    ↓
Log Production
```

Each layer should be implemented only when the layer below it is real enough to support it.

---

# No Rigid Sprint Architecture

Avoid development plans such as:

```text
Sprint 1 — Citizen System
Sprint 2 — Building System
Sprint 3 — Needs System
Sprint 4 — Construction System
Sprint 5 — Jobs System
```

This encourages artificial boundaries and speculative completeness.

A "Citizen System" is never truly complete.

Instead use concrete goals:

```text
Today:
Make one citizen exist.

Next:
Make the citizen move.

Next:
Make logs have physical weight.

Next:
Let the citizen carry logs.

Next:
Let the wagon store logs.

Next:
Let a construction site receive logs.
```

The project grows naturally from gameplay pressure.

---

# Avoid Premature Generalization

Do not create a generalized solution until multiple real gameplay cases require it.

For example:

Do not create a massive universal "Action System" because someday citizens may:

- eat;
- sleep;
- pray;
- fight;
- haul;
- build;
- farm;
- socialize;
- repair;
- heal;
- research.

First implement one real action.

Then another.

When repeated patterns become obvious from actual working code, extract the shared abstraction.

Generalization should come from observed repetition, not prediction.

---

# Refactor From Evidence

Refactor when:

- two or more real implementations contain meaningful duplication;
- a current gameplay requirement no longer fits the existing structure;
- ownership has become unclear;
- a system is actively preventing the next correct feature;
- working code reveals a better abstraction.

Do not refactor because:

- a future feature might need something;
- a roadmap predicts complexity;
- a class might become large someday;
- a pattern could theoretically be generalized.

---

# Existing Code Policy

When working in an existing codebase:

## Keep it

If existing code directly supports the current gameplay goal correctly.

## Ignore it

If it is unused and does not block current work.

Do not waste time cleaning unrelated code.

## Modify it

If it almost supports the current gameplay requirement but needs a real extension.

## Remove it

If placeholder assumptions actively force new production code into an incorrect design.

---

# When Starting Fresh May Be Better

A fresh start can be justified when the current codebase has reached the point where:

- placeholder systems are deeply interconnected;
- removing one fake assumption breaks many unrelated classes;
- new code must conform to incorrect old abstractions;
- every real feature requires a refactor before implementation;
- the project spends more time preserving prototype architecture than implementing gameplay;
- the team now understands the actual game substantially better than when the architecture was created.

In that situation, preserving the old architecture may cost more than rebuilding the small real foundation.

A fresh start should **not** mean throwing away everything.

Reusable assets may include:

- textures;
- icons;
- 3D models;
- materials;
- sounds;
- UI art;
- design discoveries;
- gameplay rules that were proven useful;
- algorithms or small pieces of code that still match the real game.

The new codebase should begin extremely small.

---

# Fresh-Start Example

## Step 1 — Buildings exist

```text
BuildingData
    ID
```

Create:

```text
Building 1
Building 2
Building 3
Building 4
Building 5
Building 6
```

They do nothing.

That is enough.

---

## Step 2 — Citizens exist

```text
CitizenData
    ID
```

Create five citizens.

They do nothing.

That is enough.

---

## Step 3 — Next Gameplay Requirement

Ask:

> What do we want the citizen to do next?

If the answer is:

> Walk to Building 1.

Add only what is required to accomplish that.

---

## Step 4 — Construction Appears

When the game actually needs construction, add the minimum real construction state.

Example:

```text
BuildingData
    ID
    State
```

Possible current states:

```text
Unbuilt
Built
```

Only add more states when real gameplay requires them.

---

# The Final Vision Still Matters

Incremental programming does not mean directionless programming.

The final vision prevents local decisions from contradicting the intended game.

Example:

If the final vision says resources are physical:

Do not implement construction using magical global resource subtraction.

If the final vision says citizens physically haul resources:

Do not design a permanent construction system that teleports materials.

If the final vision says homes matter:

Do not permanently model sleep as "stand anywhere for 8 hours."

The vision constrains the **kind of solution**.

The current gameplay requirement determines **when that solution is implemented**.

---

# Daily Development Question

At the beginning of a programming session, ask:

> **What is the next visible thing I want the player or simulation to be able to do?**

Then ask:

> **What prevents that from working correctly right now?**

Then:

> **What does that missing thing itself require?**

Continue until reaching something that can be implemented correctly using systems that already exist.

That becomes today's work.

---

# Definition of Done

A piece of work is done when:

- the current gameplay requirement works;
- the required data is real;
- the code does not rely on knowingly fake assumptions;
- the feature can be exercised in the running game;
- downstream systems are not implemented prematurely;
- future systems remain free to take the form that later gameplay demands.

---

# Project Rule

> **Never write downstream gameplay against a dependency we already know is fake.**

If the dependency does not exist:

**stop, go backward, and build it.**

If the dependency exists and is correct for the current game:

**use it and move forward.**

If the vision says a future system will eventually change the rule:

**do not implement that future system until gameplay reaches it.**

---

# Short Version

```text
Final Vision
    ↓
Choose one concrete gameplay goal
    ↓
What does it require?
    ↓
Does that requirement really exist?
    ├── Yes → continue forward
    └── No  → stop and implement it
                 ↓
          What does THAT require?
                 ↓
            repeat backward
                 ↓
       reach deepest real dependency
                 ↓
              implement
                 ↓
                test
                 ↓
           climb forward again
```

Build the game from **real dependencies**, not predicted systems.
