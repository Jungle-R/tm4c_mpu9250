#include "HAL/hal.h"
#include "libs/myLib.h"
#include "mpu9250/mpu9250.h"
#include "serialPort/uartHW.h"


/**
 * main.cpp
 */
int main(void)
{
    MPU9250& mpu = MPU9250::GetI();

    //  Initialize board and FPU
    HAL_BOARD_CLOCK_Init();

    //  Initialize serial port
    SerialPort::GetI().InitHW();
    DEBUG_WRITE("Initialized Uart... \n");

    //  Initialize hardware used by MPU9250
    mpu.InitHW();

    //  Software initialization of MPU9250
    //  Either configure registers for direct sensor readings or load DMP
    //  firmware
    mpu.InitSW();

#ifdef __HAL_USE_MPU9250_NODMP__
    //  Set AHRS time step to 1kHz and configure gains
    mpu.SetupAHRS(0.001, 0.9, 0.01);
#endif  /* __HAL_USE_MPU9250_NODMP__ */

    while (1)
    {
        //  Check if MPU toggled interrupt pin
        //  (this example doesn't use actual interrupts, but polling)
        if (HAL_MPU_DataAvail())
        {
            float rpy[3];
            //  Read sensor data
            mpu.ReadSensorData();
            //  Get RPY values
            mpu.RPY(rpy, true);

            //  Print out sensor measurements
//            DEBUG_WRITE("{%02d.%03d, %02d.%03d, %02d.%03d, ", _FTOI_(__mpu._gyro[0]), _FTOI_(__mpu._gyro[1]), _FTOI_(__mpu._gyro[2]));
//            DEBUG_WRITE("%02d.%03d, %02d.%03d, %02d.%03d, ", _FTOI_(__mpu._acc[0]), _FTOI_(__mpu._acc[1]), _FTOI_(__mpu._acc[2]));
//            DEBUG_WRITE("%02d.%03d, %02d.%03d, %02d.%03d},\n", _FTOI_(__mpu._mag[0]), _FTOI_(__mpu._mag[1]), _FTOI_(__mpu._mag[2]));

            //  Print out orientation
            //  note: _FTOI_ is just a macro to print float numbers, it takes
            //  a float a splits it in 2 integers that are printed separately
            DEBUG_WRITE("%02d.%03d, %02d.%03d, %02d.%03d},\n", _FTOI_(rpy[0]), _FTOI_(rpy[1]), _FTOI_(rpy[2]));

        }
    }
}
