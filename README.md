# Dialog-Center-Text
SAMP Dialog Center Text

- **How to use**

  ```pawn
	#include <DialogCenter>
	```
  
	```pawn
	//add at first place on new line
  \\c
	```
 
 - **Example**
 
 ```pawn
  new str[512];  
  
	format(str, sizeof(str), "\
		\\c{FFFFFF}Welcome back, {09E627}User\n \n\
		\\c{FFFFFF}Please, insert your password in box below\
	");
  
   ShowPlayerDialog(playerid, 1, DIALOG_STYLE_PASSWORD, "Login", str, "OK", "Cancel");
 ```



![alt tag](http://image.prntscr.com/image/a51b5fcb07074f4680515f48d651baa3.png)


![alt-tag](http://image.prntscr.com/image/fc959fa72a1d4eeaaf35db8be546652d.png)


![alt-tag](http://image.prntscr.com/image/e80ea3671832416b9d5b740d4ed3f900.png)


![alt-tag](http://image.prntscr.com/image/3b0c9f1aefb5447ca42bb075b11b5b45.png)
