#include "nrf24.h"

uint64_t timee = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);
  nRF24L01_HW_Init();

  nRF24L01_powerUp();
  nRF24L01_begin();
  delay(2);
  nRF24L01_setPALevel(RF24_PA_HIGH);
  nRF24L01_setDataRate(RF24_250KBPS);
  nRF24L01_setChannel(120);
  nRF24L01_set_reading_pipe(1, 0xF0F1F2F3F4LL);
  nRF24L01_Standby_Mode();

  nRF24L01_RX_mode();
  print_all();
}

void loop() {
  
  if(nRF24L01_available(0)){
    uint8_t tmp[32];
    nRF24L01_read_payload(tmp, 32);

    Serial.print("Status = ");
    Serial.println(nRF24L01_get_status());
    for(byte i = 0; i < 32; i++){
      Serial.print(tmp[i]);
      Serial.print(" ");
    }
    Serial.println("\n");
    
  }



}
void print_all()
{

  uint8_t tmp[32];
  for(int i = 0; i < 32; i++){
    nRF24L01_Read_Regs(i, tmp+i, 1);
  }
    for(int i = 0; i < 32; i++){
   
      Serial.print(tmp[i], HEX);

      Serial.print("\t");  
    }
    Serial.println();
}

