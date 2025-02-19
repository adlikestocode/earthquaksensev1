/* Includes */
#include "main.h"
#include "stm32g4xx_hal.h"

/* I2C handle */
I2C_HandleTypeDef hi2c1;

/* ADXL345 registers and constants */
#define ADXL345_ADDR 0x53 << 1  // I2C address shifted left by 1
#define POWER_CTL    0x2D
#define DATA_FORMAT  0x31
#define DATAX0      0x32
#define THRESHOLD_X  8.0f  // Acceleration threshold in g (adjust as needed)

/* Function prototypes */
static void MX_I2C1_Init(void);
static void ADXL345_Init(void);
static void ADXL345_ReadAccel(float *x, float *y, float *z);
static float calculateMagnitude(float x, float y, float z);
static void Buzzer_Init(void);
static void Buzzer_On(void);
static void Buzzer_Off(void);

/* Main function */
int main(void)
{
    /* Initialize system */
    HAL_Init();
    SystemClock_Config();
    
    /* Initialize I2C and ADXL345 */
    MX_I2C1_Init();
    ADXL345_Init();
    
    /* Initialize Buzzer (assuming connected to PA5) */
    Buzzer_Init();
    
    float x, y, z, magnitude;
    uint32_t buzzer_start_time = 0;
    uint8_t buzzer_active = 0;
    
    while (1)
    {
        /* Read accelerometer data */
        ADXL345_ReadAccel(&x, &y, &z);
        
        /* Calculate magnitude */
        magnitude = calculateMagnitude(x, y, z);
        
        /* Check if magnitude exceeds threshold */
        if (magnitude > THRESHOLD_X && !buzzer_active)
        {
            Buzzer_On();
            buzzer_active = 1;
            buzzer_start_time = HAL_GetTick();
        }
        
        /* Check if buzzer should be turned off */
        if (buzzer_active && (HAL_GetTick() - buzzer_start_time >= 10000))
        {
            Buzzer_Off();
            buzzer_active = 0;
        }
        
        HAL_Delay(10);  // Small delay between readings
    }
}

/* Initialize I2C */
static void MX_I2C1_Init(void)
{
    hi2c1.Instance = I2C1;
    hi2c1.Init.Timing = 0x10909CEC;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    
    HAL_I2C_Init(&hi2c1);
}

/* Initialize ADXL345 */
static void ADXL345_Init(void)
{
    uint8_t data = 0x08;  // Set measure bit
    HAL_I2C_Mem_Write(&hi2c1, ADXL345_ADDR, POWER_CTL, 1, &data, 1, HAL_MAX_DELAY);
    
    data = 0x0B;  // +/-16g range
    HAL_I2C_Mem_Write(&hi2c1, ADXL345_ADDR, DATA_FORMAT, 1, &data, 1, HAL_MAX_DELAY);
}

/* Read accelerometer data */
static void ADXL345_ReadAccel(float *x, float *y, float *z)
{
    uint8_t data[6];
    HAL_I2C_Mem_Read(&hi2c1, ADXL345_ADDR, DATAX0, 1, data, 6, HAL_MAX_DELAY);
    
    int16_t raw_x = (data[1] << 8) | data[0];
    int16_t raw_y = (data[3] << 8) | data[2];
    int16_t raw_z = (data[5] << 8) | data[4];
    
    /* Convert to g (assuming +/-16g range) */
    *x = raw_x * 0.004f;  // 4mg/LSB
    *y = raw_y * 0.004f;
    *z = raw_z * 0.004f;
}

/* Calculate magnitude of acceleration */
static float calculateMagnitude(float x, float y, float z)
{
    return sqrtf(x*x + y*y + z*z);
}

/* Initialize Buzzer GPIO */
static void Buzzer_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /* Enable GPIO clock */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    /* Configure GPIO pin */
    GPIO_InitStruct.Pin = GPIO_PIN_5;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

/* Turn buzzer on */
static void Buzzer_On(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
}

/* Turn buzzer off */
static void Buzzer_Off(void)
{
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
}
