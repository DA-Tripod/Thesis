#include <SoftwareSerial.h>  
#include <Servo.h>

int bluetoothTx = 2;  // TX-O pin of bluetooth mate, Arduino D2
int bluetoothRx = 3;  // RX-I pin of bluetooth mate, Arduino D3

char arr[4];
int counter = 0;
int res = 0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);
//Servo myservo;

// plug the pins TX-0 to Arduino D2 and the RX-I to Arduino D3
// before uploading the sketch make sure that the bluetooth mate isn't supplied with voltage.
// after uploading supply the bluetooth module with voltage.
// In order to get the RN-42 into CMD mode, you need to send $$$ but without any CR/LF.

void setup()
{
  //myservo.attach(5);
  Serial.begin(9600);  // Begin the serial monitor at 9600bps
  bluetooth.begin(115200);        // The Bluetooth Mate defaults to 115200bps
  delay(320);                     // IMPORTANT DELAY! (Minimum ~276ms)
  bluetooth.print("$$$");         // Enter command mode
  delay(100);                      // IMPORTANT DELAY! (Minimum ~10ms)
  bluetooth.println("U,9600,N");  // Temporarily Change the baudrate to 9600, no parity
  bluetooth.println("---");
  bluetooth.begin(9600);          // Start bluetooth serial at 9600
}

void loop()
{
  if(bluetooth.available())  // If the bluetooth sent any characters
  {
    // Send any characters the bluetooth prints to the serial monitor
    arr[counter] = (char)bluetooth.read();
    if((arr[counter] != ';') && counter <= 4){
      counter++;
    }else{
      counter = 0;
      res = atoi(arr);
    }
    //myservo.write(map(bluetooth.read(), 0, 1024, 0, 180));  
  }
  if(Serial.available())  // If stuff was typed in the serial monitor
  {
    // Send any characters the Serial monitor prints to the bluetooth
    bluetooth.print(Serial.read());
  }
  // and loop forever and ever!
}
