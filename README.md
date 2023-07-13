<h1 style = "color:cyan"> Vulkan Engine</h1>


<h2 style = "color:cyan"> Introduction <h2>

<p style = "font-size:15px">
This project aim to to create a graphic engine using Vulkan <br>
We want to be able to setup and load Vulkan and also load obj's file with textures <br>
We also want to have a functional camera which will allow us to move friely in the scene <br>
Basically every aspect of vulkan setup was made using the vulkan tutorial online, i did everything until Model loading section
</p>

<h2 style = "color:cyan"> Architecture </h2>
<p style = "font-size:15px">
The project is architectured using the base architecture given in the subject i just hadded the class Model and VulkanManager<br> 
The class Model will aim to Load obj and texture and do everything linked to this. 
The class VulkanManager will load and handle everything about Vulkan.
</p>

<h2 style = "color:cyan"> Obj textures and Math</h2>
<p>
To parse the obj i use the tiny_obj_loader library which is a single file that allow us to parse and use an obj file <br>
To use the texture i use the stb_image library which is also a single file library <br>
For the math of the project i used the glm library <br>
</p>

<h2 style = "color:cyan"> Camera </h2>

<p>
The camera is also pretty simple, we calculate the projection matrix at the beginning of the application using glm::perspective <br>
The view matrix is created using the lookAt function from glm and we use the calculated vectors position , forward and up <br>
The up vector never change, the forward is calculated using the mouse movement and the pos is modified every time we press a key by multiplying the speed by the delta time and the forward vector <br>
</p>


<h2 style = "color:cyan"> Utilisation <h2>
<p style = "font-size:15px">
<h3> Move </h3>
To move around inside the scene you just have to use WASD input to move, you can turn using the mouse <br>
To use the mouse you just have to maintain right click and move it <br>

<h3> The objects </h3>
All objects are loaded in the while vulkan is setting up and can't be moved for now <br>
Here is a screenshot of the scene with two objects loaded <br>
<br>
<img src="screenshot/2ObjScene.PNG" alt="obj">
