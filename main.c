
# include <stm32f10x.h>
# include <stm32f10x_rcc.h>
# include <stm32f10x_gpio.h>

#include "Naze32.h"
#define RED_LED_ON()  GPIO_WriteBit (LED_PORT, RED_LED, Bit_RESET);
#define RED_LED_OFF()  GPIO_WriteBit (LED_PORT, RED_LED, Bit_SET);
#define GREEN_LED_ON()  GPIO_WriteBit (LED_PORT, GREEN_LED, Bit_RESET);
#define GREEN_LED_OFF()  GPIO_WriteBit (LED_PORT, GREEN_LED, Bit_SET);

void Delay( uint32_t nTime );

static __IO uint8_t TimerEventFlag;   //When 

int main(void)
{
  
  int MS_count =0;    //Counts the number of timer ticks so far.
  
  const int LED_ON_TIME = 300;        //LED on for this many ms.
  const int LED_FREQUENCY = 1000;     //LED blink rate this many ms.

  initialize_PROC();

  RED_LED_ON();
  GREEN_LED_ON();


  if (SysTick_Config(SystemCoreClock/1000)) //Systick at 1kHz.
    while (1);
  
  while (1) { 
    if (TimerEventFlag==TRUE){
      ++MS_count;
      if (MS_count>=LED_FREQUENCY)
        MS_count=0;
      TimerEventFlag=FALSE;
    }

    if(MS_count<LED_ON_TIME){
      RED_LED_ON();
      GREEN_LED_ON();
    }
    else if(MS_count >LED_ON_TIME && MS_count<LED_FREQUENCY){
      RED_LED_OFF();
      GREEN_LED_OFF();
    }  //END: if(MS_count<LED_ON_TIME) else...
  }    //END: while(1)
}      //END: main()

static __IO uint32_t TimingDelay;

void Delay( uint32_t nTime ){
  TimingDelay = nTime ;
  while ( TimingDelay != 0);
}

void SysTick_Handler (void){            // ISR
  if ( TimingDelay != 0x00)
    TimingDelay --;
  
  TimerEventFlag = TRUE; //Let main know systick occurred.
}


#ifdef USE_FULL_ASSERT
  void assert_failed ( uint8_t* file, uint32_t line)
  {
    while (1){ }
  }
#endif


void initialize_PROC (void)
{

  // Turn off JTAG port to be able to the ports for other uses.
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  //Both below seem to work OK:
  //GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//Disable only JTAG, keep SWJ on.
  GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable, ENABLE); //Disable both JTAG&SWJ

  //"Normal" program continues from here...

  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd (LED_PORT_RCC, ENABLE ); 

  GPIO_StructInit (&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = RED_LED | GREEN_LED;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

  GPIO_Init(LED_PORT, &GPIO_InitStructure);

}
