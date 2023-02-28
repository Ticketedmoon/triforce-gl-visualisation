# Triforce-Visualisation
Fun 3D Graphics project built with Modern OpenGL visualising the Triforce from The Legend of Zelda Games. 

#### Prerequisites
- OpenGL 4.6  
- Libraries can be installed with `./setup.sh`  
- glad and KHR can be installed from `https://glad.dav1d.de/`

#### Dev Log

#### 27/02/2023

https://user-images.githubusercontent.com/21260839/222000251-13bba5e7-2c21-4f36-a818-0d2f87cdb272.mp4  

---

**Notes:**
- The rotating Triforce was constructed with an 18 vertice vao, but some of these were reused several times to fill-in the walls of each 3D triangle. This was done using an Index Buffer (ebo), with a total count of 54 indices.

- The camera/frustum has a perspective projection, with functionality to translate the vertices in the world with w-s-a-d. The pitch and yaw of the frustum can be adjusted using the movement of the mouse. Scrolling forward and back also zooms-in and zooms-out by means of adjusting the fov.

- This is also functional with a joystick controller, e.g., a ps4 controller is what I have been using.
  Movement is bound to the left stick, pitch/yaw adjustment to the right stick and L2/R2 for zoom/fov change.
