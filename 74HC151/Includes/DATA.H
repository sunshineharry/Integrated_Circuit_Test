// Data.h: interface for the CDataLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATA_H__B7DC5661_3A21_11D5_A107_5254AB1A9005__INCLUDED_)
#define AFX_DATA_H__B7DC5661_3A21_11D5_A107_5254AB1A9005__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "structdef.h"
/////////////////////////////////////////////////////
//测试结果数据，处理数据
//
/////////////////////////////////////////////////////
class AFX_EXT_CLASS CDataLog : public CObject  
{
	DECLARE_DYNAMIC(CDataLog);    
public:
	BOOL PatternFailFlag;
	int DebugFlag;
	BYTE* addr_pattern;
	short bin;
	unsigned short total_tests,current_tests_count;
	datalog_struct log;
    dlog_test* tests;	
   	BOOL pass_fail;
	int no_of_tests;
    BOOL go_nogo;

//	void set_test_time();
//	void set_bin(BYTE bin_no);
	void set_function_no(unsigned short function_no);
	BOOL set_display_param(double test_val,char* test_name,
            double max_limit_val,double min_limit_val,int units);
	BOOL set_display_param(double test_val,char* test_name,
            double max_limit_val,double min_limit_val,CString units);
   	void set_display_param(BOOL Pass_Fail,char* test_name);
	void init_test_no();

	CDataLog();
	virtual ~CDataLog();
private:

};

#endif // !defined(AFX_DATA_H__B7DC5661_3A21_11D5_A107_5254AB1A9005__INCLUDED_)
