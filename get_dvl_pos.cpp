#include "communication.h"

void dvlA50_pos_data_python2cpp()
{
    float att[] = {0.0, 0.0, 0.0};
    float roll, pitch, yaw;
while(1){
    PyGILState_STATE gstate;
    gstate = PyGILState_Ensure();   //如果没有GIL，则申请获取GIL

    PyRun_SimpleString("print 'dvlA50_pos_data_python2cpp'");
    // Py_BEGIN_ALLOW_THREADS;
    // Py_BLOCK_THREADS;
    PyObject *pName, *pModule, *pFunc_connect, *pFunc_message;
    PyObject *pArgs, *pReturn;
    
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('/home/pi/FXC/dvl-python/tcp')");
    pName = PyString_FromString("dvl_tcp_parser");
    // cout <<"pName : " << pName;
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);
    if (pModule == NULL)
    {
        cout << "dvlA50 pos module not found" << endl;
        return;
    }
    pFunc_connect = PyObject_GetAttrString(pModule, "hc_connet_dvl_pos");

    if (!pFunc_connect || !PyCallable_Check(pFunc_connect))
    {
        cout << "not found function hc_connet_dvl_pos" << endl;
        return;
    }
    PyObject *dvl_socket2 = PyObject_CallObject(pFunc_connect, NULL);

    pFunc_message = PyObject_GetAttrString(pModule, "hc_process_messages");
    if (!pFunc_message || !PyCallable_Check(pFunc_message))
    {
        cout << "not found function hc_process_messages" << endl;
        return;
    }
    //建立形参
    Py_DECREF(pFunc_connect);
    Py_DECREF(pModule);
    pArgs = PyTuple_New(2);

    //定义元组 socket 、 message——type
    // PyTuple_SetItem = (pArgs, 0, Py_BuildValue("O&", dvl_socket));
    PyTuple_SetItem(pArgs, 0, dvl_socket2);
    PyTuple_SetItem(pArgs, 1, Py_BuildValue("s", "position_local"));
    //调用函数
    pReturn = PyObject_CallObject(pFunc_message, pArgs);
    Py_DECREF(pArgs);
    Py_DECREF(dvl_socket2);
    Py_DECREF(pFunc_message);
        
    // PyObject *PyList  = PyList_New(2); //定义一个与数组等长的PyList对象数组
    // PyObject *ArgList = PyTuple_New(1);//定义一个Tuple对象，Tuple对象的长度与Python函数参数个数一致
    // for(int i = 0; i < PyList_Size(PyList); i++)
    // {
    //     PyList_SetItem(PyList,i, PyFloat_FromFloat(pressure_and_temperture[i])); //给PyList对象的每个元素赋值
    // }
    // PyTuple_SetItem(ArgList, 0, PyList);//将PyList对象放入PyTuple对象中

    if (PyList_Check(pReturn))
    {                                          //检查是否为List对象
        int SizeOfList = PyList_Size(pReturn); //List对象的大小，这里SizeOfList =
        for (int i = 0; i < SizeOfList; i++)
        {
            PyObject *Item = PyList_GetItem(pReturn, i); //获取List对象中的每一个元素
            float result;
            PyArg_Parse(Item, "f", &result); //f表示转换成float型变量
            // cout << result<<endl;
            att[i] = result;
            //cout << PyInt_AsLong(Item) <<" "; //输出元素
            Py_DECREF(Item); //释放空间
        }
    }
    else
    {
        cout << "Not a List" << endl;
    }
    Py_DECREF(pReturn);
    roll = att[0];
    pitch = att[1];
    yaw = att[2];
    cout << "roll : " << roll << "pitch : " << pitch << "yaw : " << yaw<< endl;

    

    int len = 3 * 4;
    send_to_deque(att, len, sensor_mode_att, disarm);
  
    PyGILState_Release(gstate);    //释放当前线程的GIL
    usleep(1000 * 500);

}
}

// int main() {
//     cout << "dvlA50_pos_data_python2cpp is " ;
//     dvlA50_pos_data_python2cpp();
//     return 0;
// }