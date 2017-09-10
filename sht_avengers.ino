void setup() {
  Serial.begin(9600);
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  pinMode(14, INPUT);
  pinMode(15, INPUT);

  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);

  Serial.println("Start..");
}

int arr[6]={ false, false, false, false, false, false };
int arrLift[2]={ false, false };

void loop() {
  for (int i = 2; i < 8; i++) {
    int pin = digitalRead(i);
    int j = i + 6;
    int arrInt = i - 2;

    if (pin) {
//      Serial.println("========================pin: " 
//        + (String)pin 
//        + ", i=" 
//        + (String)i 
//        + ", j=" 
//        + (String)j);
        
      if (!arr[arrInt]) {

        int speed = 200;
        if (i == 3 || i == 5) {
          analogWrite(j, speed);  //pwm
        } else if (i == 6) {
          Serial.println("yoko");
          analogWrite(j, speed);  //pwm
        } else {
          digitalWrite(j, HIGH);
        }
        arr[arrInt] = true;

        //Serial.println((String)j + ": high");
      }
    
    } else {
//      Serial.println(
//        "------------------------pin: " 
//        + (String)pin 
//        + ", i=" 
//        + (String)i 
//        + ", j=" 
//        + (String)j);
        
      if (arr[arrInt]) {
         digitalWrite(j, LOW);
         arr[arrInt] = false;
         //Serial.println((String)j + ": low");
      }
    }
  }

  boolean outPin = false;
  for (int x = 14; x < 16; x++) {
    int pin = digitalRead(x);
    int z = x + 2;
    int arrLiftInt = x - 14;

    if (pin) {
      Serial.println("======================*pin: " 
        + (String)pin 
        + ", i=" 
        + (String)x
        + ", j=" 
        + (String)z);
        
      if (!arrLift[arrLiftInt]) {
        
        int speed = 200;
        if (x == 151) {
          analogWrite(z, speed);  //pwm
        } else {
          digitalWrite(z, HIGH);
        }
        arrLift[arrLiftInt] = true;

        Serial.println((String)z + ": high");
      }
    
    } else {
      Serial.println(
        "-----------------------*pin: " 
        + (String)pin 
        + ", i=" 
        + (String)x
        + ", j=" 
        + (String)z);
        
      if (arrLift[arrLiftInt]) {
         digitalWrite(z, LOW);
         arrLift[arrLiftInt] = false;
         Serial.println((String)z + "*: low");
      }
    }
    //delay(100);
    //Serial.println("==========");
  }
}
