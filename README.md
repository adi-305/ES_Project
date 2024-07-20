
# Calculator using ARM LPC1768 Microcontroller

A scientific calculator is a device which can perform complex mathematical operations and functions. It typically features a range of specialized functions such as trigonometric, logarithmic, and exponential functions, as well as statistical, probability, and engineering functions.
In addition to basic arithmetic operations, such as addition, subtraction, multiplication, and division,we have implemented the ability to calculate more advanced mathematical operations, such as square roots, exponents, and logarithms.
This calculator will be interfaced with the help of the 16x2 LCD Panel and the 4X4 Key Matrix found on the LPC1768 .The input for this calculator will be given using the 4x4 Key Matrix board and the output will be shown on the 16 x 2 LCD Panel.
Thorough testing and debugging has been conducted to ensure correct functionality and reliability, with attention given to edge cases and user input errors. The final outcome is a functional scientific calculator that showcases the capabilities of the LPC1768 microcontroller for interfacing with peripherals and performing arithmetic calculations accurately and efficiently.
This project will demonstrate the integration of hardware and software components and the utilization of LPC1768 for developing an embedded system application. The resulting calculator can be used in various real-world applications where efficient and accurate arithmetic calculations are required, showcasing the practical implementation of a calculator using an ARM Cortex M microcontroller for interfacing with peripherals.


## Configuration

#### 1. LCD Display:
The LPC1768 board features a small LCD panel that allows for basic visual feedback and interaction with the device. This LCD panel is usually a monochrome, backlit display that can show up to 16 characters per line, with two lines available each of which can display a single character, and two rows of these character positions, one on top of the other. Each character position is usually made up of a 5x8 dot matrix, which can be used to display a variety of characters and symbols.
This LCD can be used to display the message from the controller.16 pin small LCD has to be mounted to the connector CN11. 10 pin connector CNAD is used to interface this LCD from the controller. Only higher 4 data lines are used among the 8 LCD data lines.


#### 2. 4x4 Key Matrix:
The switches SW3 to SW18 are organized as 4 rows X 4 columns matrix. One end of all the switches are configured as columns. The other end of the matrix is configured as rows. A row line will always be an output from the controller. Column lines are pulled to ground.Input signals to be read by a microcontroller or other device using only a few input pins.
Each switch in the matrix is connected to a unique row and column in the matrix. When a switch is pressed, it connects the corresponding row and column together, creating a connection that can be detected by the microcontroller. By scanning through each row and column of the matrix, the microcontroller can determine which switches are pressed and read their corresponding signals.
A high level sent from the row will appear at column end if the switch is pressed.

#### 3. Hardware setup:
For the LCD Panel connect 10 pin FRC cable from CND to CNAD. For the 4x4 Key Matrix connect 10 pin FRC cable from CNB to CNB3


## Block Diagram
![Alt text](https://www.exploreembedded.com/wiki/images/b/b8/LPC1768_4bit_LCD.PNG)

