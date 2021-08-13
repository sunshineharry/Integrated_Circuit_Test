'''
Date: 2021-08-12 22:31:03
LastEditors: Jiang Hankun
LastEditTime: 2021-08-12 22:46:28
'''

def dec2hex(dec_num):
    hex_num = hex(dec_num)
    hex_num = hex_num[2:]
    hex_num = hex_num.upper()
    if len(hex_num) == 1:
        hex_num = '0' + hex_num
    return hex_num


if __name__ == "__main__":
    with open('result.mdc','w') as f:
        for A in range(0,256):
            for B in range(0,256):

                if A==B:
                    result = 'L'
                else:
                    result = 'H'
            
                f.write(' INC (' + dec2hex(A) + dec2hex(B) + ' 0 ' + result +')\n')
            


        