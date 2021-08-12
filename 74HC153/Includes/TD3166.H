// td3166.h : main header file for the TD3166 DLL
//

#if !defined(AFX_TD3166_H__8B82EDC6_C9EE_11D4_A5E8_5254AB1A9659__INCLUDED_)
#define AFX_TD3166_H__8B82EDC6_C9EE_11D4_A5E8_5254AB1A9659__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#define	_DebugDps					0
#define	_DebugPmu					1
#define	_DebugPtn					2

#include "resource.h"		// main symbols

	typedef	struct	_PmuStruct _MeasureType;
	struct	_PmuStruct	// 运行图形，在RUN_PATTERN指令中设置
	{
		int				iPinNum;
		int				iaPin[129];
		int				iMode;
		unsigned int	tDelay;
		CString			csItem;
//		CString			csUnit;
		int 			csUnit;
		double			fUpLimit;
		double			fDnLimit;
		BOOL			bTestResult;
	};

	typedef	struct	struHDpsTerm	HDpsTermType;	// 设置HDPS的参数，在SET_HDPS指令中设置
	typedef	struct	struDpsTerm		DpsTermType;	// 设置DPS的参数，在SET_DPS指令中设置
	typedef	struct	struPmuTerm		PmuTermType;	// 设置PMU的参数，在PMU_CONDITIONS指令中设置
	typedef	struct	struVixTerm		VixTermType;	// 设置输入参考电平的参数，在SET_INPUT_LEVEL指令中设置
	typedef	struct	struVoxTerm		VoxTermType;	// 设置输出参考电平的参数，在SET_OUTPUT_LEVEL指令中设置
	typedef	struct	struPerTerm		PerTermType;	// 设置时钟周期，在SET_PERIOD指令中设置
	typedef	struct	struTimTerm		TimTermType;	// 设置定时，在SET_TIMING指令中设置
	typedef	struct	struFmtTerm		FmtTermType;	// 格式化设置，在FORMAT指令中设置
	typedef	struct	struPtnTerm		PtnTermType;	// 运行图形，在RUN_PATTERN指令中设置
	// 以下为施加命令参数的数据结构
	struct	struHDpsTerm	// 设置DPS的参数，在SET_DPS指令中设置
	{
		int		iPosNeg;	// DPS 正/负
		double	fForceVal;	// 施加值
		int		iUnit;		// 施加单位
		double	fClampVal;	// 钳位值
		int		iClampUnit;	// 钳位单位
	};
	struct	struDpsTerm	// 设置DPS的参数，在SET_DPS指令中设置
	{
		int		iDpsNum;	// DPS 第几路
		double	fForceVal;	// 施加值
		int		iUnit;		// 施加单位
		double	fClampVal;	// 钳位值
		int		iClampUnit;	// 钳位单位
	};
	struct	struPmuTerm	// 设置PMU的参数，在PMU_CONDITIONS指令中设置
	{
		int		iTestMode;	// 测量模式
		double	fForceVal;	// 施加值
		int		iUnit;		// 施加单位
		double	fClampVal;	// 钳位值
		int		iClampUnit;	// 钳位单位
	};
	struct	struVixTerm		// 设置输入参考电平的参数，在SET_INPUT_LEVEL指令中设置
	{
		double	fForceVih;	// 输入高电平施加值
		double	fForceVil;	// 输入低电平施加值
	};
	struct	struVoxTerm		// 设置输出参考电平的参数，在SET_OUTPUT_LEVEL指令中设置
	{
		double	fForceVoh;	// 输出高电平施加值
		double	fForceVol;	// 输出低电平施加值
	};
	struct	struPerTerm		// 设置时钟周期，在SET_PERIOD指令中设置
	{
		unsigned int	uiPeriod;	// 输出时钟周期施加值
	};
	struct	struTimTerm		// 设置定时，在SET_TIMING指令中设置
	{
		unsigned int	lEdge;		// 前沿
		unsigned int	lWidth;		// 宽度
		unsigned int	lCtg;		// 选通
	};
	struct	struFmtTerm			// 格式化设置，在FORMAT指令中设置
	{
		int		iMode;			// 模式
		int		iChannel[132];	// 通道
		CString	csChannel;
	};
	struct	struPtnTerm		// 运行图形，在RUN_PATTERN指令中设置
	{
		int		iIndex;		// 起始点索引
		BYTE	*bpAddr;	// 地址指针
		int		iFailRt;	// 失效设置
		int		iApgen;
		int		iTimeRange;
	};

/////////////////////////////////////////////////////////////////////////////
// CTd3166App
// See td3166.cpp for the implementation of this class
//

class CTd3166App : public CWinApp
{
public:
	CTd3166App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTd3166App)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CTd3166App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TD3166_H__8B82EDC6_C9EE_11D4_A5E8_5254AB1A9659__INCLUDED_)
