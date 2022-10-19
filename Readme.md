#Template for C embedded projects.

##I. Description:
The assumption is to create a project that separates firmware (hardware libraries) from software (target functionalities).

##II. Structure:
The embedded project has been divided into three parts:

External:
This is where documents and external libraries are stored.

Project:
   - Logic:
     This is where environment-specific but hardware-independent code is stored.
   
   - Hardware:
     This is where the environment-specific code is stored.
   
Tests:
   - BlackBox:
     This is where the black-box tests are stored.
   
   - WhiteBox:
     This is where the white-box tests are stored.
     
     - Hardware
     - Logic
       - Fakes,
       - Fixtures.
       

##III. Interface:
- Project is based on the structures interfaces,
- Every unit (.h and .c file) is represented by one object,
- Object has end of source file scope which be extended with extern keyword.
