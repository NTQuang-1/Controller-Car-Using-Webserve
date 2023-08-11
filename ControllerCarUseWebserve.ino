#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#define ENA   5
#define ENB   12
#define IN1   4
#define IN2   0
#define IN3   2
#define IN4   14

int minRange = 312;
int maxRange = 712;
int tocdoxe = 800;

MDNSResponder mdns;

ESP8266WebServer server(80);

String webPage =
{
  //code html
"<!DOCTYPE html>"
"<html lang='vi'>"
"<head>"
"    <title>My Controller</title>"
"    <meta http-equiv='Content-Type' content='text/html; charset=utf-8'>"
"    <meta name='viewport' content='width=device-width, initial-scale=1'>"
"    <style>"
"        * {"
"            margin: 0;"
"            padding: 0;"
"        }"
"        html {"
"            font-family: Arial, Helvetica, sans-serif;"
"            background-color: #CCFF99;"
"        }"
"        .equalrightleft {"
"            margin-left: auto;"
"            margin-right: auto;"
"        }"
"        .shadow {"
"            box-shadow: 0 0 10px rgba(0, 0, 0, 0.5);"
"        }"
"        .button-control {"
"            height: 50px;"
"            float:left;"
"            line-height: 50px;"
"            text-align:center;"
"            border-radius: 20px;"
"        }"
"        #main {"
"            width: 800px;"
"        }"
"        #main h2 {"
"            margin-left: 130px;"
"            margin-bottom: 20px;"
"        }"
"        #main a {"
"            text-decoration: none;"
"        }"
"        h1,table {"
"            text-align: center;"
"            margin-top: 30px;"
"            margin-bottom: 20px;"
"        }"
"        table {"
"            border: 1px groove #ffffff;"
"            background-color:#70AD47;"
"        }"
"        th {"
"            background-color:#00B050;"
"            color:#ffffff;"
"            border: 3px outset #00B050;"
"            padding:10px;"
"        }"
"        td {"
"            border: 3px outset #ffffff;"
"            padding:10px;"
"            background: #ffffff;"
"        }"
"        tr {"
"            text-align: center;"
"        }"
"        .name {"
"            text-align: left;"
"        }"
"        .table-control {"
"            width: 300px;"
"            height:250px;"
"            margin-bottom: 48px;"
"            background: #00B050;"
"            border-radius: 20px;"
"            border: 5px groove #00B050;"
"        }"
"        #main .tien {"
"            position: relative;"
"            top:10px;"
"            left: 117px;"
"        }"
"        #main .phai {"
"        position: relative;"
"        top: 88px;"
"        left: 140px;"
"        }"
"        #main .lui {"
"            position: relative;"
"            top: 175px;"
"            right: 30px;"
"        }"
"        #main .trai {"
"            position: relative;"
"            top: 90px;"
"            right: 210px;"
"        }"
"        #main .dung {"
"            position: relative;"
"            top: 20px;"
"            left: 100px;"
"        }"
"        #button {"
"            padding: 7px 15px;"
"            background: #FFFF00;"
"            border-radius: 40px;"
"            border:4px outset  #ffffff;"
"        }"
"        #lui, #tien {"
"            padding: 5px 24px;"
"            background: #FFFF00;"
"            border-radius: 40px;"
"            border: 4px inset #ffffff;"
"        }"
"        #dung {"
"            padding: 5px 24px;"
"            border-radius: 40px;"
"            border: 4px inset #ffffff;"
"            background:#FF0000;"
"        }"
"        #button:active, #lui:active, #tien:active, #dung:active  {"
"            background-color: orange;"
"        }"
"        span {"
"            font-size: 35px;"
"            color: black;"
"        }"
"    </style>"
"</head>"
"<body>"
"    <div id='main' class='equalrightleft'>"
"        <h1>Đề tài : Robot điều khiển từ xa</h1>"
"        <table class='equalrightleft'>"
"            <thead>"
"                <th>STT</th>"
"                <th>Lớp</th>"
"                <th>MÃ SINH VIÊN</th>"
"                <th>TÊN SINH VIÊN</th>"
"            </thead>"
"            <tbody>"
"                <tr>"
"                    <td>1</td>"
"                    <td>DT3A</td>"
"                    <td>DT030115</td>"
"                    <td class='name'>BÙI HỒNG HẠNH</td>"
"                </tr>"
"                <tr>"
"                    <td>2</td>"
"                    <td>DT3A</td>"
"                    <td>DT030142</td>"
"                    <td class='name'> HOÀNG NGỌC ĐOAN TRANG</td>"
"                </tr>"
"                <tr>"
"                    <td>3</td>"
"                    <td>DT3A</td>"
"                    <td>DT030134</td>"
"                    <td class='name'>NGUYỄN THÀNH QUANG</td>"
"                </tr>"
"            </tbody>"
"        </table>"
"            <h2>TABLE CONTROL</h2>"
"            <div class='table-control equalrightleft'>"
"                <div id='tien' class='button-control tien'><a href='/tien'><span>&#x21E7;</span></a></div>"
"                <div id='button' class='button-control phai'><a href='/phai'><span>&#x21E8;</span></a></div>"
"                <div id='lui' class='button-control lui'><a href='/lui'><span>&#x21E9;</span></a></div>"
"                <div id='button' class='button-control trai'><a href='/trai'><span>&#x21E6;</span></a></div>"
"                <div id='dung' class='button-control dung'><a href='/dung'><span>&#x1F6B3;</span></a></div>"
"            </div>"
"    </div>"
"</body>"
"</html>"
};

void TrangChu()
{
  server.send(200, "text/html", webPage);
}

void tien()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, tocdoxe+300);
  server.send(200, "text/html", webPage);
}

void lui()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, tocdoxe+300);
  server.send(200, "text/html", webPage);
}

void dung()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
  server.send(200, "text/html", webPage);
}

void retrai()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, tocdoxe);
  server.send(200, "text/html", webPage);
}

void rephai()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, tocdoxe);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, tocdoxe);
  server.send(200, "text/html", webPage);
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

  Serial.print("Connecting to ");
  WiFi.begin("NTQ", "uabcyekh");

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected"); 
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  if (mdns.begin("esp8266", WiFi.localIP()))
  Serial.println("MDNS responder started");

  server.on("/", TrangChu);
  server.on("/tien", tien);
  server.on("/phai", rephai);
  server.on("/lui", lui);
  server.on("/trai", retrai);
  server.on("/dung", dung);
  server.begin();
}

void loop()
{
  server.handleClient();
}