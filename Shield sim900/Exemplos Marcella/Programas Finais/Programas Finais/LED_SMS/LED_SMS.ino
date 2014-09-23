#include <SoftwareSerial.h>
#include "SIM900.h"
#include "sms.h"

SMSGSM sms;

char number[20];
char message[180];
char pos;
char *p, *g;
char security[] = "Houve Uma Tentativa de Acesso Nao Autorizado - Veja o Log";
int error;

void setup()
{
 pinMode(13,OUTPUT);
 Serial.begin(9600);
 
 if (gsm.begin(9600))
   Serial.println("\nStatus = PRONTO");
   else Serial.println("\nStatus = ESPERA");
   
 sms.DeleteSMS(SMS_ALL);
}
 
void loop()
{
 
 pos = sms.IsSMSPresent(SMS_UNREAD);
 Serial.println("Aguardando Comando...");
 
 if((int)pos>0){
   if(GETSMS_AUTH_SMS == sms.GetAuthorizedSMS((int)pos, number, message, 50, 1, 3)){
   
   Serial.print("NOVA MENSAGEM AUTORIZADA, POS=");
   
   Serial.print((int)pos);
   
   message[0]='\0';
   
   sms.GetSMS((int)pos,number,message,180);

   p=strstr(message,"On");
   g=strstr(message,"Off");
   
   if(p){
     Serial.println(" - Led On");
     digitalWrite(13,HIGH);}
     
   if(g){
     Serial.println(" - Led off");
     digitalWrite(13,LOW);}
   
   if(!g && !p){
     Serial.println(" - Mensagem Error");}
 
 sms.DeleteSMS(SMS_ALL);

 }else {
  Serial.print("NOVA MENSAGEM NAO AUTORIZADA, POS=");
  Serial.println((int)pos);
  Serial.print("ENVIANDO MENSAGEM DE SEGURANCA PARA: ");
  Serial.println("+556191942518");
  error=sms.SendSMS("+556191942518", security);
    if (error==0){
       Serial.println("SMS NAO ENVIADO");}
       else{
       Serial.println("SMS ENVIADO");}
  sms.DeleteSMS(SMS_ALL);
 }}
 delay(7000);
}
