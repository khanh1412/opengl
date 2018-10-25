g++ -std=c++11 -c -fPIC -o objects\Renderer.o sources\Renderer.cc .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -c -fPIC -o objects\VertexArray.o sources\VertexArray.cc .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -c -fPIC -o objects\VertexBuffer.o sources\VertexBuffer.cc .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -c -fPIC -o objects\IndexBuffer.o sources\IndexBuffer.cc .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -c -fPIC -o objects\Shader.o sources\Shader.cc .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -shared -o libRenderer.dll objects\Renderer.o objects\VertexArray.o objects\VertexBuffer.o objects\IndexBuffer.o objects\Shader.o .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -o run.exe main.cc .\libRenderer.dll .\glew32.dll .\glfw3.dll -I.\include -lopengl32
