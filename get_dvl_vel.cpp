#include "communication.h"
// void dvlA50_connect(){
//     PyObject *pName_dvlA50, *pModule_dvlA50, *pFunc_connect_dvlA50;
//     PyRun_SimpleString("import sys");
//     PyRun_SimpleString("sys.path.append('/home/pi/FXC/dvl-python/tcp')");
//     pName_dvlA50 = PyString_FromString("dvl_tcp_parser");
//     pModule_dvlA50 = PyImport_Import(pName_dvlA50);
//     Py_DECREF(pName_dvlA50);
//     if( pModule_dvlA50 == NULL ){
// 		cout <<"dvlA50 vel module not found" << endl;
// 		return ;
// 	}
//     pFunc_connect_dvlA50 = PyObject_GetAttrString(pModule_dvlA50, "hc_connet_dvl_vel");    
//     if( !pFunc_connect_dvlA50 || !PyCallable_Check(pFunc_connect_dvlA50)){
// 		cout <<"not found function hc_connet_dvl_vel" << endl;
// 		return ;
// 	}
//     Py_DECREF(pModule_dvlA50);
//     dvl_socket = PyObject_CallObject(pFunc_connect_dvlA50, NULL);
//     Py_DECREF(pFunc_connect_dvlA50);
// }

void dvlA50_vel_data_python2cpp(){
    float velocity_and_distance[] = {0.0, 0.0, 0.0, 0.0};
    float vx,vy,vz,distance;
    int nHold = 0;

while(1){
    // Py_BEGIN_ALLOW_THREADS;
    // Py_BLOCK_THREADS;
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();
    // PyRun_SimpleString("print 'dvlA50_vel_data_python2cpp'");
    
    PyObject *pName, *pModule, *pFunc_connect, *pFunc_message;
    PyObject *pArgs, *pReturn;

    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/pi/FXC/dvl-python/tcp')");
    pName = PyString_FromString("dvl_tcp_parser");

    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if( pModule == NULL ){
		cout <<"dvlA50 vel module not found" << endl;
		return ;
	}
    pFunc_connect = PyObject_GetAttrString(pModule, "hc_connet_dvl_vel");
            
    if( !pFunc_connect || !PyCallable_Check(pFunc_connect)){
		cout <<"not found function hc_connet_dvl_vel" << endl;
		return ;
	}
    PyObject *dvl_socket1 = PyObject_CallObject(pFunc_connect, NULL);

    pFunc_message = PyObject_GetAttrString(pModule, "hc_process_messages");
    if( !pFunc_message || !PyCallable_Check(pFunc_message)){
		cout <<"not found function hc_process_messages" << endl;
		return ;
	}
    
    Py_DECREF(pFunc_connect);
    Py_DECREF(pModule);
    //????????????
    pArgs = PyTuple_New(2);
    //???????????? socket ??? message??????type
    // PyTuple_SetItem = (pArgs, 0, Py_BuildValue("O&", dvl_socket));
    PyTuple_SetItem (pArgs, 0, dvl_socket1);
    PyTuple_SetItem (pArgs, 1, Py_BuildValue("s", "velocity")); 
    
    pReturn=PyObject_CallObject(pFunc_message, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(dvl_socket1);
    // PyObject *PyList  = PyList_New(2); //??????????????????????????????PyList????????????
    // PyObject *ArgList = PyTuple_New(1);//????????????Tuple?????????Tuple??????????????????Python????????????????????????
    // for(int i = 0; i < PyList_Size(PyList); i++)
    // {
    //     PyList_SetItem(PyList,i, PyFloat_FromFloat(pressure_and_temperture[i])); //???PyList???????????????????????????
    // }
    // PyTuple_SetItem(ArgList, 0, PyList);//???PyList????????????PyTuple?????????
        
    // cout << "pReturn" << pReturn <<endl;

    Py_DECREF(pFunc_message);
    if(PyList_Check(pReturn)){ //???????????????List??????
        int SizeOfList = PyList_Size(pReturn);//List????????????????????????SizeOfList =
        for(int i = 0; i < SizeOfList; i++){
            PyObject *Item = PyList_GetItem(pReturn, i);//??????List???????????????????????????
            float result;
            PyArg_Parse(Item, "f", &result);//f???????????????float?????????
            // cout << result<<endl;
            velocity_and_distance[i] = result;
            //cout << PyInt_AsLong(Item) <<" "; //????????????
            Py_DECREF(Item); //????????????
        }
    }else{
        cout<<"Not a List"<<endl;
    }
    
    Py_DECREF(pReturn);
    vx = velocity_and_distance[0];
    vy = velocity_and_distance[1];
    vz = velocity_and_distance[2];
    distance = velocity_and_distance[3];

    int len = 4 * 4;
    // cout << " vx: "<< vx << " vy: "<< vy << " vz: "<< vz <<"distance" << distance << endl;
    send_to_deque(velocity_and_distance, len, sensor_mode_v, 0x20);
    PyGILState_Release(gstate);
    usleep(1000 * 50);
}
}

