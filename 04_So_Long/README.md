Hello, welcome to my game !
Just git clone and make, then execute with the map of your choice as an argument (in the maps folder)

Possible errors :
>> You may miss a library. If you do (pick and choose depending on the error message) :
sudo apt install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev'

If the Makefile starts with
'# Makefile pour Eval (l'original a été backup)'
It's the right one.

If if starts with
'# All notes are now in the Makefile template'
Don't use it.
Instead, delete that Makefile, and rename the 'Makefile_for_eval' to Makefile, and you should be good to go !

Have fun ^^'

NB : You can add your own map, or use any other .png (put it in 'textures' folder and update path in the .h),
as long as it's 72 x 72 pxl
