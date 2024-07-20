#include <LPC17xx.h>

// Define control signals for the LCD
#define RS_CTRL 0x08000000  // Register Select control signal
#define EN_CTRL 0x10000000  // Enable control signal
#define DT_CTRL 0x07800000  // Data lines control signal

unsigned long int temp1 = 0, temp2 = 0; // Temporary variables for data manipulation

// Function prototypes
void lcd_init(void);
void lcd_com(void);
void clear_ports(void);
void delay_lcd(unsigned int);
void lcd_puts(unsigned char *);
void lcd_data(void);
void wr_cn(void);
void wr_dn(void);

// Initialize the LCD
void lcd_init(void) {
    // Set the direction of the GPIO pins to output for LCD control
    LPC_GPIO0->FIODIR |= DT_CTRL;
    LPC_GPIO0->FIODIR |= RS_CTRL;
    LPC_GPIO0->FIODIR |= EN_CTRL;
    
    clear_ports();           // Clear all control ports
    delay_lcd(3200);         // Delay for LCD power stabilization
    
    // Initialize the LCD in 4-bit mode
    temp1 = 0x33;            // Command to set LCD in 4-bit mode
    lcd_com();
    delay_lcd(800);

    temp1 = 0x32;            // Command to set LCD in 4-bit mode (again for safety)
    lcd_com();
    delay_lcd(800);

    temp1 = 0x28;            // Function set: 4-bit, 2 line, 5x8 dots
    lcd_com();
    delay_lcd(800);

    temp1 = 0x0c;            // Display ON, Cursor OFF, Blink OFF
    lcd_com();
    delay_lcd(800);

    temp1 = 0x06;            // Entry mode: Increment cursor
    lcd_com();
    delay_lcd(800);

    temp1 = 0x01;            // Clear display
    lcd_com();
    delay_lcd(10000);

    return;
}

// Clear all ports connected to the LCD
void clear_ports(void) {
    LPC_GPIO0->FIOCLR = DT_CTRL;
    LPC_GPIO0->FIOCLR = RS_CTRL;
    LPC_GPIO0->FIOCLR = EN_CTRL;
}

// Simple delay function
void delay_lcd(unsigned int r1) {
    unsigned int r;
    for (r = 0; r < r1; r++);
    return;
}

// Send a command to the LCD
void lcd_com(void) {
    // Send higher nibble
    temp2 = temp1 & 0xf0;    // Mask lower nibble
    temp2 = temp2 << 19;     // Shift to the correct position
    wr_cn();                 // Write command nibble
    delay_lcd(30000);

    // Send lower nibble
    temp2 = temp1 & 0x0f;    // Mask higher nibble
    temp2 = temp2 << 23;     // Shift to the correct position
    wr_cn();                 // Write command nibble
    delay_lcd(30000);

    return;
}

// Write command nibble to LCD
void wr_cn() {
    LPC_GPIO0->FIOPIN = temp2; // Set data lines
    LPC_GPIO0->FIOCLR = RS_CTRL; // RS = 0 for command
    LPC_GPIO0->FIOSET = EN_CTRL; // Enable pulse
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL; // Disable pulse
}

// Display a string on the LCD
void lcd_puts(unsigned char *buf) {
    unsigned int i = 0;
    while (buf[i] != '\0') {
        temp1 = buf[i];       // Get character from buffer
        lcd_data();           // Write data to LCD
        delay_lcd(800);
        i++;
        
        // Move to next line after 16 characters
        if (i == 16) {
            temp1 = 0xc0;     // Command to move to second line
            lcd_com();
            delay_lcd(800);
        }
    }
    return;
}

// Send data to the LCD
void lcd_data(void) {
    // Send higher nibble
    temp2 = temp1 & 0xf0;    // Mask lower nibble
    temp2 = temp2 << 19;     // Shift to the correct position
    wr_dn();                 // Write data nibble
    delay_lcd(30000);

    // Send lower nibble
    temp2 = temp1 & 0x0f;    // Mask higher nibble
    temp2 = temp2 << 23;     // Shift to the correct position
    wr_dn();                 // Write data nibble
    delay_lcd(30000);

    return;
}

// Write data nibble to LCD
void wr_dn() {
    LPC_GPIO0->FIOPIN = temp2; // Set data lines
    LPC_GPIO0->FIOSET = RS_CTRL; // RS = 1 for data
    LPC_GPIO0->FIOSET = EN_CTRL; // Enable pulse
    delay_lcd(25);
    LPC_GPIO0->FIOCLR = EN_CTRL; // Disable pulse
    return;
}
