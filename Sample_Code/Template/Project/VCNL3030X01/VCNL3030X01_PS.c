/*
 * VCNL3030X01_PS.c
 *
 * Created  : 23 July 2021
 * Modified : 4 August 2021
 * Author   : HWanyusof
 * Version	: 1.1
 */

#include "VCNL3030X01_Prototypes.h"
#include "VCNL3030X01.h"
#include "I2C_Functions.h"
#include "VCNL3030X01_Application_Library.h"
#include "typedefinition.h"
//#include "MS51_16K.h"

extern int I2C_Bus;

//****************************************************************************************************
//*****************************************Sensor API*************************************************

/*Set the PS On/Off Duty Ratio
 *VCNL3030X01_SET_PS_DUTY(Byte DutyRatio)
 *Byte DutyRatio - Input Parameter:
 *
 * VCNL3030X01_PS_DR_1_40
 * VCNL3030X01_PS_DR_1_80
 * VCNL3030X01_PS_DR_1_160
 * VCNL3030X01_PS_DR_1_320
 */
void VCNL3030X01_SET_PS_DUTY(unsigned char DutyRatio)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_1;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_DR_1_40|VCNL3030X01_PS_DR_1_80|VCNL3030X01_PS_DR_1_160|VCNL3030X01_PS_DR_1_320))|DutyRatio;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Persistence
 *VCNL3030X01_SET_PS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL3030X01_PS_PERS_1
 * VCNL3030X01_PS_PERS_2
 * VCNL3030X01_PS_PERS_3
 * VCNL3030X01_PS_PERS_4
 */
void VCNL3030X01_SET_PS_PERS(unsigned char Pers)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_1;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_PERS_1|VCNL3030X01_PS_PERS_2|VCNL3030X01_PS_PERS_3|VCNL3030X01_PS_PERS_4))|Pers;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Integration Time
 *VCNL3030X01_SET_PS_IT(Byte IntegrationTime)
 *Byte IntegrationTime - Input Parameter:
 *
 * VCNL3030X01_PS_IT_1T
 * VCNL3030X01_PS_IT_1_5T
 * VCNL3030X01_PS_IT_2T
 * VCNL3030X01_PS_IT_2_5T
 * VCNL3030X01_PS_IT_3T
 * VCNL3030X01_PS_IT_3_5T
 * VCNL3030X01_PS_IT_4T
 * VCNL3030X01_PS_IT_8T
 */
void VCNL3030X01_SET_PS_IT(unsigned char IntegrationTime)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_1;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_IT_1T|VCNL3030X01_PS_IT_1_5T|VCNL3030X01_PS_IT_2T|VCNL3030X01_PS_IT_2_5T|VCNL3030X01_PS_IT_3T|VCNL3030X01_PS_IT_3_5T|VCNL3030X01_PS_IT_4T|VCNL3030X01_PS_IT_8T))|IntegrationTime;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Turn the PS Sensor On/Off
 *VCNL3030X01_SET_PS_SD(Byte SDBit)
 *Byte SDBit - Input Parameter:
 *
 * VCNL3030X01_PS_SD_EN
 * VCNL3030X01_PS_SD_DIS
 */
void VCNL3030X01_SET_PS_SD(unsigned char SDBit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_1;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_SD_DIS|VCNL3030X01_PS_SD_EN))|SDBit;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Gain
 *VCNL3030X01_SET_PS_Gain(Byte Gain)
 *Byte Gain - Input Parameter:
 *
 * VCNL3030X01_PS_GAIN_2_STEP
 * VCNL3030X01_PS_GAIN_SINGLEx8
 * VCNL3030X01_PS_GAIN_SINGLEx1
 */
void VCNL3030X01_SET_PS_Gain(unsigned char Gain)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_2;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = VCNL3030X01_Data.RData[0];
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_GAIN_2_STEP|VCNL3030X01_PS_GAIN_SINGLEx8|VCNL3030X01_PS_GAIN_SINGLEx1))|Gain;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the PS Output size (12/16Bits)
 *VCNL3030X01_SET_PS_HD(Byte HDBit)
 *Byte HDBit - Input Parameter:
 *
 * VCNL3030X01_PS_HD_12Bits
 * VCNL3030X01_PS_HD_16Bits
 */
void VCNL3030X01_SET_PS_HD(unsigned char HDBit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_2;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = VCNL3030X01_Data.RData[0];
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_HD_12Bits|VCNL3030X01_PS_HD_16Bits))|HDBit;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Sensitivity
 *VCNL3030X01_SET_PS_NS(Byte NSBit)
 *Byte NSBit - Input Parameter:
 *
 * VCNL3030X01_PS_NS_2STEP_MODE_X4
 * VCNL3030X01_PS_NS_2STEP_MODE
 */
void VCNL3030X01_SET_PS_NS(unsigned char NSBit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_2;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = VCNL3030X01_Data.RData[0];
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_NS_2STEP_MODE_X4|VCNL3030X01_PS_NS_2STEP_MODE))|NSBit;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Interrupt Mode
 *VCNL3030X01_SET_PS_INT(Byte InterruptMode)
 *Byte InterruptMode - Input Parameter:
 *
 * VCNL3030X01_PS_INT_DIS
 * VCNL3030X01_PS_INT_CLOSE
 * VCNL3030X01_PS_INT_AWAY
 * VCNL3030X01_PS_INT_CLOSE_AWAY
 */
void VCNL3030X01_SET_PS_INT(unsigned char InterruptMode)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_2;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = VCNL3030X01_Data.RData[0];
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_INT_CLOSE|VCNL3030X01_PS_INT_AWAY|VCNL3030X01_PS_INT_CLOSE_AWAY))|InterruptMode;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Enable/Disable Low Power Mode
 *VCNL3030X01_SET_PS_LED_I_LOW(Byte LOW_I_Bit)
 *Byte LOW_I_Bit - Input Parameter:
 *
 * VCNL3030X01_PS_I_LOW_EN
 * VCNL3030X01_PS_I_LOW_DIS
 */
void VCNL3030X01_SET_PS_LED_I_LOW(unsigned char LOW_I_Bit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_I_LOW_DIS|VCNL3030X01_PS_I_LOW_EN))|LOW_I_Bit;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Enable/Disable Smart Persistence
 *VCNL3030X01_SET_PS_SMART_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL3030X01_PS_SMART_PERS_EN
 * VCNL3030X01_PS_SMART_PERS_DIS
 */
void VCNL3030X01_SET_PS_SMART_PERS(unsigned char Pers)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_SMART_PERS_DIS|VCNL3030X01_PS_SMART_PERS_EN))|Pers;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Enable/Disable Active Force or Auto Mode
 *VCNL3030X01_SET_PS_AF(Byte AF_Bit)
 *Byte AF_Bit - Input Parameter:
 *
 * VCNL3030X01_PS_AUTO
 * VCNL3030X01_PS_AF_EN
 */
void VCNL3030X01_SET_PS_AF(unsigned char AF_Bit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_AUTO|VCNL3030X01_PS_AF_EN))|AF_Bit;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Enable/Disable Trigger for AF Mode
 *VCNL3030X01_SET_PS_TRIG(Byte TriggerBit)
 *Byte TriggerBit - Input Parameter:
 *
 * VCNL3030X01_PS_TRIG_EN
 * VCNL3030X01_PS_TRIG_DIS
 */
void VCNL3030X01_SET_PS_TRIG(unsigned char TriggerBit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_TRIG_DIS|VCNL3030X01_PS_TRIG_EN))|TriggerBit;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Proximity Mode (Normal/Logic)
 *VCNL3030X01_SET_PS_MS(Byte MS_Bit)
 *Byte MS_Bit - Input Parameter:
 *
 * VCNL3030X01_PS_MS_NORMAL
 * VCNL3030X01_PS_MS_LOGIC
 */
void VCNL3030X01_SET_PS_MS(unsigned char MS_Bit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_MS_NORMAL|VCNL3030X01_PS_MS_LOGIC))|MS_Bit;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Enable/Disable Sunlight Cancellation
 *VCNL3030X01_SET_PS_SC_EN(Byte SunlightBit)
 *Byte SunlightBit - Input Parameter:
 *
 * VCNL3030X01_PS_SC_EN
 * VCNL3030X01_PS_SC_DIS
 */
void VCNL3030X01_SET_PS_SC_EN(unsigned char SunlightBit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]&~(VCNL3030X01_PS_SC_DIS|VCNL3030X01_PS_SC_EN))|SunlightBit;
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]);
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Sunlight Cancellation Current
 *VCNL3030X01_SET_PS_SC_CUR(Byte SC_Current)
 *Byte SC_Current - Input Parameter:
 *
 * VCNL3030X01_PS_SC_CURx1
 * VCNL3030X01_PS_SC_CURx2
 * VCNL3030X01_PS_SC_CURx4
 * VCNL3030X01_PS_SC_CURx8
 */
void VCNL3030X01_SET_PS_SC_CUR(unsigned char SC_Current)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_MS;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]);
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_SC_CURx1|VCNL3030X01_PS_SC_CURx2|VCNL3030X01_PS_SC_CURx4|VCNL3030X01_PS_SC_CURx8))|SC_Current;
	WriteI2C_Bus(&VCNL3030X01_Data);

}

/*Set the Sunlight Capability
 *VCNL3030X01_SET_PS_SP(Byte SP_Bit)
 *Byte SP_Bit - Input Parameter:
 *
 * VCNL3030X01_PS_SPx1
 * VCNL3030X01_PS_SPx1_5
 */
void VCNL3030X01_SET_PS_SP(unsigned char SP_Bit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_MS;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]);
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_SPx1|VCNL3030X01_PS_SPx1_5))|SP_Bit;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Output of Sunlight Protect Mode
 *VCNL3030X01_SET_PS_SPO(Byte SPO_Bit)
 *Byte SPO_Bit - Input Parameter:
 *
 * VCNL3030X01_PS_SPO_00
 * VCNL3030X01_PS_SPO_FF
 */
void VCNL3030X01_SET_PS_SPO(unsigned char SPO_Bit)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_MS;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]);
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_SPO_00 | VCNL3030X01_PS_SPO_FF))|SPO_Bit;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the LED current
 *VCNL3030X01_SET_PS_LED_I(Byte IRED_Current))
 *Byte IRED_Current - Input Parameter:
 *
 * VCNL3030X01_PS_LED_I_50mA
 * VCNL3030X01_PS_LED_I_75mA
 * VCNL3030X01_PS_LED_I_100mA
 * VCNL3030X01_PS_LED_I_120mA
 * VCNL3030X01_PS_LED_I_140mA
 * VCNL3030X01_PS_LED_I_160mA
 * VCNL3030X01_PS_LED_I_180mA
 * VCNL3030X01_PS_LED_I_200mA
 */
void VCNL3030X01_SET_PS_LED_I(unsigned char IRED_Current)
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_MS;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	VCNL3030X01_Data.WData[0] = (VCNL3030X01_Data.RData[0]);
	VCNL3030X01_Data.WData[1] = (VCNL3030X01_Data.RData[1]&~(VCNL3030X01_PS_LED_I_50mA|VCNL3030X01_PS_LED_I_75mA|VCNL3030X01_PS_LED_I_100mA|VCNL3030X01_PS_LED_I_120mA|VCNL3030X01_PS_LED_I_140mA|VCNL3030X01_PS_LED_I_160mA|VCNL3030X01_PS_LED_I_180mA|VCNL3030X01_PS_LED_I_200mA))|IRED_Current;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the PS Cancellation
 *VCNL3030X01_SET_PS_CANC(Word CancelValue)
 *Word CancelValue - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL3030X01_SET_PS_CANC(unsigned int CancelValue)
{
	unsigned char LowByte = CancelValue;
	unsigned char HighByte = CancelValue>>8;
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CANC;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = LowByte;
	VCNL3030X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the Low Threshold
 *VCNL3030X01_SET_PS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL3030X01_SET_PS_LowThreshold(unsigned int LowThreshold)
{
	unsigned char LowByte = LowThreshold;
	unsigned char HighByte = LowThreshold>>8;
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_THDL;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = LowByte;
	VCNL3030X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Set the High Threshold
 *VCNL3030X01_SET_PS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL3030X01_SET_PS_HighThreshold(unsigned int HighThreshold)
{
	unsigned char LowByte = HighThreshold;
	unsigned char HighByte = HighThreshold>>8;
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_THDH;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	VCNL3030X01_Data.WData[0] = LowByte;
	VCNL3030X01_Data.WData[1] = HighByte;
	WriteI2C_Bus(&VCNL3030X01_Data);
}

/*Read the PS Data
 *VCNL3030X01_GET_PS_Data()
 *
 *returns PS Data between 0d0 and 0d65535
 */
unsigned int VCNL3030X01_GET_PS_Data()
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_DATA;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	return (VCNL3030X01_Data.RData[1]<<8|VCNL3030X01_Data.RData[0]);
}

/*Read the PS Interruppt Flag
 *VCNL3030X01_GET_PS_Interrupt() returns interrupt flag status.
 *Please refer to Table 9 in the Datasheet page 11
 */
unsigned int VCNL3030X01_GET_PS_Interrupt()
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_INT_FLAG;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	return (VCNL3030X01_Data.RData[1]<<8|VCNL3030X01_Data.RData[0]);
}

/*Read Register value
 *VCNL3030X01_READ_Reg(Byte Reg)
 *Byte Reg - Input Parameter:
 *
 * VCNL3030X01_PS_CONF_1
 * VCNL3030X01_PS_CONF_2
 * VCNL3030X01_PS_CONF_3
 * VCNL3030X01_PS_CONF_MS
 * VCNL3030X01_PS_CANC
 * VCNL3030X01_PS_THDL
 * VCNL3030X01_PS_THDH
 * VCNL3030X01_PS_DATA
 * VCNL3030X01_INT_FLAG
 * VCNL3030X01_ID
 *
 *returns Register Value between 0d0/0x00 and 0d65535/0xFFFF
 */
unsigned int VCNL3030X01_READ_Reg(unsigned char Reg)
{
	unsigned int RegValue;
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = Reg;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	RegValue = VCNL3030X01_Data.RData[1]<<8|VCNL3030X01_Data.RData[0];
	return RegValue;
}

/*Read the PS_SD bit
*returns 1 for Shutdown and 0 for Sensor On
*/
bool VCNL3030X01_GET_PS_SD_Bit()
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_1;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	if ((VCNL3030X01_Data.RData[0] & 0x01) == 0x01) {return 1;}
    else
    return 0;
}

/*Read the PS_AF bit
 *returns 1 for AF Mode and 0 for Auto Mode
 */
bool VCNL3030X01_GET_PS_AF_Bit()
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	if ((VCNL3030X01_Data.RData[0] & 0x08) == 0x08) {return 1;}
    else
    return 0;
}

/*Read the LED_I_LOW bit
 *returns 1 for Low Power Mode and 0 for Normal Mode
 */
bool VCNL3030X01_GET_LED_I_LOW_Bit()
{
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_PS_CONF_3;
    VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	if ((VCNL3030X01_Data.RData[0] & 0x80) == 0x80) {return 1;}
    else
    return 0;
}

/*Read Device ID
 *Returns ID
 */
unsigned int VCNL3030X01_GET_ID()
{
	unsigned int RegValue;
	TransferData VCNL3030X01_Data;
	VCNL3030X01_Data.Slave_Address = VCNL3030X01_SlaveAddress;
	VCNL3030X01_Data.RegisterAddress = VCNL3030X01_ID;
	VCNL3030X01_Data.Select_I2C_Bus = I2C_Bus;
	ReadI2C_Bus(&VCNL3030X01_Data);
	RegValue = VCNL3030X01_Data.RData[1]<<8|VCNL3030X01_Data.RData[0];
	return RegValue;
}
