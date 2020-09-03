#include<Wire.h>

#define sOne A0
#define sTwo A1
#define sThree A2

const int MPU_addr = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
int xValues[3];

int minVal = 265;
int maxVal = 402;
int counterSensor = 0;
int average = 0;


double x, y, z;

int xAverage[3];
int yAverage[3];
//int zAverage[3];

void setup() {
  Wire.begin();
  Wire.setClock(400000);
  delay(2);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  Serial.begin(115200);
  pinMode(sOne, OUTPUT);
  pinMode(sTwo, OUTPUT);
  pinMode(sThree, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

void loop() {

  /*for (int i = 0; i < 3; i++)
    {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 6, true);

    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    int xAng = map(AcX, minVal, maxVal, -90, 90);
    int yAng = map(AcY, minVal, maxVal, -90, 90);
    int zAng = map(AcZ, minVal, maxVal, -90, 90);


    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI); //incorrect


    xAverage[i] = x;
    yAverage[i] = y;
    //zAverage[i] = z; //not used yet
    }

    int xTrans = 0, yTrans = 0;
    for (int i = 0; i < 3; i++) xTrans += xAverage[i];
    for (int i = 0; i < 3; i++) yTrans += yAverage[i];

    int xFinal = xTrans / 3;
    int yFinal = yTrans / 3;*/

  float xYes, yYes;

  readValues(&xYes, &yYes);


  //Serial.print("AngleX= ");
  Serial.print(xValues[counterSensor]);
  Serial.print(",");

  //no problem
  if ((xValues[1] <= xValues[0] + 5) && (xValues[1] >= xValues[0] - 5) &&
      (xValues[2] <= xValues[0] + 5) && (xValues[2] >= xValues[0] - 5) &&
      (xValues[2] <= xValues[1] + 5) && (xValues[2] >= xValues[1] - 5))
  {
    digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    average = (xValues[0] + xValues[1] + xValues[2]) / 3;
    goto endc;
  }
 /*
  else if (xValues[0] > 354 || xValues[1] > 354 || xValues > 354) {
    if (xValues[0] > 354) {
      xValues[0] -= 360;
    }
    if (xValues[1] > 354) {
      xValues[1] -= 360;
    }
    if (xValues[2] > 354) {
      xValues[2] -= 360;
    }
    if ((xValues[1] <= xValues[0] + 5) && (xValues[1] >= xValues[0] - 5) &&
        (xValues[2] <= xValues[0] + 5) && (xValues[2] >= xValues[0] - 5) &&
        (xValues[2] <= xValues[1] + 5) && (xValues[2] >= xValues[1] - 5))
    {
      digitalWrite(2, HIGH);
      digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);

      if (xValues[0] < 0) {
        xValues[0] += 360;
      }
      if (xValues[1] < 0) {
        xValues[1] += 360;
      }
      if (xValues[2] < 0) {
        xValues[2] += 360;
      }
      average = (xValues[0] + xValues[1] + xValues[2]) / 3;
      goto endc;

    }
    else {
      if (xValues[0] < 0) {
        xValues[0] += 360;
      }
      if (xValues[1] < 0) {
        xValues[1] += 360;
      }
      if (xValues[2] < 0) {
        xValues[2] += 360;
      }
    }
  }
*/

  //some problem
  if ((xValues[1] <= xValues[0] + 5) && (xValues[1] >= xValues[0] - 5))
  {
    digitalWrite(3, HIGH);
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    average = (xValues[0] + xValues[1]) / 2;
    goto endc;
  }
  if ((xValues[2] <= xValues[0] + 5) && (xValues[2] >= xValues[0] - 5))
  {
    digitalWrite(4, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(2, LOW);
    digitalWrite(5, LOW);
    average = (xValues[0] + xValues[2]) / 2;
    goto endc;
  }
  if ((xValues[2] <= xValues[1] + 5) && (xValues[2] >= xValues[1] - 5))
  {
    digitalWrite(5, HIGH);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(2, LOW);
    average = (xValues[2] + xValues[1]) / 2;
    goto endc;
  }


endc:




  if (counterSensor == 2)
  {
    Serial.print("           ");
    Serial.println(average);
  }

  //Serial.print("AngleY= ");
  //Serial.println(y);
  //Serial.println();

  //Serial.print("AngleZ= ");
  //int dz = map(z, 0, 360, 0, 18);
  //Serial.println(dz);
  //Serial.println();
  changeSensor();
  //delay(1000);
  digitalWrite(6, HIGH);
  digitalWrite(6, LOW);
}

void changeSensor()
{
  switch (counterSensor)
  {
    case 0:
      digitalWrite(sTwo, HIGH);
      delayMicroseconds(10);
      digitalWrite(sThree, HIGH);
      delayMicroseconds(10);
      digitalWrite(sOne, LOW);
      delayMicroseconds(10);
      break;

    case 1:
      digitalWrite(sOne, HIGH);
      delayMicroseconds(10);
      digitalWrite(sThree, HIGH);
      delayMicroseconds(10);
      digitalWrite(sTwo, LOW);
      delayMicroseconds(10);
      break;

    case 2:
      digitalWrite(sOne, HIGH);
      delayMicroseconds(10);
      digitalWrite(sTwo, HIGH);
      delayMicroseconds(10);
      digitalWrite(sThree, LOW);
      delayMicroseconds(10);

      //Serial.println();
      //delay(1000);
      break;
  }
  counterSensor++;
  if (counterSensor >= 3)
    counterSensor = 0;
}

void  readValues(float * xTransfer, float * yTransfer)
{
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  for (int i = 0; i < 1; i++)
  {
    Wire.beginTransmission(MPU_addr);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 6, true);

    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    int xAng = map(AcX, minVal, maxVal, -90, 90);
    int yAng = map(AcY, minVal, maxVal, -90, 90);
    int zAng = map(AcZ, minVal, maxVal, -90, 90);


    x = RAD_TO_DEG * (atan2(-yAng, -zAng) + PI);
    y = RAD_TO_DEG * (atan2(-xAng, -zAng) + PI);
    z = RAD_TO_DEG * (atan2(-yAng, -xAng) + PI); //incorrect


    xAverage[i] = x;
    yAverage[i] = y;
    //zAverage[i] = z; //not used yet
    //delay(1);
  }

  int xTrans = 0, yTrans = 0;
  for (int i = 0; i < 3; i++) xTrans += xAverage[i];
  for (int i = 0; i < 3; i++) yTrans += yAverage[i];

  *xTransfer = xTrans / 3;
  *yTransfer = yTrans / 3;

  xValues[counterSensor] = (int)(xTrans / 3);
  //delay(1);
}
