struct  dlog_test
{
 	union 	{
        double		f_measured_value;
		ULONGLONG   u_measured_value;
			};         //测量值
   	unsigned char	passed_fail;            
    char			test_name[16];      //测试项名  
	double			max_limit_val;      //上限
	double			min_limit_val;      //下限
	char			units[7];           //单位
    unsigned short  function_no;        //测试项号
    unsigned short  sub_test_no;        


};

struct datalog_struct
{
    char            operator_name[10];
//    char            date_tested[10];
//    char            time_tested[9];
    unsigned short  current_serial;
    unsigned short  batch_number[17];

};

#ifdef UNICODE
struct stat
{
    unsigned short       total;
	unsigned short       pass;
	unsigned short       fail;
	float                yield;
    struct               bin_struct
    {
        unsigned short   bin_count;
        float            bin_yield;
    }bin[16];
};
#endif