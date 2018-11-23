#include "HX711.h"

byte line_error_code = 0, sw01 = 0, sw02 = 0, sw12 = 0;
byte sensor[7] = {0, 0, 0, 0, 0, 0, 0};
String table_error_code = "00", tCode = "00";
int checkweight = 0;

unsigned long previousMillis05 = 0, previousMillis10 = 0;

const long interval10 = 10000;
const long interval05 = 5000;

void read_sensor_values(void);
void main_Control(void);
void check(void);
void waitC(void);

// Line sensor Input
#define sensor01 A1
#define sensor02 A2
#define sensor03 A3
#define sensor04 A4
#define sensor05 A5
// Line sensor Input

// Table sensor Input
#define table_sensor01 A6
#define table_sensor02 A7
// Table sensor Input

//Load cell
#define loadcell_sensor01 A14
#define loadcell_sensor02 A15

HX711 balanza(loadcell_sensor02, loadcell_sensor01);
//Load cell

// select Table  Button
#define table01 10
#define table02 11
#define table12 12
// select Table  Button

// Output
#define pwm_2 2
#define motorR 3
#define pwm_1 4
#define motorL 5
// Output

void motor_output(int _PWM_1, int _PWM_2, int _MotorL, int _MotorR)
{
  analogWrite(pwm_1, _PWM_1);
  analogWrite(pwm_2, _PWM_2);
  analogWrite(motorL, _MotorL);
  analogWrite(motorR, _MotorR);
}

void sucess(String _code)
{
  sw01 = 0;
  sw02 = 0;
  sw12 = 0;
  table_error_code = _code;
  motor_output(0, 0, 0, 0);
}
void check_pr() {
  Serial.print("table_error_code : ");
  Serial.println(table_error_code);
  sensor[5] = digitalRead(table_sensor02);
  sensor[6] = digitalRead(table_sensor01);
  delay(10);
  Serial.print("sensor[5] : ");
  Serial.println(sensor[5]);
  Serial.print("sensor[6] : ");
  Serial.println(sensor[6]);
}

void setup()
{
  Serial.begin(9600);

  pinMode(pwm_1, OUTPUT);
  pinMode(pwm_2, OUTPUT);
  pinMode(motorL, OUTPUT);
  pinMode(motorR, OUTPUT);
  // Line sensor Input
  pinMode(sensor01, INPUT);
  pinMode(sensor02, INPUT);
  pinMode(sensor03, INPUT);
  pinMode(sensor04, INPUT);
  pinMode(sensor05, INPUT);
  // Line sensor Input

  // Table sensor Input
  pinMode(table_sensor01, INPUT);
  pinMode(table_sensor02, INPUT);
  // Table sensor Input

  // select Table button
  pinMode(table01, INPUT);
  pinMode(table02, INPUT);
  // select Table button

  Serial.print("Lectura del valor del ADC:  ");
  Serial.println(balanza.read());
  Serial.println("Destarando...");
  Serial.println("...");
  balanza.set_scale(207.5);
  balanza.tare(20);
}

void loop()
{
  sw01 = digitalRead(table01);
  sw02 = digitalRead(table02);
  sw12 = digitalRead(table12);
  check_pr();

  while (sw01 == HIGH)
  {
    check_pr();
    if (table_error_code == "00")
    {
      if (sensor[5] == HIGH && sensor[6] == LOW)
      {
        table_error_code = "01";
        motor_output(0, 0, 0, 0);
        delay(5000);
      } else {
        read_sensor_values();
        main_Control();
      }
    }
    if (table_error_code == "01")
    {
      if (sensor[5] == HIGH && sensor[6] == HIGH)
      {
        sucess("00");
        break;
      } else {
        read_sensor_values();
        main_Control();
      }
    }
  }
  while (sw02 == HIGH)
  {
    check_pr();
    if (table_error_code == "00")
    {
      if (sensor[5] == LOW && sensor[6] == HIGH)
      {
        table_error_code = "10";
        motor_output(0, 0, 0, 0);
        waitC();
        //        delay(5000);
      } else {
        read_sensor_values();
        main_Control();
      }
    }
    if (table_error_code == "10")
    {
      if (sensor[5] == HIGH && sensor[6] == HIGH)
      {
        sucess("00");
        break;
      } else {
        read_sensor_values();
        main_Control();
      }
    }
  }
  while (sw12 == HIGH)
  {

    // sensor[5] = digitalRead(table_sensor02);
    // sensor[6] = digitalRead(table_sensor01);
    check_pr();
    if (table_error_code == "00")
    {
      if (sensor[5] == HIGH && sensor[6] == LOW)
      {
        table_error_code = "01";
        sw01 = 0;
        motor_output(0, 0, 0, 0);
        delay(5000);
      } else {
        read_sensor_values();
        main_Control();
      }
    }
    if (table_error_code == "01")
    {
      if (sensor[5] == LOW && sensor[6] == HIGH)
      {
        table_error_code = "10";
        sw02 = 0;
        motor_output(0, 0, 0, 0);
        delay(5000);
      } else {
        read_sensor_values();
        main_Control();
      }
    }
    if (table_error_code == "10")
    {
      if (sensor[5] == HIGH && sensor[6] == HIGH)
      {
        sucess("00");
        break;
      } else {
        read_sensor_values();
        main_Control();
      }
    }
  }
}

void read_sensor_values()
{
  sensor[0] = digitalRead(sensor01);
  sensor[1] = digitalRead(sensor02);
  sensor[2] = digitalRead(sensor03);
  sensor[3] = digitalRead(sensor04);
  sensor[4] = digitalRead(sensor05);

  if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 31;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 0))
  {
    line_error_code = 17;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 0;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 19;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 3;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 7;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 15;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 0))
  {
    line_error_code = 25;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 24;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 28;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 0) && (sensor[1] == 0) && (sensor[0] == 1))
  {
    line_error_code = 30;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 1))
  {
    line_error_code = 16;
  }
  else if ((sensor[4] == 1) && (sensor[3] == 1) && (sensor[2] == 1) && (sensor[1] == 1) && (sensor[0] == 0))
  {
    line_error_code = 1;
  }
  else if ((sensor[4] == 0) && (sensor[3] == 0) && (sensor[2] == 1) && (sensor[1] == 0) && (sensor[0] == 0))
  {
    line_error_code = 4;
  }
}
void main_Control()
{
  if (line_error_code == 17)
  {
    motor_output(34, 45, 255, 255);
  }
  else if (line_error_code == 4)
  {
    motor_output(35, 45, 255, 255);
  }
  else if (line_error_code == 3)
  {
    motor_output(45, 15, 255, 255);
  }
  else if (line_error_code == 7)
  {
    motor_output(50, 25, 255, 255);
  }
  else if (line_error_code == 15)
  {
    motor_output(70, 35, 255, 0);
  }
  else if (line_error_code == 19)
  {
    motor_output(35, 15, 255, 255);
  }
  else if (line_error_code == 24)
  {
    motor_output(15, 45, 255, 255);
  }
  else if (line_error_code == 25)
  {
    motor_output(15, 35, 255, 255);
  }
  else if (line_error_code == 28)
  {
    motor_output(25, 50, 255, 255);
  }
  else if (line_error_code == 30)
  {
    motor_output(35, 70, 0, 255);
  }
  else if (line_error_code == 31)
  {
    motor_output(30, 30, 0, 0);
  }
  else if (line_error_code == 1)
  {
    motor_output(0, 85, 0, 255);
  }
  else if (line_error_code == 16)
  {
    motor_output(85, 0, 255, 0);
  }
  else if (line_error_code == 0)      // line_error_code code:Stop
  {
    motor_output(0, 0, 0, 0);
  }
}

void waitC() {
  while (1) {
    unsigned long currentMillis05 = millis();
    unsigned long currentMillis10 = millis();
    digitalWrite(led1, HIGH);
    checkweight = balanza.get_units(1), 0;
    if ((currentMillis05 - previousMillis05 >= interval05) && (checkweight >= -5 && checkweight < 20) ) {
      // save the last time you blinked the LED
      Serial.println(previousMillis05);
      Serial.println(currentMillis05);
      previousMillis05 = currentMillis05;
      Serial.println("in 05");
      break;
    }
    if (currentMillis10 - previousMillis10 >= interval10 && checkweight >= 22 ) {
      // save the last time you blinked the LED
      previousMillis10 = currentMillis10;
      Serial.println("in 10");
      break;
    }
  }
}
