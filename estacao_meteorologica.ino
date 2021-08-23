#include <ArduinoJson.h>
const int TAMANHO = 200;

int x=0;
int lastx=0;
int lasty=60;
const int sensorLuz  = A0;
const int sensorTemp = A1;
float rLdr = 0;
float l = 0;
const float elevado = 1/0.71;
const int rDark = 127410;
const float r = 10000.0;
const int vcc = 5;
float vout = 0;
float adc = 0;
int radius = 147;  // Raio do anemometro
const float pi = 3.14159265;
int period = 1000;

//Variáveis
int valorSensorLuz  = 0;
int valorSensorLuzTeste  = 0;
int resistenciaLdr = 0;
int valorSensorTemp = 0;
int menorValorTemp  = 9999999;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf, temp, templast, luxlast;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07; //valores constante para calculo
volatile unsigned long cont = 0;
unsigned long tempo = 0;
float speedwind = 0;
unsigned int RPM = 0;

void setup(){
	pinMode(sensorTemp, INPUT);
	Serial.begin(115200);
	pinMode(2,INPUT_PULLUP);   //  Configura o pino 2 do arduino como entrada com resistor de pullup interno (assim não precisa mais colocar o resistor no pino)
	attachInterrupt(digitalPinToInterrupt(2),interrupcaoPino2,RISING);  //  Configura o pino2 como interrupção externa do tipo Rising (borda de LOW para HIGH)
}

void loop() {

	StaticJsonDocument<TAMANHO> json;

  	resistenciaLdr  = map(analogRead(A0),54,974,10000,0);
	valorSensorLuzTeste = analogRead(A0);
	  
	float tensaoTemp = analogRead(A1)*5.0/1023;
	float temp = round((tensaoTemp-.5)*100);
	vout = analogRead(A0)*5.0/1023;
	rLdr = (r/(vcc/vout)-1);
	l = pow(127410/rLdr,elevado);
	temp = readTemp(sensorTemp);
	printTemp(temp);
	
	json["topic1"] = "lux";
	json["payload1"] = l;
	json["topic2"] = "temp";
	json["payload2"] = temp;
	serializeJson(json, Serial);
	
	// Validação de interrupção para o frequencimetro
	if( (millis() - tempo) > period) {
		tempo = millis();
		Serial.print("Hertz: ");
		Serial.println(cont);
		RPMcalc();
		velocidadeVento();
		cont = 0;
	}
}

//funcão de interrupção do pino2, é executado quando o botao do pino2 pressionado
void interrupcaoPino2(){
  	cont++;
}

// Calcular RPM (rotações por minuto)
void RPMcalc(){
	RPM=((cont)*60)/(period/1000);  
}

//função que calcula a velocidade do vento em km/h
void velocidadeVento(){
	speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;
	Serial.print("KM/H: ");
	Serial.println(speedwind);
}

//função que faz leitura da temperatura e retorna o valor em graus celcius
float readTemp(int ThermistorPin){
 	 Vo = analogRead(ThermistorPin);
	 R2 = R1 * (1023.0 / (float)Vo - 1.0); //calculo R2, demonstração no arquivo pdf da aula
	 logR2 = log(R2);
	 T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));// Equação de Steinhart–Hart 
	 Tc = T - 273.15; //temp em Graus celcius
	 //Tf = (Tc * 9.0)/ 5.0 + 32.0; // temp em fahrenheit
	 return Tc;
}

//função que printa o valor da temperatura na serial
void printTemp(float Tc){
	Serial.print("Temperatura: ");
	Serial.print(Tc);
	Serial.println(" C");   
}

