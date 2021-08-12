#include "Data.h"
#include "visa.h"
#define	ADD_DATA    0x3a4
#define	ADD_ADD     0x3a6
#define	ADD_INP     0x3a8

#define F_MEM			2
#define M_MEM			4


// PMU Mode
#define	FVMI			0
#define	FIMV			1
#define	DMV				2

// DPS Mode
#define	DPS1			1
#define	DPS2			2
#define	DPS3			3
#define	DPS4			4

#define	TURN_DPS_ON	    0
#define	ADJUST_DPS	    1
#define	TURN_DPS_OFF	2

//DPS IRange
#define	R200NA			0
#define	R2UA			1
#define	R20UA			2
#define	R200UA			3
#define	R2MA			4
#define	R20MA			5
#define	R250MA			6
#define	R200MA			6

// FMT Mode
#define	NRZ				0
#define	RO				1
#define	RZ				2
#define	NRZ0			3

///////////////////////////////////////////////////////////
// ��Ƶ��������
#define	R4V				0
#define	R400MV			1
#define	R40MV			2
#define	R4MV			3

// ��Ƶ��ͨͨ·ѡ��
#define	LPPASS			0
#define	LP20			1
#define	LP250			2
// ��Ƶ��ͨͨ·ѡ��
#define	BPPASS			0
#define	BP1K			1
#define	BPNOT			2
// I Unit
#define A               0
#define	UA				2
#define	MA				1

// V Unit
#define	MV				4
#define	V				3

//hz Unit
#define HZ              5
#define KHZ             6

////////////////////pattern/////////////////////
#define NOGO			0
#define GO_NOGO			1
#define PRINT_ON_FAIL	2

#define	NOAPG 			0
#define	APGEN1			1
#define	APGEN2			2
#define	APGEN3			3
#define No_UpLimit		1e100
#define No_LoLimit	   -1e100

///////////////////////////////////////////////////////////
// ʱ�������ʱ��־
// Start Time
#define	T1				0
#define	T2				1
// Stop  Time
#define	POS				0
#define	NEG				1

//#define BIN(bin)    if (SET_BIN(bin))  	return;
void	SET_LDCLK();
WORD READ_MEMORY(int n_CHANNEL,int FDM_MEM);
BYTE  *LOAD_PATTERN(CString FileName);
BOOL  RUN_PATTERN(CString csItem,int start_idx,int get_fail,int apgen,int time_range );
BOOL  RUN_PATTERN(int start_idx,int get_fail,int apgen,int time_range );
BOOL  RUN_PATTERN(int start_idx,BYTE *addr,int get_fail,int apgen,int time_range);
void  DEBUG_PATTERN(int PC,BYTE *addr,int get_fail, int apgen,int time_range,int TestMode );
DWORD READ_PC();


/////////////////���Եơ�����״̬////////////////////
BOOL ConnectToPCI();
void SET_PASS_LIGHT();
void SET_FAIL_LIGHT();
void CLEAR_START_STAT();
BOOL READ_START_STAT();
void CLEAR_PASS_FAIL_LIGHT();
void     SET_READ_MEM_START(int FDM_MEM);
BYTE     READ_MEMORY(int n_CHANNEL);
        
//	void WriteAddr(WORD add, WORD data);
//	void WriteAddData(WORD data);
//	void WriteAddr(WORD wAddr, BOOL bIsIO);
//	void WriteAdd(WORD add,BOOL isIO=TRUE);

BOOL WriteDataExt(ULONG Addr,USHORT Data);
//BOOL ReadDataExt(ULONG Addr,USHORT * pData);
USHORT ReadDataExt(ULONG Addr);

	long Delay(double us);

	BOOL LoadFile(CString fname);
	BOOL GetData(CString str, double &xp, double &yp);
	void	LoadInstruction(BYTE *instruction);				// װͼ��ָ��
	void	LoadData(BYTE* data,int width);					// ����ͼ������        
	void LoadBin_pmu( );

	void LoadText_pmu( );
	void LoadText_dps( );
	void LoadText_vref( );
	void LoadText_vout( );

	void Modify_vs4(int i,double k,double b);
	void Load_Pmu_Cali();
	void	Modify_asx(int i,double k,double b);
	void Modify_dmv(int i,double k,double b);
	void Modify_pmu(int i,double k,double b);
	void Modify_dps(int i,double k,double b);
	void Modify_voh(int i,double k,double b);
	void Modify_vol(int i,double k,double b);
	void Modify_vout(int i,double k,double b);
	void Modify_vix(int i,double k,double b);
	void Modify_vih(int i,double k,double b);
	void Modify_vil(int i,double k,double b);
	void Modify_vis(int i,double k,double b);
	void Modify_Hdps(int i,double k,double b);
	void Modify_Rdps(int i,double k,double b);
	void Modify_avm(int i,double k,double b);
	void Clear_Pmu();
	void REDEFINE_POWER(BYTE No,double Vdd,unsigned int Vdd_Unit);
	void SET_POWER(BYTE No,BYTE FunStyle);
	void Init_Drv();
	void Fmt_Data(int *board,int boardNum,int nchannel,BYTE fmt,WORD *wdata,WORD *wdata2,BOOL *f0,BOOL *f1);
	void	CLEAR_ALL();
//PMU
	void	PMU_CONDITIONS( unsigned int Mode,
							double Value,		unsigned int Value_Unit,
							double Clamp_Value, unsigned int Clamp_Unit);
	double	PMU_MEASURE(	unsigned int pin,	unsigned int tDelay);
    BOOL	PMU_MEASURE(CString csPin,	unsigned int tDelay,
							CString csItem,	int  csUnit,
							double  fUpLimit,double   fDnLimit);
	double	PMU_MEASURE(unsigned int tDelay);
//DPS
	void	SET_DPS(BYTE No,        
					double Vdd,		unsigned int Vdd_Unit,
					double Iclamp,	unsigned int Iclamp_Unit);
	double	DPS_MEASURE(BYTE No,	BYTE IRange,unsigned int Delayms);
	double	DPS_MEASURE(BYTE No,	unsigned int Delayms);
	BOOL	DPS_MEASURE(BYTE No,	BYTE IRange,unsigned int Delayms,
							   CString	csItem, int csUnit,
							   double	fIccMax,double fIccMin);

	void	Init_Drv();
	void	DPS_OFF(BYTE No);
	//��ʼ��AS
	bool Init_AS();
//FORMAT        
	void	RESET_CHB();
	void	FORMAT(BYTE fmt,CString csChannel);
//RLY AND Vres
	void	SET_RELAY(LPCTSTR sRelay);
	void	CLOSE_RELAY(CString sRelay);
	void	CLEAR_RELAY(CString sRelay);
	void	SET_INPUT_LEVEL (double Voh,double Vol);
	void	SET_OUTPUT_LEVEL(double Voh,double Vol);
//TIMING
	void	SET_PERIOD(unsigned int period);
	void	SET_TIMING(unsigned int LeadEdge,unsigned int Fwidth,unsigned int Ctg);
	BOOL	RUN_TIMING();
	void	SET_TRUN();
	void	STOP_TIMING();
	void	CLEAR_TIMING();
	void	SET_STEP_TIMING();
	BOOL	RUN_STEP_TIMING(void);
	void	CLEAR_STEP_TIMING();
	BYTE	READ_FAIL_DATA(int n_CHANNEL);

//RDPS
	void    SET_RDPS(	double fVdd,	unsigned int uiVdd_Unit,
								double fIclamp,	unsigned int uiIclamp_Unit);
	double  RDPS_MEASURE(unsigned int uiDelayms);
	void	RDPS_OFF_POS();		// �ر�RDPS��
	void	CLEAR_RDPS(void);	// ��RDPS

//HDPS
	void	SET_DPS_POS(	double fVdd,	unsigned int uiVdd_Unit,
								double fIclamp,	unsigned int uiIclamp_Unit);
	void	SET_DPS_POS_CALB(double Vdd,		unsigned int Vdd_Unit,
						double Iclamp,	unsigned int Iclamp_Unit);
	void	SET_DPS_NEG(	double fVdd,	unsigned int uiVdd_Unit,
								double fIclamp,	unsigned int uiIclamp_Unit);
	void	SET_DPS_NEG_CALB(	double fVdd,	unsigned int uiVdd_Unit,
								double fIclamp,	unsigned int uiIclamp_Unit);
	double	DPS_MEASURE_POS(unsigned int uiDelayms);
	double	DPS_MEASURE_NEG(unsigned int uiDelayms);
	void	DPS_OFF_POS();		// �ر�DPS��
	void	DPS_OFF_NEG();		// �ر�DPS��
	double	MEASURE_POS_REGVO(	double	fIload,int	iIunit,
								double	fVout, int	iVunit,
								int		iRtimes);
	double	MEASURE_NEG_REGVO(	double	fIload,int	iIunit,
								double	fVout, int	iVunit,
								int		iRtimes);
	//	�����Ĳ�
	void	SET_POS_RIPPLE(double fVol,	int iVolUnit,	double freq);
	void	CLEAR_POS_RIPPLE();
	void	SET_NEG_RIPPLE(double fVol,	int iVolUnit,	double freq);
	void	CLEAR_NEG_RIPPLE();

//VIS
	void	SET_VIS( unsigned int Mode,
					double Value,		unsigned int Value_Unit,
					double Clamp_Value, unsigned int Clamp_Unit);
	double	VI_MEASURE(unsigned int uiDelayms);	
	void	CLEAR_VIS();

	//	PMU��������ο���ƽ
	double	VOH_MEASURE(double fVoltage,int iVolUnit,unsigned int tDelay);
	double	VOL_MEASURE(double fVoltage,int iVolUnit,unsigned int tDelay);
	
	double	DVM_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);
	double	DVM_MEASURE_1(double fVoltage,int iVolUnit,unsigned int tDelay);
	double	DVM_DIFF_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);	
	
	
	double	DVM_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);
	double	DVM_DIFF_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);

	
	//	��ƵԴ
	void	SET_AS		(double	fVol,	int iVolUnit,double	freq);
	void	SET_AS		(double	fVol,	int iVolUnit,double	freq,int iUnit);
	void	SET_AS_CALB	(double	fVol,	int iVolUnit,double	freq,int iUnit);

	void	SET_AS_DC	(double fVol,	int iVolUnit);
	void	SET_AS_DC_CALB(double fVol,	int iVolUnit);
	void	SET_AS_SQUARE		(double fVol,	int iVolUnit,double	freq);
	void	SET_AS_SQUARE		(double	fVol, int iVolUnit,double freq,int iUnit);


//AVM	
	double	AVM_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);
	double	AVM_MEASURE_CALB(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);
	int		SET_AVM(int iLpSel,int iBpSel,double fvRange, int iUnit);
	void	SET_AVM_RANGE(int ivRange);


// ƫ�õ�ѹԴ
	void	SET_VS1(double fVolt,	int iVolUnit);
	void	SET_VS2(double fVolt,	int iVolUnit);
	void	SET_VS3(double fVolt,	int iVolUnit);
	void    SET_VS(int iCanal, double fVolt, int iVolUnit);
	void	SET_VS4(double fVolt,	int iVolUnit);
	void	CLEAR_VS();

	int		RUN_PATTERN(int		iStartIdx,					// ����ͼ��
		BYTE	*btAddr,
		int		iINH_FAIL,
		unsigned int	iTimeRange);
	BOOL	RUN_PATTERN(int start_idx,
		int get_fail,
						int time_range);



////////////////�����/////////////////////
	BOOL	SET_BIN(unsigned char bin);
	BOOL	init(CDataLog *dlog,CString PathName);
//	void DEBUGMODE();
	void	SET_PMU(CString csPin,		unsigned int Mode,	
	               double   Value,		unsigned int Value_Unit,
	               double  Clamp_Value,	unsigned int Clamp_Unit);
	void	SET_PMU(unsigned int Mode,	
					double   Value,		unsigned int Value_Unit,
					double  Clamp_Value,	unsigned int Clamp_Unit);
	void	CLR_PMU(void);
	BOOL    SHOW_RESULT(CString csItem, double measure_value,int  csUnit,double  fUpLimit,double fDnLimit);
	BOOL    SHOW_RESULT(CString csItem, double measure_value,CString  csUnit,double  fUpLimit,double fDnLimit);
	void	WRITE_MEM(int data);
	void	SET_WLD();
	void	SET_PC(DWORD PC);
	void	SET_CLRWLD();

	void	SET_MASKJMP();
	void    CLEAR_MASKJMP();
	int     TEST_DATA_INIT(char	*caIniFileName);

	double	MeasureVoh(double fVoltage);
	double	MeasureVol(double fVoltage);
	BOOL	DFT(double* dataRe, int numData,double* fftRe);
	void	MAT_DVM_MEASURE(int	iMeasNo,		//	�ڼ�·
								 double fVoltage,		//	���̵�ѹ
								 int	iVolUnit,		//	��λ:		V/MV
								 unsigned int tDelay,	//	������ʱ	mS
								 int	ipNumber,		//	��������
								 int	fFreq,			//	����Ƶ��
								 double	*fValue);		//	����ֵ
 
//����̽��̨
	void    SET_EOT();
	void    SET_CAT(WORD CadData);
	void    CLEAR_PHI_START();

	double	MeasureVal(WORD wData, int iPosi,int R);

	void	Init_PCICard();
	WORD ReadPortData();
	WORD ReadAddRead();
	void IEEE488(BYTE addr, CString command, BOOL endFlag);
	double IEEE488(BYTE addr, CString command);
	BOOL Scan5920();
	void	SET_VIL(CString csPin,double Vil);
	void	SET_VIH(CString csPin,double Vih);
	void	SET_VOL(CString csPin,double Vol);
	void	SET_VOH(CString csPin,double Voh);
	void	SET_IOL(CString csPin,double Iol);
	void	SET_IOH(CString csPin,double Ioh);
	void	WRITE_DRV(WORD DrvAdd,int pin,WORD Add,WORD Data);
	WORD	READ_DRV(WORD DrvAdd,int pin,WORD Add);
	void	DRV_MONITOR(int Channel,int Source,int OE);
	void	SET_AVM_PATH(int iLpSel,int	iBpSel);

	bool InitGPIBInterface();//��ʼ������
	bool CloseGPIBInterface();//�رմ���
	float A34401_DCMeasure(ViString vstring);//����һ������ֵ
	bool SetAttribute();//��������
	bool Reset34401A();//��λ34401A
//������
//#define BIN(bin,nCat,delay)    if (SET_BIN(bin)){	SET_INPUT_LEVEL(0,0);DPS_OFF(1);DPS_OFF(2);SET_CAT(nCat);Delay(delay);SET_EOT();return;}
	#define BIN(bin)    if (SET_BIN(bin))return;

	void	TIME_MEASURE_CONDITIONS(
								int		iStartT,
								int		iEdgeStart,
								double	fVol1,
								int		iUnit1,
								int		iStopT,
								int		iEdgeStop,
								double	fVol2,
								int		iUnit2);
	double	TIME_MEASURE_EXECUTE(unsigned int	iDelay);

	double	MEASURE_PERIOD(	int		iStartT,
							double	fVoltage,
							int		iVolUnit,
							int		iNum,
							int		iDelay);

	BOOL	MEASURE_PERIOD(	int	iStartT,	double	fVoltage,
		int	iVolUnit,	int	iNum,
		int	iDelay,
		CString csItem,	int  csUnit,
							double  fUpLimit,double fDnLimit);
	double	HDPS_MEASURE(unsigned int Delayms);
	double ADDA_MEASURE(double fVoltage,int iVolUnit,unsigned int tDelay);
	double ADDA_TC(unsigned int iState);
	double ADDA_SETINT(double	fVol);
	void SET_ADDA_CTRL(BYTE data);
	double ADDA_SET_RELAY(BOOL bState);
	void RESET_AD_SERVO(void);
	double ADDA_SERIAL(BOOL bSerial,BOOL bBusy,BOOL bCyc,int iBitNum);
	double ADDA_STRB(void);
	void ADDA_START(void);
	double ADDA_SLM_VOL(unsigned int iRange,double fVol);
	double ADDA_SLM_VOL(int iFlag,int iBitNum,unsigned int iRange,double fVol,int iCarry,int iPole,int iPosNeg);
	void SET_ADDA_DATA(WORD data);
