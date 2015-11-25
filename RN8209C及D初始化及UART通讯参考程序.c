//----------------------start RN8209  ��ַ����---------------------------------------------------//
#define					ADSYSCON 0x00 
#define        	ADEMUCON 0x01
#define        	ADHFConst     	0x02 
#define        	ADPStart      	0x03 
#define        	ADDStart      	0x04 
#define					ADGPQA        	0x05 
#define        	ADGPQB        	0x06 
#define        	ADPhsA        	0x07 
#define        	ADPhsB        	0x08
#define					ADQPHSCAL				0x09    
#define					ADAPOSA 				0x0a
#define        	ADAPOSB 				0x0b
#define        	ADRPOSA 				0x0c
#define        	ADRPOSB 				0x0d
#define        	ADIARMSOS     	0x0e
#define        	ADIBRMSOS     	0x0f
#define        	ADIBGain      	0x10
#define					ADD2FPL       	0x11
#define        	ADD2FPH       	0x12
#define        	ADDCIAH       	0x13
#define        	ADDCIBH       	0x14
#define         ADDCUH		0x15   
#define         ADDCL   	0x16 
#define         ADEMUCON2	0x17
#define					ADPFCnt    	0x20
#define        	ADDFcnt    	0x21
#define        	ADIARMS       	0x22
#define        	ADIBRMS       	0x23
#define        	ADURMS        	0x24
#define					ADUFreq       	0x25
#define        	ADPowerPA     	0x26
#define        	ADPowerPB     	0x27
#define         ADEnergyP  	0x29
#define         ADEnergyP2 	0x2a
#define         ADEnergyD  	0x2b
#define         ADEnergyD2    	0x2c
#define         ADEMUStatus   	0x2d
#define         ADSPL_IA      	0x30
#define         ADSPL_IB      	0x31
#define         ADSPL_U       	0x32
#define         ADIE  		0x40
#define         ADIF  		0x41
#define         ADRIF    	0x42
#define         ADSysStatus  	0x43
#define         ADRData      	0x44
#define         ADWData      	0x45
#define         ADDeviceID   	0x7f
#define         WriteEn   	0xea
//----------------------end RN8209  ��ַ����-----------------------------------------------//
//---start У������ļ�-------���ɸ��ݼ���оƬ���ģ�
typedef struct 
{		
	u16			SYSCON;
	u16			EMUCON;
	u16			HFConst;
	u16			PStart;	
	u16			QStart;  			//10
	u16			GPQA;    	
	u16			GPQB;    	
	u16			IAGain;  	
	u16			UGain;   	
	u16			IBGain;  	
	u16			PhsA;	   	
	u16			PhsB;    	
	u16			QPhsCal; 			//22
	u16			APOSA;   	
	u16			APOSB;	 	
	u16			RPOSA;   	
	u16			RPOSB;   	
	u16			IARMSOS; 			//32
	u16			IBRMSOS;			//34
	u16			EMUCON2; 	
	float		KUrms;								// ��ѹϵ��
	float		KIArms;								// Aͨ������ϵ��
	float		KIBrms;								// Bͨ������ϵ��
	float		KPrms;								// ����ϵ��
	u16			RealUI[2];						// ������ʾֵ�����ʴ��ڴ�ֵʱ��ʾ 0.2%
	u32			RealPw;								// ������ʾֵ���������ڴ�ֵʱ��ʾ 0.2%
	u32			ChkSum;             	
	u16			RTCDota0;							// RTCУ���Ĵ���
	u8			TemperAdj[2];					// �ߵ��²���ֵ
	u8			RTCAdj[4];						// RTC�ߵ���ʱ����ֵ
	u8			CurAdj;								// ����Ӱ�첹��ֵ
	u8 			OfsetAdjAcVolt[2]; 		//���ݵ�ѹ����OFFSET��ֵ
	u16			CorrectionTemper;  		//У��ʱ�̱�Ƶ��¶�
}sDl645FirmParaFile_TypeDef;		//58 Byte
//---end У������ļ�-------���ɸ��ݼ���оƬ���ģ� 

//---start ����ֵ˲ʱֵ��ת�ļ�-------
typedef struct
{
  u8		ChkErrCnt;
  u32 	Pw[2];   		    //pa,pb   
  u32 	UI[3];          // Ia=UI[0] Inal U         
  u16 	Frequency;   		//����Ƶ�ʣ���λ��                            	
  u32		Pulse;		    	//ǰ̨����
  u16     Pstart;
  //---��������---	
  u32		Pulse_Eg;	    	//�������
  u32 	PDirect;				//���ʷ���
  u32 	ChkSum1;				//����EMU��У�����У��
  // У��ʹ�ò���
  u16		RatintU;				// ���ѹ
	u16		RatingI;				// �����
  u32		TempU;					// ��ǰУ�����ѹ
  u32		TempI;					// ��ǰУ�������
  u32		TempPw;					// ��ǰУ���㹦��
} sDl645FrontTmp_TypeDef;
//---end ����ֵ˲ʱֵ��ת�ļ�-------

//---start ����ֵ˲ʱֵ�ļ�-------
typedef struct
{	
	struct sDl645FrontPubData_TypeDef  
	{
		u16			U;			    		//---��ѹ---NNN.N
		u32	    Ia;			    		//---����NNNN.NNNN(����ֵҪ��3��3С������ֵҪ��2��4С�����λ��ʾ����)---		
		u32	    In;         		//---���ߵ���
		sDF09		Pw;			    		//---˲ʱ�й�p
		u16			Pf;			    		//---��������N.NNN---	���λ��ʾ����{Pf Pfa Pfb Pfc}	
		u16			Angle;		  		//---���NNN.N---		
		u16			Frequency;			//---Ƶ��NN.NN
		u32			PPwave;					//---һ����ƽ������NN.NNNN
		u8      Chnsel;     		
		u16			Temperature;		//---NNN.N  �¶�
		u16			ClockBat;				//---NN.NN  ��ص�ѹ
		u32			tWorkBat;				//---NNNN  ʱ�ӹ���ʱ�䣨���ӣ�
		u8			PDirect;				//---ԭ���ʷ���
		                    		
	  u16    	CfIn; 					//���������ƽ�ж�
	  u8    	CfTime;					//
	  u8    	Step;       		
	  u16   	FrontStamp; 		
	  u16			tMaxI;					// ����������ʱ�䣬0.5sΪ��λ
	  u8			SafeCurFlag;		// �������޲�Ϊ���־
	} PubData;
	
	struct sDl645FrontPriData_TypeDef  
	{		
		u8			Flag;						//---�����쳣��־---
	} PriData;	
	
	struct sDl645FrontPriPara_TypeDef  
	{		
		u32	 PConstE;						//�й�����
		u16	 Crc;
	} PriPara;		
} sDl645Front_TypeDef;	
//---end ����ֵ˲ʱֵ�ļ�-------

//---start ����ͨѶ�����ļ�-------
typedef struct
{
	u16		EFlag;							//ͨѶ״̬
	
  u16 	RxLen;							//�������ݳ���
  u16  	TxLen;
  u32		TimeOutStamp;				//�������ݳ���
  u8 		*pTx;
  
  u8		fBps;								//�����ʱ����־
  u8		NewBps;							//�²�����
  u32 	NewBpsStamp;				//������ʱ��
//u8 		TxAddr;
  
  u8 		RxBuf[MAX_COMPACK_SIZE];//���ջ���
  u8		TxBuf[MAX_COMPACK_SIZE];//���ͻ���
}sComPack_TypeDef;
//---end ͨѶ�����ļ�-------
/*****************************************************************************
** Function name:	fnUSART_RN8209_Init(u8 Cfg)
**
** Description:		����UART��ʼ���������ʡ������ֽڸ�ʽ���ơ����͡������������ã�������оƬ��ʼ��ʱִ��
**
** Parameters:		������
**
** Returned value:	NONE
**
******************************************************************************/
#define PinMode_RN8209RX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xfbffffff) : (GPIO->PMA |= 0x04000000) )	// P3.2
#define PinMode_RN8209TX(x) 		( (x == GPIO_MODE_OUT) ? (GPIO->PMA &= 0xf7ffffff) : (GPIO->PMA |= 0x08000000) )	// P3.3
void fnUSART_RN8209_Init(u8 Cfg)
{
	u32	ClkDiv;
	ClkDiv = fnDl645MainClock_Get();//��ȡϵͳ��ǰʱ��Ƶ��
	switch(Cfg & 0xE0)
	{
		case USART_BPS_600:		//600
			ClkDiv=ClkDiv/(600*16)-1;//����ϵͳ��ǰʱ��Ƶ���봮��ͨѶ���ʣ�����UART2->BAUDֵ
			break;
	  case USART_BPS_1200:	//1200
			ClkDiv=ClkDiv/(1200*16)-1;
			break;
		case USART_BPS_2400:	//2400
			ClkDiv=ClkDiv/(2400*16)-1;
			break;
		case USART_BPS_4800:	//RN8209C��֧�ֲ����ʣ�4800
			ClkDiv=ClkDiv/(4800*16)-1;
			break;
		case USART_BPS_9600:	//9600
			ClkDiv=ClkDiv/(9300*16)-1;
			break;
		default:	
			ClkDiv=ClkDiv/(2400*16)-1;			//2400
			break;
	}
	//UART2����RN8209ͨѶ.
	UART2->BAUD = ClkDiv;
	UART2->CTRL = (3 << 0)	|   /* uart enable ʹ��*/
                  (3 << 6)	|	/* data bit: 8 ����λ*/
                  (2 << 8);	/* even  żУ��*/
	PinMode_RN8209RX(GPIO_MODE_IN);//MCU���ڽ�����������
	PinMode_RN8209TX(GPIO_MODE_OUT);//MCU���ڷ�����������
	return;
}

/***************************************************************************** 
** Function name:	USART_ITConfig(u8 ComPort, FunctionalMODE USART_IT, FunctionalState NewState)                                  
**                                                                             
** Description:		�˿ڹ���������ʽ���ƺ���
**                                                                             
** Parameters:		ComPort������ѡ�񣨴���0��1��2��3����  USART_IT�����ڹ�����ʽѡ�񣨽��ջ��ͣ���
**								NewState������״̬ѡ��ʹ�ܻ�رգ�                                                     
**                                                                             
** Returned value:	NONE                                                       
**                                                                             
******************************************************************************/

void USART_ITConfig(u8 ComPort, FunctionalMODE USART_IT, FunctionalState NewState)
{
	u8 Compose;	
	Compose=(ComPort<<2)|(USART_IT<<1)|(NewState);
	switch(Compose)
	{

	//----------------RN8209-----------------------------
	case (SCOM_PORT_RN8209<<2)|(USART_IT_RX<<1)|DISABLE:	//RN8209ͨ�ſ�|����|�ر�
		UART2->CTRL &=0xffe7; 	//���ν����ж�,���ν��մ����ж�
		UART2->STA = 0x3d;		//������жϱ�־�����մ����־
		break;
	case (SCOM_PORT_RN8209<<2)|(USART_IT_RX<<1)|ENABLE:	//RN8209ͨ�ſ�|����|��
		UART2->CTRL |=0x18; 	//��������ж�,������մ����ж�
		UART2->STA = 0x3d;		//������жϱ�־�����մ����־
		break;
	case (SCOM_PORT_RN8209<<2)|(USART_IT_TX<<1)|DISABLE:	//RN8209ͨ�ſ�|����|�ر�
		UART2->CTRL &=0xfff9;		//���η����ж�
		UART2->STA = 0x02;		//�巢���жϱ�־
		break;
	case (SCOM_PORT_RN8209<<2)|(USART_IT_TX<<1)|ENABLE:	//RN8209ͨ�ſ�|����|��
		UART2->CTRL |=0x06;		//���η����ж�
		UART2->STA = 0x02;		//�巢���жϱ�־

	  UART2->TXD=*(ComPack[SCOM_PORT_RN8209].pTx++);
	  ComPack[SCOM_PORT_RN8209].TxLen--;
		break;
	default: return;
	}
	return;
}


/*****************************************************************************
** Function name:UART2_HANDLER(void)
**
** Description:��RN8209���еײ�ͨѶ�Ĵ����жϺ���������RN8209���ݵĽ��ռ�����
**
** Parameters: NONE
**
** Returned value:	NONE
**
******************************************************************************/
void UART2_HANDLER(void)
{
	u32  status;
	u8	 temp;
	status = UART2->STA;
	/* UART error irq ���ڴ�����*/
	if((UART2->CTRL & 0x10) && (status & 0x3c))
	{
		ComPack[SCOM_PORT_RN8209].RxLen=0;
		ComPack[SCOM_PORT_RN8209].EFlag=SCOMPK_EFLAG_IDLE;
		UART2->STA = status;
	}
	/* receive data complete irq �����жϴ���*/
  	if((UART2->CTRL & 0x8) && (status & 0x1))
  	{
    	temp = UART2->RXD;
    	ComPack[SCOM_PORT_RN8209].RxBuf[ComPack[SCOM_PORT_RN8209].RxLen++]=temp; 
  		UART2->STA = 0x1;			// clear receive IF
  	}
  	
  	/* transmit data complete irq �����жϴ���*/
  	if((UART2->CTRL & 0x4) && (status & 0x2))
  	{
		if(ComPack[SCOM_PORT_RN8209].TxLen>0)
		{
			//for(i=0;i<30;i++) __NOP();
			UART2->TXD=*(ComPack[SCOM_PORT_RN8209].pTx++);
			ComPack[SCOM_PORT_RN8209].TxLen--;
			UART2->STA = 0x2;		
		}
	}
  	UART2->STA = status;//���жϱ�ʶλ
  	return;
}

/*****************************************************************************
** Function name:Rn8209Delay(u16 t)
**
** Description:��ʱ����
**
** Parameters: t ����ʱʱ��
**
** Returned value:	NONE
**
******************************************************************************/

void Rn8209Delay(u16 t)
{
	u16 i;
	if(Dl645Inactive.PubData.InactiveStamp) return;
	while(t--)
	{
		for (i = 0;i < 400;i++)
		  ;
		WDT->EN = 0xbb;
	}
}
/*****************************************************************************
** Function name:fnRN8209_Write(u8 wReg,u8 *pBuf,u8 ucLen)
**
** Description:дRN8209�Ĵ���
**
** Parameters:wReg �Ĵ�����ַ��*pBuf��д��ֵ�Ĵ�ŵ�ַ��ucLen����д��ֵ�ĳ���
**
** Returned value:	������ʶ-�ɹ���ʧ��
**
******************************************************************************/

ErrorStatus fnRN8209_Write(u8 wReg,u8 *pBuf,u8 ucLen)
{
	u8 i,j,temp,chksum,Repeat;
	ErrorStatus	err;	
	if( (ucLen == 0) || (ucLen > 4) ) return(ERROR);
	for( Repeat =2; Repeat != 0 ; Repeat--)	
	{
		err = SUCCESS;	
		ComPack[SCOM_PORT_RN8209].pTx=&ComPack[SCOM_PORT_RN8209].TxBuf[0];	
		
		//д����ǰ���ȷ��������ֽڣ������ֽڵ����λbit[7]=0:��������1��д������bit[6:0]Ϊ�������Ĵ�ĵ�ַ		
		temp =wReg|0x80;//�������Ĵ�����ַ���λ��1��ʹ�����ֽ�Ϊд����
		*(ComPack[SCOM_PORT_RN8209].pTx++)=temp;
		chksum = temp;		
		for(i = ucLen; i > 0;i-- )
		{		
			*(ComPack[SCOM_PORT_RN8209].pTx++)=pBuf[i-1];	//��RN8209��������		
			chksum +=pBuf[i-1];
		}
		chksum = ~chksum;
		*(ComPack[SCOM_PORT_RN8209].pTx++)=chksum;
		ComPack[SCOM_PORT_RN8209].TxLen = ucLen+2;
		ComPack[SCOM_PORT_RN8209].pTx=&ComPack[SCOM_PORT_RN8209].TxBuf[0];
		USART_ITConfig(SCOM_PORT_RN8209 , USART_IT_TX, ENABLE);         //����ʹ��	
		Rn8209Delay(30);//�ȴ����ڷ������
		
		//RN8209дʹ�ܻ�д��������д��WData�Ĵ�����飨�Ƿ���ȷд�룩-----------------------	
		ComPack[SCOM_PORT_RN8209].pTx=&ComPack[SCOM_PORT_RN8209].TxBuf[0];	
    if(wReg == 0xEA) 
    {//RN8209дʹ�ܻ�д����
    	*(ComPack[SCOM_PORT_RN8209].pTx)=0X43;
    }	
    else 
    {//��д��WData�Ĵ������
    	*(ComPack[SCOM_PORT_RN8209].pTx)=wReg;
    }	
		ComPack[SCOM_PORT_RN8209].TxLen = 1;	
		ComPack[SCOM_PORT_RN8209].RxLen=0; 
		
		USART_ITConfig(SCOM_PORT_RN8209 , USART_IT_RX, ENABLE);         //����ʹ��  
		USART_ITConfig(SCOM_PORT_RN8209 , USART_IT_TX, ENABLE);         //����ʹ��
		memset(&ComPack[SCOM_PORT_RN8209].RxBuf[0] , 0x00 , 10);
		
	  Rn8209Delay(25);//�ȴ�ͨѶ���
	  
	  fnWDT_Restart();
	  j = 0;
	  if(wReg == 0xEA)
	 	{//RN8209дʹ�ܻ�д����
	 		if(pBuf[0] == 0XE5) 
	 		{//RN8209дʹ��
	 			temp = ComPack[SCOM_PORT_RN8209].RxBuf[0];
	 			if(!(temp&0x10)) err = ERROR; 
	 		}
	 		else if(pBuf[0] == 0XDC)
	 		{//RN8209д����
	 			temp = ComPack[SCOM_PORT_RN8209].RxBuf[0];
	 			if(temp&0x10) err = ERROR; 
	 		}
	 	}
	 	else
	 	{	//��д��WData�Ĵ�����飨��������ComPack[SCOM_PORT_RN8209].RxBuf[j++]����������pBuf[i-1]��
		  for(i = ucLen; i > 0;i--)
			{
				temp = ComPack[SCOM_PORT_RN8209].RxBuf[j++]; 
				if((wReg == 0)&&(i==2)) temp = 0;//�쳣����
				if(temp != pBuf[i-1]) 
				{
					err = ERROR;
					break;
				}
			}
		}
											
	 fnWDT_Restart();
	 if(err == SUCCESS) break;
	 fnScomPk_Init(SCOM_PORT_RN8209);
	}
	USART_ITConfig(SCOM_PORT_RN8209 , USART_IT_TX, DISABLE);         //����ʹ�ܹر�
	return(err);
}
/*****************************************************************************  
** Function name:fnRN8209_Read(u8 wReg,u8 *pBuf,u8 ucLen)                      
**                                                                              
** Description:��RN8209�Ĵ���                                                   
**                                                                              
** Parameters:wReg �Ĵ�����ַ��*pBuf����ֵ�Ĵ�ŵ�ַ��ucLen������ֵ�ĳ���   
**                                                                              
** Returned value:	������ʶ-�ɹ���ʧ��                                         
**                                                                              
******************************************************************************/ 

ErrorStatus fnRN8209_Read(u8 wReg,u8 *pBuf,u8 ucLen)
{
	u8 i,temp,Repeat;
	u8 j=0;
	u8 chksum=0;	
	ErrorStatus	err;
	if(ucLen == 0) return(ERROR);

	for( Repeat=2; Repeat != 0 ; Repeat--)	
	{
		err  = SUCCESS;	    
		temp = wReg ;
		chksum=wReg;
		j = 0;	  
		
    ComPack[SCOM_PORT_RN8209].pTx=&ComPack[SCOM_PORT_RN8209].TxBuf[0];	
    
    //������ǰ���ȷ��������ֽڣ������ֽڵ����λbit[7]=0:��������1��д������bit[6:0]Ϊ�������Ĵ�ĵ�ַ
    *(ComPack[SCOM_PORT_RN8209].pTx)=temp;	
		ComPack[SCOM_PORT_RN8209].TxLen = 1;	

		USART_ITConfig(SCOM_PORT_RN8209 , USART_IT_RX, ENABLE);         //����ʹ��  

		USART_ITConfig(SCOM_PORT_RN8209 , USART_IT_TX, ENABLE);         //����ʹ��
		memset(&ComPack[SCOM_PORT_RN8209].RxBuf[0] , 0x00 , 10);
	    
	  Rn8209Delay(25);//�ӳ٣��Եȴ����ݽ������
	  fnWDT_Restart();	
	    		        			        				    
		for(i = ucLen; i > 0;i--)
		{
			pBuf[i-1] = ComPack[SCOM_PORT_RN8209].RxBuf[j++]; //�����յ������ݱ��浽����pBuf[]
			chksum += pBuf[i-1];//����������ݵ�У���
		}
		chksum = ~chksum;
		temp=ComPack[SCOM_PORT_RN8209].RxBuf[j++];
		
		if(temp!=chksum)  
		{//��У��ʹ������������
			err = ERROR;
			for(i = ucLen; i > 0;i--) pBuf[i-1] = 0;
		}
		if(err == SUCCESS) break;
		fnScomPk_Init(SCOM_PORT_RN8209);	  	  	
	}

	USART_ITConfig(SCOM_PORT_RN8209 , USART_IT_TX, DISABLE);         //����ʹ�ܹر�
	ComPack[SCOM_PORT_RN8209].RxLen=0;                               //  

	return(err);
}
/*****************************************************************************
** Function name:	fnDl645_ComInitRN8209(void)
**
** Description:		�������У��������������RN8209�Ĵ���
**
** Parameters:		NONE
**
** Returned value:	NONE
**
******************************************************************************/
void fnDl645_ComInitRN8209(void)
{
	Dl645FirmPara.HFConst = 0x1000;
	Dl645FirmPara.PStart = 0x0060;
	Dl645FirmPara.QStart  = 0x0120;
	Dl645FirmPara.GPQA = 0x0000;
	Dl645FirmPara.GPQB = 0x0000;
	Dl645FirmPara.PhsA= 0x0000;
	Dl645FirmPara.PhsB= 0x0000;
	Dl645FirmPara.QPhsCal = 0x0000;
	Dl645FirmPara.APOSA = 0x0000;
	Dl645FirmPara.APOSB = 0x0000;
	Dl645FirmPara.RPOSA = 0x0000;
	Dl645FirmPara.RPOSB = 0x0000;
	Dl645FirmPara.IARMSOS = 0x0000;
	Dl645FirmPara.IBRMSOS = 0x0000;
	Dl645FirmPara.IBGain = 0x0000;
	//Dl645FirmPara.KUrms= 0x00000000;
	//Dl645FirmPara.KIArms= 0x00000000;
	//Dl645FirmPara.KIBrms= 0x00000000;
	
	Dl645FirmPara.KPrms= 0x00000000;
	Dl645RN8209DataComm.ucTemp8 =0XE5;
	//if(fnRN8209_Write( 0xEA , Dl645RN8209DataComm.ucTempBuf , 1 ) == ERROR) return ;   //дʹ��
	fnRN8209_Write( 0xEA , Dl645RN8209DataComm.ucTempBuf , 1 );
	
	//if(fnRN8209_Write( 0x00 , (u8 *)&Dl645FirmPara.SYSCON , 2 ) == ERROR) return ;   //дϵͳ���ƼĴ���
	//if(fnRN8209_Write( 0x01 , (u8 *)&Dl645FirmPara.EMUCON , 2 ) == ERROR) return ;   //д�������ƼĴ���
		
	if(fnRN8209_Write( ADHFConst , (u8 *)&Dl645FirmPara.HFConst , 2 ) == ERROR) return ; 
	if(fnRN8209_Write( ADPStart , (u8 *)&Dl645FirmPara.PStart , 2 ) == ERROR) return ; 	
	if(fnRN8209_Write( ADDStart , (u8 *)&Dl645FirmPara.QStart , 2 ) == ERROR) return ; 
	
	if(fnRN8209_Write( ADGPQA , (u8 *)&Dl645FirmPara.GPQA , 2 ) == ERROR) return;   //д��������Ĵ���
	if(fnRN8209_Write( ADGPQB , (u8 *)&Dl645FirmPara.GPQB , 2 ) == ERROR) return;   //д��������Ĵ���
	if(fnRN8209_Write( ADPhsA , (u8 *)&Dl645FirmPara.PhsA , 1 ) == ERROR) return;   //д��λУ���Ĵ���
	if(fnRN8209_Write( ADPhsB , (u8 *)&Dl645FirmPara.PhsB , 1 ) == ERROR) return;   //д��λУ���Ĵ���
	if(fnRN8209_Write( ADQPHSCAL , (u8 *)&Dl645FirmPara.QPhsCal , 2 ) == ERROR) return;    
	if(fnRN8209_Write( ADAPOSA , (u8 *)&Dl645FirmPara.APOSA , 2 ) == ERROR) return;
	if(fnRN8209_Write( ADAPOSB , (u8 *)&Dl645FirmPara.APOSB , 2 ) == ERROR) return;
	if(fnRN8209_Write( ADRPOSA , (u8 *)&Dl645FirmPara.RPOSA , 2 ) == ERROR) return;
	if(fnRN8209_Write( ADRPOSB , (u8 *)&Dl645FirmPara.RPOSB , 2 ) == ERROR) return;
	if(fnRN8209_Write( ADIARMSOS , (u8 *)&Dl645FirmPara.IARMSOS , 2 ) == ERROR) return;
	if(fnRN8209_Write( ADIBRMSOS , (u8 *)&Dl645FirmPara.IBRMSOS , 2 ) == ERROR) return;
	if(fnRN8209_Write( ADIBGain , (u8 *)&Dl645FirmPara.IBGain , 2 ) == ERROR) return;
	if(fnRN8209_Write( ADEMUCON2 , (u8 *)&Dl645FirmPara.EMUCON2 , 2 ) == ERROR) return;
	fnWDT_Restart();
	Dl645RN8209DataComm.ucTemp8 =0XDC;
	fnRN8209_Write( 0xEA , Dl645RN8209DataComm.ucTempBuf , 1 ) ; 
	fnDl645File_Write(Dl645FileId_FirmPara,Dl645FileItemInfoOffAddr_FirmPara_HFConst,(u8 *)&Dl645FirmPara.HFConst,42);

}

/*****************************************************************************
** Function name:	fnEMU_Init(void)
**
** Description:		����EMU��ʼ����������ʼ��RN8209�Ĵ���
**
** Parameters:		NONE
**
** Returned value:	NONE
**
******************************************************************************/
void fnEMU_Init(void)
{

	//д����оƬ�������
	Dl645FirmPara.EMUCON2 = 0x300;
	
  Dl645RN8209DataComm.ucTemp8 =0XE5;
  //if(fnRN8209_Write( 0xEA , Dl645RN8209DataComm.ucTempBuf , 1 ) == ERROR) return ;   //дʹ��
  fnRN8209_Write( 0xEA , Dl645RN8209DataComm.ucTempBuf , 1 ); 
	
	//if(fnRN8209_Write( ADSYSCON , (u8 *)&Dl645FirmPara.SYSCON , 2 ) == ERROR) return ;   //дϵͳ���ƼĴ���
	//if(fnRN8209_Write( ADEMUCON , (u8 *)&Dl645FirmPara.EMUCON , 2 ) == ERROR) return ;   //д�������ƼĴ���
	if(fnRN8209_Write( ADHFConst , (u8 *)&Dl645FirmPara.HFConst , 2 ) == ERROR) return ; 
	if(fnRN8209_Write( ADPStart , (u8 *)&Dl645FirmPara.PStart , 2 ) == ERROR) return ; 	
	if(fnRN8209_Write( ADDStart , (u8 *)&Dl645FirmPara.QStart , 2 ) == ERROR) return ; 
	
	if(fnRN8209_Write( ADGPQA , (u8 *)&Dl645FirmPara.GPQA , 2 ) == ERROR) return;   //д��������Ĵ���
	if(fnRN8209_Write( ADGPQB , (u8 *)&Dl645FirmPara.GPQB , 2 ) == ERROR) return;   //д��������Ĵ���
	if(fnRN8209_Write( ADPhsA , (u8 *)&Dl645FirmPara.PhsA , 1 ) == ERROR) return;   //д��λУ���Ĵ���
	if(fnRN8209_Write( ADPhsB , (u8 *)&Dl645FirmPara.PhsB , 1 ) == ERROR) return;   //д��λУ���Ĵ���
	if(fnRN8209_Write( ADQPHSCAL , (u8 *)&Dl645FirmPara.QPhsCal , 2 ) == ERROR) return;    
  if(fnRN8209_Write( ADAPOSA , (u8 *)&Dl645FirmPara.APOSA , 2 ) == ERROR) return;
  if(fnRN8209_Write( ADAPOSB , (u8 *)&Dl645FirmPara.APOSB , 2 ) == ERROR) return;
  if(fnRN8209_Write( ADRPOSA , (u8 *)&Dl645FirmPara.RPOSA , 2 ) == ERROR) return;
  if(fnRN8209_Write( ADRPOSB , (u8 *)&Dl645FirmPara.RPOSB , 2 ) == ERROR) return;
  if(fnRN8209_Write( ADIARMSOS , (u8 *)&Dl645FirmPara.IARMSOS , 2 ) == ERROR) return;
  if(fnRN8209_Write( ADIBRMSOS , (u8 *)&Dl645FirmPara.IBRMSOS , 2 ) == ERROR) return;
  if(fnRN8209_Write( ADIBGain , (u8 *)&Dl645FirmPara.IBGain , 2 ) == ERROR) return;
  if(fnRN8209_Write( ADEMUCON2 , (u8 *)&Dl645FirmPara.EMUCON2 , 2 ) == ERROR) return;
  fnWDT_Restart();
  Dl645RN8209DataComm.ucTemp8 =0XDC;
  fnRN8209_Write( 0xEA , Dl645RN8209DataComm.ucTempBuf , 1 ) ; //�ر�дʹ�� 
}
/*****************************************************************************
** Function name:	fnDl645Front_Init(void)
**
** Description:		����ģ���ʼ���������������õ���RAM���ݽ��г�ʼ��
**
** Parameters:		NONE
**
** Returned value:	NONE
**
******************************************************************************/
void fnDl645Front_Init(void)
{
	u8 	i,j;
	u32 ChkSum;	
	Dl645Front.PriData.Flag |= FRONT_FLAG_RN8209RST;//��RN8209��ʼ����ʶλ
	
	memset(&Dl645FrontTmp , 0 , sizeof(sDl645FrontTmp_TypeDef) );//������õ���RAM����
	memset(&Dl645Front , 0 , sizeof(sDl645Front_TypeDef) );//������õ���RAM����	
	
	//д��У��Ĵ��������У���Ƿ���ȷ����ȷ�˳�������ȷ�ٴ�д�롣���ѭ��д�����5�Ρ�
	fnDl645File_Read(Dl645FileId_FirmPara , 0 , (u8 *)&Dl645FirmPara , sizeof(sDl645FirmParaFile_TypeDef) );//��E2�б����У�����
	Dl645FrontTmp.ChkSum1 = Dl645FirmPara.ChkSum;
	for(i=0;i<5;i++)
	{
		fnEMU_Init();
		SystemDelay(10);
		ChkSum = 0;		
		for(j=0;j<5;j++)
		{
			fnRN8209_Read( ADEMUStatus , (u8 *)&ChkSum , 3 ) ;
			if(!(ChkSum & 0x010000))	break;
			SystemDelay(10);
		}
		fnWDT_Restart();
		ChkSum = ChkSum & 0x0000ffff;
		if(Dl645FrontTmp.ChkSum1 == ChkSum) 
		{
			Dl645Front.PriData.Flag &= ~FRONT_FLAG_RN8209RST;
			break;
		}			
	}
	if(i>=5)
	{//��У��ֵ����5�δ��������¼���У��ֵ
		Dl645FirmPara.ChkSum = 0;
		SystemDelay(1);		
		Dl645FirmPara.ChkSum = ChkSum & 0x0000ffff;
		Dl645FrontTmp.ChkSum1 = Dl645FirmPara.ChkSum;
		fnDl645File_Write(Dl645FileId_FirmPara,Dl645FileItemInfoOffAddr_FirmPara_ChkSum,(u8 *)&Dl645FirmPara.ChkSum,4);
	}
	
}
/*****************************************************************************
** Function name:	fnDl645Front_Exec(void)
**
** Description:		�Ӽ���оƬ��ȡ���ݣ���ѹ�����������ʡ���������������ѹ��������Ƶ�ʡ��������ؼ���
**
** Parameters:		NONE
**
** Returned value:	NONE
**
******************************************************************************/	
	
void fnDl645Front_Exec(void)
{ 
	u8 i;
	u32 TempU,TempI,TempIn;
	u32 TempStatus;
	u16 TempAngle;	
	u8	PFlag;		
	
	if(Dl645Front.PriData.Flag & FRONT_FLAG_RN8209RST)//RN8209��λ
	{
		fnDl645Front_Init();
		Dl645Front.PriData.Flag &= ~FRONT_FLAG_RN8209RST;
		return;
	}
	  
  //������״̬��У���
	TempStatus = 0;
	fnRN8209_Read( 0x2d , (u8 *)&TempStatus , 3 ) ;
	if(!(TempStatus & 0x010000))
	{//У������У��ͼ�������ɣ�У��ֵ����
		if(Dl645FrontTmp.ChkSum1 == (TempStatus&0x0000ffff)) 
		{//У��ֵ��ȷ����У��������
			Dl645FrontTmp.ChkErrCnt = 0 ;
		}
		else 
		{
			Dl645FrontTmp.ChkErrCnt++; 
			if(Dl645FrontTmp.ChkErrCnt > 3) 
			{//У������������3�κ󣬸�λRN8209
				Dl645Front.PriData.Flag |= FRONT_FLAG_RN8209RST;
				Dl645FrontTmp.ChkErrCnt = 0 ;
			}
			return;
		}
	}
    //�жϹ��ʷ���
  if(TempStatus & 0x020000) 
  {
  	Dl645Front.PubData.PDirect =  INVERSION ;
  }  //�жϹ��ʷ����Ƿ��ġ�
  else 
  {
  	Dl645Front.PubData.PDirect = POSITIVE ;
  }    

  //����ѹ��������������������Ϊ�����д���
	for(i = 0 ; i < 3 ; i++)
  {
		Dl645FrontTmp.UI[i] = 0;//���ѹ����������
		fnRN8209_Read( 0x22+i , (u8 *)&Dl645FrontTmp.UI[i] , 3 ) ;
		if(Dl645FrontTmp.UI[i]&0x00800000) Dl645FrontTmp.UI[i]=0;
  }
    //��Ƶ��
	fnRN8209_Read( 0x25 , (u8 *)&Dl645FrontTmp.Frequency , 2 ) ;
    //�����ʵ�������������Ϊ�����д���
  fnRN8209_Read( 0x26 , (u8 *)&Dl645FrontTmp.Pw[0] , 4 ) ;
	fnRN8209_Read( 0x27 , (u8 *)&Dl645FrontTmp.Pw[1] , 4 ) ;
	if(Dl645FrontTmp.Pw[0]&0x80000000) 
	{
		Dl645FrontTmp.Pw[0]=(~Dl645FrontTmp.Pw[0])+1;PFlag = 1;
	}
	else PFlag = 0;
	//���㹦��
	Dl645Front.PubData.Pw = fnDFConver_Hex32ToDF09((s32)((Dl645FrontTmp.Pw[0])*((Dl645FirmPara.KPrms))));
	if(PFlag) Dl645Front.PubData.Pw.S = 1;
	//������ѹ����
	Dl645Front.PubData.U = 0x7fff&(fnDFConver_Bcd16To16((s16)(Dl645FrontTmp.UI[2]/(10*(Dl645FirmPara.KUrms))))); //��ѹ
  TempI = (s32)(Dl645FrontTmp.UI[0]/(Dl645FirmPara.KIArms));   
  TempIn = (s32)(Dl645FrontTmp.UI[1]/(Dl645FirmPara.KIBrms));	
	Dl645Front.PubData.Ia = fnDFConver_Bcd32To32(TempI);	
	Dl645Front.PubData.In = fnDFConver_Bcd32To32(TempIn);
	if(PFlag) Dl645Front.PubData.Ia |= 0x80000000;
	
	//������Чֵ����,������������  
	//���㹦������
	TempU &=0x00ffffff; 
	if(TempU&0x00800000) TempU=((~TempU)&0x00ffffff)+1;
	Dl645Front.PubData.Pf = fnHexToBcd_u16((u16)((float)TempU/8388.608));
	Dl645Front.PubData.Angle=	fnHexToBcd_u16(TempAngle*3600/32768); 
	//����С��0.0030�����㣬����������0.999
	if(((Dl645Front.PubData.Pw.Dat2&0x7f)==0)&&(Dl645Front.PubData.Pw.Dat1==0)&&(Dl645Front.PubData.Pw.Dat0<0x30)) 
	{
		Dl645Front.PubData.Pw.Dat0 = 0;
		Dl645Front.PubData.Pw.Dat1 = 0;
		Dl645Front.PubData.Pw.Dat2 = 0;
	}
	//����С���𶯵���������
	if((Dl645Front.PubData.Ia&0x7fffffff) < 0x00000150) {Dl645Front.PubData.Ia = 0;Dl645Front.PubData.Pf = 0x0999;}
	if((Dl645Front.PubData.In&0x7fffffff) < 0x00000150) Dl645Front.PubData.In = 0;
	
	//��ѹƵ�ʼ���	
	Dl645Front.PubData.Frequency = fnHexToBcd_u16((u16)(((u32)357954500)/((u32)8*Dl645FrontTmp.Frequency)));	
	if((Dl645Front.PubData.Ia&0x7fffffff) > 0x00550000) 
	{	
		if(Dl645Front.PubData.tMaxI < 2405) Dl645Front.PubData.tMaxI++;
	}
	else Dl645Front.PubData.tMaxI = 0;
	
	if(Dl645Front.PubData.Pw.S) Dl645Front.PubData.Pf |=0x8000;
	
	//���������壬�������������
	Dl645FrontTmp.Pulse = 0;
	fnRN8209_Read( 0x2a , (u8 *)&Dl645FrontTmp.Pulse , 3 ) ;
	if(Dl645FrontTmp.Pulse > 100) Dl645FrontTmp.Pulse = 0;	//�ݴ���������������
	Dl645FrontTmp.Pulse_Eg+=Dl645FrontTmp.Pulse;
	
	#if  DL645SOFT_DEBUG
	Dl645FrontTmp.Pulse_Eg+=1;
	#endif 
	
}