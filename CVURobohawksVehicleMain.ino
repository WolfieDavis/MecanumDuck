/**
 * @author Cailean Sorce
 * @date 1/10/2021
 * @brief Arduino vehicle example for CVU Robohawks. this runs on nodeMCU esp8266 dev board for wifi access
 */

// include the necessary files
#include <Servo.h>  //used to easily control the wheel servos
#include <EEPROM.h> //used to store the servo errors in EEPROM (flash) memoory, so that it can be saved through power down
#include <SparkFun_TB6612.h>
#include "CVURobohawksVehicleWifi.h" //contains the html + js and funcitons used to set up and interface with the
// wifi client that will be used to control the vehicle
#include "CaileanSorce_nodemcuESP8266_pinDefinitions.h" //contains the const ints used to convert the GPIO port names silkscreened on the
// dev board to the esp8266 GPIO numbers

// declare the variables/ objects
char wifiName[] = "MecanumDuck",   // the name of the wifi network that will be created
    wifiPassword[] = "quackquack"; // the password to join the wifi network. MUST BE >= 8 characters

// int joyLX, joyRX, joyRY;
float mLFinput, mLBinput, mRFinput, mRBinput;

CVURobohawksVehicleWiFi WiFiControl;

const int flashButton = 0; // the flash button on the nodemcu is on GPIO 0 (thats esp8266 GPIO 0, not D0)

const int mLFpwm = 15;
const int mLFin1 = 3;
const int mLFin2 = 1;
const int mLFoffset = 1; // side offset?? maybe?

const int mLBpwm = 5;
const int mLBin1 = 0;
const int mLBin2 = 2;
const int mLBoffset = 1; // side offset?? maybe?

const int mRFpwm = 12;
const int mRFin1 = 11;
const int mRFin2 = 7;
const int mRFoffset = -1; // side offset?? maybe?

const int mRBpwm = 4;
const int mRBin1 = 16;
const int mRBin2 = 5;
const int mRBoffset = -1; // side offset?? maybe?

const int STBYfront = 14;
const int STBYrear = 12;

Motor mLF = Motor(mLFin1, mLFin2, mLFpwm, mLFoffset, STBYfront);
Motor mLB = Motor(mLBin1, mLBin2, mLBpwm, mLBoffset, STBYfront);
Motor mRF = Motor(mRFin1, mRFin2, mRFpwm, mRFoffset, STBYrear);
Motor mRB = Motor(mRBin1, mRBin2, mRBpwm, mRBoffset, STBYrear);

void setup()
{
  Serial.begin(115200); // begin serial communication at 115200 baud rate

  // WiFiControl.setUpWiFi(wifiName, wifiPassword, 8, joyStickX, joyStickY, leftServoError, rightServoError, saveWheelError, runAutonomous); //set up the wifi stuff
  WiFiControl.setUpWiFi(wifiName, wifiPassword, 8, mLF, mLB, mRF, mRB); // set up the wifi stuff

  ESP.wdtDisable(); // disable the software watchdog timer. the hardware timer is still active (for 6 seconds)
}

void loop()
{
  ESP.wdtFeed(); // feed the watch dog timer. this should be done automatically, but call the funcion to avoid errors

  WiFiControl.refreshWiFi(); // get any new info from the wifi client

  MLF = map(mLFinput, -100, 100, -255, 255);
  MLB = map(mLBinput, -100, 100, -255, 255);
  MRF = map(mRFinput, -100, 100, -255, 255);
  MRB = map(mRBinput, -100, 100, -255, 255);

  if (Math.abs(mLFinput) == 0 && Math.abs(mRFinput) == 0 && Math.abs(mLFinput) == 0 && Math.abs(mLFinput) == 0)
  {
    mLF.brake();
    mLB.brake();
    mRF.brake();
    mRB.brake();
  }
  else
  {
    mLF.drive(MLF);
    mLB.drive(MLB);
    mRF.drive(MRF);
    mRB.drive(MRB);
  }
}