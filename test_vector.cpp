// // #include <stdio.h>
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
// // int main(void)
// // {
// //     // Py_Initialize();                        //初始化python解释器.C/C++中调用Python之前必须先初始化解释器
// //     // //Py_IsInitialized();                //返回python解析器的是否已经初始化完成，如果已完成，返回大于0，否则返回0
// //     // if(!Py_IsInitialized()){
// // 	// 	cout << "python init fail" << endl;
// // 	// 	return 0;
// // 	// }
// //     // // PyRun_SimpleString("import sys");
// //     // // PyRun_SimpleString("sys.path.append('/home/pi/FXC')");
    
// //     // PyObject* pModule = PyImport_ImportModule("test");
// //     // if( pModule == NULL ){
// // 	// 	cout <<"module not found" << endl;
// // 	// 	return 0;
// // 	// }

// //     // PyObject* pFunc = PyObject_GetAttrString(pModule, "test_C_python");
// // 	// if( !pFunc || !PyCallable_Check(pFunc)){
// // 	// 	cout <<"not found function add_num" << endl;
// // 	// 	return 0;
// // 	// }
// //     // PyObject_CallObject(pFunc, NULL);

// //     // Py_Finalize(); //  撤销Py_Initialize()和随后使用Python/C API函数进行的所有初始化， 并销毁自上次调用Py_Initialize()以来创建并为被销毁的所有子解释器。
// //     PyObject *pName, *pModule, *pFunc;
// //     PyObject *pArgs, *pValue;
// //     int i;

// //     // if (argc < 3) {
// //     //     fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
// //     //     return 1;
// //     // }

// //     Py_Initialize();
// //     pName = PyString_FromString("test");
// //     /* Error checking of pName left out */
// //     cout << pName << endl;

// //     pModule = PyImport_Import(pName);
// //     Py_DECREF(pName);

// //     if (pModule != NULL) {
// //         pFunc = PyObject_GetAttrString(pModule, "multiply");
// //         /* pFunc is a new reference */

// //         if (pFunc && PyCallable_Check(pFunc)) {
// //             // pArgs = PyTuple_New(argc - 3);
// //             // // for (i = 0; i < argc - 3; ++i) {
// //             //     pValue = PyInt_FromLong(atoi(argv[i + 3]));
// //             //     if (!pValue) {
// //             //         Py_DECREF(pArgs);
// //             //         Py_DECREF(pModule);
// //             //         fprintf(stderr, "Cannot convert argument\n");
// //             //         return 1;
// //             //     }
// //             //     /* pValue reference stolen here: */
// //             //     PyTuple_SetItem(pArgs, i, pValue);
// //             // // }
// //             pValue = PyObject_CallObject(pFunc, NULL);
// //             // Py_DECREF(pArgs);
// //             if (pValue != NULL) {
// //                 printf("Result of call: %ld\n", PyInt_AsLong(pValue));
// //                 Py_DECREF(pValue);
// //             }
// //             else {
// //                 Py_DECREF(pFunc);
// //                 Py_DECREF(pModule);
// //                 PyErr_Print();
// //                 fprintf(stderr,"Call failed\n");
// //                 return 1;
// //             }
// //         }
// //         else {
// //             if (PyErr_Occurred())
// //                 PyErr_Print();
// //             // fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
// //         }
// //         Py_XDECREF(pFunc);
// //         Py_DECREF(pModule);
// //     }
// //     else {
// //         PyErr_Print();
// //         // fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
// //         return 1;
// //     }
// //     Py_Finalize();
 
// //     return 0;
// // }
// int great_function_from_python(int a){
// 	Py_Initialize();
//     int res;
// 	if( !Py_IsInitialized()){
// 		cout << "python init fail" << endl;
// 		return 0;
// 	}
// 	// PyRun_SimpleString("import sys");
// 	// PyRun_SimpleString("sys.path.append('./script')");
//     PyObject* pName = PyString_FromString("test");
// 	PyObject* pModule = PyImport_Import(pName);
// 	if( pModule == NULL ){
// 		cout <<"module not found" << endl;
// 		return 1;
// 	}
//     // cout << "module :" << pModule << endl;
// 	PyObject* pFunc = PyObject_GetAttrString(pModule, "multiply");
//     // cout << "pFunc :" << pFunc << endl;
// 	if( !pFunc || !PyCallable_Check(pFunc)){
// 		cout <<"not found function add_num" << endl;
// 		return 0;
// 	}
//     PyObject* pArgs = PyTuple_New(1);
//     PyTuple_SetItem(pArgs,0, PyInt_FromLong(a));

// 	PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
//     res = PyInt_AsLong(pValue);
// 	Py_Finalize();
// 	return res;
// }

// int main() {    
//     cout << "great is "  << great_function_from_python(5) << endl;
//     return 0;    
// }

#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> chen = {1,2,3,4,5,6,7,8,9};
    vector<int>::iterator i_begin = chen.begin(),i_end = chen.end();
    cout << chen.size() << endl;

    return 0;
}
