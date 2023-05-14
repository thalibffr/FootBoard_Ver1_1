/*******************************************************************************
  Copyright 2016 ROBOTIS CO., LTD.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*******************************************************************************/

#include <Dynamixel2Arduino.h>
#include "HX711.h"

#define DXL_SERIAL   Serial2
#define DEBUG_SERIAL Serial
const uint8_t DXL_DIR_PIN = 4;

HX711 cell1, cell2, cell3, cell4;


// Create a port object for DYNAMIXEL communication.
// The list of available classes is as follows.
// 1) DYNAMIXEL::SerialPortHandler     (HardwareSerial only)
//     -note: If you do not want to use half duplex communication, do not enter the second parameter.
// 2) DYNAMIXEL::USBSerialPortHandler  (Only USB port on each board)
DYNAMIXEL::SerialPortHandler dxl_port(DXL_SERIAL, DXL_DIR_PIN);

// Create a Slave object to communicate with the master.
const float DXL_PROTOCOL_VER_1_0 = 1.0;
const float DXL_PROTOCOL_VER_2_0 = 2.0;
const uint16_t DXL_MODEL_NUM = 0x0140; // Modify it to what you want.
DYNAMIXEL::Slave dxl(dxl_port, DXL_MODEL_NUM);

// Declare the address of the Slave control item you want
// to register and the variable (size is also important)
// to store its data.

//uint16_t ADDR_LCQ1 = 42;
//uint16_t ADDR_LCQ2 = 44;
//uint16_t ADDR_LCQ3 = 46;
//uint16_t ADDR_LCQ4 = 48;

uint16_t ADDR_SUM_LC = 50;

// note: 'int' is not supported because its size varies by system architecture.p
int q1;
int q2;
int q3;
int q4;

uint16_t s;

//This namespace is required to use Control table item names
using namespace ControlTableItem;

void setup() {
  // put your setup code here, to run once:
  DEBUG_SERIAL.begin(115200);
//  DEBUG_SERIAL.println("OKE");

  cell1.begin(18, 5);
  cell2.begin(27, 26);
  cell3.begin(32, 33);
  cell4.begin(14, 12);

  // Speed setting for communication (not necessary for USB)
  dxl_port.begin(1000000);

  dxl.setPortProtocolVersion(DXL_PROTOCOL_VER_1_0);
  dxl.setFirmwareVersion(1);
  dxl.setID(25);

  // Add control items.
  // Input the address(p1) and the variable(p2) to write/read the data as parameters.
//  dxl.addControlItem(ADDR_LCQ1, q1);
//  dxl.addControlItem(ADDR_LCQ2, q2);
//  dxl.addControlItem(ADDR_LCQ3, q3);
//  dxl.addControlItem(ADDR_LCQ4, q4);

  dxl.addControlItem(ADDR_SUM_LC, s);
}

void loop() {
  // put your main code here, to run repeatedly:

//   If there is a packet from the master, process it.
  if (dxl.processPacket() == false) {
    DEBUG_SERIAL.print("Last lib err code: ");
    DEBUG_SERIAL.print(dxl.getLastLibErrCode());
    DEBUG_SERIAL.print(", ");
    DEBUG_SERIAL.print("Last status packet err code: ");
    DEBUG_SERIAL.println(dxl.getLastStatusPacketError());
    DEBUG_SERIAL.println();
  }
  
  q1 = cell1.read()/400;
  q2 = 1400;
  q3 = 1400;
  q4 = 1400;

//  q1 = random(1200, 1400);
//  q2 = random(1000, 1200);
//  q3 = random(1000, 1200);
//  q4 = random(1000, 1200);
  
  s = (q1 + q2 + q3 + q4)/4;
  
//
    DEBUG_SERIAL.print(q1); DEBUG_SERIAL.print("\t"); //DEBUG_SERIAL.print(q2);  DEBUG_SERIAL.print("\t");
//  DEBUG_SERIAL.print(q3); DEBUG_SERIAL.print("\t"); DEBUG_SERIAL.print(q4);  DEBUG_SERIAL.print("\t");
//  DEBUG_SERIAL.print(s);  DEBUG_SERIAL.print("\t");
 DEBUG_SERIAL.println("");
}
