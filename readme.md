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

Generating 4 types of waveforms is fundamental to all tasks. For this aspect, I referenced the code from the article ["Verilog 代码编写 DDS信号发生器（幅频相可调正弦波、方波、三角波、锯齿波）纯VIVADO编写仿真" (2022)](https://blog.csdn.net/qq_46132759/article/details/122651657).

Here are some steps to get started:
1. Open my_dds.xpr in vivado
2. make sure all IP cores and modules are working successfully under DDS.v
3. Change the pins in the constraint file according to your hardware
4. Run simulation
5. Run synthesis
6. Run implementation
7. Generate bitstream
8. Connect your computer to your hardware,and open hardware manager.
9. Configuring the bitstream file.

Good luck!