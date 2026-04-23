# Graphics Programming mit OpenGL

## Programmable Renderpipeline
```mermaid
	flowchart LR
	IA("Vertex Specification <br> (Input Assembler)") --> VS(Vertex Shader) --> RS(Rasterization) --> FS("Fragment Shader <br> (Pixel Shader)") --> OM(Output Merger)
```

## Dependencies
```mermaid
    flowchart TD

    Viewer[3D-Viewer] --> Engine
    Window --> GLFW
    Input[User Input] --> GLFW

    Viewer --> OpenGL --> glad

    subgraph Engine
        Input
        Window
    end
```

## Links
### package manager:
https://vcpkg.io

### Dependencies
https://www.glfw.org/ </br>
https://glad.dav1d.de/ / https://vcpkg.io/en/package/glad  
### OpenGL Dokumentation:
https://docs.gl/
### C++
[C++ reference](https://en.cppreference.com/w/) </br>
[C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines.html) </br>
[Compiler Explorer](https://godbolt.org/)