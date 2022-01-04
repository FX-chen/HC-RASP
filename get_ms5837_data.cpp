#include "communication.h"

void ms5837_data_connect(){
    PyObject *pName_ms5837,*pModule_ms5837, *pFunc_ms5837, *pFung_ms5837;
    
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/pi/FXC/ms5837-python')");
    pName_ms5837 = PyString_FromString("get_ms5837_data");
    pModule_ms5837 = PyImport_Import(pName_ms5837);
    Py_DECREF(pName_ms5837);
    if( pModule_ms5837 == NULL ){
		cout <<"ms5837 module not found" << endl;
		return ;
	}
    pFunc_ms5837 = PyObject_GetAttrString(pModule_ms5837, "ms5837_connect");
    

    if( !pFunc_ms5837 || !PyCallable_Check(pFunc_ms5837)){
		cout <<"not found function add_num" << endl;
		return ;
	}
    PyObject_CallObject(pFunc_ms5837, NULL);
    Py_DECREF(pModule_ms5837); 
}

void ms5837_data_python2cpp(){
    float pressure_and_temperture[] = {0.0, 0.0};
    float ms5837_pressure = 0.0;
    float ms5837_temperature = 0.0;
    int nHold = 0;

while(1)
{
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();   //如果没有GIL，则申请获取GIL
    // Py_BEGIN_ALLOW_THREADS;
    PyObject *pName, *pModule, *pFunc, *pFung;
    PyObject *pArgs, *pValue, *pReturn;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/pi/FXC/ms5837-python')");
    pName = PyString_FromString("get_ms5837_data");
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if( pModule == NULL ){
		cout <<"ms5837 module not found" << endl;
		return ;
	}

    pFung = PyObject_GetAttrString(pModule, "get_pressure_and_temp");
    if( !pFung || !PyCallable_Check(pFung)){
		cout <<"not found function add_num" << endl;
		return ;
	}

    Py_DECREF(pModule); 

    pReturn=PyObject_CallObject(pFung, NULL);//调用函数，完成传递
    if(PyList_Check(pReturn)){ //检查是否为List对象
        int SizeOfList = PyList_Size(pReturn);//List对象的大小，这里SizeOfList =
        for(int i = 0; i < SizeOfList; i++){
            PyObject *Item = PyList_GetItem(pReturn, i);//获取List对象中的每一个元素
            float result;
            PyArg_Parse(Item, "f", &result);//i表示转换成int型变量
            // cout << result<<endl;
            pressure_and_temperture[i] = result;
            //cout << PyInt_AsLong(Item) <<" "; //输出元素
            Py_DECREF(Item); //释放空间
        }
    }else{
        cout<<"Not a List"<<endl;
    }
    Py_DECREF(pFung);    
    Py_DECREF(pReturn);

    ms5837_pressure = pressure_and_temperture[0];
    ms5837_temperature = pressure_and_temperture[1];
    cout << "ms5837_pressure: " << ms5837_pressure ;
    cout << endl;
    int len = 1 * 4;
    send_to_deque(pressure_and_temperture, len, sensor_mode_pressure, disarm);
    PyGILState_Release(gstate);    //释放当前线程的GIL
    usleep(1000 * 500);

} 
    
}

