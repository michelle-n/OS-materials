This was a series of exercises to demo the popen system call and later on, multithreading. 

How to set up the exercises:
1. Compile the secret_pin program and host the binary on some server the students can reach/run it from. 
---> Bonus: show students why it's not good to hard-code passwords, either using the 'strings' linux command or even by opening the binary
2. Have students write a program to "crack" the 4-digit pin (i.e. 0000 to 9999) via brute force, using the popen call. 
---> Students can assume the wrong pin message is always "__(whatever you write in the secret_pin code)__" 
3. Have students multithread their code. 

Example solutions are given. 