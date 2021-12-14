//AUTHOR: youssef sherif mostafa amin mohaseb
//ID:CU1900480
// LCD module connections
sbit LCD_RS at RC2_bit;
sbit LCD_EN at RC3_bit;
sbit LCD_D4 at RC4_bit;
sbit LCD_D5 at RC5_bit;
sbit LCD_D6 at RC6_bit;
sbit LCD_D7 at RC7_bit;
                                       //lcd connected to port c
sbit LCD_RS_Direction at TRISC2_bit;
sbit LCD_EN_Direction at TRISC3_bit;
sbit LCD_D4_Direction at TRISC4_bit;
sbit LCD_D5_Direction at TRISC5_bit;
sbit LCD_D6_Direction at TRISC6_bit;
sbit LCD_D7_Direction at TRISC7_bit;
//KEYPAD
char keypadport at PORTD;          //key pad connected to port


// End LCD module connections
void main()
{
float temp_new;                                    // variable from type float
float temp_real;                                   //  variable from type float
 int max=150 ;                                     // maximum value tempreture sensor can detect
 int temp ;                                        //  tepmreture value type int
 int key=0;                                        //   store value type integer
 char key_txt[7];                                   // Array to store data
 char result[10];                                   // Array to store data
 int index =0;                                      // index to store data in array
 int thresh = 0;                                    // hold threshold value

  TRISA  = 0xFF;                                   // PORTA is input
  TRISB  = 0;                                     // PORTB is output
  PORTB = 0;                                      // initializing  port b
  Keypad_Init();                                   // Int keypad
  Lcd_Init();                                     // Initialize LCD

  Lcd_Cmd(_LCD_CLEAR);                            // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);                       // Cursor off


  while(1){                                       // WHILE   Loop
    key = 0;                                      // making key = 0 to be always in loop
    while(!key){                                   // enter while loop if key not equel 0  whch means there is a key pressed
      key =  Keypad_key_Click();                   //   Store key presed  in key variable
    }
    switch (key){                                   //switch case for keypad
     case 1 : key= 7+'0'; break;                    //  character  '0' = 48 in ASCII
     case 2 : key=4+'0'; break;
     case 3 : key=1+'0'; break;
     case 4 : key='#';   break;
     case 5 : key='8';   break;
     case 6 : key=5+'0'; break;
     case 7 : key=2+'0'; break;
     case 8 : key=0+'0'; break;
     case 9 : key=9+'0'; break;
     case 10 : key=6+'0'; break;
     case 11 : key=3+'0'; break;
     case 12: key='='; break;
     case 13 : key='/'; break;
     case 14 : key='*'; break;
     case 15 : key='-'; break;
     case 16 : key='+'; break;
    }

    if ((key == '=') || (index == 5)){      // = is presed on keypad or 5 no have been presed
       Lcd_Out(1,1, key_txt);              // on first row first coloumn print on lcd
       thresh = StrToInt(key_txt);        // store value that is inside key_text after convert from string to integer
       break;                             // get out of the function
    }
    key_txt[index]= key ;                 //  getting key_txt array stored data in key variable
    index = index +1;                     // increment value of index + 1

//    WordToStr(key, key_txt);d
    Lcd_Out(2,1,"Thresh=");              // on the second row first coloumn print on lcd "Thresh="
    Lcd_Chr(2,index+8,key);              // Prints character on Lcd which s thereshhold vslue at specified position to which is 2nd row and column is indesx value + 8
  }                                       // lcd char is used to avoid overwite between numbers and text


  while(1){
           temp = ADC_Read(1);           // ADC COVERT VALUE OF temp from analouge to degital
           temp_new = (temp*5)/1024. ;
           temp_real = temp_new*100 ;
           FloatToStr(temp_real,  result);      // integer value temp will be converted to string to be stored in result
           Lcd_Out(1,1,"Temp=");         // on the first row first coloumn print on lcd "Temp"
           Lcd_Out(1,7,result);          // on the first row first coloumn print on lcd the r
//                                         //TEST CASES
    if (temp >= thresh && temp<max ){    // if temp greater than thresh or equel and less than the maximum temp
        PORTB = 0x1;                    // BUZZER IS ON
//



    }
    else if (temp < thresh)       //  iF tempreture less than buzzer
    {                             //LED Blinking and buzzer off
    PORTB = 0b11111110   ;        //
    Delay_ms(1000);             //delay 1 second
    PORTB = 0b00000000 ;
    Delay_ms(1000) ;
    }
    else if (temp >=thresh && temp >=max)      // if tempreture greater than thresh and greater than max                                                // OTHERWISE
    {
      PORTB = 0b10101011 ;
      Delay_ms(1000) ;
      PORTB = 0b01010101 ;
      Delay_ms(1000) ;                                               // delay 1 second
      //
      //

     }
  }
}