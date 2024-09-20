I wrote the project to finish the tasks below:
1. After powering on, the LCD1602 displays basic messages;
2. It can output square wave, sine wave, sawtooth wave, and triangle wave;
3. The output waveform can be switched using independent buttons;
4. The waveform parameters, such as amplitude, duty cycle, and frequency, can be adjusted via buttons.

This waveform generator has 4 major functions:
1. Menu function: The TFT screen displays the waveform, amplitude, frequency, and duty cycle in real time;
2. RTC clock function: It can display the date and time in real time;
3. Power-down protection function: Pressing the reset button allows retrieving the most recent saved waveform data;
4. ASK function: Digital modulation signals with different duty cycles can be switched using buttons. 

Here are some steps to get started:
1. Open "My_Waveform_Generator\USER\KEY.uvprojx" in keil.
2. Change the paths in the "main.c" to make the project work successfully.
3. Change the pins in the constraint file according to your device.
4. Build taget files.
5. Configure target options.
6. Connect your computer to the device using ST-LINK.
7. Download code to flash memory.

Good luck!
