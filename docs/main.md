# getting started with glfw
- include necessary headers (glfw3 + glad)
- init glfw
- create window after giving window hints
- make glfw context the new window
- init glad
- check for errors for previous code

# create a shape
- generate valid ids
- bind to this ids using proper targets
- load the data

# create shader
- create a shader id
- load the shader source code
- compile the shader for both (vertex + fragment)

# create program
- create a program id
- attach newly created shaders
- link the program

# setting vertex attributes
- enable vertex attribute arrays to a certain attribute
- set attribute size, type, stride and offset
- make sure to set them before drawing an object and after binding

# get uniforms locations

# game loop
- create projection matrix and view matrix
- fill them with necessary data
- upload the matrix using it's uniform location
- update game logic and poll events
- swap screen buffers
