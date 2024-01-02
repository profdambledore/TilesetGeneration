# TilesetGeneration
 A tileset generation system in Unreal Engine 4/5

 In this project, I have created a tileset-based generation system to allow worlds to be generated via separate 'islands' with doorways connecting each one in order.  Using a tree data structure to store the world elements, users can generate, clear and regenerate worlds at a call of a function, while a seed system allows users to create the same worlds multiple times via an integer.

## Project Document
 
 [Link](https://github.com/profdambledore/TilesetGeneration/blob/main/Document/Tileset_Generation_System.pdf)

 ## Latest Update
<table><tr><td valign="center" width="100%">
 
### v0.13 - Collision and Seed Fix
-- TileManager --

Updated GenerateNode to return an int
- This was not actually used, so could be reverted
Updated GetTile functions to return a FTileData struct
- Could be reverted also, as the property added to the struct is stored else ware now
When spawning a new child node, after being rotated and moved into position a collision overlap test is conducted. If something other then the child tile or the parent is overlapped by this collision box, the tile is deleted and rerolled
- Updated FTreeSettings to now hold NodeRerolls, or how many times a tile can fail before the doorway it is to be connected too is not tried again.

-- Tile --

GetMatchingDoorPosition now takes in the SeedStream, so door positions are now affected by the seed
Now has two new FVector properties for the location and size of the overlap box.

-- TileData --

Added FVector Size property
- Was originally going to be stored here, but was moved to the Tile class for simplicity.

-- Tile Classes --

Updated all classes to use the new Overlap box variables
</td></tr></tr></table> 

 ## Assets Used:
- Polygon Sci-Fi Space by SyntyStudios 

## Programs Used:
- Unreal Engine 4.26 - Game Engine.
- Visual Studio 2019 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 
