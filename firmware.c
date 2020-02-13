#include <htc.h>


#define s1 RA0
#define s2 RA1
#define s3 RA2
#define s4 RA3

void main(void)
 {
   unsigned int a,b,c,d,e,f,g,h; //just variables
   int i = 0;                    //the 4-digit value that is to be displayed
   int flagDelay = 0;            //for creating delay
    int flagStop = 0;
   TRISA = 0x00;
   PORTA = 0x00;
   TRISB = 0x00;
   PORTB = 0x00;
    char seg_code [] = { 0xc0 , 0xf9 , 0xa4 , 0xb0 , 0x99 , 0x92 , 0x82 , 0xf8 , 0x80 , 0x90 };
    
   while (1)
   {    
      if(RB7 == 0 && flagStop == 0){
	      flagStop = 1;
	      i=0;
      }
      if(RB7 == 1 && flagStop == 1){
	      flagStop = 0;
	    }	 
   
      //***Splitting "i" into four digits***//  
      a=i%10; //4th digit is saved here
      b=i/10;
      c=b%10; //3rd digit is saved here
      d=b/10;
      e=d%10; //2nd digit is saved here
      f=d/10;
      g=f%10; //1st digit is saved here
      h=f/10;
      
      if(e>5){
	        e=0;
	        i=i+40;
          g=g+1;
      }

      PORTB=seg_code[g];s1=1; //Turn ON display 1 and print 4th digit
      __delay_ms(5);s1=0;     //Turn OFF display 1 after 5ms delay
      PORTB=seg_code[e];s2=1; //Turn ON display 2 and print 3rd digit
      __delay_ms(5);s2=0;     //Turn OFF display 2 after 5ms delay
      PORTB=seg_code[c];s3=1; //Turn ON display 3 and print 2nd digit
      __delay_ms(5);s3=0;     //Turn OFF display 3 after 5ms delay
      PORTB=seg_code[a];s4=1; //Turn ON display 4 and print 1st digit
      __delay_ms(5);s4=0;     //Turn OFF display 4 after 5ms delay
      
      if(flagDelay>=2 && flagStop == 1) //wait till flag reaches 100
      {
	      i++;flagDelay=0;       //only if flag is hundred "i" will be incremented 
      }
      flagDelay++;             //increment flag for each flash      
   }
 }
