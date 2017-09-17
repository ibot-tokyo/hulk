// RaspberryPi Tire Inputs
const int INPUT_A1 = 2;
const int INPUT_A2 = 3;
const int INPUT_B1 = 4;
const int INPUT_B2 = 5;
const int INPUT_C1 = 6;
const int INPUT_C2 = 7;
// Lifter Inputs
const int INPUT_L1 = 14;
const int INPUT_L2 = 15;

// Tire MoterDriver Outputs
const int OUTPUT_A1 = 8;
const int OUTPUT_A2 = 9;
const int OUTPUT_B1 = 10;
const int OUTPUT_B2 = 11;
const int OUTPUT_C1 = 12;
const int OUTPUT_C2 = 13;
// Lifter MoterDriver Outputs
const int OUTPUT_L1 = 16;
const int OUTPUT_L2 = 17;

const int PWM_SPEED = 200;

void setup() {
  Serial.begin(9600);
  
  pinMode(INPUT_A1, INPUT);
  pinMode(INPUT_A2, INPUT);
  pinMode(INPUT_B1, INPUT);
  pinMode(INPUT_B2, INPUT);
  pinMode(INPUT_C1, INPUT);
  pinMode(INPUT_C2, INPUT);
  pinMode(INPUT_L1, INPUT);
  pinMode(INPUT_L2, INPUT);

  pinMode(OUTPUT_A1, OUTPUT);
  pinMode(OUTPUT_A2, OUTPUT);
  pinMode(OUTPUT_B1, OUTPUT);
  pinMode(OUTPUT_B2, OUTPUT);
  pinMode(OUTPUT_C1, OUTPUT);
  pinMode(OUTPUT_C2, OUTPUT);
  pinMode(OUTPUT_L1, OUTPUT);
  pinMode(OUTPUT_L2, OUTPUT);

  Serial.println("Start...");
}

String readA = "stop";
String readB = "stop";
String readC = "stop";
String readL = "stop";


void loop() {
  Serial.println("=====");

  String newReadA = read("readA", INPUT_A1, INPUT_A2);
  String newReadB = read("readB", INPUT_B1, INPUT_B2);
  String newReadC = read("readC", INPUT_C1, INPUT_C2);
  String newReadL = read("readL", INPUT_L1, INPUT_L2);
  
  delay(5);

  if (readA != newReadA) {
    readA = newReadA;
    send(readA, OUTPUT_A1, OUTPUT_A2, true);
  }
  if (readB != newReadB) {
    readB = newReadB;
    send(readB, OUTPUT_B1, OUTPUT_B2, true);
  }
  if (readC != newReadC) {
    readC = newReadC;
    send(readC, OUTPUT_C1, OUTPUT_C2, true);
  }
  if (readL != newReadL) {
    readL = newReadL;
    send(readL, OUTPUT_L1, OUTPUT_L2, false);
  }

  delay(5);
  // delay(1000);
}

String read(String label, int v1, int v2) {
  bool read1 = digitalRead(v1);
  bool read2 = digitalRead(v2);

  // Serial.println(label + ": " + (String)read1 + ", " + (String)read2);
  
  String state = "stop";
  if (read2) {
    if (read1) {
      state = "forward";  // 1, 1
    } else {
      state = "reverse";  // 0, 1
    }
  }
  Serial.println(label + ": " + state);
  return state;
}

void send(String state, int out1, int out2, bool isPwm) {
  if (state == "forward") {
    // pwm
    if (isPwm) {
      analogWrite(out2, PWM_SPEED);
    } else {
      digitalWrite(out2, HIGH);
    }
    // dir
    digitalWrite(out1, HIGH);
    return;
  }
  
  if (state == "reverse") {
    // pwm
    if (isPwm) {
      analogWrite(out2, PWM_SPEED);
    } else {
      digitalWrite(out2, HIGH);
    }
    // dir
    digitalWrite(out1, LOW);
    return;
  }

  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
}
