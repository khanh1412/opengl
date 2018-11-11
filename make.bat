mkdir objects
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\Renderer.o sources\Renderer.cc 		
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\VertexArray.o sources\VertexArray.cc 	
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\VertexBuffer.o sources\VertexBuffer.cc 	
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\IndexBuffer.o sources\IndexBuffer.cc 	
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\Shader.o sources\Shader.cc 			
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\VertexBufferLayout.o sources\VertexBufferLayout.cc
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\Texture.o sources\Texture.cc
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\stb_image.o sources\vendor\stb_image.cc
g++ -std=c++11 -I.\include -I.\include\vendor -shared -o libRenderer.dll objects\Renderer.o objects\VertexArray.o objects\VertexBuffer.o objects\IndexBuffer.o objects\Shader.o objects\VertexBufferLayout.o objects\Texture.o objects\stb_image.o .\glew32.dll .\glfw3.dll -I.\include -lopengl32
g++ -std=c++11 -I.\include -I.\include\vendor -o run.exe main.cc .\libRenderer.dll .\glew32.dll .\glfw3.dll -lopengl32

del objects\*.o
rmdir objects
