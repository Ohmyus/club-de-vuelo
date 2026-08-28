### 1. The Core Components

To capture all 22 inputs, you will build a circuit around three **CD4021B** shift registers daisy-chained together.

* **U1 (Register 1):** Handles bits 16-23.
* **U2 (Register 2):** Handles bits 8-15.
* **U3 (Register 3):** Handles bits 0-7.

### 2. Wiring the Shift Registers (The Bus)

The registers need to share power and control signals from the base, and pass data down the line to the Mini-DIN 5 connector.

* **Power:** Connect Pin 1 (VCC, 3.3V) and Pin 5 (GND) from the Mini-DIN to the VCC and GND pins of all three ICs. Place a 100nF capacitor across the VCC and GND pins of each IC to prevent ghosting.
* **Control Lines:** Connect Pin 2 (P/S - LOAD) and Pin 3 (CLOCK) from the Mini-DIN to the respective Load and Clock pins on all three ICs.
* **The Daisy Chain (Data):**
- Connect the Q8 output of **U3** to the Serial-In of **U2**.
- Connect the Q8 output of **U2** to the Serial-In of **U1**.
- Connect the Q8 output of **U1** directly to Pin 4 (DATA) on the Mini-DIN.

### 3. Wiring the Buttons and Hats

Each CD4021B has 8 parallel input pins (P1 through P8). Here is how you wire your switches to them:

* **The Pull-Up Network:** Every single input pin (P1-P8 on all three chips) must be connected to 3.3V (VCC) through a **10k resistor**. This keeps the inputs "High" when nothing is pressed. Using bussed resistor networks (a single component with multiple resistors inside) will save you a ton of space here.

* **The Switches:** Wire one side of your button or hat switch to the specific input pin (P1-P8), and the other side directly to common Ground (GND).

* **The Action:** When you press a button, it connects the input pin to GND, dropping the signal to "Low," which the shift register reads as a button press.

* **Unused Inputs:** Since you only have 22 inputs for 24 available slots, leave the 2 unused input pins connected to their 10k pull-up resistors so they remain constantly "High". Never leave an input pin floating.

Are you planning to test this circuit on a breadboard first, or are you going straight to designing the custom PCB?
