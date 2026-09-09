# The Dark Frontier

## v0.1.1-alpha

**Release type:** Internal Alpha Patch  
**Status:** In Development

### Added

- Stonecutter building
  - Added the Stonecutter as part of the expanding settlement production chain.
  - Stone processing is now part of early settlement progression.

- Expanded progression system
  - Added new progression beyond the original Town Hall milestone.
  - Added additional building unlock progression.
  - Added citizen population rewards to the progression system.
  - Progression rewards can now add new citizens to the settlement.
  - Completing the Town Hall progression rewards the settlement with 3 new citizens.
  - Settlements continue to begin with 5 citizens and can grow to 8 through the Town Hall progression reward.

- Persistent world foliage state
  - Removed trees are now tracked in settlement save data.
  - Harvested trees remain removed after saving and loading.

### Improved

- Early-game progression expanded beyond the original v0.1.0 Town Hall milestone.
- Settlement development now includes additional production and progression rewards.
- Save/load system expanded beyond the original v0.1.0 foundation.
- Building restoration now preserves saved building identity and state.
- Saved buildings restore to their saved transforms.
- Construction progress is restored correctly when loading.
- Loaded settlements reuse their saved citizens instead of creating a second set of starting citizens.
- Citizen identities are restored from save data.
- Settlement identity and name are restored from save data.

### Fixed

- Fixed removed trees reappearing after loading a saved game.
- Fixed potential duplicate starting citizens when loading an existing settlement.
- Building restoration no longer incorrectly triggers construction-completion progression while reconstructing saved buildings.

### Testing

- New settlement creation verified with the original 5 starting citizens.
- Town Hall progression completion verified to award 3 additional citizens.
- Settlement population verified to increase from 5 to 8 through progression.
- Stonecutter progression tested in-game.
- Progression beyond the original Town Hall milestone tested.
- Removed a tree, saved the settlement, reloaded, and verified the tree remained removed.
- Save/load verified with existing settlement data.
- Building restoration verified.
- Citizen restoration verified.

### Known Limitations

- Additional world-state persistence is still under development.
- Progression beyond the currently implemented buildings remains incomplete.
- Early-alpha balance is temporary.
- Building selection is still limited.
- Some building icons are missing.
- UI is still under development.
- Audio and presentation polish are incomplete.
- Additional gameplay tuning and packaged-build testing are still required.