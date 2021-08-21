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


void setup(){
	pinMode(sensorTemp, INPUT);
	Serial.begin(115200);
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
	}
	
	json["topic1"] = "lux";
	json["payload1"] = l;
	json["topic2"] = "temp";
	json["payload2"] = temp;
	serializeJson(json, Serial);
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