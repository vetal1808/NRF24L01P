#include "nrf24_low.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  nRF24L01_HW_Init();
  for(int i = 0; i < 32; i++){
    uint8_t tmp;
    nRF24L01_Read_Regs(i, &tmp, 1);
    Serial.println(tmp, HEX);  
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
