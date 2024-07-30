# Mocha - An OpenGL rendering engine
It's planned to support Deferred Rendering as well as PBR shaders.

 ---

 ## Structure: 

The software is separated into two projects: Mocha and App. App builds into App.exe which includes Mocha.dll as a library. This ensures that Mocha.dll can be used as an external library. 

```
Repository
|
|-- Dependencies            # Dependencies are included in the repository
|   |-- glew-2.1.0
|   |-- glfw-3.4.bin.WIN64
|   |-- glm-0.9.9.8
|   |-- imgui
|   `-- stb
|
|-- Binaries                # This folder is only shown/generated when building
|
|-- Application             # Contains all the interesting stuff
|   |-- App                 # Builds as an .exe using Mocha.dll, this is where you run the program
|   |   `-- Source
|   `-- Mocha               # Mocha contains the implementation that is built into a .dll
|       `-- Source
|           ` Mocha         # Mocha.h exposes the 'api' of Mocha.dll and is included in App.exe
|
`-- git_img                 # Web preview stuff for github
```
 ---

## Building:

This project should compile and link properly on Microsoft Visual Studio 2022 (17) with any compiler supporting C++ 20 or higher on Windows x64.
The dependencies are included in the repository and do not require to be downloaded and linked manually.
OpenGL is required. It is assumed that OpenGL is pre-installed on the system.

 ---

 ## Dependencies:
 - GLEW 2.1.0
 - GLFW 3.4
 - imgui
 - stb_image
 - glm 0.9.9.8

---
