g++ -std=c++11 -I.\include -c -fPIC -o objects\Renderer.o sources\Renderer.cc 		
g++ -std=c++11 -I.\include -c -fPIC -o objects\VertexArray.o sources\VertexArray.cc 	
g++ -std=c++11 -I.\include -c -fPIC -o objects\VertexBuffer.o sources\VertexBuffer.cc 	
g++ -std=c++11 -I.\include -c -fPIC -o objects\IndexBuffer.o sources\IndexBuffer.cc 	
g++ -std=c++11 -I.\include -c -fPIC -o objects\Shader.o sources\Shader.cc 			
g++ -std=c++11 -I.\include -c -fPIC -o objects\VertexBufferLayout.o sources\VertexBufferLayout.cc
g++ -std=c++11 -I.\include -shared -o libRenderer.dll objects\Renderer.o objects\VertexArray.o objects\VertexBuffer.o objects\IndexBuffer.o objects\Shader.o objects\VertexBufferLayout.o .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -I.\include -o run.exe main.cc .\libRenderer.dll .\glew32.dll .\glfw3.dll -lopengl32
