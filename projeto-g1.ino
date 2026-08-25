const int laserPin = 11;
int trig = 13;
int echo = 12;
int led = 10;
int buzzer = 2;
int button = 4;
int ldrPin = 0;
int ldrValor = 0;
boolean oculosLigado = false;

void setup() {
  pinMode(laserPin, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(button, INPUT);
  pinMode(ldrPin, INPUT);
}
void loop() {
  long duracao;
  long distancia;
  ldrValor = analogRead(ldrPin);
  //Serial.println(ldrValor);
  int estadoBotao = digitalRead(button);

  if (estadoBotao == HIGH){
    if (oculosLigado){
      oculosLigado = false;
      Serial.println("Desligado \n");
      delay(500);
    }else{
      oculosLigado = true;
      Serial.println("Ligado \n");
      delay(500);
    }
  }

  if (oculosLigado) {
    if (ldrValor >= 400) {
      digitalWrite(laserPin, HIGH);
      digitalWrite(led, HIGH);
      digitalWrite(trig, LOW);
      delayMicroseconds(2);
      digitalWrite(trig, HIGH);
      delayMicroseconds(10);
      digitalWrite(trig, LOW);
      duracao = pulseIn(echo, HIGH);
      distancia = duracao / 50;
      Serial.print(distancia);
      Serial.println(" cm");
      //delay(500);

      if (distancia > 80 && distancia < 100) {
        digitalWrite(buzzer, HIGH);
        digitalWrite(led, HIGH);
        delay(1000);
        digitalWrite(buzzer, LOW);
        digitalWrite(led, LOW);
        delay(1000);
      }
      if (distancia <= 80 && distancia >= 50) {
        digitalWrite(buzzer, HIGH);
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(buzzer, LOW);
        digitalWrite(led, LOW);
        delay(500);
      }
      if (distancia < 50) {
        digitalWrite(buzzer, HIGH);
        digitalWrite(led, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        digitalWrite(led, LOW);
        delay(50);
      }
    }else{
      digitalWrite(led, LOW);
      digitalWrite(laserPin, LOW);
      digitalWrite(buzzer, LOW);
    }
  }else{
    digitalWrite(led, LOW);
    digitalWrite(laserPin, LOW);
    digitalWrite(buzzer, LOW);
    //delay(1000);
  }
}