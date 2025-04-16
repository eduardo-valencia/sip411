/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5StickC sample source code
*                          配套  M5StickC 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/m5stickc
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/m5stickc
*
* Describe:  IMU.
* Date: 2021/9/3
*******************************************************************************
*/
#include <M5StickC.h>

float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

float accXSq = 0.0F;
float accYSq = 0.0F;
float accZSq = 0.0F;

float accMagSq = 0.0F;
float accMag = 0.0F;
float maxAccMag = 0.0F;

#define LED_BUILTIN 10

/* After M5StickC is started or reset
  the program in the setUp () function will be run, and this part will only be
  run once. 在 M5StickC
  启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。 */
void setup() {
    M5.begin();
    M5.IMU.Init();  // Init IMU.  初始化IMU
    M5.Lcd.setRotation(3);
    M5.Lcd.setCursor(40, 0);
    M5.Lcd.println("IMU TEST");
    M5.Lcd.setCursor(0, 10);
    M5.Lcd.println("   X       Y       Z");
    M5.Lcd.setCursor(0, 50);
    // TODO: Add this again
    // M5.Lcd.println("Max accel magnitude");
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage LOW
}

/*****************************************
M5.IMU.getGyroData(&gyroX,&gyroY,&gyroZ);
M5.IMU.getAccelData(&accX,&accY,&accZ);
M5.IMU.getAhrsData(&pitch,&roll,&yaw);
M5.IMU.getTempData(&temp);
*****************************************/
/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    M5.update();

    if (M5.BtnA.wasReleased()) {
      maxAccMag = 0.0F;
    }

    M5.IMU.getAccelData(&accX, &accY, &accZ);
    
    accXSq = sq(accX);
    accYSq = sq(accY);
    accZSq = sq(accZ);

    accMagSq = accXSq + accYSq + accZSq;
    accMag = sqrt(accMagSq);

    if (accMag > 9.5) {
      for(int i=0; i < 5; i++) {
        digitalWrite(LED_BUILTIN, LOW);  // turn the LED on (HIGH is the voltage level)
        delay(250);                     // wait for a second
        digitalWrite(LED_BUILTIN, HIGH);   // turn the LED off by making the voltage LOW
        delay(250);
      }
    }

    if(accMag > maxAccMag) {
      maxAccMag = accMag;
    }

    M5.Lcd.setCursor(0, 20);
    M5.Lcd.printf(" %5.2f   %5.2f   %5.2f G\n\n\n\n", accX, accY, accZ);
    M5.Lcd.setCursor(170, 50);

    M5.Lcd.print("G");
    M5.Lcd.println(maxAccMag);
}
