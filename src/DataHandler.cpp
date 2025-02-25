#include <DataHandler.h>

namespace RCD
{
    DataHandler::DataHandler()
    {
        std::cout<<"DataHandler Constructor"<<std::endl;
        // this->main_path = "/home/despargy/go1_ws/src/maestro/CSV/";
    }
    DataHandler::~DataHandler()
    {
        std::cout<<"DataHandler De-Constructor"<<std::endl;
    }
    // logfile对象代表了一个输出流，他将数据写入到一个文件中
    void DataHandler::logData()
    {
        logfile
            // time, virtual, d_virtual
            << *log_data.t_real<<"," <<*log_data.tv<<","<<  *log_data.d_tv<<"," <<
            (*log_data.e_p)(0)<<"," << (*log_data.e_p)(1)<<"," << (*log_data.e_p)(2)<<"," <<
            (*log_data.e_o)(0)<<"," << (*log_data.e_o)(1)<<"," << (*log_data.e_o)(2)<<"," <<
            (*log_data.e_v)(0)<<"," << (*log_data.e_v)(1)<<"," << (*log_data.e_v)(2)<<"," <<
            (*log_data.e_v)(3)<<"," << (*log_data.e_v)(4)<<"," << (*log_data.e_v)(5)<<"," <<
            (*log_data.vvvv)(0)<<"," << (*log_data.vvvv)(1)<<"," << (*log_data.vvvv)(2)<<"," <<
            (*log_data.vvvv)(3)<<"," << (*log_data.vvvv)(4)<<"," << (*log_data.vvvv)(5)<<"," <<
            (*log_data.vvvv)(6)<<"," << (*log_data.vvvv)(7)<<"," << (*log_data.vvvv)(8)<<"," <<
            (*log_data.vvvv)(9)<<"," << (*log_data.vvvv)(10)<<"," << (*log_data.vvvv)(11)<<"," <<                    
            (*log_data.p_c)(0)<<"," << (*log_data.p_c)(1)<<"," << (*log_data.p_c)(2)<<"," <<
            (*log_data.p_d)(0)<<"," << (*log_data.p_d)(1)<<"," << (*log_data.p_d)(2)<<"," <<      
            (*log_data.leg_prob_0)<<"," << (*log_data.leg_prob_1)<<"," << (*log_data.leg_prob_2)<<"," << (*log_data.leg_prob_3)<<"\n" ;              
    }
    //CSV文件通常由逗号分隔的值组成，因此可以使用逗号作为分隔符来解析每个值。
    void DataHandler::openOnce()
    {
        logfile.open(main_path + "Log.csv");//打开Log.csv文件
        logfile
              // time, virtual, d_virtual
                << "t_real, tv, d_tv, "
                "e_p_x, e_p_y,e_p_z, e_o_x, e_o_y, e_o_z, "
                "e_v_lin_x, e_v_lin_y, e_v_lin_z, e_v_ang_x, e_v_ang_y, e_v_ang_z,"
                "W_0x, W_0y, W_0z,  "              
                "W_1x, W_1y, W_1z,  "              
                "W_2x, W_2y, W_2z,  "              
                "W_3x, W_3y, W_3z,"
                "p_c_x, p_c_y, p_c_z,"
                "p_d_x, p_d_y, p_d_z,"
                "prob0, prob1, prob2, prob3 \n";

    }
    void DataHandler::closeOnce()
    {
        logfile.close();
    }
    
}
