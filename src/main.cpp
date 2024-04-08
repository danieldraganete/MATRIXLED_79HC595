#include <Arduino.h>

// Define 74HC595 pins
const int latchPin = 2;     // ST_CP pin
const int clockPinR = 12;   // SH_CP pin for rows
const int dataPinR = 9;     // DS pin for rows
const int clockPinC = 11;   // SH_CP pin for columns
const int dataPinC = 10;    // DS pin for columns

// LED configuration matrix for each digit
int ledMatrix[10][2][8] = {
  // 0
  {
    {1, 0, 0, 0, 0, 0, 0, 0}, {1,
                               0, 
                               0, 
                               0, 
                               0, 
                               0, 
                               0, 
                               0}
   
  },
  // 1
  {
    {1, 1, 0, 0, 0, 0, 0, 0},
    {1, 1, 0, 0, 0, 0, 0, 0}
  },
  // 2
  {
    {1, 1, 1, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0}
  },
  // 3
  {
    {1, 1, 1, 1, 0, 0, 0, 0},
    {1, 1, 1, 1, 0, 0, 0, 0}
  },
  // 4
  {
    {1, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 1, 1, 1, 0, 0, 0}
  },
  // 5
  {
    {1, 1, 1, 1, 1, 1, 0, 0},
    {1, 1, 1, 1, 1, 1, 0, 0}
  },
  // 6
  {
    {1, 1, 1, 1, 1, 1, 1, 0},
    {1, 1, 1, 1, 1, 1, 1, 0}
  },
  // 7
  {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
  },
  // 8
  {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
  },
  // 9
  {
    {1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1}
  }
};

void setup() {
  // Set control pins as outputs
  pinMode(latchPin, OUTPUT);
  pinMode(clockPinR, OUTPUT);
  pinMode(dataPinR, OUTPUT);
  pinMode(clockPinC, OUTPUT);
  pinMode(dataPinC, OUTPUT);
  
  // Start serial communication
  Serial.begin(9600);
}

// Function to send a bit for rows
void sendBitR(int bit) {
  // Set data pin for rows (DS)
  digitalWrite(dataPinR, bit);
  // Generate clock pulse for rows (SH_CP)
  digitalWrite(clockPinR, HIGH);
  digitalWrite(clockPinR, LOW);
}

// Function to send a bit for columns
void sendBitC(int bit) {
  // Set data pin for columns (DS)
  digitalWrite(dataPinC, bit);
  // Generate clock pulse for columns (SH_CP)
  digitalWrite(clockPinC, HIGH);
  digitalWrite(clockPinC, LOW);
}

// Function to send a byte to 74HC595 for rows
void sendDataR(int ledState) {
  // Send a bit for LED state for rows
  sendBitR(ledState ? HIGH : LOW);
}

// Function to send a byte to 74HC595 for columns
void sendDataC(int ledState) {
  // Send a bit for LED state for columns
  sendBitC(ledState ? HIGH : LOW);
}

void displayDigit(int digit) {
  // Send current configuration to the two 74HC595s
  digitalWrite(latchPin, LOW);
  
  // Send data for rows
  for (int j = 8; j >0; j--) {
	int x=j-1;
    sendDataR(ledMatrix[digit][1][x]);
  }

  // Send data for columns
  for (int j = 0; j < 8; j++) {
    sendDataC(ledMatrix[digit][0][j]);
  }

  digitalWrite(latchPin, HIGH);
}

void displayDigitMirror(int digit) {
  // Send current configuration to the two 74HC595s
  digitalWrite(latchPin, LOW);
  
  // Send data for rows
  for (int j = 8; j >0; j--) {
	int x=j-1;
    sendDataC(ledMatrix[digit][0][x]);
  }

  // Send data for columns
  for (int j = 0; j < 8; j++) {

    sendDataR(ledMatrix[digit][1][j]);
  }

 digitalWrite(latchPin, HIGH);
}

  void loop() {
  // Iterate through each digit from 0 to 9 and display it on LEDs
  for (int digit = 0; digit < 8; digit++) {
    // Display the current digit
    displayDigit(digit);
    // Delay between displaying each digit
    delay(100); // Adjust as necessary
  }
    
      for (int digit = 8; digit > 0; digit--) {
    // Display the current digit
    displayDigitMirror(digit);
    // Delay between displaying each digit
    delay(100); // Adjust as necessary
  }
}
