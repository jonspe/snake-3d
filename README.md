# snake-3d
Snake game in 3D, made in C++ and OpenGL with QtCreator for university Programming 2 course.

- The game was made using the OpenGL ES graphics programming library provided by QtCreator.
- The game features shaders written in GLSL, such as toon shaders for the food items and snake, and customized vertex/fragment shaders for forming the snake shape and texture.
- The game features collisions with both the map objects and the snake itself.
- Blender was used as the 3D modeling software for modeling the map and food items.
- A custom .obj-file reader was written in `resourcemanager.cpp` to read the 3D models exported from Blender. The .obj-reader uses regular expressions to detect different data features of the .obj-file. There is one parser for normal 3D models, and another for 2D polygons for collision detection in game.

[snake2_dBc91QaqSX.webm](https://user-images.githubusercontent.com/45041362/227081888-1b916d0f-7cae-4a54-bf0f-1cb10c069f6b.webm)
