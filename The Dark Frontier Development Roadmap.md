# The Dark Frontier Development Roadmap

_Last updated: July 11, 2026_

## Status Key

- ✅ Implemented and tested
- 🟡 Foundation or working prototype
- ☐ Not started
- 🐞 Known issue

---

## 🏛 Core Framework

- ✅ Building Data Assets
- ✅ Building Catalog Data Asset
- ✅ Resource Catalog Data Asset
- ✅ Building Placement
- ✅ Road Placement
- ✅ Settlement Subsystem
- ✅ City Data Objects
- ✅ Active City support
- ✅ Runtime building instance data
- ✅ Runtime road instance data
- ✅ Day / Night Cycle
- ✅ Gameplay Tag building categories
- ✅ Learned building and road lists
- ✅ Enhanced Input framework
- ✅ RTS camera pan, zoom, and yaw rotation
- ✅ Generic entity selection framework
- ✅ Selectable Entity interface
- ☐ Save / Load
- ☐ World Generation
- ☐ Multiple Settlements
- ☐ AI Settlements

---

## 🏘 Settlement Progression

### Starting Settlement

- ✅ Expedition Wagon building definition
- ✅ Expedition Wagon runtime spawn
- ✅ Starting supplies
- ✅ Starting citizens
- ✅ Citizen character spawning
- ✅ Citizen AI controller spawning
- ✅ Spawn citizens around the Expedition Wagon
- ✅ Wagon fallback idle location
- 🟡 Starting families
- 🟡 Starting workers
- ☐ Player-selected spawn location

### Town Hall

- ✅ Town Hall building definition
- ✅ Town Hall placement and construction
- ✅ Town Hall higher-priority idle location
- 🟡 Settlement center behavior
- ☐ Tier 1
- ☐ Tier 2
- ☐ Tier 3
- ☐ Tier 4
- ☐ Upgrade requirements

---

## 🏠 Buildings

### Building Framework

- ✅ Single reusable `ABuildingBase` actor
- ✅ Placement, Construction, and Finished states
- ✅ Separate placement, construction, and permanent meshes
- ✅ Footprint box driven by building data
- ✅ Runtime GUID identity
- ✅ Health and construction progress
- ✅ Construction cost data
- ✅ Construction worker capacity
- ✅ Citizen-driven construction progress
- ✅ Multiple builders contribute to construction
- ✅ Builder reservations and release
- ✅ Multiple simultaneous construction sites
- ✅ Building unlock lists
- ✅ Unique-per-city rule data
- ✅ Static building definitions resolved through the building catalog
- ✅ Building work-slot definitions
- ✅ Runtime assigned-worker groups
- ✅ Safe citizen-to-building assignment functions
- ✅ Idle/social location capacity, priority, and radius
- ✅ Construction sites and finished buildings selectable
- ☐ Building upgrade framework
- ☐ Demolition
- ☐ Repair
- ☐ Building maintenance

### Housing

- ✅ Small House prototype
- ☐ Medium House
- ☐ Large House
- ☐ Noble Housing

### Civic

- ✅ Expedition Wagon prototype
- ✅ Town Hall prototype

### Production

- ✅ Lumber Mill prototype
- ☐ Quarry
- ☐ Mine
- ☐ Blacksmith
- ☐ Sawmill
- ☐ Carpenter
- ☐ Smelter

### Food

- ☐ Farm
- ☐ Hunter
- ☐ Fishing Dock
- ☐ Orchard
- ☐ Bakery

### Storage

- ☐ Warehouse
- ☐ Barn
- ☐ Stockpile

### Military

- ☐ Barracks
- ☐ Guard Tower
- ☐ Walls
- ☐ Gatehouse

### Magic

- ☐ Mage Tower
- ☐ Rune Circle
- ☐ Arcane Library

### Dragons

- ☐ Dragon Roost
- ☐ Hatchery
- ☐ Dragon Stable

---

## 🌲 Resources

### Resource Framework

- ✅ Gameplay Tag resource identities
- ✅ Resource amount structure
- ✅ City resource array
- ✅ Add, remove, and query resource functions
- ✅ City Resource Manager foundation
- ✅ Resource catalog
- ✅ Starting building resources
- ✅ Resource top-bar display
- 🟡 Construction resource costs
- ☐ Resource gathering
- ☐ Resource production
- ☐ Resource consumption
- ☐ Resource reservations

### Basic

- 🟡 Wood tracking
- 🟡 Stone tracking
- 🟡 Food tracking
- 🟡 Gold tracking

### Advanced

- ☐ Iron
- ☐ Coal
- ☐ Steel
- ☐ Cloth
- ☐ Leather

### Rare

- ☐ Mana Crystal
- ☐ Dragon Scale
- ☐ Ancient Relics

---

## 📦 Storage System

- ✅ Storage container data structure
- ✅ Building storage capability flag
- ✅ Storage capacity data
- ✅ Allowed resource tag data
- ✅ Allowed resource category data
- 🟡 Per-building runtime storage data
- ☐ Warehouse behavior
- ☐ Barn behavior
- ☐ Stockpile behavior
- ☐ Overflow handling
- ☐ Resource priorities
- ☐ Supply chains
- ☐ Hauler delivery tasks

---

## 👥 Population

### Citizen Framework

- ✅ Citizen Data Object
- ✅ Persistent citizen GUID
- ✅ Citizen name and age
- ✅ Life-stage data
- ✅ Citizen character actor
- ✅ Citizen data linked to spawned character
- ✅ Citizen count shown in the HUD
- ✅ Home and workplace building links
- ✅ Current assignment data
- ✅ Activity state data
- ✅ Work schedule block data
- ✅ Trait array foundation
- ✅ Carry capacity and work-speed stats
- ✅ Citizen selection
- 🟡 Adults
- ☐ Children simulation
- ☐ Elderly simulation
- ☐ Families and relationships
- ☐ Births and deaths
- ☐ Immigration

### Work Roles

- ✅ Work-role enum and citizen role state
- ✅ None / unassigned worker
- ✅ Builder framework
- ✅ Hauler framework data
- ✅ Lumberjack framework data
- ✅ Farmer framework data
- ✅ Miner framework data
- ✅ Guard framework data
- ✅ Mage framework data
- ✅ Dragon Handler framework data
- ✅ Player-assigned building work-slot backend
- ☐ Player worker-assignment UI
- ☐ Lumberjack behavior
- ☐ Farmer behavior
- ☐ Miner behavior
- ☐ Guard behavior
- ☐ Mage behavior
- ☐ Dragon Handler behavior

### Needs

- ✅ Hunger data
- ✅ Rest data
- ✅ Happiness data
- ☐ Hunger simulation
- ☐ Rest simulation
- ☐ Housing need
- ☐ Warmth
- ☐ Safety
- ☐ Entertainment need
- ☐ Religion

### Happiness

- ☐ Housing quality
- ☐ Food variety
- ☐ Taxes
- ☐ Roads
- ☐ Crime
- ☐ Health

---

## 🚶 Citizen AI

### AI Foundation

- ✅ Citizen AI Controller
- ✅ Blackboard
- ✅ Behavior Tree
- ✅ AI possession of spawned citizens
- ✅ NavMesh movement
- ✅ Blackboard synchronization from citizen data
- ✅ Assignment request behavior-tree task
- ✅ Move-to-assignment behavior

### Idle and Social Behavior

- ✅ Priority-based idle locations
- ✅ Idle location capacity
- ✅ Fallback to Expedition Wagon
- ✅ Town Hall preferred over Wagon
- ✅ Second-best location when a higher-priority location is full
- ✅ Idle-slot reservation and release
- ✅ Citizens move back to idle after construction
- ☐ Avoid unnecessary reassignment when already at the best location
- ☐ Entertainment duration and activity variety

### Construction Behavior

- ✅ Citizens detect construction tasks
- ✅ Construction tasks take priority over idle tasks
- ✅ Citizens move to construction sites
- ✅ Citizens apply construction work over time
- ✅ Building finishes only through citizen work
- ✅ Citizens release completed construction assignments
- ✅ Construction worker capacities
- ✅ Construction reservation counts
- ✅ Multiple buildings and builder quantities tested

### Future AI

- 🟡 Job selection framework
- 🟡 Daily schedule data: Work / Free Time / Sleep
- ☐ Daily schedule behavior
- ☐ Go to workplace
- ☐ Work production cycle
- ☐ Resource delivery
- ☐ Hauling
- ☐ Go home
- ☐ Sleeping
- ☐ Eating
- ☐ Entertainment activities

### Known AI / Navigation Issues

- 🐞 Citizens can walk through placeholder buildings because buildings do not yet carve or block the NavMesh
- ☐ Add finished-building navigation obstacles or Nav Modifier components

---

## 🎮 Input, Camera, and Selection

### Enhanced Input

- ✅ `UTDFInputConfig` Data Asset
- ✅ `IMC_Gameplay` mapping context
- ✅ Input Actions stored in the controller configuration
- ✅ Controller owns all gameplay input decisions
- ✅ WASD and arrow-key camera movement
- ✅ Mouse-wheel zoom
- ✅ Middle-mouse yaw rotation
- 🟡 Camera pitch rotation
- ✅ Left-click selection
- ✅ Right-click clear selection foundation
- 🟡 Placement rotation action
- 🟡 Focus-selection action
- 🟡 Pause action
- ☐ Pause/options menu
- ☐ Simulation pause and speed controls
- ☐ Input rebinding UI

### Entity Selection System

- ✅ Generic `SelectedActor`
- ✅ `ISelectableEntity` interface
- ✅ Buildings selectable
- ✅ Citizens selectable
- ✅ Selection trace collision
- ✅ Placement ghosts ignore selection traces
- ✅ Construction and finished buildings accept selection traces
- ✅ Typed getters for selected buildings and citizens
- ✅ Custom Depth selection state foundation
- ☐ Visible outline post-process material
- ☐ Selection information panel
- ☐ Selection ring or additional feedback
- ☐ Roads selectable
- ☐ Trees and resource nodes selectable
- ☐ Animals selectable
- ☐ Enemies, military units, wizards, and dragons selectable

---

## 🖥 User Interface

- ✅ Main HUD
- ✅ Top resource bar
- ✅ Population display
- ✅ City name display
- ✅ Bottom building-category bar
- ✅ Dynamic sub-button menu
- ✅ Building buttons generated from learned building data
- ✅ Road button support
- ✅ Exit button
- 🟡 Empty selection-information area available in the HUD
- ☐ Building selection panel
- ☐ Citizen selection panel
- ☐ Worker assignment panel
- ☐ Construction progress display
- ☐ Storage display
- ☐ Needs and happiness display
- ☐ Pause/options menu

---

## 🌳 World

### Terrain

- ☐ Forests
- ☐ Rivers
- ☐ Mountains
- ☐ Lakes
- ☐ Swamps

### World Resources

- ☐ Trees
- ☐ Stone Deposits
- ☐ Iron Veins
- ☐ Wildlife

---

## 🛣 Roads

### Implemented

- ✅ Placement
- ✅ Validation
- ✅ Auto Connections
- ✅ Road data assets
- ✅ Road catalog / learned roads support
- ✅ Runtime road instance data

### Future

- ☐ Road Upgrades
- ☐ Bridges
- ☐ Dirt Roads
- ☐ Stone Roads
- ☐ Road Bonuses
- ☐ Road Maintenance

---

## ⚔ Military

- ☐ Weapons
- ☐ Armor
- ☐ Patrols
- ☐ Raids
- ☐ Bandits
- ☐ Siege
- ☐ Dragons

---

## 📖 Knowledge System

This is one of the systems that could define **The Dark Frontier**.

### Civilization — Growth Through Settlement

Unlocked through the Town Hall and settlement advancement:

```text
Town Hall
    ↓
Village Buildings
    ↓
Town Buildings
    ↓
City Buildings
```

These are the civic necessities that allow the settlement to grow.

### Mastery — Improvement Through Action

Unlocked by doing:

- Cut 1,000 trees → Sharpened Axes
- Mine 500 stone → Improved Masonry
- Harvest 2,000 wheat → Better Farming
- Forge 1,000 iron bars → Advanced Smithing

The civilization improves through accumulated experience.

### Discovery — Knowledge Through Exploration

Unlocked by exploring the world:

- Ancient Library → Arcane Studies
- Dragon Nest → Dragon Handling
- Forgotten Forge → Dwarven Smithing
- Ancient Observatory → Astronomy
- Lost Shrine → Divine Blessings

Some discoveries may never appear on every map, making each world unique.

### Institutions — Multipliers and Gateways

Buildings do not passively create generic research points. Instead, institutions enhance knowledge already earned:

- University — Speeds up mastery and analysis
- Arcane Library — Unlocks advanced magical discoveries
- Guild Hall — Improves profession specialization
- War College — Advances military doctrines
- Royal Archives — Preserves and accelerates civilization-wide knowledge

Institutions are multipliers and gateways, not passive science generators.

### Implementation Status

- ✅ Learned building and road framework provides an early unlock foundation
- ☐ Civilization growth tree
- ☐ Mastery tracking
- ☐ Discovery sites
- ☐ Institution effects
- ☐ Knowledge UI

---

## 🐉 Dragons

- ☐ Discover Nest
- ☐ Study Eggs
- ☐ Dragon Handler
- ☐ Dragon Roost
- ☐ Dragon Breeding
- ☐ Dragon Riders

---

## 🔮 Magic

- ☐ Discover Ancient Magic
- ☐ Apprentice Mages
- ☐ Mage Guild
- ☐ Ritual Magic
- ☐ Elemental Magic
- ☐ Necromancy
- ☐ High Magic

---

## 🌍 Diplomacy

- ☐ AI Kingdoms
- ☐ Trade
- ☐ Alliances
- ☐ Wars
- ☐ Espionage

---

## 🎯 Endgame

- ☐ Kingdom
- ☐ Empire
- ☐ World Events
- ☐ Dragon Wars
- ☐ Ancient Evil
- ☐ Sandbox Endless Mode

---

## Core Design Philosophy

Progress should come from three different sources:

- **Growth** — Expanding the settlement through the Town Hall and infrastructure
- **Mastery** — Improving by doing and gaining experience
- **Discovery** — Exploring the world and uncovering forgotten knowledge

This gives players multiple paths to progress. Two settlements of the same size may have completely different capabilities: one may become expert foresters, while another uncovers ancient magic or learns to work with dragons.

That variety should give **The Dark Frontier** its own identity instead of making it another city builder with a linear technology tree.

---

## Recommended Near-Term Milestones

1. Complete visible selection feedback with a Custom Depth outline.
2. Add a reusable selection information panel for buildings and citizens.
3. Connect controller input to placement confirm, cancel, and rotation.
4. Add the player-facing worker assignment UI for building work slots.
5. Implement the first productive workplace loop with the Lumber Mill.
6. Add resource gathering and hauling tasks.
7. Add work, free-time, and sleep schedule behavior.
8. Replace colored cubes with simple recognizable prototype models.
