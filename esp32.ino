
#include <OneWire.h>
#include <DallasTemperature.h>

const int rele = 23;
const int sensor = 21;

OneWire oneWire(sensor);
DallasTemperature sensors(&oneWire);

unsigned long t_antes = 0;
bool estado_rele = false;

void setup() {
  Serial.begin(115200);

  pinMode(rele, OUTPUT);
  digitalWrite(rele, LOW);

  sensors.begin();
}

void loop() {
  unsigned long t_atual = millis();

  if (t_atual - t_antes >= 3000) {
    t_antes = t_atual;

    estado_rele = !estado_rele;
    digitalWrite(rele, estado_rele);

    if (estado_rele) {
      Serial.println("rele on");
    } else {
      Serial.println("rele off");
    }
  }

  sensors.requestTemperatures();
  float temp = sensors.getTempCByIndex(0);

  if (temp == DEVICE_DISCONNECTED_C) {
    Serial.println("Sensor desconectado!");
  } else {
    Serial.print("Temp = ");
    Serial.print(temp);
    Serial.println(" °C");
  }

  delay(1000);
}
