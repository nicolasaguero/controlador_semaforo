//Se pueden sustituir 3 entradas digitales por una analogica con distintos niveles de tension para cada boton
//Se puede usar VirtualSerial para leer lo de Raspberry (por si se quiere usar la nano)
//Se puede usar el display por i2c

#include  <LiquidCrystal.h>

#define led_test 34
#define rele 38
#define aceptar 51
#define escape 50
#define funcion 49


//RS E D4 D5 D6 D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const byte numMenuP = 5;
const byte numMaxSubM = 4;
const byte numBttn = 3;

byte buttn[numBttn]={aceptar, escape, funcion};

String menuP[numMenuP]={
  "Item 1",
  "Item 2",
  "Item 3",
  "Item 4",
  "Item 5"
};

String subM[numMenuP][numMaxSubM]={
      // 0 - 1 - 2 - 3 :: Y
  {"Sub item 1.1","Sub item 1.2","Sub item 1.3","Sub item 1.4"}, //0
  {"Sub item 2.1","Sub item 2.2","Sub item 2.3","Sub item 2.4"}, //1
  {"Sub item 3.1","Sub item 3.2","Sub item 3.3","Sub item 3.4"}, //2
  {"Sub item 4.1","Sub item 4.2","Sub item 4.3","Sub item 4.4"}, //3
  {"Sub item 5.1","Sub item 5.2","Sub item 5.3","Sub item 5.4"}  //4  :: X
};

int tecla = -1;
int teclaAnt = -1;
unsigned long tiempo;
int x = -1;
int y = 0;

void setup()
{
  Serial.begin(9600);
  //Configuracion de pines
  pinMode(led_test, OUTPUT);
  pinMode(rele, OUTPUT);
  for (int i = 0; i < numBttn; i++) {
    pinMode(buttn[i], INPUT);
  }

  //Configuracion de modulos
  
  lcd.begin(16, 2);
  
  msjBienvenida();
  tiempo = millis();
}


void loop(){

  if(millis() - tiempo > 5000){
    //lcd.noBlink();
    }

    tecla = getKey(buttn);

    if(tecla != teclaAnt){
      delay(50); //Eliminador de rebotes

    tecla = getKey(buttn);

    if(tecla != teclaAnt){
      tiempo = millis();
      teclaAnt = tecla;
      
      if(tecla>=0){
        //lcd.blink();
      }
      if(tecla==2){ //Aceptar
        x++;
        y=0;
        if(x > numMenuP -1) x = numMenuP-1;
      }

      if(tecla==0){ //Escape
        x--;
        if(x<0) x=0;
        y=0;//28:26
        Serial.println(x);
    }
    if(tecla==1){ //Funcion
      y++;
      if(y>numMaxSubM-1) y=numMaxSubM-1; //Creo que aca debo volver
    }

    lcd.clear();
    
    lcd.print(menuP[x]);
    lcd.setCursor(0,1);
    lcd.print(subM[x][y]);


}
}
delay(50);
}

void msjBienvenida(){
  
  lcd.setCursor(7, 0); 
  lcd.print("Sistema de control");
  lcd.setCursor(4, 1); 
  lcd.print("inteligente de transito");
  delay (1000);
  for(int i=0; i<=27; i++){
    lcd.scrollDisplayLeft();
    delay (500);
  }
  lcd.clear();
}


int getKey(byte args[]){
  int k;
  if(digitalRead(args[0])==HIGH){
    k=0;
  }else if(digitalRead(args[1])==HIGH){
    k=1;
  }else if(digitalRead(args[2])==HIGH){
    k=2;
  }else{
    k=-1;
  }
  return k;
}


 



