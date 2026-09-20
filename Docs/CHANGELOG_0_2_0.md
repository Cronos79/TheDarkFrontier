# The Dark Frontier

## v0.2.0-alpha

**Release type:** Internal Alpha Update  
**Status:** Ready for Internal Steam Test

### Added

- Stonecutter building
  - Added the Stonecutter to the early production chain.
  - Stone processing is now part of settlement progression.

- Expanded progression
  - Progression now continues beyond the original Town Hall milestone.
  - Added additional building unlock progression.
  - Added citizen population rewards.
  - Completing the Town Hall progression awards 3 additional citizens.
  - Settlements begin with 5 citizens and can grow to 8 through progression.

- Building cancellation and demolition
  - Added cancel/remove controls to the building details UI.
  - Construction sites can now be cancelled.
  - Finished buildings can now be demolished.

- Salvage system
  - Cancelling an unfinished building creates salvage from resources actually delivered to the construction site.
  - Demolishing a completed building salvages 100% of its current inventory.
  - Completed buildings also return 50% of their original construction-resource cost.
  - Salvaged resources appear in physical salvage piles in the world.
  - Citizens automatically haul salvage back to valid storage.
  - Empty salvage piles automatically remove themselves.

- Town Hall storage
  - The Town Hall now functions as permanent general-purpose settlement storage.
  - The Town Hall can accept all configured resource types.

- Wagon retirement
  - The starting wagon is retired when the Town Hall is completed.
  - Remaining wagon inventory is converted into a salvage pile.
  - Citizens haul the recovered wagon resources into settlement storage.

- Camera rotation
  - Added middle-mouse drag camera rotation.
  - Camera-relative WASD movement follows the current camera orientation.
  - Camera rotation is preserved while zooming.

- Persistent world foliage state
  - Removed trees are tracked by save data.
  - Harvested trees remain removed after saving and loading.

### Improved

- Expanded the playable early-game flow beyond the original Town Hall milestone.
- Improved the building removal lifecycle so jobs, workplaces, housing, inventory, and salvage are handled cleanly.
- Added salvage hauling priority ahead of ordinary hauling work.
- The starting wagon remains excluded from normal storage hauling and only accepts salvage as a special-case fallback before permanent storage is available.
- Save/load restoration preserves building identity, state, transform, construction progress, inventories, citizens, settlement identity, and settlement name.
- Loaded settlements reuse saved citizens instead of spawning a duplicate starting population.
- Resource and population summary systems refresh correctly as buildings and citizens change.
- Schedule UI now refreshes automatically when new citizens are added.
- Schedule rows remain scrollable as settlement population grows.
- Building and environment art received a substantial alpha art pass, including updated quarry-related assets and props.
- Added or updated several build-menu/category icons, including roads, dirt road, storage, and production/building icons.

### Fixed

- Fixed removed trees reappearing after loading a save.
- Fixed duplicate starting citizens after loading an existing settlement.
- Fixed building restoration incorrectly triggering completion progression.
- Fixed new progression-awarded citizens not appearing in the Schedule window.
- Fixed cancelled construction resources disappearing instead of being recoverable.
- Fixed completed-building inventory disappearing when the building was demolished.
- Fixed empty salvage piles remaining in the world after all resources were collected.
- Fixed early-game salvage having no valid destination before permanent storage existed by allowing salvage-only return to the starting wagon.

### Internal Testing Completed

- New settlement creation verified with 5 starting citizens.
- Town Hall progression verified to increase population from 5 to 8.
- Newly added citizens verified to appear in the Schedule window.
- Construction cancellation verified.
- Partial construction-resource salvage verified.
- Completed-building demolition verified.
- Completed-building inventory salvage verified.
- 50% completed-building construction-cost salvage verified.
- Salvage hauling verified.
- Empty salvage-pile cleanup verified.
- Town Hall general storage verified.
- Starting wagon retirement verified.
- Wagon inventory conversion to salvage verified.
- Salvaged wagon resources verified to move into Town Hall storage.
- Camera rotation tested in-game.
- Save/load restoration tested.
- Persistent removed foliage tested.

### Known Limitations

- Early-alpha balance is temporary.
- Some building meshes and construction meshes still use placeholder or work-in-progress art.
- UI is still under development.
- Audio and presentation polish are incomplete.
- Progression beyond the currently implemented buildings remains incomplete.
- Additional world-state persistence is still under development.
- Additional packaged-build and Steam-distributed testing is required.
