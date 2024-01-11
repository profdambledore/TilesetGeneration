# TilesetGeneration
 A tileset generation system in Unreal Engine 4/5

 <p align="center">
  <img src="https://github.com/profdambledore/TilesetGeneration/blob/main/Images/Display.png" />
</p>

 In this project, I have created a tileset-based generation system to allow worlds to be generated via separate 'islands' with doorways connecting each one in order.  Using a tree data structure to store the world elements, users can generate, clear and regenerate worlds at a call of a function, while a seed system allows users to create the same worlds multiple times via an integer.

## Project Document
 
 [Link](https://github.com/profdambledore/TilesetGeneration/blob/main/Document/Tileset_Generation_System.pdf)

 ## Latest Update
<table><tr><td valign="center" width="100%">
 
### v0.14 - Collision Update and Galleon Tileset
-- TileManager --

Changed the tileset found by FObjectFinder to the new Galleon Tileset
Updated Overlap collision
- Removed unneeded variables (TraceResult)
- Removed ObjectTypeQuery1 from ObjectTypes
- Replaced ActorClassFilter with NULL (filters no classes)
- Replaced TraceHit.Num with HitTiles.Num
-- As TraceResult was never being used, the overlap never got queried

Updated Tile Rerolls
- Originally used a while look, but this caused the project to hang
- Now uses a for loop, checking if the tile is still invalid each time a tile is created

-- Galleon Tileset --

Created 8 new tiles to show the project off
Added a new data table for this tileset
Merged meshes together to create new tile static meshes (only one mesh per tile now)
Used implemented systems to setup the tiles (TileDoorPosition and CollisionTestOrigin/Bounds)
</td></tr></tr></table> 

## Overview Videos

<table><tr><td valign="center" width="100%">
 
[![IMAGE ALT TEXT](http://img.youtube.com/vi/XMy0BoMvCBQ/0.jpg)](https://youtu.be/XMy0BoMvCBQ "Tileset Generator Overview") 

[![IMAGE ALT TEXT](http://img.youtube.com/vi/gtHHQCKSiKg/0.jpg)](https://youtu.be/gtHHQCKSiKg "Example of Tileset Generator") 

</td></tr></tr></table> 

 ## Assets Used:
- Polygon Sci-Fi Space by SyntyStudios 

## Programs Used:
- Unreal Engine 5.2 - Game Engine.
- Visual Studio 2022 - Code Editing.
- Overleaf with LaTeX - Document Creation
- GitHub Desktop - Git Control. 
