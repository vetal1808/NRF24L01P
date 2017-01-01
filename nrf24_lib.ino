#include "nrf24.h"

uint64_t timee = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  nRF24L01_HW_Init();
  print_all();

  nRF24L01_setPALevel(RF24_250KBPS);
  nRF24L01_setChannel(120);
  nRF24L01_set_reading_pipe(0, 0xF0F1F2F3F4LL);
  print_all();
  nRF24L01_RX_mode();
  print_all();
}

void loop() {
  
  if(nRF24L01_available(0)){
    uint8_t tmp[32];
    nRF24L01_read_payload(tmp, 32);
    for(byte i = 0; i < 32; i++){
      Serial.print(tmp[i]);
      Serial.print("\t");
    }
    Serial.println("\n");
  }
  if(millis()-timee > 1000){
    timee = millis();
    Serial.println(nRF24L01_get_status(), HEX);
  }

}
void print_all()
{
    for(int i = 0; i < 32; i++){
      uint8_t tmp;
      nRF24L01_Read_Regs(i, &tmp, 1);
      Serial.print(tmp, HEX);
      Serial.print("\t");  
    }
    Serial.println();
}

