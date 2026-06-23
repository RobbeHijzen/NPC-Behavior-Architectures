# Comparative Research Project for Pedestrian NPC Behavior Architectures
 
Code accompanying the master's thesis **A Comparative Performance Analysis of
NPC Behavior Architectures for CrowdScale Pedestrians in Open-World Games** - Robbe Hijzen

## What this is
 
This repository contains **only the files added or changed** relative to Epic Games' *City Sample* project — it is **not** a complete, openable Unreal project. The folder layout mirrors the City Sample project so that files land in the right place when copied over (step 3). Additionally, this repository contains one .utrace file for each configuration as to provide the raw data of the experiment.
 
## Requirements
 
- Unreal Engine **5.7.[x]**
- The *City Sample* project, UE 5.7-compatible release (free, from Fab)
- Visual Studio with the *Game development with C++* workload
## Setup
 
1. **Install UE 5.7** via the Epic Games Launcher.
2. **Get the City Sample.** In the Launcher: *Unreal Engine → Library → Fab Library* (samples appear only once a compatible engine version is installed). Open *City Sample*, click **Create Project**, and choose engine version 5.7.
3. **Copy this repo's folders** (Config, Content, Source) into the **root of the City Sample project** (the folder containing the `.uproject`), preserving the folder structure and **overwriting** when prompted. 
4. right-click the `.uproject` → *Generate Visual Studio project files*, then build (or accept the editor's prompt to rebuild).
5. **Open the project** in UE 5.7 and let shaders finish compiling (slow on first launch).
## Running it
 
Open the level `Content/map/Small_City_LVL.umap` and press **Play**.
 
