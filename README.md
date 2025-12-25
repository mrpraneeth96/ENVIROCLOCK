# ⏰ENVIROCLOCK
EnviroClock is a simple embedded systems project using the LPC2148 microcontroller that displays the current time, alarm status, and room temperature on an LCD. Users can set or modify the time and alarm using a keypad. When the alarm time is reached, a buzzer is activated. The system combines clock functionality, temperature sensing, and an alarm system into one easy-to-use device.

# Project Overview 

The EnviroClock displays:

Current time and date using the on-chip RTC

Day of the week

Room temperature using an LM35 temperature sensor

Alarm functionality with buzzer alert


# Block Diagram

<img width="500" height="250" alt="image" src="https://github.com/user-attachments/assets/3ce9dd5f-180b-49fd-aa97-3e3dd5dbfdc7" />


# Hardware Setup


The hardware setup consists of an LPC2148 development board connected to external peripherals such as the LCD, keypad, LM35 temperature sensor, buzzer, LEDs, and switches. This setup demonstrates the practical wiring and proper integration of all components required for the system to function correctly.

<img width="500" height="450" alt="image" src="https://github.com/user-attachments/assets/4cc02396-1be6-4518-9db8-b9106bb0f9a7" />


# LCD Output


The LCD displays real-time information provided by the EnviroClock system. It shows the current time, date, day, and room temperature, all of which are continuously updated using the on-chip RTC and ADC modules. This output confirms the successful operation of the display interface and sensor data processing.

<img width="300" height="150" alt="image" src="https://github.com/user-attachments/assets/9c312edf-51ce-46fd-b837-6dc582ec9aba" />

The menu screen shows the interrupt-driven user interface used to configure the system. When the user presses the interrupt switch, a menu appears on the LCD with options to edit RTC information, set the alarm, or exit. This screen highlights the interactive nature of the system and the keypad-based navigation for user-friendly configuration.

# Conclusion

The EnviroClock project successfully demonstrates the design and implementation of a multifunction embedded system using the LPC2148 microcontroller. By integrating real-time clock functionality, temperature monitoring through the LM35 sensor, and an alarm system with buzzer indication, the project provides a compact and efficient solution for time and environmental monitoring. The interrupt-driven menu and keypad-based user interface allow easy modification of time and alarm settings, making the system user-friendly and flexible. Overall, this project highlights the effective use of on-chip peripherals such as RTC, ADC, GPIO, and interrupts, and serves as a practical learning platform for embedded systems design and real-time applications.
