#pragma NOP
#pragma sfr
/***********************************************************************/
#include "includes.h"
/***********************************************************************/
const u8 _rn8209default[][3] = /*/////RN8209Ĭ�ϲ���//////*/  
{   
   #ifdef _IB1DOT5ATO6A   
     {0x00,0x02,0x02},    /*///// 1.5(6)A��ʹ��ͨ��2 ͨ��1����8������//////*/ 	      
   #else
     {0x00,0x43,0x43},    /*///// ֻ����00-04��ַĬ��ֵ ����Ĭ�϶�Ϊ0  ��3���ֽ�ΪУ���//////*/
   #endif
   {0x00,0x01,0x01},	
   {0x2B,0x00,0x2B},
   //{0x40,0x00,0x40},	
   {0x00,0x60,0x60},	
   {0x01,0x20,0x21}
};	
/***********************************************************************/
extern  ST_BN8209_CS  BN8209_CS;
extern  ST_MPARA  MeterPara;

u8 RN8209_SPI_Read(void);
void RN8209_SPI_Write(u8 bdata); 
void RN8209_DisablePulse(void);
void RN8209_EnablePulse(void);
/***********************************************************************/
/*///// ��������: void RN8209_SPI_Ini(void) //////*/  
/*///// ��������: SPIͨ�ſڳ�ʼ�� //////*/  
/*///// �������: �� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/
void RN8209_SPI_Ini(void)
{
  DIR_SPIRST = OUT_PORT;
  PIN_SPIRST = HIGH_LEVEL;
  DIR_SPICS  = OUT_PORT; 
  PIN_SPICS  = HIGH_LEVEL;
  DIR_SPISDO = OUT_PORT ;
  PIN_SPISDO = HIGH_LEVEL;
  DIR_SPISDI = INPUT;      
  DIR_SPICLK = OUT_PORT;
  PIN_SPICLK = HIGH_LEVEL; 
  
  return; 
}
/***********************************************************************/
/*///// ��������: u8 RN8209_SPI_Read(void) //////*/  
/*///// ��������: ��ȡ8209һ�ֽ����� //////*/  
/*///// �������: �� //////*/  
/*///// �������: ��ȡ��1�ֽ����� //////*/  
/***********************************************************************/
u8 RN8209_SPI_Read(void)
{
	u8 i,rbyte=0;
	
	DIR_SPICLK = OUT_PORT;
	PIN_SPICLK = HIGH_LEVEL;
	
	for(i=0;i<8;i++)
	{		
		Delay1us();		
	  DIR_SPICLK = OUT_PORT;		
		Delay1us();		
		PIN_SPICLK = HIGH_LEVEL;		
		DelayNus(50);		
		rbyte <<= 1;		
		PIN_SPICLK = LOW_LEVEL;			 
		DIR_SPISDI = INPUT; 		
		if (PIN_SPISDI == 1)  
		{
			rbyte |= 1; 
	  } 	
//		PIN_SPICLK  = LOW_LEVEL ;			
		DelayNus(50);
	}	
	DIR_SPICLK = OUT_PORT;	
	PIN_SPICLK = HIGH_LEVEL;	
	DelayNus(1);
	
	return(rbyte);
}
/***********************************************************************/
/*///// ��������: void RN8209_SPI_Write(u8 bdata) //////*/  
/*///// ��������: д��1���ֽ����ݵ�8209�� //////*/  
/*///// �������: bdata-���� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/
void RN8209_SPI_Write(u8 bdata)
{
	u8 i;
	u8 byte;
	
	for(i=0;i<8;i++)
	{
		Delay1us();	
		byte = bdata & 0x80;		
		DIR_SPISDO = OUT_PORT;		
		if (byte==0) 
		{	
		  PIN_SPISDO = LOW_LEVEL;
		}     
		else
		{	
		  PIN_SPISDO = HIGH_LEVEL;
		}
		DIR_SPICLK = OUT_PORT;		
		PIN_SPICLK = HIGH_LEVEL;		
		DelayNus(50);
		PIN_SPICLK = LOW_LEVEL;
		DelayNus(50);
		bdata <<= 1;
	}	  
	DIR_SPISDO = OUT_PORT; 
	PIN_SPISDO = HIGH_LEVEL; 
	DelayNus(2);
	
	return;		 
}
/***********************************************************************/
/*///// ��������: u8 RN8209_ReadData(u8 add,u8 *data,u8 *len) //////*/  
/*///// ��������: ��ȡ8209�Ĵ������� //////*/  
/*///// �������: add-8209�Ĵ�����ַ *data-��ȡ����õĻ����� *len-���ݳ��� //////*/  
/*///// �������: 0-��ȡʧ�� 1-��ȡ�ɹ� //////*/  
/***********************************************************************/
u8 RN8209_ReadData(u8 add,u8 *data,u8 *len)
{
	u8 ret=1;
	
	DIR_SPICS = OUT_PORT ; 
  PIN_SPICS = LOW_LEVEL;
  DelayNus(2);
  PIN_SPICS = LOW_LEVEL;
	RN8209_SPI_Write(add);
	switch(add)
	{
    case 0x00:
		case 0x01:
		case 0x02:	
		case 0x03:	
		case 0x04:	
		case 0x05:
		case 0x06:				
		case 0x09:	
		case 0x0A:	
		case 0x0B:	
		case 0x0C:	
		case 0x0D:	
		case 0x0E:	
		case 0x0F:	
		case 0x10:	
		case 0x20: 
		case 0x21:
		case 0x25:	
		case 0x45: 	
			*data = RN8209_SPI_Read();
			*(data+1) = RN8209_SPI_Read(); 
			*len = 2;
		break; 				
		case 0x07:	 
		case 0x08:	
		case 0x40:
		case 0x41:
		case 0x42:
		case 0x43:  
			*data = RN8209_SPI_Read();
			*len = 1;
			break; 				 
		case 0x22:
		case 0x23:
		case 0x24:
		case 0x29:	
		case 0x2A:	
		case 0x2B:
		case 0x2C:	
		case 0x2D:
    case 0x7f : 
    	*data = RN8209_SPI_Read();
			*(data+1) = RN8209_SPI_Read(); 
			*(data+2) = RN8209_SPI_Read(); 
			*len = 3;
			break; 
		case 0x26 :	 
		case 0x27 :	 
		case 0x28 :	 
		case 0x44 :	
			*data = RN8209_SPI_Read();
			*(data+1) = RN8209_SPI_Read(); 
			*(data+2) = RN8209_SPI_Read(); 
		  *(data+3) = RN8209_SPI_Read();
			*len = 4;
			break;        
		default :
			ret = 0;	
			break;
	}
	DelayNus(2);
	DIR_SPICS = OUT_PORT ; 
  PIN_SPICS = HIGH_LEVEL;
  
	return(ret);
}
/***********************************************************************/
/*///// ��������: void RN8209_WriteData(u8 *ptr) //////*/  
/*///// ��������: д�����ݵ�8209�Ĵ�����//////*/  
/*///// �������: *ptr-ָ��Ҫд������ݻ����� //////*/  
/*///// �������: ��  //////*/  
/***********************************************************************/
void RN8209_WriteData(u8 *ptr)    
{
	u8 temp[2];
	
	if ((*ptr) > 0x10)      /*// ���ƼĴ�����ַ������0x10 //*/ 
	{
		return;
	}
	
	DIR_SPICS = OUT_PORT; 
  PIN_SPICS = LOW_LEVEL;
  DelayNus(2);
	temp[0] = 0xea;        /*// дʹ������ //*/
	temp[1] = 0xe5;
	RN8209_SPI_Write(temp[0]);
	RN8209_SPI_Write(temp[1]);
	
	RN8209_SPI_Write((*ptr)+0x80);	 /*// д������ //*/
	if ( (*ptr != 0x07) && (*ptr != 0x08) )
	{ 
	  RN8209_SPI_Write(*(ptr+1));
	}	
	RN8209_SPI_Write(*(ptr+2));
	
	temp[0] = 0xea;       /*// д�������� //*/
	temp[1] = 0xdc;  
	RN8209_SPI_Write(temp[0]);
	RN8209_SPI_Write(temp[1]);
	DelayNus(2);
	DIR_SPICS = OUT_PORT ; 
  PIN_SPICS = HIGH_LEVEL;
  
  return;
}
/***********************************************************************/
/*///// ��������: u8 RN8209_WriteDataToEE(u8 *ptr) //////*/  
/*///// ��������: д��У�����ݵ�EEP��//////*/  
/*///// �������: *ptr-ָ��Ҫд������ݻ����� //////*/  
/*///// �������: 0-ʧ�� 1-�ɹ�  //////*/  
/***********************************************************************/
u8 RN8209_WriteDataToEE(u8 *ptr)  
{
	u8 len;
	u16 tmpadr;	
	
	if(*ptr > 0x14)
	{
		return;
	}
	
	if(*ptr > 0x10)
	{
		if (*ptr == 0x11)      /*///// 0x11-����У��ϵ��Ϊ4���ֽ� //////*/  
		{		  
		  len = 4;
		  tmpadr = EM_ADR_JBCSP; 
		}
		else                  /*/////  0x12-����У׼ϵ��  0x13-���ߵ���У׼ϵ��  0x14��ѹУ׼ϵ��//////*/  
		{
			len = 3;
			tmpadr = EM_ADR_JBCSP+5+((u16)((*ptr)-0x12))*4; 
		}
	}
	else 
	{
	  tmpadr = EM_ADR_RN8209JBCS+((u16)(*ptr))*3;
	  len = 2;
	}
 	
 	return( Write24LC64WithBK(tmpadr,len,ptr+1) ); 
}
/***********************************************************************/
/*///// ��������: void RN8209_TestJBCS(u16 r8209chksum) //////*/  
/*///// ��������: �ȶ�EEP�е�У������У��ͺ�8209�ļĴ���У���  1��У��1��//////*/  
/*///// �������: r8209chksum-8209�ж�ȡ��У��� //////*/  
/*///// �������: ��  //////*/  
/***********************************************************************/
void RN8209_TestJBCS(u16 r8209chksum)    
{  
  if(BN8209_CS.RegDataChkSum != r8209chksum)
  {
  	RN8209_LoadJBCS();
  	
  	#ifdef _NBKZCMD       
	    Print_DebugInf_Uart6((u8 *)("DEBUG INF: BN8209 chksum error \r\n"),ISN,0,ISTRUE);
	    Print_DebugInf_Uart6((u8 *)("DEBUG INF: end\r\n"),ISN,0,ISFALSE);
		#endif 
  }
  
  return;
}
/***********************************************************************/
/*///// ��������: u8 RN8209_Test(u8 testnum) //////*/  
/*///// ��������: ������8209��ͨ��״̬//////*/  
/*///// �������: testnum-���Դ��� //////*/  
/*///// �������: 0-ͨ��ʧ�� 1-ͨ������ //////*/  
/*///// ˵��: ͨ�Ź���ʱ��8209��λ ֱ��ͨѶ���� //////*/  
/***********************************************************************/
u8 RN8209_Test(u8 testnum)   /*// ����8209 ////*/
{
   u8 i,tmpbyte;
   u8 temp[2];     
   
   RN8209_SPI_Ini();
   
   i = 0;
   while(i < testnum)
   {   	 
   	 MemCopyNN(0,temp,2);
	   RN8209_ReadData(0x7f,temp,&tmpbyte);	   
	   if ((temp[0] == 0x82) && (temp[1] == 0x09))
	   {
	   	 break;
	   }
	   Delay2ms(1);
	   FeedWatchDog();
	   i++;
	 }	
	  
	 if(i == testnum)
	 {
	 	 DIR_SPIRST = OUT_PORT;
     PIN_SPIRST = LOW_LEVEL;
	 	 
	 	 Set_MeterErr_8209Err();
	 	 AlarmLED_On();
     BackLight_On();
	 	 return(false);
	 }
	 
	 Set_MeterErr_8209OK();
	 return(true);	
} 
/***********************************************************************/
/*///// ��������: void RN8209_LoadJBCS(void) //////*/  
/*///// ��������: ��ȡEEPУ�������д�뵽8209��//////*/  
/*///// �������: �� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/
void RN8209_LoadJBCS(void)     
{
	 u8 tmpbyte,i,j;
	 u8 temp[3];
	 u8 temptst[2];
	 u16 addr;     
   
   RN8209_SPI_Ini();
   
	 RN8209_DisablePulse();
	 if (RN8209_Test(TPOWERONTSTNUM) == 1) /*// �ϵ�ʱ����50�� ////*/ 
	 {	 	 
  	 for (i=0;i<=16;i++)  
  	 {
  	 	 addr = EM_ADR_RN8209JBCS+i*3;
  	 	 ReadParameter(addr,2,&temp[1]);
  	 	 temp[0] = i;	 
  	 	 if(i == 1)
  	 	 {
  	 	 	 temp[2] = 0;	
  	 	 	 temp[1] = 0;
  	 	 }	 
  	 	 for (j=0;j<3;j++)
  	 	 {
  		   RN8209_WriteData(&temp[0]);
  		   Delay2ms(1);
  		   RN8209_ReadData(i,temptst,&tmpbyte);	
  		   	   		   
  		   if ((i == 7) || (i == 8))
  		   {
  		   	 temptst[1] = temptst[0];
  		   	 temptst[0] = 0;
  		   }
  		   
  		   if (MemCompareZheng(&temp[1],temptst,2) == ISEQUAL)
  		   {
  		   	 break;
  		   }
  		 }
  	 }
	 }	 	 
	 RN8209_CalChkSum();         /*// ����EEPROMУ�������ۼ�У��� ////*/ 
	 
	 RN8209_EnablePulse();
	 
	 return;
}
/***********************************************************************/
/*///// ��������: void RN8209_InitDefault(void) //////*/  
/*///// ��������: ��ʼ��EEPУ�����ΪĬ�ϲ��� //////*/  
/*///// �������: �� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/
void  RN8209_InitDefault(void) /*// ��ʼ��EEPУ�����ΪĬ�ϲ��� ////*/ 
{
   u8 tempbuf[3];
   
   Read24LC64(EM_ADR_RN8209JBCS,3,tempbuf,TNOCHK); 
   if( IsEqualSpecialData(tempbuf,0xff,3) == OK)
   {
     RN8209_PInitDefault();
   }
	 
	 return;
}
/***********************************************************************/
/*///// ��������: void RN8209_PInitDefault(void) //////*/  
/*///// ��������: ��ʼ��EEPУ�����ΪĬ�ϲ��� //////*/  
/*///// �������: �� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/
void  RN8209_PInitDefault(void) /*// ��ʼ��EEPУ�����ΪĬ�ϲ��� ////*/ 
{
   u8 tempbuf[36];

   MemCopyNN(0,tempbuf,36);
      	    	     
	 Write24LC64(EM_ADR_RN8209JBCS,15,&_rn8209default[0][0],TNOCHK); 
	 Write24LC64(EM_ADR_RN8209JBCS+BACKUP_LOCATION,15,&_rn8209default[0][0],TNOCHK); 
	 FeedWatchDog();
	 Write24LC64(EM_ADR_RN8209JBCS+15,36,tempbuf,TNOCHK);
	 Write24LC64(EM_ADR_RN8209JBCS+15+BACKUP_LOCATION,36,tempbuf,TNOCHK);
	 
	 return;
}
/***********************************************************************/
/*///// ��������: void RN8209_CalChkSum(void) //////*/  
/*///// ��������: ����EEPУ������У��� �洢��ram�� //////*/  
/*///// �������: �� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/
void  RN8209_CalChkSum(void)     
{
	u8 i;
	u8 tmpbuf[2];
	u16 addr,tmpeepchksum;  
  
  tmpeepchksum = 0;
  i = 0;
  while(i <= 16)
  {
  	addr = EM_ADR_RN8209JBCS+i*3;
  	ReadParameter(addr,2,&tmpbuf[0]);  	
  	tmpeepchksum += (((u16)(tmpbuf[0])) << 8)+tmpbuf[1]; 
  	i++;
  }	
  
  BN8209_CS.RegDataChkSum = 0xffff-tmpeepchksum; 
	
	return; 
}
/***********************************************************************/
/*///// ��������: void RN8209_DisablePulse(void) //////*/  
/*///// ��������: �ر�8029������� //////*/  
/*///// �������: �� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/
void  RN8209_DisablePulse(void) 
{
	 u8 temp[3];	 
	 
	 temp[0] = 0x01;
	 temp[1] = 0x00;
	 temp[2] = 0x00;
	 RN8209_WriteData(&temp[0]);
	 
	 return;
}
/***********************************************************************/
/*///// ��������: void RN8209_DisablePulse(void) //////*/  
/*///// ��������: ʹ��8029������� //////*/  
/*///// �������: �� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/ 
void  RN8209_EnablePulse(void)  
{
	 u8 temp[3];
	 
	 temp[0] = 0x01;
	 temp[1] = 0x00;
	 temp[2] = 0x01;
	 RN8209_WriteData(&temp[0]);
	 
	 return;
}
/***********************************************************************/
/*///// ��������: void RN8209_DisablePulse(void) //////*/  
/*///// ��������: ����У�������д�뵽8209�Ĵ�����EEPROM�� //////*/  
/*///// �������: regadr-8209�Ĵ�����ַ *ptr-ָ��Ҫд������ݻ����� //////*/  
/*///// �������: �� //////*/  
/***********************************************************************/ 
void  RN8209_CalJBCS(u8 regadr,u8 *ptr)   
{
	 u8 tmpbyte,tmpadr;
	 u8 tmpbuf[5];
	 u16 tmpcal,tmpu16;
	 u32 tmp8209P,tmprealP;
	 float tmpfloat;
	 
   switch (regadr)	
   {
     case 0x02:     /*//////HFConst����/////*/
     	 tmpbuf[1] = *(ptr+1);
	     tmpbuf[2] = *(ptr); 
     break; 
     case 0x03:     /*//////��������ֵ����/////*/
     	 /*//////̨�Ӵ�0.2%Ib,�����й�����,ȡ�м�����λ�����й������Ĵ���03��/////*/
     	 RN8209_ReadData(RN8209_REG_PA,&tmpbuf[0],&tmpbyte);     	 
     break; 
     case 0x05:     /*//////�й�����1.0У��/////*/
     case 0x07:	    /*//////�й�����0.5LУ��/////*/
   	   tmp8209P = ((u32)(BN8209_CS.P[2]) << 16) + ((u32)(BN8209_CS.P[1]) << 8) + BN8209_CS.P[0];
   	   tmp8209P &= 0x7fffff;    /*//////���ι��ʷ���λ/////*/
   	   tmprealP = ((u32)(*(ptr+2)) << 16) + ((u32)(*(ptr+1)) << 8) + (*(ptr));   	 
   	   tmp8209P = BCDLongTOHexlong(tmp8209P); /*//////RN8209����ֵ/////*/
   	   tmprealP = BCDLongTOHexlong(tmprealP); /*//////У��̨����ֵ/////*/
     	 
     	 if(regadr == 0x05)           
     	 {
     	 	 if(tmprealP > tmp8209P)    /*//////���ƫ��/////*/
   	     {
   	 	     tmpfloat = ((float)(tmprealP - tmp8209P)) / ((float)(tmprealP));
   	 	     tmpfloat = tmpfloat/(1.0000-tmpfloat);
   	 	     tmpu16 = (u16)(32768*tmpfloat);
   	     }
   	     else                       /*//////���ƫ��/////*/
   	     {
   	       tmpfloat = ((float)(tmp8209P - tmprealP)) / ((float)(tmprealP));
   	       tmpfloat = tmpfloat/(1.0000+tmpfloat);
   	 	     tmpu16 = (u16)(32768*(2.0000-tmpfloat));
   	     }
     	 }
     	 else if(regadr == 0x07)      
     	 {
     	 	 if(tmprealP > tmp8209P)    /*//////���ƫ��/////*/
   	 		 {
   	 	     tmpfloat = ((float)(tmprealP - tmp8209P)) / ((float)(tmprealP));
   	 	     tmpu16 = (u16)(1654*tmpfloat);
   	     }
   	     else
   	     {
   	       tmpfloat = ((float)(tmp8209P - tmprealP)) / ((float)(tmprealP));
   	 	     tmpu16 = (u16)(256-(u8)(1654*tmpfloat));
   	     }
     	 }
     	 
     	 tmpbuf[1] = (u8)(tmpu16 >> 8);
	     tmpbuf[2] = (u8)(tmpu16);
     break;	
     case 0x12:   /*//////������ЧֵУ��/////*/
     case 0x13:   /*//////���ߵ�����ЧֵУ��/////*/
     case 0x14:   /*//////��ѹ��ЧֵУ��/////*/
     	 if((regadr == 0x12) || (regadr == 0x13))
     	 {
     	 	 if(regadr == 0x12)
     	 	 {
     	 	   tmpadr = RN8209_REG_IA;
     	 	 }
     	 	 else
     	 	 {
     	 	 	 tmpadr = RN8209_REG_IB;
     	 	 }
     	 	 tmprealP = ((u32)(*(ptr+2)) << 16) + ((u32)(*(ptr+1)) << 8) + (*(ptr));   	 
   	     tmprealP = BCDLongTOHexlong(tmprealP); /*//////RN8209����ֵ/////*/
     	 	 tmpcal = 1000;
     	 }
     	 else
     	 {
     	 	 tmpadr = RN8209_REG_U;
     	 	 tmprealP = (u32)(BcdTOHexInt(((u16)(*(ptr+1)) << 8) + (*(ptr)))); 
     	 	 tmpcal = 10;
     	 }
     	 
     	 RN8209_ReadData(tmpadr,&tmpbuf[0],&tmpbyte);  /*//////��ȡ�Ĵ�����ֵ/////*/
   	   tmp8209P = ((u32)(tmpbuf[0]) << 16) + ((u32)(tmpbuf[1]) << 8) + tmpbuf[2];   	       
       tmprealP = (u32)((tmpcal*tmp8209P)/tmprealP); /*//////������ڼĴ���ֵ����ʵ��ֵ/////*/ 
       
       tmpbuf[1] = (u8)(tmprealP >> 16);
	     tmpbuf[2] = (u8)(tmprealP >> 8); 
	     tmpbuf[3] = (u8)(tmprealP);
	   break;
	   case 0x0A:     /*//////�й�����offsetУ��/////*/
	   	 /*//////̨�������5%Ib,1.0,����ʱ������,�����ֵ,�õĻ��Ͳ�������/////*/
	   	 RN8209_ReadData(RN8209_REG_PA,&tmpbuf[0],&tmpbyte); /*//////��ȡ�Ĵ�����ֵ/////*/
	   	 tmpu16 = ((u16)(tmpbuf[2]) << 8) + tmpbuf[3];	   	 
	   	 tmpu16 = (~tmpu16)+1;
	   	 tmpbuf[1] = (u8)(tmpu16 >> 8); 
	     tmpbuf[2] = (u8)(tmpu16);
	   break;
	   case 0x0E:     /*//////������ЧֵoffsetУ��/////*/
	   case 0x0f:     /*//////���ߵ�����ЧֵoffsetУ��/////*/
	   	 if(regadr == 0x0e)
	   	 {
     	 	 tmpadr = RN8209_REG_IA;
     	 }
     	 else if(regadr == 0x0f)
     	 {
     	 	 tmpadr = RN8209_REG_IB;
     	 }	
	   	 RN8209_ReadData(RN8209_REG_IA,&tmpbuf[0],&tmpbyte); /*//////��ȡ�Ĵ�����ֵ/////*/
	   	 
	   	 tmpu16 = ((u16)(tmpbuf[1]) << 8) + tmpbuf[2];
	   	 tmp8209P = ((u32)(tmpu16))*tmpu16;	   	 
	   	 tmp8209P = (~tmp8209P)+1;
	   	 
	   	 tmpbuf[1] = (u8)(tmp8209P >> 16); 
	     tmpbuf[2] = (u8)(tmp8209P >> 8);
	   break;
	   case 0xff:     /*//////У���ʼ��/////*/
	     RN8209_PInitDefault();
 	 	   RN8209_LoadJBCS();
 	 	 
 	 	   return;      
	   break;
     default:break;
   }                    	                   
	 
	 tmpbuf[0] = regadr;     /*//////д��У�������EEP�к�RN8209��/////*/
   RN8209_WriteDataToEE(&tmpbuf[0]);
	 RN8209_WriteData(&tmpbuf[0]);         
  
   if(regadr == 0x02)      /*//////���㹦�ʻ���ϵ��/////*/
   {         	 
	   tmpu16 = ((u16)(tmpbuf[1]) << 8)+tmpbuf[2];
//	   tmprealP = ((u32)(tmpu16))*1600;     
     tmpfloat = ((float)(tmpu16))*133.3013*(IMPULSE_CONSTANT);
     tmprealP = (u32)(tmpfloat);           
	   UlongTOUcharbuf(tmprealP,&tmpbuf[1]);    		   
	   tmpbuf[0] = 0x11;
     RN8209_WriteDataToEE(&tmpbuf[0]);
   }
   
   RN8209_CalChkSum();   /*///// ����8209У�������ۼ�У��� //////*/
   
	 return;
}
