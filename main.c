/*******************************************************************************
* File Name: main.c
*
* Description: This is the source code for the CYW43907 MCU PWM Square Wave code
*              example.
*              
*
* Related Document: See README.md
*
*******************************************************************************
* $ Copyright 2021-2023 Cypress Semiconductor $
*******************************************************************************/

#include "cybsp.h"
#include "cyhal.h"
#include "cy_retarget_io.h"
#include "cy_utils.h"

/*******************************************************************************
* Macros
*******************************************************************************/
/* PWM Frequency = 1000Hz */
#define PWM_FREQUENCY (1000u)
/*delay of 150 milliseconds*/
#define DELAY_PWM (150u)
/*minimum Dutycycle*/
#define MIN_DUTYCYCLE 1.0f
/*maximum Dutycycle*/
#define MAX_DUTYCYCLE 99.0f

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*   This is the main function for the CPU. It configures and start the PWM.
*
* Parameters:
*  void
*
* Return:
*  int
*
*******************************************************************************/
int main(void)
{
    /* PWM object */
    cyhal_pwm_t pwm_led_control;
    /* API return code */
    cy_rslt_t result;
    /*Duty cycle*/
    float PWM_DUTY_CYCLE = 1.0f;

    /* Initialize the device and board peripherals */
    result = cybsp_init();

    /* Board init failed. Stop program execution */
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    /* Enable global interrupts */
    __enable_irq();

    /* Initialize the retarget-io to use the debug UART port */
    result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    /* UART init failed. Stop program execution */
     if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }


    /* \x1b[2J\x1b[;H - ANSI ESC sequence for clear screen */
    printf("\x1b[2J\x1b[;H");
    printf("****************** CYW43907 MCU: PWM Square Wave ******************\r\n\n");

    /* In this example, PWM output is routed to the user LED on the kit.
       See HAL API Reference document for API details. */

    /* Initialize the PWM */
    result = cyhal_pwm_init(&pwm_led_control, CYBSP_LED1, NULL);

    /* PWM init failed. Stop program execution */
     if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    printf("PWM started successfully.\r\n");

    /* Loop infinitely */
    for (;;)
    {
         /* Set the PWM output frequency and duty cycle */
         result = cyhal_pwm_set_duty_cycle(&pwm_led_control, PWM_DUTY_CYCLE, PWM_FREQUENCY);

         /* PWM set duty cycle failed. Stop program execution */
         if (result != CY_RSLT_SUCCESS)
         {
               CY_ASSERT(0);
         }

         /* Start the PWM */
         result = cyhal_pwm_start(&pwm_led_control);

         /* PWM start failed. Stop program execution */
         if (result != CY_RSLT_SUCCESS)
         {
               CY_ASSERT(0);
         }

         /* Incrementing the Duty Cycle*/
         PWM_DUTY_CYCLE = PWM_DUTY_CYCLE + MIN_DUTYCYCLE;

         if(PWM_DUTY_CYCLE > MAX_DUTYCYCLE)
         {
              PWM_DUTY_CYCLE = MIN_DUTYCYCLE;
         }

         cyhal_system_delay_ms(DELAY_PWM);
    }
}


/* [] END OF FILE */
    