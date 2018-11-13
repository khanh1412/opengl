mkdir objects
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\Renderer.o sources\Renderer.cc 		
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\VertexArray.o sources\VertexArray.cc 	
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\VertexBuffer.o sources\VertexBuffer.cc 	
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\IndexBuffer.o sources\IndexBuffer.cc 	
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\Shader.o sources\Shader.cc 			
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\VertexBufferLayout.o sources\VertexBufferLayout.cc
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\Texture.o sources\Texture.cc
g++ -std=c++11 -I.\include -I.\include\vendor -c -fPIC -o objects\stb_image.o sources\vendor\stb_image.cc
g++ -std=c++11 -I.\include -I.\include\vendor -shared -o libRenderer.dll objects\*.o

del objects\*.o
rmdir objects
