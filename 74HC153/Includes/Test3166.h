//WriteAddData(add[vref],0x0);
// Test3166.h: interface for the CTest3166 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST3166_H__8B82EDCD_C9EE_11D4_A5E8_5254AB1A9659__INCLUDED_)
#define AFX_TEST3166_H__8B82EDCD_C9EE_11D4_A5E8_5254AB1A9659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Data.h"

class CTest3166  
{
public:
	CTest3166();
	virtual ~CTest3166();

	int m_InsideRegRegion;
	int m_WriteRegion;
	int m_ReadRegion;

	BYTE ieee_ml;
	BYTE ieee_mh;
	char ieee_c;
	BYTE ieee_a;
	BYTE ieee_m[6][256];

public:
	void Init_PCICard();
	void p13();
	void p12();
	void p11();
	void p10();
	void p9();
	void IEEE488(BYTE addr, CString command, BOOL endFlag);
	double IEEE488(BYTE addr, CString command);
	void Init_ieee488();
	BOOL Scan5920();
	WORD ReadPortData();
	WORD ReadAddRead();
	BOOL	MEASURE_IIH(	double Value,		unsigned int Value_Unit,
							double Clamp_Value,	unsigned int Clamp_Unit,
							CString csPin,		unsigned int tDelay,
							CString csItem,
							double  fUpLimit,	double fDnLimit);
	BOOL	MEASURE_IIL(double Value,		unsigned int Value_Unit,
						double Clamp_Value,	unsigned int Clamp_Unit,
						CString csPin,		unsigned int tDelay,
						CString csItem,
						double  fUpLimit,	double fDnLimit);

	BOOL	SHOW_RESULT(CString csItem,	double measure_value, CString  csUnit,double  fUpLimit,double fDnLimit);
	void    CLEAR_MASKJMP();
	BOOL    SHOW_RESULT(CString csItem,	double measure_value,int  csUnit,
							   double  fUpLimit,double fDnLimit);
	BOOL    init(CDataLog *dlog,CString PathName);
	void    SET_READ_MEM_START(int FDM_MEM);
	int		TEST_DATA_INIT(char	*caIniFileName);
	//________________________________________测试端口命令_____________
	void	WriteAddData(WORD wAddr, WORD wData);
	void	WriteAddr(WORD wAddr, BOOL bIsIO);
	void	WriteData(WORD data);

	//________________________________________装入校准文件_____________
	int		LoadText_pmu (char *caFilePath);
	int		LoadText_dps (char *caFilePath);
	int		LoadText_VOH(char *caFilePath);
	int		LoadText_VOL (char *caFilePath);
	int		LoadText_VIH(char *caFilePath);
	int		LoadText_VIL (char *caFilePath);
	int		LoadText_tim (char *caFilePath);
	int		LoadText_vis (char *caFilePath);
	int		LoadText_vref (char *caFilePath);
	int		LoadText_vout (char *caFilePath);
	int		LoadText_Vs4 (char *caFilePath);
	int		LoadText_dmv (char *caFilePath);
	int		LoadText_Asx (char *caFilePath);
	int		LoadText_Avm (char *caFilePath);
	int		LoadText_AdDa (char *caFilePath);
	int		LoadText_HDPS (char *caFilePath);

	void Modify_pmu(int i,double k,double b);
	void Modify_dps(int i,double k,double b);
	void Modify_Hdps(int i,double k,double b);
	void Modify_voh(int i,double k,double b);
	void Modify_vol(int i,double k,double b);
	void Modify_vih(int i,double k,double b);
	void Modify_vil(int i,double k,double b);
	void Modify_vis(int i,double k,double b);
	void Modify_vix(int i,double k,double b);
	void Modify_vout(int i,double k,double b);
	void Modify_vs4(int i,double k,double b);
	void Modify_dmv(int i,double k,double b);
	void Modify_asx(int i,double k,double b);
	void Modify_avm(int i,double k,double b);

	//________________________________________各种工具函数_____________
	long	Delay(double us);
	// 用于装入校准文件
	BOOL	GetData(CString str, double &xp, double &yp);
	// 用于FORMAT指令
	void	Fmt_Data(int *board,int boardNum,int nchannel,BYTE fmt,WORD *wdata,WORD *_wData2,BOOL *f0,BOOL *f1);

	//________________________________________测试驱动指令_____________
	void	SET_DPS(BYTE No,double Vdd,	unsigned int Vdd_Unit,
							    double Iclamp,	unsigned int Iclamp_Unit);

	double	DPS_MEASURE(BYTE No,	unsigned int Delayms);
	double	DPS_MEASURE(BYTE No,	BYTE IRange,unsigned int Delayms);
	double  DPS_MEASURE(BYTE No,	double fIvalue, unsigned int Delayms, int x);
	BOOL  	DPS_MEASURE(BYTE No,	BYTE IRange,unsigned int Delayms,
						CString	csItem, int csUnit,
						double	fIccMax,double  fIccMin);

	double	MeasureVoh(double fVoltage);
	double	MeasureVol(double fVoltage);
	double	MeasureVal(WORD Rdata, int iPosi,int R);

	void	DPS_OFF(BYTE No);

	void	FORMAT(BYTE fmt,CString csChannel);

	void	PMU_CONDITIONS(unsigned int Mode,
						   double Value,		unsigned int Value_Unit,
						   double Clamp_Value,	unsigned int Clamp_Unit);
	double	PMU_MEASURE(unsigned int pin,unsigned int tDelay);
	BOOL	PMU_MEASURE(CString csPin,	unsigned int tDelay,
						CString csItem,	int  csUnit,
						double  fUpLimit,double   fDnLimit);
	void	SET_INPUT_LEVEL(double Voh,double Vol);
	void	SET_OUTPUT_LEVEL(double Voh,double Vol);

	void	SET_PERIOD(unsigned int period);
	void	SET_TIMING(unsigned int LeadEdge,unsigned int Fwidth,unsigned int Ctg);
	BOOL	RUN_TIMING(void);
	void	STOP_TIMING(void);
	void	CLEAR_TIMING(void);

	void	CLEAR_ALL(void);



	//	程控电压源指令
	void	SET_DPS_POS(double Vdd,		unsigned int Vdd_Unit,
						double Iclamp,	unsigned int Iclamp_Unit);
	double	DPS_MEASURE_POS(unsigned int uiDelayms);
	void	DPS_OFF_POS();		// 关闭DPS正
	void	SET_DPS_NEG(double Vdd,		unsigned int Vdd_Unit,
						double Iclamp,	unsigned int Iclamp_Unit);
	double	DPS_MEASURE_NEG(unsigned int uiDelayms);
	void	DPS_OFF_NEG();		// 关闭DPS负
//	char	*DPS_STATE(int	*iNum);
	void	CLEAR_DPS(void);	// 清DPS
	
	double	MEASURE_POS_REGVO(	double	fIload,int	iIunit,
								double	fVout, int	iVunit,
								int		iRtimes);
	double	MEASURE_NEG_REGVO(	double	fIload,int	iIunit,
								double	fVout, int	iVunit,
								int		iRtimes);

	//	设置文波
	void	SET_POS_RIPPLE(double fVol,	int iVolUnit,	double freq);
	void	CLEAR_POS_RIPPLE();
	void	SET_NEG_RIPPLE(double fVol,	int iVolUnit,	double freq);
	void	CLEAR_NEG_RIPPLE();

	//	音频源
	void	SET_AS		(double	fVol,	int iVolUnit,double	freq);
	void	SET_AS		(double	fVol,	int iVolUnit,double	freq,int iUnit);
	void	SET_AS_DC	(double fVol,	int iVolUnit);
	void	SET_AS_SQUARE		(double fVol,	int iVolUnit,double	freq);
	void	SET_AS_SQUARE		(double	fVol, int iVolUnit,double freq,int iUnit);

	//	音频表
	void	SET_AVM_PATH(int iLpSel,int	iBpSel);
	double	AVM_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);
	int		SET_AVM(int iLpSel,int iBpSel,double fvRange, int iUnit);
	void	SET_AVM_RANGE(int ivRange);
//	void	CLEAR_DA();
	
	// 偏置电压源
	void	SET_VS1(double fVolt,	int iVolUnit);
	void	SET_VS2(double fVolt,	int iVolUnit);
	void	SET_VS3(double fVolt,	int iVolUnit);
	void	SET_VS4(double fVolt,	int iVolUnit);

//	void	CONNECT_RELAY	(int iFlag,	CString iChannel);
//	void	DISCONNECT_RELAY(int iFlag,	CString csChannel);
//	void	DISCONNECT_ALL();
	
	// 参考源_______________________________________________________
	void	SET_VS (int iCanal,		double fVolt,	int iVolUnit);
	void	CLEAR_VS();
	void	START_VS();

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

	// 继电器控制
	void	SET_RELAY(CString csRelay);
	void	CLOSE_RELAY(CString csRelay);
	void	CLEAR_RELAY(CString csRelay);

	//	通道/时间测量单元
	double	MEASURE_PERIOD(		int		iStartT,			// 测量周期
								double	fVoltage,
								int		iVolUnit,
								int		iNum,
								int		iDelay);
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
	BYTE*	LOAD_PATTERN(CString FileName);					// 装图形
	int		RUN_PATTERN(int		iStartIdx,					// 运行图形
						BYTE	*btAddr,
						int		iINH_FAIL,
						unsigned int	iTimeRange);
	BOOL	RUN_PATTERN(int start_idx,
						int get_fail,
						int time_range);
	void	CLEAR_PATTERN(void);							// 清图形

	//	精密测量单元
	void	CLEAR_PMU(void);
	void	SET_PMU(unsigned int Mode,	
					double Value,		unsigned int Value_Unit,
					double Clamp_Value,	unsigned int Clamp_Unit);
	void	SET_PMU(CString csPin,		unsigned int Mode,	
					double Value,		unsigned int Value_Unit,
					double Clamp_Value,	unsigned int Clamp_Unit);
	double	PMU_MEASURE(unsigned int tDelay);
	void	CLR_PMU(void);

	//	电压电流源
	void	SET_VIS(unsigned int Mode,
					double Value,		unsigned int Value_Unit,
					double Clamp_Value,	unsigned int Clamp_Unit);
	void	CLEAR_VIS();
	double	VI_MEASURE (double fVoltage,int iVolUnit,unsigned int tDelay);
	double	VI_MEASURE(unsigned int tDelay);

	void	MAT_DVM_MEASURE(int	iMeasNo,		//	第几路
								 double fVoltage,		//	量程电压
								 int	iVolUnit,		//	单位:		V/MV
								 unsigned int tDelay,	//	测量延时	mS
								 int	ipNumber,		//	测量点数
								 int	fFreq,			//	采样频率
								 double	*fValue);		//	测量值

	//	PMU测量输出参考电平
	double	VOH_MEASURE(double fVoltage,int iVolUnit,unsigned int tDelay);
	double	VOL_MEASURE(double fVoltage,int iVolUnit,unsigned int tDelay);

	double	DVM_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);
	double	DVM_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay,int iTimes);
	double	DVM_DIFF_MEASURE(int iMeasNo,double fVoltage,int iVolUnit,unsigned int tDelay);

	BOOL	DPS_MEASURE_POS(BYTE IRange,	unsigned int Delayms,
		CString	csItem, int csUnit,
							double	fIccMax,double fIccMin);
	BOOL	DPS_MEASURE_NEG(BYTE IRange,unsigned int Delayms,
		CString	csItem, int csUnit,
		double	fIccMax,double fIccMin);
	BOOL	DVM_MEASURE(int iMeasNo,	 double fVoltage,
		int iVolUnit,unsigned int tDelay,
		CString	csItem, int iUnit,
		double  fUpLimit,double fDnLimit);
	BOOL	MEASURE_PERIOD(	int	iStartT,	double	fVoltage,
		int	iVolUnit,	int	iNum,
		int	iDelay,
		CString csItem,	int  csUnit,
		double  fUpLimit,double fDnLimit);
	BOOL	DVM_DIFF_MEASURE(int iMeasNo,	double fVoltage,
							 int iVolUnit,	unsigned int tDelay,
							 CString  csItem,	int csUnit,
							 double  fUpLimit,double fDnLimit);
	///////////////////////////////////////////////////////////////////
	void	SET_STEP_TIMING(void);
	BOOL	RUN_STEP_TIMING(void);
	void	CLEAR_STEP_TIMING(void);
	void	Clear_Pmu(void);
	void	Init_Dps_Reg(void);
	void	Init_Drv(void);

    BOOL    RUN_PATTERN(int start_idx,BYTE *addr,int get_fail,int apgen,int time_range);
	BOOL    RUN_PATTERN(int start_idx,int get_fail,int apgen,int time_range);
	BOOL    RUN_PATTERN(CString csItem, int start_idx,int get_fail,int apgen,int time_range);
	void	DEBUG_PATTERN(int start_idx,int get_fail,int apgen);
	void	SET_WLD();
	void	SET_PC(DWORD PC);
	void	SET_LDPCX();
	void	SET_LDCLK();
	void	SET_CLRWLD();
	void	SET_FDM(int SEL_FDM, int n_CHANNEL);
	void	SET_WE();
	void	SET_LOCALCLR();
	void	SET_APGEN();
	void	SET_ADREN();
	void	SET_SETMASKF();
	void	SET_TRUN();
	void	SET_CAT(WORD CadData);
	void	SET_CAT1(WORD CadData);
	void	SET_EOT();
	void	SET_MASKJMP();
	void	SET_MASKF();//
	void	SET_STEP();
	void	CLEAR_STEP();
	void	SET_TIMING_STATE(int instruction);
	WORD	READ_STATE();
	void	SET_STOP();
	DWORD	READ_PC();
	WORD	READ_PCL();
	BYTE	READ_FAIL_DATA(int n_CHANNEL);
	WORD	READ_DATA();
	void	WRITE_PCL(WORD PCL);
	void	WRITE_PCH(WORD PCH);
	void	WRITE_WDH(int data);
	void	WRITE_WDL(int data);
	void	LoadInstruction(BYTE *instruction);
	void	LoadData(BYTE* data,int width);
	void	CLEAR_FAIL(int n_CHANNEL);
	void	MASK_CHANB_FAIL(int n_CHANNEL);
	void	RESUME_CHANB_FAIL(int n_CHANNEL);
	BYTE	READ_NOM_CHANB(int n_CHANNEL);
	BYTE	READ_MASK_CHANB(int n_CHANNEL);
	void	SET_PASS_LIGHT();
	void	SET_FAIL_LIGHT();
	int		READ_START_STAT();
	void	CLEAR_START_STAT();
	void	CLEAR_PASS_FAIL_LIGHT();
	void	CLEAR_APGEN();	//
	void	TEST_MEMERY();
	void	CLEAR_BD_ADR();
	void	SET_RIP();
	void	CLEAR_RIP();
	void	SET_BD_ADR();
	void	CLEAR_ADREN();
	WORD	READ_MEMORY(int n_CHANNEL,int FDM_MEM);
	void	CLEAR_PHI_START();
	BYTE*	SELF_TEST_LOAD(CString FileName);

	void	DispDlg(int iDebugItem);

	void	WRITE_MEM(int data);
	void	MAT_PMU_MEASURE(int	iMeasNo,		//	第几路
								 unsigned int tDelay,	//	测量延时	mS
								 int	ipNumber,		//	测量点数
								 int	fFreq,			//	采样频率
								 double	*fValue);		//	测量值
	BOOL 	 DFT(double* dataRe, int numData,double* fftRe);
	void	SET_VIL(CString csPin,double Vil);
	void	SET_VIH(CString csPin,double Vih);
	void	SET_VOL(CString csPin,double Vol);
	void	SET_VOH(CString csPin,double Voh);
	void	WRITE_DRV(WORD DrvAdd,int Pin,WORD Add,WORD Data);
	WORD	READ_DRV(WORD DrvAdd,int Pin,WORD Add);
	void	SET_IOL(CString csPin,double Iol);
	void	SET_IOH(CString csPin,double Ioh);
	void	DRV_MONITOR(int Channel,int Source,int OE);

};

 #endif // !defined(AFX_TEST3166_H__8B82EDCD_C9EE_11D4_A5E8_5254AB1A9659__INCLUDED_)
