#include <WiFi.h>
#include "MPU9250.h"

#define IMU_ADDR 0x68
#define LED 2

const char *ssid = "yourssid";
const char *password = "yourpasswd";

NetworkServer server(80);

MPU9250 mpu;

void calibrateIMU(bool);
void startWifiServer(void);

void setup() {
  Serial.begin(115200);
  startWifiServer();

}

void loop() {
  
}


void startWifiServer(void) {
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  server.begin();
}


void calibrateIMU(bool verbose=true) {
  if (!mpu.setup(IMU_ADDR)) {
    while (1) {
        Serial.println("MPU connection failed.");
        delay(5000);
    }
  }
  digitalWrite(LED,HIGH);
  if(verbose) {
    mpu.verbose(true);
    Serial.println("Accel Gyro calibration will start in 5sec.");
    Serial.println("Please leave the device still on a flat plane.");
  }
  
  delay(5000);
  mpu.calibrateAccelGyro();
  
  if(verbose) {
    Serial.println("Mag calibration will start in 5sec.");
    Serial.println("Please Wave device in a figure eight until done.");
  }

  delay(5000);
  mpu.calibrateMag();

  mpu.verbose(false);
  digitalWrite(LED,LOW);
}
