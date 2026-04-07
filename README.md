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