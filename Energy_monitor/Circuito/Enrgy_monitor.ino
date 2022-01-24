  ////////////////////////////////////////////////////////////////////
////////////////////// INCLUSÃO DE BIBLIOTECAS /////////////////////
////////////////////////////////////////////////////////////////////
//
#include <LiquidCrystal.h>                                        //ADICIONA A BIBLIOTECA PARA UTILIZAR DISPLAY LCD
#include <FirebaseESP32.h>                                        //ADICIONA BIBLIOTECA PARA COMUNICAÇÃO DO ESP32 COM O BANCO DE DADOS
#include <WiFi.h>                                                 //ADICIONA A BIBLIOTECA PARA UTILIZAÇÃO DO WIFI
//
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
/////////////// definição e declaração de variáveis ////////////////
////////////////////////////////////////////////////////////////////
//
#define FIREBASE_HOST "https://laranjas-bc5c5.firebaseio.com/"    //DEFINE UM NOME PARA O ENDEREÇO WEB
#define FIREBASE_AUTH "IENh1JdMwgMHM1azCSsznV97GHgb1l34nJ0ZAyp1"  //DEFINE UM NOME PARA A CHAVE DE AUTENTICAÇÃO DO BANDO DE DADOS
#define WIFI_SSID "TROIA"                                         //DEFINE UM NOME PARA O NOME DO WIFI QUE SERÁ SOLICITADO
#define WIFI_PASSWORD "ASUSFURGRICO"                               //DEFINE UM NOME PARA A SENHA DO WIFI QUE SERÁ SOLICITADO
FirebaseData firebaseData;                                        //INICIALIZA O BANCO DE DADOS
int sensorPin = 36;                                               //DECLARA UMA VARIÁVEL COM O NÚMERO DA ENTRADA ANALÓGICA
float x = 0, y = 0, z = 0, a = 0.0, xx = 0, yy = 0, zz = 0, cont = 0; //DECLARAÇÃO DE VARIÁVEIS
float ptc = 0, t = 0, ti = 0, tf = 0, acum = 0;                   //DECLARAÇÃO DE VARIÁVEIS
float vlr = 0, svt = 0, vlrt = 0, tt = 0, vlrtt = 0;              //DECLARAÇÃO DE VARIÁVEIS
float sv = 0, svm = 0, med = 0;                                                     //DECLARAÇÃO DE VARIÁVEIS
const int rs = 22, en = 23, d4 = 5, d5 = 18, d6 = 19, d7 = 21;    //DECLARAÇÃO DE VARIÁVEIS
//
////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////
////////// INICIALIZAÇÃO DOS MÓDULOS E VALORES /////////////////////
////////////////////////////////////////////////////////////////////
//
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                        //DEFINE OS PINOS PARA UTILIZAÇÃO DO DISPLAY LCD
//
void setup() {                                                    //FUNÇÃO PRINCIPAL
  pinMode(sensorPin, INPUT);                                      //DEFINE A PORTA 36 COMO ENTRADA
  Serial.begin(9600);                                             //INICIALIZA A COMUNICAÇÃO SERIAL
  //
  ////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////
  ///////ALGORÍTMO QUE DITA O FUNCIONAMENTO DO DISPOSITIVO////////////
  ////////////////////////////////////////////////////////////////////
  //
  Serial.print("A ligar a: ");                                      //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
  Serial.println(WIFI_SSID);                                      //ESCREVE NO SERIAL O NOME DO WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                           //ESCREVE NO SERIAL A SENHA DO WIFI
  while (WiFi.status() != WL_CONNECTED) {                         //VERIFICA SE O WIFI ESTÁ CONECTADO
    delay(500);                                                   //ESPERA 500 MILISEGUNDOS
    Serial.print(".");                                            //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
  }                                                               //
  Serial.println("");                                               //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
  Serial.println("Ligado");                                       //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
  Serial.println("IP address: ");                                 //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
  Serial.println(WiFi.localIP());                                 //ESCREVE NO SERIAL, O ENDEREÇO DE IP
  //
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                   //INICIALIZA O FIREBASE
  //
  //////////////////////////////////////////////////////////////////
  //
  lcd.begin(16, 2);                                               //INICIALIZA O DISPLAY LCD COM (COLUNA, LINHA)
  lcd.clear();                                                    //LIMPA O DISPLAY LCD
  lcd.setCursor(0, 0);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print("  FURG E TOP!   ");                                  //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  lcd.setCursor(0, 1);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print("INICIALIZANDO ... ");                                    //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  delay(1000);                                                    //AGUARDA 1 SEGUNDO
  lcd.clear();                                                    //LIMPA O DISPLAY LCD
  lcd.setCursor(0, 0);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print(" NÃO CONECTE ");                                     //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  lcd.setCursor(0, 1);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print("    O SENSOR    ");                                  //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  /*while (x < 900) {                                               //COMPARA OS VALORES PARA CONTINUAR OU NÃO O LOOP
    sv = analogRead(sensorPin);                                   //RECEBE NA VARIÁVEL O VALOR LIDO NA ENTRADA ANALÓGICA
    //Serial.print("\nvalor em bit: ");                           //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
    //Serial.println(sv);                                         //ESCREVE NO SERIAL O VALOR DA VARIÁVEL
    //Serial.print("\n");                                         //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
    x = x + 1;                                                    //INCRMENTADOR PARA COMPARAÇÃO DO LOOP
    sv = sv - 1917;                                               //ZERA O VALOR EM BITs PARA O CASO EM QUE O SENSOR NÃO ESTÁ LENDO NADA.
    y = (sv) * (sv);                                              //TIRA O NEGATIVO DO VALOR EM BITs, NO MOMENTOS QUE O VALOR DÁ NEGATIVO
    a = a + y;                                                    //SOMATÓRIO DO QUADRADO DOS VALORES RECEBIDOS
    delayMicroseconds(55);                                       //AGUARDA 55 MICROSEGUNDOS
  }
  med = y / 900;
  Serial.print("setado: ");
  Serial.println(med);
  x = 0;                                                          //ZERA O VALOR DA VARIÁVEL
  y = 0;                                                          //ZERA O VALOR DA VARIÁVEL
  z = 0;*/                                                          //ZERA O VALOR DA VARIÁVEL
  delay(1000);                                                    //AGUARDA 1 SEGUNDO
  lcd.clear();                                                    //LIMPA O DISPLAY LCD
  lcd.setCursor(0, 0);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print(" TUDO PRONTO !! ");                                  //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  lcd.setCursor(0, 1);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print(" VALORES SETADOS ");                                 //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  delay(1000);                                                    //AGUARDA 1 SEGUNDO
}                                                                 //
                                                                  //
void loop() {                                                     //FUNÇÃO INFINITA EXECUTADA ENQUANTO O MICROCONTROLADOR ESTIVER ENERGIZADO
  float p = 0, corrente = 0, c, valor;                                   //DECLARAÇÃO DE VARIÁVEIS
  ti = millis();                                                  //SALVA NA VARIÁVEL O TEMPO EM QUE O ARDUINO ESTÁ LIGADO NESTE INSTANTE
  while (x < 300) {                                               //COMPARA OS VALORES PARA CONTINUAR OU NÃO O LOOP
    sv = analogRead(sensorPin);                                   //RECEBE NA VARIÁVEL O VALOR LIDO NA ENTRADA ANALÓGICA
    //Serial.print("\nvalor em bit: ");                           //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
    //Serial.println(sv);                                         //ESCREVE NO SERIAL O VALOR DA VARIÁVEL
    //Serial.print("\n");                                         //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
    x = x + 1;                                                    //INCRMENTADOR PARA COMPARAÇÃO DO LOOP
    sv = sv - 1917;                                               //ZERA O VALOR EM BITs PARA O CASO EM QUE O SENSOR NÃO ESTÁ LENDO NADA.
    y = (sv) * (sv);                                              //TIRA O NEGATIVO DO VALOR EM BITs, NO MOMENTOS QUE O VALOR DÁ NEGATIVO
    a = a + y;                                                    //SOMATÓRIO DO QUADRADO DOS VALORES RECEBIDOS
    delayMicroseconds(55.56);                 //AGUARDA 55 MICROSEGUNDOS
  }                                                               //
  z = (a / 300);                                                  //DIVIDE O VALOR SOMADO PELO NUMERO DE AMOSTRAS(FINALIZA A MÉDIA )
  sv = sqrt(z);                                                   //TIRA A RAÍZ DO VALOR DA MÉDIA (PARA FINALIZAR O VALOR EM RMS)
  Serial.println(sv);                                             //
  if (sv < 20) {                                                  //COMPARA O VALOR EM RMS PARA ELIMINAR O RUÍDO DO MICROCONTROLADOR
    sv = 0;                                                       //ZERA O VALOR DA VARIÁVEL
  }                                                               //
  else {                                                          //SEGUNDO PLANO DA COMPARAÇÃO ACIMA
    sv = sv * 0.01074;                                                 // TRANSFORMA O VALOR EM BITs PARA CORRENTE
  }                                                               //
  //Serial.println(sv,8);                                         //ESCREVE NO SERIAL, O VALOR DA VARIÁVEL COM 8 CASAS APÓS A VÍRGULA E DEPOIS PULA PARA PÓRXIMA LINHA
  //Serial.println("\n\n");                                       //ESCREVE NA SERIAL, DOIS ENTER
                                                                  //
  x = 0;                                                          //ZERA O VALOR DA VARIÁVEL
                                                                  //
  lcd.clear();                                                    //LIMPA O DISPLAY LCD
  lcd.setCursor(0, 0);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print("Custo: ");                                           //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  lcd.setCursor(7, 0);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print(vlrt, 4);                                             //ESCREVE NO DISPLAY, O VALOR DA VARIÁVEL COM 4 DIGITOS APÓS A VIRGULA
  lcd.print(" R$");                                               //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES  
  lcd.setCursor(0, 1);                                            //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print("Corrente:");                                         //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  lcd.print(svt, 3);                                              //ESCREVE NO DISPLAY, O VALOR DA VARIÁVEL COM 3 DIGITOS APÓS A VIRGULA
  lcd.setCursor(14, 1);                                           //SETA O CURSOR NA POSIÇÃO(COLUNA, LINHA)
  lcd.print(" A");                                                //ESCREVE NO DISPLAY LCD O QUE ESTA ENTRE PARÊNTESES
  delay(970);                                                     //AGUARDA 970 MILISEGUNDOS
  a = 0;                                                          //ZERA A VARIÁVEL
  z = 0;                                                          //ZERA A VARIÁVEL
  y = 0;                                                          //ZERA A VARIÁVEL
                                                                  //
  tf = millis();                                                  //SALVA NA VARIÁVEL O TEMPO EM QUE O ARDUINO ESTÁ LIGADO NESTE INSTANTE
  t = tf - ti;                                                    //OBTÉM O TEMPO GASTO PARA EXECUÇÃO DO CÓDIGO
  tt = (t / 1000);                                                //TRANSFORMA MILISEGUNDOS PARA SEGUNDOS
  svt = sv;// / 7,42857;                                                   //CÁCULO DE CALIBRAÇÃO
  //Serial.print("corrente: ");                                   //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
  //Serial.println(svt, 10);                                      //ESCREVE NA SERIAL, O VALOR DA VARIÁVEL
  //Serial.print("Custo: ");                                      //ESCREVE NO SERIAL A FRASE ENTRE ASPAS
  //Serial.println(vlrt, 4);                                      //ESCREVE NA SERIAL, O VALOR DA VARIÁVEL
  ptc = (svt * 127.0) / 1000.0;                                   //CALCULA A POTENCIA EM KILOWATTS
  ptc = (ptc * (t / 1000.0)) / 3600.0;                            //CALCULA O KILOWATTS HORA
  vlr = 0.49 * ptc;                                               //REALIZA O CÁCULO DO VALOR GASTO POR KW/h
  vlrt = vlrt + vlr;                                              //SOMATÓRIO DOS VALORES A SE PAGAR POR KW/h
                                                                  //
  p = p + ptc;                                                    //SALVA EM UMA VARIÁVEL O VALOR DE OUTRA VARIÁVEL
  c = vlrt;                                                        //SALVA EM UMA VARIÁVEL O VALOR DE OUTRA VARIÁVEL
  corrente = svt;                                                 //SALVA EM UMA VARIÁVEL O VALOR DE OUTRA VARIÁVEL
  valor = valor + (vlr * 240);                                    //SALVA EM UMA VARIÁVEL O VALOR DE OUTRA VARIÁVEL
  Firebase.setFloat (firebaseData, "laranjas/consumo", c);        // envia para o servidor
  Firebase.setFloat (firebaseData, "laranjas/potencia", p);       //envia para o servidor
  Firebase.setFloat (firebaseData, "laranjas/corrente", corrente);// envia para o servidor
  Firebase.setFloat (firebaseData, "laranjas/prev_valor", valor); // envia para o servidor
}
