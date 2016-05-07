# Naze32-LED-Blink-STM32F10x-GCC
First step of writing your custom program for the Naze32 flight controller board.

Naze32 and many clones such as Flip32 make great prototyping boards for your own ARM STM project. They are inexpensive, compact, readily available, have voltage regulator, USB serial converter, LEDs, nice 0.1" pin headers, and several sensors. However, there is a catch; The red LED is connected to the JTAG port NJTRST. So if you want to try out the board with your own code, it will probably not work. The solution is to disable the JTAG port so that its pins are now accessible as normal functions such as GPIO.

This is a sample LED blink project for the Flip32 board. By running this, you check that your toolchain, directory definitions, ld script, flashing method etc. are all  fine, and now you can start writing custom code for the board. 
