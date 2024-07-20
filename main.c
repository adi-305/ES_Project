#include <LPC17xx.h>
#include "lcdmsh.h"
#include <math.h>

void scan(void); // Function prototype for scanning the keypad

// Global variables
unsigned char row, flag, key;
unsigned long int i, j, var1, temp, temp2, temp3;

// Keypad scan codes and corresponding ASCII codes
unsigned char scan_code[16] = {0x11, 0x21, 0x41, 0x81, 0x12, 0x22, 0x42, 0x82, 0x14, 0x24, 0x44, 0x84, 0x18, 0x28, 0x48, 0x88};
unsigned char ascii_code[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', '+', '-', '*', '/'};

// Variables for calculations
int idx = 3;
int ans = 0;
unsigned char finans[5] = {'0', '0', '0', '0', '\0'};
int a = 0;
int b = 0;
char *op;
int count = 0;

// Operation types and their corresponding operations
unsigned char *operations[4][4] = {
    {"+", "-", "*", "/"},
    {"log", "pow", "nCr", "nPr"},
    {"10log", "sin", "cos", "tan"},
    {"sqrt", "square", "cube", "factorial"}
};

int num_operands = 0;
int operands[2] = {0};
int result = 0;

// Function to calculate factorial
int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i;
    }
    return result;
}

int main(void) {
    // Initialize GPIO for keypad and LCD
    LPC_GPIO2->FIODIR = 0x3c00; // Set rows as outputs
    LPC_GPIO1->FIODIR = 0xf87fffff; // Set columns as inputs

    lcd_init(); // Initialize the LCD

    // Set cursor position to the first line
    temp1 = 0x80;
    lcd_com();
    delay_lcd(800);

    // Main loop to detect key press
    while (1) {
        for (row = 1; row < 5; row++) {
            if (row == 1)
                var1 = 0x400;
            else if (row == 2)
                var1 = 0x800;
            else if (row == 3)
                var1 = 0x1000;
            else if (row == 4)
                var1 = 0x2000;
            
            temp = var1;
            LPC_GPIO2->FIOCLR = 0x3c00;
            LPC_GPIO2->FIOSET = var1;
            flag = 0;
            scan(); // Scan for key press
            
            if (flag == 1) {
                count++;
                break;
            }
        }
        
        if (flag == 1)
            break;
    }

    // Determine the operation based on key press
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            if (key == scan_code[i * 4 + j]) {
                op = operations[i][j];
                if (i < 2)
                    num_operands = 2;
                else
                    num_operands = 1;
                break;
            }
        }
    }

    // Handle operations with one operand
    switch (num_operands) {
    case 1:
        while (count < 1) {
            while (1) {
                for (row = 1; row < 5; row++) {
                    if (row == 1)
                        var1 = 0x400;
                    else if (row == 2)
                        var1 = 0x800;
                    else if (row == 3)
                        var1 = 0x1000;
                    else if (row == 4)
                        var1 = 0x2000;
                    
                    temp = var1;
                    LPC_GPIO2->FIOCLR = 0x3c00;
                    LPC_GPIO2->FIOSET = var1;
                    flag = 0;
                    scan(); // Scan for key press
                    
                    if (flag == 1) {
                        count++;
                        break;
                    }
                }
                
                if (flag == 1)
                    break;
            }

            // Process the key press and display on LCD
            for (i = 0; i < 16; i++) {
                if (key == scan_code[i]) {
                    key = ascii_code[i];
                    lcd_puts(&key);
                    delay_lcd(50000);
                    
                    if (count == 1)
                        a = key - 48; // Convert ASCII to integer
                    break;
                }
            }
        }

        // Perform the operation based on the key press
        switch (op) {
        case "10log":
            ans = log(a) / log(10);
            break;
        case "sin":
            ans = sin(a);
            break;
        case "cos":
            ans = cos(a);
            break;
        case "tan":
            ans = tan(a);
            break;
        case "sqrt":
            ans = sqrt(a);
            break;
        case "square":
            ans = pow(a, 2);
            break;
        case "cube":
            ans = pow(a, 3);
            break;
        case "factorial":
            ans = factorial(a);
            break;
        default:
            break;
        }
        break;

    // Handle operations with two operands
    case 2:
        while (count < 2) {
            while (1) {
                for (row = 1; row < 5; row++) {
                    if (row == 1)
                        var1 = 0x400;
                    else if (row == 2)
                        var1 = 0x800;
                    else if (row == 3)
                        var1 = 0x1000;
                    else if (row == 4)
                        var1 = 0x2000;
                    
                    temp = var1;
                    LPC_GPIO2->FIOCLR = 0x3c00;
                    LPC_GPIO2->FIOSET = var1;
                    flag = 0;
                    scan(); // Scan for key press
                    
                    if (flag == 1) {
                        count++;
                        break;
                    }
                }
                
                if (flag == 1)
                    break;
            }

            // Process the key press and display on LCD
            for (i = 0; i < 16; i++) {
                if (key == scan_code[i]) {
                    key = ascii_code[i];
                    lcd_puts(&key);
                    delay_lcd(50000);
                    
                    if (count == 1)
                        a = key - 48; // Convert ASCII to integer
                    else if (count == 2)
                        b = key - 48; // Convert ASCII to integer
                    break;
                }
            }
        }

        // Perform the operation based on the key press
        switch (op) {
        case "+":
            ans = a + b;
            break;
        case "-":
            ans = a - b;
            break;
        case "*":
            ans = a * b;
            break;
        case "/":
            ans = a / b;
            break;
        case "log":
            ans = log(a) / log(b);
            break;
        case "pow":
            ans = pow(a, b);
            break;
        case "nCr":
            ans = factorial(a) / (factorial(a - b) * factorial(b));
            break;
        case "nPr":
            ans = factorial(a) / factorial(a - b);
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }

    // Display the result on the second line of the LCD
    temp1 = 0xc0;
    lcd_com();
    delay_lcd(800);

    while (ans != 0) {
        finans[idx--] = (ans % 10) + 48; // Convert integer to ASCII
        ans = ans / 10;
    }

    lcd_puts(&finans[0]); // Display the result
    return 0;
}

// Function to scan the keypad and set the key variable
void scan(void) {
    temp3 = LPC_GPIO1->FIOPIN;
    temp3 &= 0x07800000; // Mask the column bits

    if (temp3 != 0) {
        flag = 1;
        temp3 >>= 19; // Align the column bits
        temp >>= 10;  // Align the row bits
        key = temp3 | temp; // Combine row and column bits to get the key code
    }
}
