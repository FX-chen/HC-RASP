// #include <stdio.h>
// #include <wiringPi.h>
// #include <wiringSerial.h>
// // #include <thread>  
// #include <iostream>
// #include <Python.h>
// using namespace std;



// #define MaxFrameLength	20			// �����֡���ȼ����޶�����ֹ���յ�������֡����

// #define Frame_Header1   0x3A                    // ���ڽ�����Ϣ����֡ͷ�ĵ�1���ֽ�
// #define Frame_Header2   0x3B                    // ���ڽ�����Ϣ����֡ͷ�ĵ�2���ֽ�

// #define Frame_Tail1     0x7E                    // ���ڽ�����Ϣ����֡β�ĵ�1���ֽ�
// #define Frame_Tail2     0x7F                    // ���ڽ�����Ϣ����֡β�ĵ�2���ֽ�

// union hc_sensor
// {
//     float value;
//     unsigned char value_char[4];  
// }dvl_vx,dvl_vy,dvl_vz,dvl_distance,dvl_roll,dvl_pitch,dvl_yaw,ms5837_pressure,ms5837_depth;

// union hc_control
// {
//     float value;
//     unsigned char value_char[4];	
// }yaw_force,depth_force,att_force;

// void connectSerial()
// {
//         int hs1;
//     int snum = 0;                               // ϵͳ���ڽ��ջ������Ŀ����ֽ���
//     int tnum = 0;                               // �û����ڽ���������Ŀ
//     unsigned char chrtmp[100];                  // �û����ڽ�����������������ݷ������ﴦ��
//     int f_h1_flag = 0;                          // ���յ�֡ͷ�ĵ�һ���ֽڱ�־λ
//     int f_h_flag = 0;                           // ���յ�֡ͷ��־λ
//     int f_t1_flag = 0;                          // ���յ�֡β�ĵ�һ���ֽڱ�־λ
    
//     float number = 0.0;                         //Ҫ���յĸ�����
//     float roll = 1.2468;
    
 
 
//     wiringPiSetup();                            // ʹ��wiring����ȥ��ʼ��GPIO���
//     hs1 = serialOpen("/dev/ttyAMA0", 115200);     // �� /dev/ttyS0 �����豸��������115200 
//     //hs1 = serialOpen("/dev/ttyUSB0", 115200);     // �� /dev/ttyUSB0 �����豸��������115200
 
//     printf("ttyAMA0 uart test2:\n");              // �ն˴�ӡ
// //    serialPrintf(hs1, "Hello World!\r\n");      // ���ڴ�ӡ
// //    serialPrintf(hs1, "Enter a paragraph and end with Enter:\r\n");
// // while(1){
// //     roll += 0.01;
// //     chrtmp[0] = Frame_Header1;
// //     chrtmp[1] = Frame_Header2;
// //     chrtmp[2] = 0x73;
// //     chrtmp[3] = 0x54;
// //     chrtmp[4] = 0x00;
// //     chrtmp[9] = Frame_Tail1;
// //     chrtmp[10] = Frame_Tail2;
// //     dvl_roll.value = roll;
// //      int i =0;
// //      for(i = 5;i < 9;i++ ){
// //          chrtmp[i] = dvl_roll.value_char[i-5];
// //     }
// //     int j = 0;
// //     for(j = 0;j < 11; j++){
// //         serialPutchar(hs1, chrtmp[j]);
// //     }

// //     for(j = 0;j < 11; j++){
// //         chrtmp[j] = 0x00;
// //     }
// // }   

//     // serialPutchar(hs1,0x73);

//     // while (1)
//     // {
//     // 	// printf("last one");
//     //     snum = serialDataAvail(hs1);                	// ��ȡ���ڽ��ջ������Ŀ����ֽ���  //���ؿɹ���ȡ���ַ���
//     //     if(snum > 0)
//     //     {
//     //         chrtmp[tnum] = serialGetchar(hs1);  		// �ӽ��ջ�������ȡһ���ֽ�  //���ش����豸�Ͽ��õ���һ���ַ�
 
//     //         if (f_h_flag == 1)  // ��֡ͷ���ж�֡β��������Ϣ
//     //         {
//     //             if (f_t1_flag == 1) //��֡ͷ����֡β1
//     //             {
//     //                 if (chrtmp[tnum] == Frame_Tail2)
//     //                 {
                        
//     //                     int i = 0;
//     //                     for (i = 0; i < (tnum + 1); i++)
//     //                     {
//     //                         serialPutchar(hs1, chrtmp[i]);	// ͨ�����ڷ����ֽ� // �������ֽڷ��͵��ɸ����ļ���������ʶ�Ĵ����豸
//     //                     }
 
//     //                     tnum = 0;
//     //                 }
//     //                 else
//     //                 {
//     //                     f_t1_flag = 0;
//     //                     tnum ++;
//     //                 }
//     //             }
//     //             else						// ��֡ͷ����֡β1
//     //             {
//     //                 if (chrtmp[tnum] == Frame_Tail1)
//     //                 {
//     //                     f_t1_flag = 1;
//     //                     tnum ++;
//     //                 }
//     //                 else					// ������Ϣ���м�����
//     //                 {
//     //                     tnum ++;
//     //                 }
//     //             }
//     //         }
//     //         else						// û�н��յ�֡ͷ
//     //         {
//     //             if (f_h1_flag == 1)			        //û��֡ͷ����֡ͷ1����һ���ж��Ƿ�Ϊ��2���ֽ�
//     //             {
//     //                 if (chrtmp[tnum] == Frame_Header2)          // ���Ϊ֡ͷ�ĵ�2���ֽڣ����յ�֡ͷ��־λ��־λ��1��tnum����
//     //                 {
//     //                     f_h_flag = 1;
//     //                     tnum ++;
//     //                 }
//     //                 else
//     //                 {
//     //                     f_h1_flag = 0;
//     //                     tnum = 0;
//     //                 }
//     //             }
//     //             else						//û��֡ͷ��û����֡ͷ1����һ���жϣ��Ƿ�Ϊ֡ͷ�ĵ�1���ֽ�
//     //             {
//     //                 if (chrtmp[tnum] == Frame_Header1)  // ���Ϊ֡ͷ�ĵ�1���ֽڣ���־λ��1��tnum����
//     //                 {
//     //                     f_h1_flag = 1;
//     //                     tnum ++;
//     //                 }
//     //                 else                                // ���򣬱�־λ��0��tnum��0
//     //                 {
//     //                     tnum = 0;
//     //                 }
//     //             }
//     //         }
 
//     //         // ����MaxFrameLength���ֽڵ�֡������
//     //         if (tnum > (MaxFrameLength - 1) )
//     //         {
//     //             tnum = 0;
//     //             f_h1_flag = 0;
//     //             f_h_flag = 0;
//     //             f_t1_flag = 0;
//     //             continue;
//     //         }
 
//     //     }
//     // }
// }

// void creatWiFi()
// {
//     cout << "im Wifi";
// }
// int main(void)
// {
//     PyObject *pName, *pModule, *pFunc; //使用PyObject指针调用各种函数
//     PyObject *pArgs, *pValue;
//     int i;

//     // if (argc < 3) {
//     //     fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
//     //     return 1;
//     // }

//     Py_Initialize();                        //初始化python解释器.C/C++中调用Python之前必须先初始化解释器
//     //Py_IsInitialized();                //返回python解析器的是否已经初始化完成，如果已完成，返回大于0，否则返回0
//     if(!Py_IsInitialized()){
// 		cout << "python init fail" << endl;
// 		return 0;
// 	}
    
//     Py_Finalize(); //  撤销Py_Initialize()和随后使用Python/C API函数进行的所有初始化， 并销毁自上次调用Py_Initialize()以来创建并为被销毁的所有子解释器。

//     // thread t(creatWiFi);
//     // int ser = pthread_create(&serial,NULL,connectSerial,NULL);
//     // if(ser != 0)
//     // {
//     //     cout << "pthread creat serial error"<<endl;
//     // }
//     // t.join();

//     // thread t(connectSerial);
//     // int wif = pthread_create(&wifi,NULL,creatWiFi,NULL);
//     // if(wif != 0)
//     // {
//     //     cout << "pthread creat serial error"<<endl;
//     // }


// //     int hs1;
// //     int snum = 0;                               // ϵͳ���ڽ��ջ������Ŀ����ֽ���
// //     int tnum = 0;                               // �û����ڽ���������Ŀ
// //     unsigned char chrtmp[100];                  // �û����ڽ�����������������ݷ������ﴦ��
// //     int f_h1_flag = 0;                          // ���յ�֡ͷ�ĵ�һ���ֽڱ�־λ
// //     int f_h_flag = 0;                           // ���յ�֡ͷ��־λ
// //     int f_t1_flag = 0;                          // ���յ�֡β�ĵ�һ���ֽڱ�־λ
    
// //     float number = 0.0;                         //Ҫ���յĸ�����
// //     float roll = 1.2468;
    
 
 
// //     wiringPiSetup();                            // ʹ��wiring����ȥ��ʼ��GPIO���
// //     hs1 = serialOpen("/dev/ttyAMA0", 115200);     // �� /dev/ttyS0 �����豸��������115200 
// //     //hs1 = serialOpen("/dev/ttyUSB0", 115200);     // �� /dev/ttyUSB0 �����豸��������115200
 
// //     printf("ttyAMA0 uart test2:\n");              // �ն˴�ӡ
// // //    serialPrintf(hs1, "Hello World!\r\n");      // ���ڴ�ӡ
// // //    serialPrintf(hs1, "Enter a paragraph and end with Enter:\r\n");
// // // while(1){
// // //     roll += 0.01;
// // //     chrtmp[0] = Frame_Header1;
// // //     chrtmp[1] = Frame_Header2;
// // //     chrtmp[2] = 0x73;
// // //     chrtmp[3] = 0x54;
// // //     chrtmp[4] = 0x00;
// // //     chrtmp[9] = Frame_Tail1;
// // //     chrtmp[10] = Frame_Tail2;
// // //     dvl_roll.value = roll;
// // //      int i =0;
// // //      for(i = 5;i < 9;i++ ){
// // //          chrtmp[i] = dvl_roll.value_char[i-5];
// // //     }
// // //     int j = 0;
// // //     for(j = 0;j < 11; j++){
// // //         serialPutchar(hs1, chrtmp[j]);
// // //     }

// // //     for(j = 0;j < 11; j++){
// // //         chrtmp[j] = 0x00;
// // //     }
// // // }   

// //     // serialPutchar(hs1,0x73);

// //     while (1)
// //     {
// //     	// printf("last one");
// //         snum = serialDataAvail(hs1);                	// ��ȡ���ڽ��ջ������Ŀ����ֽ���  //���ؿɹ���ȡ���ַ���
// //         if(snum > 0)
// //         {
// //             chrtmp[tnum] = serialGetchar(hs1);  		// �ӽ��ջ�������ȡһ���ֽ�  //���ش����豸�Ͽ��õ���һ���ַ�
 
// //             if (f_h_flag == 1)  // ��֡ͷ���ж�֡β��������Ϣ
// //             {
// //                 if (f_t1_flag == 1) //��֡ͷ����֡β1
// //                 {
// //                     if (chrtmp[tnum] == Frame_Tail2)
// //                     {
                        
// //                         int i = 0;
// //                         for (i = 0; i < (tnum + 1); i++)
// //                         {
// //                             serialPutchar(hs1, chrtmp[i]);	// ͨ�����ڷ����ֽ� // �������ֽڷ��͵��ɸ����ļ���������ʶ�Ĵ����豸
// //                         }
 
// //                         tnum = 0;
// //                     }
// //                     else
// //                     {
// //                         f_t1_flag = 0;
// //                         tnum ++;
// //                     }
// //                 }
// //                 else						// ��֡ͷ����֡β1
// //                 {
// //                     if (chrtmp[tnum] == Frame_Tail1)
// //                     {
// //                         f_t1_flag = 1;
// //                         tnum ++;
// //                     }
// //                     else					// ������Ϣ���м�����
// //                     {
// //                         tnum ++;
// //                     }
// //                 }
// //             }
// //             else						// û�н��յ�֡ͷ
// //             {
// //                 if (f_h1_flag == 1)			        //û��֡ͷ����֡ͷ1����һ���ж��Ƿ�Ϊ��2���ֽ�
// //                 {
// //                     if (chrtmp[tnum] == Frame_Header2)          // ���Ϊ֡ͷ�ĵ�2���ֽڣ����յ�֡ͷ��־λ��־λ��1��tnum����
// //                     {
// //                         f_h_flag = 1;
// //                         tnum ++;
// //                     }
// //                     else
// //                     {
// //                         f_h1_flag = 0;
// //                         tnum = 0;
// //                     }
// //                 }
// //                 else						//û��֡ͷ��û����֡ͷ1����һ���жϣ��Ƿ�Ϊ֡ͷ�ĵ�1���ֽ�
// //                 {
// //                     if (chrtmp[tnum] == Frame_Header1)  // ���Ϊ֡ͷ�ĵ�1���ֽڣ���־λ��1��tnum����
// //                     {
// //                         f_h1_flag = 1;
// //                         tnum ++;
// //                     }
// //                     else                                // ���򣬱�־λ��0��tnum��0
// //                     {
// //                         tnum = 0;
// //                     }
// //                 }
// //             }
 
// //             // ����MaxFrameLength���ֽڵ�֡������
// //             if (tnum > (MaxFrameLength - 1) )
// //             {
// //                 tnum = 0;
// //                 f_h1_flag = 0;
// //                 f_h_flag = 0;
// //                 f_t1_flag = 0;
// //                 continue;
// //             }
 
// //         }
// //     }

// int main(void)
// // {
// //     int hs1;
// //     int snum = 0;                               
// //     int tnum = 0;                              
// //     unsigned char chrtmp[100];                  
// //     int f_h1_flag = 0;                         
// //     int f_h_flag = 0;                          
// //     int f_t1_flag = 0;                        
// //     chrtmp[0] = Frame_Header1;
// //     chrtmp[1] = Frame_Header2;
// //     chrtmp[2] = 0x73;
// //     chrtmp[3] = 0x54;
// //     chrtmp[4] = 0x00;
// //     chrtmp[9] = Frame_Tail1;
// //     chrtmp[10] = Frame_Tail2;
// //     float number = 0.0;                      
// //     float roll = 1.2468;

// //     wiringPiSetup();                            
// //     hs1 = serialOpen("/dev/ttyAMA0", 115200);    
// //     //hs1 = serialOpen("/dev/ttyUSB0", 115200);    
 
// //     printf("ttyAMA0 uart test2:\n");             

// // while(1){
// //     roll += 0.01;
// //     chrtmp[0] = Frame_Header1;
// //     chrtmp[1] = Frame_Header2;
// //     chrtmp[2] = 0x73;
// //     chrtmp[3] = 0x54;
// //     chrtmp[4] = 0x00;
// //     chrtmp[9] = Frame_Tail1;
// //     chrtmp[10] = Frame_Tail2;
// //     dvl_roll.value = roll;
// //      int i =0;
// //      for(i = 5;i < 9;i++ ){
// //          chrtmp[i] = dvl_roll.value_char[i-5];
// //     }
// //     int j = 0;
// //     for(j = 0;j < 11; j++){
// //         serialPutchar(hs1, chrtmp[j]);
// //     }

// //     for(j = 0;j < 11; j++){
// //         chrtmp[j] = 0x00;
// //     }
// // }   

// //     // serialPutchar(hs1,0x73);

// //     // while (1)
// //     // {
// //     // 	// printf("last one");
// //     //     snum = serialDataAvail(hs1);                	// ��ȡ���ڽ��ջ������Ŀ����ֽ���  //���ؿɹ���ȡ���ַ���
// //     //     if(snum > 0)
// //     //     {
// //     //         chrtmp[tnum] = serialGetchar(hs1);  		// �ӽ��ջ�������ȡһ���ֽ�  //���ش����豸�Ͽ��õ���һ���ַ�
 
// //     //         if (f_h_flag == 1)  // ��֡ͷ���ж�֡β��������Ϣ
// //     //         {
// //     //             if (f_t1_flag == 1) //��֡ͷ����֡β1
// //     //             {
// //     //                 if (chrtmp[tnum] == Frame_Tail2)
// //     //                 {
                        
// //     //                     int i = 0;
// //     //                     for (i = 0; i < (tnum + 1); i++)
// //     //                     {
// //     //                         serialPutchar(hs1, chrtmp[i]);	// ͨ�����ڷ����ֽ� // �������ֽڷ��͵��ɸ����ļ���������ʶ�Ĵ����豸
// //     //                     }
 
// //     //                     tnum = 0;
// //     //                 }
// //     //                 else
// //     //                 {
// //     //                     f_t1_flag = 0;
// //     //                     tnum ++;
// //     //                 }
// //     //             }
// //     //             else						// ��֡ͷ����֡β1
// //     //             {
// //     //                 if (chrtmp[tnum] == Frame_Tail1)
// //     //                 {
// //     //                     f_t1_flag = 1;
// //     //                     tnum ++;
// //     //                 }
// //     //                 else					// ������Ϣ���м�����
// //     //                 {
// //     //                     tnum ++;
// //     //                 }
// //     //             }
// //     //         }
// //     //         else						// û�н��յ�֡ͷ
// //     //         {
// //     //             if (f_h1_flag == 1)			        //û��֡ͷ����֡ͷ1����һ���ж��Ƿ�Ϊ��2���ֽ�
// //     //             {
// //     //                 if (chrtmp[tnum] == Frame_Header2)          // ���Ϊ֡ͷ�ĵ�2���ֽڣ����յ�֡ͷ��־λ��־λ��1��tnum����
// //     //                 {
// //     //                     f_h_flag = 1;
// //     //                     tnum ++;
// //     //                 }
// //     //                 else
// //     //                 {
// //     //                     f_h1_flag = 0;
// //     //                     tnum = 0;
// //     //                 }
// //     //             }
// //     //             else						//û��֡ͷ��û����֡ͷ1����һ���жϣ��Ƿ�Ϊ֡ͷ�ĵ�1���ֽ�
// //     //             {
// //     //                 if (chrtmp[tnum] == Frame_Header1)  // ���Ϊ֡ͷ�ĵ�1���ֽڣ���־λ��1��tnum����
// //     //                 {
// //     //                     f_h1_flag = 1;
// //     //                     tnum ++;
// //     //                 }
// //     //                 else                                // ���򣬱�־λ��0��tnum��0
// //     //                 {
// //     //                     tnum = 0;
// //     //                 }
// //     //             }
// //     //         }
 
// //     //         // ����MaxFrameLength���ֽڵ�֡������
// //     //         if (tnum > (MaxFrameLength - 1) )
// //     //         {
// //     //             tnum = 0;
// //     //             f_h1_flag = 0;
// //     //             f_h_flag = 0;
// //     //             f_t1_flag = 0;
// //     //             continue;
// //     //         }
 
// //     //     }
// //     // }
 
//     return 0;
// }

#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
 
// 最大帧长度
#define MaxFrameLength	10			// 对最大帧长度加以限定，防止接收到过长的帧数据
// 完整的帧头，2个字节
#define Frame_Header1   0x3A                    // 串口接收消息包的帧头的第1个字节
#define Frame_Header2   0x3B                    // 串口接收消息包的帧头的第2个字节
// 完整的帧尾，2个字节
#define Frame_Tail1     0x7E                    // 串口接收消息包的帧尾的第1个字节
#define Frame_Tail2     0x7F                    // 串口接收消息包的帧尾的第2个字节
 
int main(void)
{
    int hs1;
    int snum = 0;                               // 系统串口接收缓存区的可用字节数
    int tnum = 0;                               // 用户串口接收区的数目
    unsigned char chrtmp[100];                  // 用户串口接收区，将缓存的数据放入这里处理
    int f_h1_flag = 0;                          // 接收到帧头的第一个字节标志位
    int f_h_flag = 0;                           // 接收到帧头标志位
    int f_t1_flag = 0;                          // 接收到帧尾的第一个字节标志位
 
 
    wiringPiSetup();                            // 使用wiring编码去初始化GPIO序号
    //hs1 = serialOpen("/dev/ttyS0", 115200);     // 打开 /dev/ttyS0 串口设备，波特率115200
    hs1 = serialOpen("/dev/ttyUSB0", 115200);     // 打开 /dev/ttyUSB0 串口设备，波特率115200
 
 
    /*printf("ttyS0 uart test2:\n");              // 终端打印
    serialPrintf(hs1, "Hello World!\r\n");      // 串口打印
    serialPrintf(hs1, "Enter a paragraph and end with Enter:\r\n");*/
 
    while (1)
    {
        snum = serialDataAvail(hs1);                	// 获取串口接收缓存区的可用字节数
        if(snum > 0)
        {
            chrtmp[tnum] = serialGetchar(hs1);  		// 从接收缓存区读取一个字节
 
            if (f_h_flag == 1)  // 有帧头，判断帧尾，接收消息
            {
                if (f_t1_flag == 1) //有帧头，有帧尾1
                {
                    if (chrtmp[tnum] == Frame_Tail2)
                    {
                        /* 用户处理代码 */
                        /* 将接收到符合帧定义的帧，原路发送回去 */
                        int i = 0;
                        for (i = 0; i < (tnum + 1); i++)
                        {
                            serialPutchar(hs1, chrtmp[i]);	// 通过串口发送字节
                        }
 
                        /*  处理完用户代码，重新接收计数 */
                        tnum = 0;
                    }
                    else
                    {
                        f_t1_flag = 0;
                        tnum ++;
                    }
                }
                else						// 有帧头，无帧尾1
                {
                    if (chrtmp[tnum] == Frame_Tail1)
                    {
                        f_t1_flag = 1;
                        tnum ++;
                    }
                    else					// 接收消息包中间内容
                    {
                        tnum ++;
                    }
                }
            }
            else						// 没有接收到帧头
            {
                if (f_h1_flag == 1)			        //没有帧头，有帧头1。下一步判断是否为第2个字节
                {
                    if (chrtmp[tnum] == Frame_Header2)          // 如果为帧头的第2个字节，接收到帧头标志位标志位置1，tnum自增
                    {
                        f_h_flag = 1;
                        tnum ++;
                    }
                    else
                    {
                        f_h1_flag = 0;
                        tnum = 0;
                    }
                }
                else						//没有帧头，没有有帧头1。下一步判断，是否为帧头的第1个字节
                {
                    if (chrtmp[tnum] == Frame_Header1)  // 如果为帧头的第1个字节，标志位置1，tnum自增
                    {
                        f_h1_flag = 1;
                        tnum ++;
                    }
                    else                                // 否则，标志位清0，tnum清0
                    {
                        tnum = 0;
                    }
                }
            }
 
            // 大于MaxFrameLength个字节的帧不接收
            if (tnum > (MaxFrameLength - 1) )
            {
                tnum = 0;
                f_h1_flag = 0;
                f_h_flag = 0;
                f_t1_flag = 0;
                continue;
            }
 
        }
    }
 
    return 0;
}