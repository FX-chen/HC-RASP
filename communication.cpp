#include"communication.h"


using namespace std;


hc_sensor dvl_vx,dvl_vy,dvl_vz,dvl_distance,dvl_roll,dvl_pitch,dvl_yaw,ms5837_pressure_union,ms5837_depth_union;

hc_control yaw_force,depth_force,att_force,yaw_error,depth_error,att_error;

tran temp;

deque<vector<unsigned char>> process_deque;

mutex deque_mutex;

bool sensor_switch;

// extern temp_value sensor_value;

void send_to_pixhawk(){
    
    int hs1;
    vector<unsigned char> temp_vector;
    while(1)
    {
        cout << "send_to_pixhawk" << endl;
        wiringPiSetup();                            
        hs1 = serialOpen("/dev/ttyAMA0", 115200);
        lock_guard<mutex> lock1(deque_mutex);
        if(!process_deque.empty()){
            temp_vector = process_deque.front();
            process_deque.pop_front();
            
            for(vector<unsigned char>::iterator j = temp_vector.begin(); j < temp_vector.end() ; j++){
                // cout << *j;
                serialPutchar(hs1, *j);
            }
            temp_vector.clear();
            serialClose(hs1);
            
        }
        usleep(1000 * 2.5);//400HZ

    }



}

void receive_from_pixhawk_init(){

}

void receive_from_pixhawk(){
    // while(1){
    // cout << "receive_from_pixhawk" << endl;
    // snum_rec = serialDataAvail(hs2_rec);
    // lock_guard<mutex> lock1(deque_mutex);
    // if(snum_rec > 0)
    // {
    //     while(tnum_rec < snum_rec){

    //         chrtmp_rec[tnum_rec] = serialGetchar(hs2_rec);  		
    //         if (f_h_flag_rec == 1)
    //         {
    //             if (f_t1_flag_rec == 1)
    //             {
    //                 if (chrtmp_rec[tnum_rec] == Frame_Tail2)
    //                 {
    //                     //content
    //                     int len_receive;
    //                     len_receive = chrtmp_rec[2];
    //                     if(chrtmp_rec[4] == arm){
    //                         switch (chrtmp_rec[3])
    //                         {
    //                         case control_mode_yaw_robust:
    //                         {
    //                             cout << "control_yaw_robust" << endl;
    //                             for(int i = 0;i < len_receive; i++){
    //                                 yaw_error.value_char[i] = chrtmp_rec[i + 5];
    //                             }
    //                             hc_yaw_error = yaw_error.value;
    //                             hc_yaw_force = cal_robust_yaw_run();
    //                             int len_yaw = 1 * 4;
    //                             float temp[1];
    //                             temp[0] = hc_yaw_force;
    //                             send_to_deque(temp, len_yaw, control_mode_yaw_robust, disarm);
    //                             break;
    //                         }
    //                         case control_mode_depth_robust:
    //                         {
    //                             cout << "control_depth_hold_robust" << endl;
    //                             for(int i = 0;i < len_receive; i++){
    //                                 depth_error.value_char[i] = chrtmp_rec[i + 5];
    //                             }
    //                             hc_depth_error = depth_error.value;
    //                             hc_depth_force = cal_robust_yaw_run();
    //                             int len_depth = 1 * 4;
    //                             float temp_depth[1];
    //                             temp_depth[0] = hc_depth_force;
    //                             send_to_deque(temp_depth, len_depth, control_mode_depth_robust, disarm);
    //                             break;
    //                         }
    //                         case control_mode_att_robust:
    //                         {
    //                             cout << "control_att_robust" << endl;
    //                             for(int i = 0;i < len_receive; i++){
    //                                 att_error.value_char[i] = chrtmp_rec[i + 5];
    //                             }
    //                             hc_att_error = att_error.value;
    //                             hc_att_force = cal_robust_yaw_run();
    //                             int len_att = 1 * 4;
    //                             float temp_att[1];
    //                             temp_att[0] = hc_att_force;
    //                             send_to_deque(temp_att, len_att, control_mode_att_robust, disarm);
    //                             break;
    //                         }
    //                         default:
    //                             break;
    //                         }
    //                     }

    //                     // tnum = 0;
    //                     tnum_rec ++;
    //                 }
    //                 else
    //                 {
    //                     f_t1_flag_rec = 0;
    //                     tnum_rec ++;
    //                 }
    //             }
    //             else	
    //             {
    //                 if (chrtmp_rec[tnum_rec] == Frame_Tail1)
    //                 {
    //                     f_t1_flag_rec = 1;
    //                     tnum_rec ++;
    //                 }
    //                 else					
    //                 {
    //                     tnum_rec ++;
    //                 }
    //             }
    //         }
    //         else					
    //         {
    //             if (f_h1_flag_rec == 1)			       
    //             {
    //                 if (chrtmp_rec[tnum_rec] == Frame_Header2)         
    //                 {
    //                     f_h_flag_rec = 1;
    //                     tnum_rec ++;
    //                 }
    //                 else
    //                 {
    //                     f_h1_flag_rec = 0;
    //                     tnum_rec = 0;
    //                 }
    //             }
    //             else						
    //             {
    //                 if (chrtmp_rec[tnum_rec] == Frame_Header1)  
    //                 {
    //                     f_h1_flag_rec = 1;
    //                     tnum_rec ++;
    //                 }
    //                 else                                
    //                 {
    //                     tnum_rec = 0;
    //                 }
    //             }
    //         }
    //         // if (tnum > (MaxFrameLength - 1) )
    //         // {
    //         //     tnum = 0;
    //         //     f_h1_flag = 0;
    //         //     f_h_flag = 0;
    //         //     f_t1_flag = 0;
    //         //     // continue;
    //         // }
    //     }

    // }
    // serialClose(hs2);
    // }        
    
}

void send_to_deque(float *value, int len, int mode, int isarm){
    
    int hs1;
    int snum = 0;                               
    int tnum = 0;                              
    unsigned char chrtmp[100]; 
    int f_h1_flag = 0;                         
    int f_h_flag = 0;                          
    int f_t1_flag = 0;
    int i;
    vector<unsigned char> vector_message;
    int number;//the number of value
    number = len / 4;
    chrtmp[0] = Frame_Header1;
    chrtmp[1] = Frame_Header2;
    chrtmp[2] = len;
    chrtmp[3] = mode;
    chrtmp[4] = isarm;
    chrtmp[5+len] = Frame_Tail1;
    chrtmp[6+len] = Frame_Tail2;
    lock_guard<mutex> lock1(deque_mutex);
    switch(mode){
        case sensor_mode_pressure:
            ms5837_pressure_union.value = value[0];
            for(i = 5; i < (5 + len); i++){
                chrtmp[i] = ms5837_pressure_union.value_char[i - 5];
                // cout << "value[i]" << chrtmp[i] ;
            }
            break;
        case sensor_mode_v:
            dvl_vx.value = value[0];
            dvl_vy.value = value[1];
            dvl_vz.value = value[2];
            dvl_distance.value = value[3];
            for(i = 5; i < (5 + len/4); i++){
                chrtmp[i] = dvl_vx.value_char[i - 5];
            }
            for(i = (5 + len/4); i < (5 + len/4*2); i++){
                chrtmp[i] = dvl_vy.value_char[i - (5 + len/4)];
            }
            for(i = (5 + len/4*2); i < (5 + len/4*3); i++){
                chrtmp[i] = dvl_vz.value_char[i - (5 + len/4*2)];
            }
            for(i = (5 + len/4*3); i < (5 + len/4*4); i++){
                chrtmp[i] = dvl_distance.value_char[i - (5 + len/4*3)];
            }
            break;
        case sensor_mode_att:
            dvl_roll.value = value[0];
            dvl_pitch.value = value[1];
            dvl_yaw.value = value[2];
            for(i = 5; i < (5 + len/3); i++){
                chrtmp[i] = dvl_roll.value_char[i - 5];
            }
            for(i = (5 + len/3); i < (5 + len/3*2); i++){
                chrtmp[i] = dvl_pitch.value_char[i - (5 + len/3)];
            }
            for(i = (5 + len/3*2); i < (5 + len/3*3); i++){
                chrtmp[i] = dvl_yaw.value_char[i - (5 + len/3*2)];
                // cout << "dvl_yaw.value_char " << chrtmp[i]; 
            }
            // cout << "sensor_mode_att" << dvl_yaw.value <<endl;
            break;
        case control_mode_yaw_robust:
            yaw_force.value = value[0];
            for(i = 5; i < (5 + len); i++){
                chrtmp[i] = yaw_force.value_char[i - 5];
            }
            break;
        case control_mode_att_robust:
            att_force.value = value[0];
            for(i = 5; i < (5 + len); i++){
                chrtmp[i] = att_force.value_char[i - 5];
            }
            break;
        case control_mode_depth_robust:
            depth_force.value = value[0];
            for(i = 5; i < (5 + len); i++){
                chrtmp[i] = depth_force.value_char[i - 5];
            }
            break;
    }
    int j;
    for(j = 0;j < (7+len); j++){
        vector_message.push_back(chrtmp[j]);
    }
    // for(vector<unsigned char>::iterator j = vector_message.begin(); j < vector_message.end() ; j++){
    // // cout << *j;
    // // serialPutchar(hs1, *j);
    //     cout << *j;
    // }

    if(mode == sensor_mode_pressure or mode == sensor_mode_v or mode == sensor_mode_att){
        process_deque.push_back(vector_message);
    }
    if(mode == control_mode_yaw_robust or mode == control_mode_att_robust or mode == control_mode_depth_robust){
        process_deque.push_front(vector_message);
    }
    
    for(j = 0;j < (7+len); j++){
        chrtmp[j] = 0x00;
    }
    vector_message.clear();

}


int main(){ 
    Py_Initialize();
    if( !Py_IsInitialized()){
	    cout << "Py_Initialize init fail" << endl;
	}

    ms5837_data_connect();
    // dvlA50_connect();      
    PyEval_InitThreads(); //获取了GIL
    PyThreadState *_save;
    _save = PyEval_SaveThread();

    // PyEval_ReleaseThread(PyThreadState_Get());  
    // thread sensor_ms5837(ms5837_data_python2cpp);
    thread sensor_dvl_v(dvlA50_vel_data_python2cpp);
    thread sensor_dvl_p(dvlA50_pos_data_python2cpp);
    thread send_message(send_to_pixhawk);
    // receive_from_pixhawk_init();
    int hs2_rec;
    int snum_rec = 0;                               
    int tnum_rec = 0;                               
    unsigned char chrtmp_rec[100];                  
    int f_h1_flag_rec = 0;                          
    int f_h_flag_rec = 0;                           
    int f_t1_flag_rec = 0;
    wiringPiSetup(); 
    hs2_rec = serialOpen("/dev/ttyAMA0", 115200);
    cal_robust_yaw_init();
    cal_robust_att_init();

    while (true)
    {
        // cout << "数量:" << thread::hardware_concurrency() << endl;
        
        // receive_from_pixhawk();
        // cout << "receive_from_pixhawk" << endl;
        snum_rec = serialDataAvail(hs2_rec);
        // lock_guard<mutex> lock1(deque_mutex);
        printf("snum_rec%d\n",snum_rec);

        if(snum_rec == 11)
        {
            while(snum_rec--){
                // printf("while(snum_rec--)\n");
                chrtmp_rec[tnum_rec] = serialGetchar(hs2_rec);  		
                if (f_h_flag_rec == 1)
                {
                    if (f_t1_flag_rec == 1)
                    {
                        if (chrtmp_rec[tnum_rec] == Frame_Tail2)
                        {
                            //content
                            printf("receive from pix\n");
                            int len_receive;
                            len_receive = chrtmp_rec[2];
                            if((chrtmp_rec[4] & 0x0f) == arm){ //isarm
                                switch (chrtmp_rec[3])//mode
                                {
                                case control_mode_yaw_robust:
                                {
                                    cout << "control_yaw_robust" << endl;
                                    for(int i = protocol_payload;i < (protocol_payload + len_receive); i++){
                                        yaw_error.value_char[i-protocol_payload] = chrtmp_rec[i];
                                    }
                                    hc_yaw_error = yaw_error.value;
                                    printf("hc_yaw_error:%f\n",hc_yaw_error);
                                    hc_yaw_force = cal_robust_yaw_run();
                                    
                                    int len_yaw = 1 * 4;
                                    float temp[1];
                                    temp[0] = hc_yaw_force;
                                    send_to_deque(temp, len_yaw, control_mode_yaw_robust, disarm);
                                    cout << "hc_yaw_force" << hc_yaw_force <<endl;
                                    break;
                                }
                                case control_mode_depth_robust:
                                {
                                    cout << "control_depth_hold_robust" << endl;
                                    for(int i = protocol_payload;i < (protocol_payload + len_receive); i++){
                                        depth_error.value_char[i-protocol_payload] = chrtmp_rec[i];
                                    }
                                    hc_depth_error = depth_error.value;
                                    hc_depth_force = cal_robust_depth_run();
                                    int len_depth = 1 * 4;
                                    float temp_depth[1];
                                    temp_depth[0] = hc_depth_force;
                                    send_to_deque(temp_depth, len_depth, control_mode_depth_robust, disarm);
                                    break;
                                }
                                case control_mode_att_robust:
                                {
                                    cout << "control_att_robust" << endl;
                                    for(int i = protocol_payload;i < (protocol_payload + len_receive); i++){
                                        att_error.value_char[i-protocol_payload] = chrtmp_rec[i];
                                    }
                                    hc_att_error = att_error.value;
                                    hc_att_force = cal_robust_att_run();
                                    int len_att = 1 * 4;
                                    float temp_att[1];
                                    temp_att[0] = hc_att_force;
                                    send_to_deque(temp_att, len_att, control_mode_att_robust, disarm);
                                    break;
                                }
                                
                                default:
                                    break;
                                }
                            }
                            if((chrtmp_rec[4] && 0x80) == turnon){
                                sensor_switch = true;
                            }
                            else{
                                sensor_switch = false;
                            }

                            // tnum = 0;
                            tnum_rec = 0;
                        }
                        else
                        {
                            f_t1_flag_rec = 0;
                            tnum_rec ++;
                        }
                    }
                    else	
                    {
                        if (chrtmp_rec[tnum_rec] == Frame_Tail1)
                        {
                            f_t1_flag_rec = 1;
                            tnum_rec ++;
                        }
                        else					
                        {
                            tnum_rec ++;
                        }
                    }
                }
                else					
                {
                    if (f_h1_flag_rec == 1)			       
                    {
                        if (chrtmp_rec[tnum_rec] == Frame_Header2)         
                        {
                            f_h_flag_rec = 1;
                            tnum_rec ++;
                        }
                        else
                        {
                            f_h1_flag_rec = 0;
                            tnum_rec = 0;
                        }
                    }
                    else						
                    {
                        if (chrtmp_rec[tnum_rec] == Frame_Header1)  
                        {
                            f_h1_flag_rec = 1;
                            tnum_rec ++;
                        }
                        else                                
                        {
                            tnum_rec = 0;
                        }
                    }
                }
                // if (tnum > (MaxFrameLength - 1) )
                // {
                //     tnum = 0;
                //     f_h1_flag = 0;
                //     f_h_flag = 0;
                //     f_t1_flag = 0;
                //     // continue;
                // }
            }

        }
        else{
            while(snum_rec--){
                serialGetchar(hs2_rec);
            }
        }
        int j;
        for(j = 0; j < 11; j++){
            chrtmp_rec[j] = 0x00;
        }
        usleep(1000 * 2.5);

    }
    // sensor_ms5837.join();
    
    // sensor_dvl_p.join();
    PyEval_RestoreThread(_save);
    sensor_dvl_v.join();
    sensor_dvl_p.join();
    // sensor_ms5837.join();
    send_message.join();
    Py_Finalize();

    
    return 0;    
}