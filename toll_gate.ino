#include <Servo.h>

Servo servo;

int trigPin = 11;
int echoPin = 12;

long duration;
int distance;

int servoPos = 90;   // Track current position

void setup()
{
  Serial.begin(9600);

  servo.attach(13);
  servo.write(servoPos);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop()
{
  // Ultrasonic trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH, 25000); // timeout for stability

  if (duration == 0) return; // no echo

  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Servo control (state-based)
  if (distance <= 25 && servoPos != 90)
  {
    servoPos = 90;
    servo.write(servoPos);
    Serial.println("Servo -> 180");
  }
  else if (distance > 25 && servoPos !=180)
  {
    servoPos = 180;
    servo.write(servoPos);
    Serial.println("Servo -> 90");
  }

  delay(100); // small delay for sensor stability
}
