#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLGyenNgRm"
#define BLYNK_DEVICE_NAME "CONTROL"
#define BLYNK_AUTH_TOKEN "eUEeUuAyJv60ShYUWhKhzwNYb_4bChOk"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define ENA   5
#define ENB   12
#define IN1   4
#define IN2   0
#define IN3   2
#define IN4   14
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "NTQ";
char pass[] = "uabcyekh";
BlynkTimer timer;

int minRange = 312;
int maxRange = 712;
int tocdoxe = 800;

void tien()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, tocdoxe+300);
}

void lui()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, tocdoxe+300);
}

void dung()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void retrai()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, tocdoxe);
}

void rephai()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, tocdoxe);
}

BLYNK_WRITE (V7)
{
	//THẲNG
	if (param.asInt() == 1 )
	{
	tien();
	}else 
	{
	dung();
	}
}
BLYNK_WRITE (V8)
{
	//PHẢI
	if (param.asInt() == 1 )
	{
	rephai();
	}else 
	{
	dung();
	}
}
BLYNK_WRITE (V9)
{
	//LÙI
	if (param.asInt() == -1 )
	{
	lui();
	}else 
	{
	dung();
	}
}
BLYNK_WRITE (V10)
{
	//TRÁI
	if (param.asInt() == -1 )
	{
	retrai();
	}else 
	{
	dung();
	}
}

void setup()
{
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);

  digitalWrite(ENA, LOW);
  digitalWrite(ENB, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  Blynk.begin(auth, ssid, pass); //bắt đầu kết nối với wifi
}

void loop()
{
  Blynk.run();
  timer.run();
}