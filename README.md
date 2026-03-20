# Mocha

![Mocha Logo Banner](https://github.com/MaxineCodes/Mocha/blob/main/res/graphics/mocha_mock_banner.jpg)

---

## About Mocha

Mocha is a simple cross-platform 3D OpenGL core-profile rendering engine to render 3D objects in real-time supporting physically based rendering algorithms and scene loading.
If you're familiar with 3D viewing applications, a main point of inspiration for this project is Sketchfab and Marmoset Viewer. Performance is not a priority, but being GPU based and only handling small scenes, this should not be a major issue.

---

![Viewport Screenshot](https://github.com/MaxineCodes/Mocha/blob/main/res/graphics/screenshots/viewport-20-03-26.png)

["cute_fox.obj"](https://skfb.ly/6SxNF) by eexy.

---

Features planned:

- [ ] Physically based materials and rendering. 
- [ ] Scene and object loading. .OBJ and .USD formats planned.


- [ ] GUI using ImGui.
  - [ ] Material editor.
  - [ ] Camera controls.
  - [ ] Lighting adjustments.
  

- [ ] Skybox HDRI
- [ ] Post processing ???

---

## Building
CMake should install all dependencies to the '/dependencies' folder.
Your system should support OpenGL 3.3. It has been tested to build on Windows 11 using MSVS compiler. 

Common problems: 
- Python 3 command not executing.
- "No module found named glad"              

Make sure Python 3 is in your PATH and glad is installed.

Running `pip install glad` should do the trick.

---

## Credits

- ["cute_fox.obj"](https://skfb.ly/6SxNF) by eexy is licensed under [Creative Commons Attribution](http://creativecommons.org/licenses/by/4.0/).    
  Also available on Instagram: [@vharmeleon](https://www.instagram.com/vharmeleon/).

---

## Sources

- C++ Coding Standards: https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines
- PBR Book: https://www.pbr-book.org/
- Google Filament book and repository: https://github.com/google/filament
- Learn OpenGL website: https://learnopengl.com/
- Shaders for game programming and artists book: https://archive.org/details/shadersforgamepr0000stla/mode/2up
- SIGGRAPH 2025 Course: Physically Based Shading in Theory and Practice : https://blog.selfshadow.com/publications/s2025-shading-course/
- Wavefront OBJ file: https://en.wikipedia.org/wiki/Wavefront_.obj_file
