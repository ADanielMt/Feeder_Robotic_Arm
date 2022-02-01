
#include <Servo.h>             
int u=0;
int s=4;
//***** variables  *****
float Thethas[5];
float l2=12.0,l3=12.0,l4=14.0,za=0.0,phi=0*PI/180;
float xp=15,yp=13.5,zp=5;
//float xp=-1,yp=0,zp=38;
float r=0,xc=0,zc=0,r2=0,D=0;
float teta1=0,teta2=0,teta3=0,teta4=0,teta5=0;
int teta11_act=0,teta22_act=0,teta33_act=0,teta44_act=0,teta55_act=0;

int flags=0;

String xxpos, yypos, zzpos;
float xpos=0, ypos=0, zpos=0; 

float incoming[30];
int flag1=0, flag2=1;


//***** Servos *****
Servo servo1;                   
Servo servo2;                   
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

void angulos()
{
    
  
 //***  calculos
   r=sqrt((xp*xp)+(yp*yp));
   xc=r-l4*cos(phi);
   zc=zp-l4*sin(phi)-za;
   r2=sqrt(xc*xc+zc*zc);
   D=((r2*r2-l2*l2-l3*l3)/(2*l2*l3));
   
 //Calcular angulos
   teta1=atan(yp/xp);
   teta3=atan((sqrt(1-(D*D)))/D);
   teta2=atan(zc/xc)-atan((l3*sin(teta3))/(l2+l3*cos(teta3)));
   teta4=phi-(teta2+teta3);  
   teta5=0.0; 
   
//---- Convertir angulos grados
   teta1=teta1*(180/PI);   
   teta2=teta2*(180/PI);
   teta3=teta3*(180/PI);   
   teta4=teta4*(180/PI);   
   teta5=teta5*(180/PI); 
 //   Serial.println("....");
 //   Serial.println(teta1);
//    Serial.println(teta2);
//    Serial.println(teta3);
//    Serial.println(teta4);
//    Serial.println(teta5);
//    Serial.println("______");
      
//*****Suma Ofsset de motor
  teta1=teta1+90;
  teta3=teta3+90;
  teta4=teta4+90;
  teta5=teta5+90;
  
   verifica_posicion(xp,yp,zp);
}



void setup() {


  Serial.begin(9600);
  delay(2000);
    
   //d8,7,6,5,4,3,   
  servo3.attach(3) ;  // Conectar servo1 al pin 6     Base
  servo1.attach(4) ;  // Conectar servo2.1 al pin 8
  servo2.attach(5) ;  // Conectar servo2.2 al pin 7
  servo4.attach(6) ;  // Conectar servo3 al pin 5    Eslabon 2
  servo5.attach(7) ;  // Conectar servo4 al pin 4    Eslabon 3
  servo6.attach(8) ;  // Conectar servo5 al pin 3    Efector giratorio
    
  //Posiciona robot en el centro
  teta11_act=90;
  teta22_act=110;
  teta33_act=40;
  teta44_act=90;
  teta55_act=90;
  
}

void loop() 
{   

byte counter=0;

   while ((Serial.available ()> 0) && counter<2)
   {
       incoming [counter] = Serial.parseFloat();
       counter=counter+1;
       flag1=1;
   }

    if(flag1==1)
    {
      
     if(incoming[0]==1)
     {
 
   switch(u)
    {
       case(0):
      Serial.println("caso0");
            teta1=90.00;
            teta2=90;
            teta3=90;
            teta4=90;
            teta5=0;
            teta11_act=base(teta1,teta11_act);         //Genera movimiento base
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector            
            u=1;
      break;

      
      case(1):
      Serial.println("caso0");
            teta1=90.00;
            teta2=124.97;
            teta3=23.21;
            teta4=49.08;
            teta5=90.00;
            teta11_act=base(teta1,teta11_act);         //Genera movimiento base
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector            
            u=2;
      break;
      
      case(2):
      Serial.println("caso1");
            
            teta1=50.19;
            teta2=91.27;
            teta3=48.76;
            teta4=59.27;
            teta5=90.00;     
            teta11_act=base(teta1,teta11_act);         //Genera movimiento base
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector 
            u=3;
      break;      

      case(3):
      Serial.println("caso2");
            
            teta1=55;
            teta2=55;
            teta4=80;
            teta3=10;   

            teta1=correccion1(teta1);   //Corrige angulos
            teta2=correccion2(teta2);
            teta3=correccion3(teta3);
            teta4=correccion3(teta4); 
              
            teta11_act=base(teta1,teta11_act);         //Genera movimiento base
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2  
            u=4;                     
      break;  

      case(4):
            Serial.println("caso3");            
            teta2=45;
            teta4=75; 
            teta5=0;
                
            teta2=correccion2(teta2);    
            teta4=correccion3(teta4); 
                          
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            teta44_act=eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3               
            teta55_act=efector(teta5,teta55_act);     //Genera movimiento efector  
            delay(10);                 
            u=5;
      break;  


       case(5):
            Serial.println("caso4");
                        
            teta5=90;
            teta2=60;
            teta4=100;
            
            teta2=correccion2(teta2);
            teta4=correccion3(teta4); 

            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector                                   
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3     
            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector            
            u=6;         
      break; 

       case(6):
      Serial.println("caso5");

            teta1=131;
            teta2=70;
            teta3=55;
            teta4=70;
            teta5=90;

            teta11_act=base(teta1,teta11_act);         //Genera movimiento base
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector            
            u=7;
      break;

      case(7):
            Serial.println("caso6");

            teta1=138;
            teta4=90;
            teta3=15;           

            teta1=correccion1(teta1);   //Corrige angulos  
            teta4=correccion3(teta4);    
            teta3=correccion3(teta3);
   

            teta11_act=base(teta1,teta11_act);         //Genera movimiento base
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2                     
            u=8;
      break;


       case(8):
            Serial.println("caso6");

            teta4=110;
            teta2=45;           
            
            teta4=correccion3(teta4);    
            teta2=correccion2(teta2);

             
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            u=9;
      break;

      case(9):
            Serial.println("caso7");

            teta4=120;
            teta3=10;
                                              
            teta4=correccion3(teta4);    
            teta3=correccion3(teta3);
           
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2
            u=10;
      break;

      case(10):
            Serial.println("caso8");


            teta4=90;
            teta2=37;
            
                                              
            teta4=correccion3(teta4);    
            teta2=correccion2(teta2);
           
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            u=11;
      break;
      
      case(11):
            Serial.println("caso9");

            teta4=100;
            teta2=35;
            teta5=0;
                                                                   
            teta4=correccion3(teta4);    
            teta2=correccion2(teta2);
           
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3  
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares       
            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector     
            u=12;
      break;


      case(12):
            Serial.println("caso9");

            teta5=90;
            teta4=120;
            teta2=60;

            
            teta2=correccion2(teta2);            
            teta4=correccion3(teta4);    

            teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector  
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares                                                                            
            u=13;
      break;


      case(13):
            Serial.println("caso9");

            teta4=110;
            teta3=30;
                                
            teta4=correccion3(teta4);    
            teta3=correccion3(teta3);
            
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2                                                                       
            u=14;
      break;


      
      case(14):
            Serial.println("caso9");

            teta4=90;
            teta3=50;
                                
            teta4=correccion3(teta4);    
            teta3=correccion3(teta3);
            
            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3
            teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2                                                                       
            u=15;
      break;


      case(15):
            Serial.println("caso9");

            teta4=75;
            teta2=70;

            teta4=correccion3(teta4);    
            teta2=correccion2(teta2);

            teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3
            teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
            u=16;                                                                       
      break;

      case(16):
          Serial.println("caso9");
          teta4=65;
          teta1=90;
          teta4=correccion3(teta4);    
          teta1=correccion1(teta1);

          teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3
          teta11_act=base(teta1,teta11_act);         //Genera movimiento base
          u=17;                                                                                   
      break;
      
 }
     }
    }
    
/*        
   teta1=correccion1(teta1);   //Corrige angulos
   teta2=correccion2(teta2);
   teta3=correccion3(teta3);
   teta4=correccion3(teta4);    

   //Serial.println("teta act");
   teta11_act=base(teta1,teta11_act);         //Genera movimiento base
   //Serial.println(teta11_act);
   teta22_act=servos_pares(teta2,teta22_act); //Genera movimiento servos pares
   //Serial.println(teta22_act);
   teta33_act=eslabon2(teta3,teta33_act);     //Genera movimiento eslabon2
   //Serial.println(teta33_act);
   teta44_act= eslabon3(teta4,teta44_act);    //Genera movimiento eslabon3
   //Serial.println(teta44_act);
//   teta55_act= efector(teta5,teta55_act);     //Genera movimiento efector
*/
  
}

int servos_pares(float teta22,int teta2_act)
{
  int edes=(int)teta22;
  int e=teta2_act;
  int i;
  if(e!=edes)
  {
    
     if(e<edes)
     {  
         for(i=e; i<edes+1; i++)
         { 
             servo1.write(i);             
             delay (50);                     
             e=i;
             servo2.write(i);             
             delay (50);                     
         }
     }  
     if(e>edes)
     {
          for(i=e; i>edes-1; i--)
          {
             servo1.write(i);             
             delay (50);                     
             e=i;
             servo2.write(i);             
             delay (50);                     
          }
     }
     if(e==edes)
    {
          servo1.write(edes);
          servo2.write(edes);
          e=edes;
   }
  }
  return e;
 }

int base (float teta11,int teta1_act)
{
   int ades=(int)teta11;
   int a=teta1_act;
   int i;
  
   if(a!=ades)
  {    
    if(a<ades)
    {  
      for(i=a; i<ades+1; i++)
      {
        servo3.write(i);            
        delay (50);
         a=i;
      }
    }
    if(a>ades)
    {
      for(i=a; i>ades-1; i--)
      {
        servo3.write(i);        
        delay (50);
        a=i;
      }
    }
    if(a==ades)
    {
      servo3.write(ades);
      a=ades;
    }
  }  
  return a;
}


int eslabon2 (float teta33, int teta3_act)
{
   int bdes=(int)teta33;
   int b=teta3_act;
   int i;
   
  if(b!=bdes)
  {   
    if(b<bdes)
    {  
      for(i=b; i<bdes+1; i++)
      {
        servo4.write(i);          
        delay (50); 
        b=i;
      }
    } 
  if(b>bdes)
  {
    for(i=b; i>bdes-1; i--)
    {
      servo4.write(i);           
      delay (50); 
      b=i;
    }
  }
  if(b==bdes)
  {
    servo4.write(bdes);
    b=bdes;
  }
 }   
 return b;
}

int eslabon3 (float teta44,int teta4_act)
{
   int cdes=(int)teta44;
   int c=teta4_act;
   int i;     
  if(c!=cdes)
  {   
    if(c<cdes)
    {
      for(i=c; i<cdes+1; i++)
      {
        servo5.write(i);            
        delay (50);
        c=i;
      }
    } 
    if(c>cdes)
     {
       for(i=c; i>cdes-1; i--)
      {
        servo5.write(i);   
        delay (50);
        c=i;
      }
     }
    if(c==cdes)
    {
      servo5.write(cdes);
      c=cdes;
    }
  } 
  flags=1;
  return c; 
}

int efector (float teta55,int teta5_act)
{
   int ddes=(int)teta55;
   int d=teta5_act;
   int i;

   servo6.write(90);
   d=ddes; 
   return d;
}


float correccion1 (float a)
{
  float aa;
  
     if(a>=0&&a<=40)
     {
      aa=20+(0.5*a);
     }  
     else if(a>=160&&a<=180)
     {
      aa=160-(0.6*(160-a));
     }
     else
     {
      aa=a;
     }
     return aa;
}

float correccion2 (float a)
{
  float aa;
  
    if(a>=0&&a<=25)
     {
      aa=(a*0.8)+22;
     }
     else if(a>=26&&a<=50)
     {
      aa=((a-25)*0.8)+42;
     }
     else if(a>=51&&a<=82)
     {
      aa=a+12;
     }
     else if(a>=83&&a<=100)
     {
      aa=a+6;
     }
     else if(a>=101&&a<=115)
     {
      aa=106+(0.6*(a-100));
     }
     else if(a>=160&&a<=180)
     {
      aa=160-(0.7*(160-a));
     }
     else
     {
      aa=a;
     }   
     return aa;
}


float correccion3(float a)
{
  float aa;
  
  if(a>=0 && a<=15)
     {
      aa=(a*0.66)+15;
     }  
  else if(a>=16 && a<=25)
     {
      aa=a+10;
     }
  else if(a>=25&&a<=50)
     {
      aa=((a-25)*0.8)+35;
     }
  else if(a>=51&&a<=60)
     {
      aa=(0.5*(a-10))+35;
     }

   else if(a>=160&&a<=180)
     {
      aa=170-(0.5*(180-a));
     }
     else
     {
      aa=a;
     }
  return aa;
}
////-01.00 000.00 038.00
void verifica_posicion(float x,float y,float z)
{  float x1,y1,z1;
    x1=(float)x;
    y1=(float)y;
    z1=(float)z;
 // Serial.println("Revisar Cond especial");
 // Serial.println(x1);
 // Serial.println(y);
 // Serial.println(z1);
    
  if(z1==38.00)
  {
 //  Serial.println("Hola mundo"); 
    if (y1==0.00)
    {
     // Serial.println("Que ondi");   
       if(x1<0&&x1>-2)
      {
        //Serial.println("u.u");      
      teta1=0;
      teta2=90;
      teta3=0;
      teta4=0;
      teta5=0;

      teta1=teta1+90;
      teta3=teta3+90;   
      teta4=teta4+90;   
      teta5=teta5+90;
      }      
    }
  }  

  if(x1>36.00 && x1<38.00 && y1==00.00 && z==00.00)
  //if (x1==37.00 && y1==00.00 && z==00.00)  
  {
 //    Serial.println("si entró"); 
      teta1=0;
      teta2=0;
      teta3=0;
      teta4=0;
      teta5=0;    
      
      teta1=teta1+90;
      teta3=teta3+90;   
      teta4=teta4+90;   
      teta5=teta5+90;
   }
   if (x==0&&y==0)
  {
    teta1=0;
    teta1=teta1+90;
  }
}






