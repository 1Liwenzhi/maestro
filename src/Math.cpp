#include <Math.h>

namespace RCD
{

    Math::Math()
    {
        std::cout<<"MathLibrary Constructor"<<std::endl;
    }

    Math::~Math()
    {
        std::cout<<"MathLibrary De-Constructor"<<std::endl;
    }
    // 求反对称矩阵
    Eigen::Matrix3d Math::scewSymmetric(Eigen::Vector3d t)
    {
        Eigen::Matrix3d t_hat;
        t_hat << 0, -t(2), t(1),
            t(2), 0, -t(0),
            -t(1), t(0), 0;
        return t_hat;
    }
    // 求反对称矩阵所对应的向量
    Eigen::Vector3d Math::scewSymmetricInverse(Eigen::Matrix3d m)
    {
        return Eigen::Vector3d( (m(2,1)-m(1,2))/2.0, (m(0,2) - m(2,0))/2.0, (m(1,0) - m(0,1))/2.0 );
    }
    // 获取RcRdTwd的导数
    Eigen::Vector3d Math::deriv_RcRdTwd(Eigen::Vector3d RcRdTwd_prev,Eigen::Vector3d RcRdTwd_cur, double dt)
    {
        return  (RcRdTwd_cur - RcRdTwd_prev)/dt;
    }
    // 获取期望的机身位置
    Eigen::Vector3d Math::get_pDesiredTrajectory(Eigen::Vector3d p_d0_, double t_real)
    {
        Eigen::Vector3d p_d;

        // x,y axis
        double freq = 0.65; // sim
        // double freq = 0.4; // real

        // p_d(0) = p_d0_(0) + (0.07-0.07*cos(2*M_PI*freq*t_real)); 
        // p_d(1) = p_d0_(1) - 0.07*sin(2*M_PI*freq*t_real); 
        // p_d(2) = p_d0_(2) ;//+ 0.0;

        //  THIS WITH Q_0.x() + 0.2*cos(2*0.25*M_PI*t_real);
        // p_d(0) = p_d0_(0) - 0.07*(sin(2*M_PI*freq*t_real)); 
        // p_d(1) = p_d0_(1) - 0.07*cos(2*M_PI*freq*t_real); 
        // p_d(2) = p_d0_(2) ;//+ 0.0;

        // p_d(0) = p_d0_(0) - 0.04*(sin(2*M_PI*freq*t_real));  //0.07
        // p_d(1) = p_d0_(1) ;//- 0.05*cos(2*M_PI*freq*t_real);  //0.07
        // p_d(2) = p_d0_(2) + 0.0;

        // x, z axis 
        // p_d(0) = p_d0_(0) - 0.1*sin(2*M_PI*0.3*dt); 
        // p_d(1) = p_d0_(1) + 0.0; 
        // p_d(2) = p_d0_(2) + 0.1*cos(2*M_PI*0.25*dt) - 0.1;

        // p_d = p_d0_ + (this->p_T - p_d0_)*(1- std::exp(-0.5*t_real));
        // target 

        // x, z axis 
        p_d(0) = p_d0_(0) - 0.05*sin(2*M_PI*freq*t_real); 
        p_d(1) = p_d0_(1) + 0.0; 
        p_d(2) = p_d0_(2) -(0.05- 0.05*cos(2*M_PI*freq*t_real));

        // // x, z axis 
        // p_d(0) = p_d0_(0) - 0.03*sin(2*M_PI*freq*t_real); 
        // p_d(1) = p_d0_(1) ;//+ 0.0; 
        // p_d(2) = p_d0_(2) -(0.03- 0.03*cos(2*M_PI*freq*t_real));
        return p_d;
    }
    // 获取期望的机身速度
    Eigen::Vector3d Math::get_dpDesiredTrajectory(Eigen::Vector3d p_d0_,Eigen::Vector3d p_d_cur, double dt, double t_real)
    {
        return (get_pDesiredTrajectory(p_d0_, t_real) - p_d_cur)/dt;
    }  
    // 获取期望的机身加速度
    Eigen::Vector3d Math::get_ddpDesiredTrajectory(Eigen::Vector3d p_d0_,Eigen::Vector3d p_d_cur,Eigen::Vector3d dp_d_cur, double dt, double t_real)
    {

        return ( get_dpDesiredTrajectory(p_d0_, p_d_cur, dt, t_real) - dp_d_cur)/dt;
    }    

    // Orientation
    // 获取期望的旋转矩阵
    Eigen::Matrix3d Math::get_RDesiredRotationMatrix(Eigen::Quaterniond Q_0, double t_real)
    {
        Eigen::Quaterniond temp = Q_0;
        temp.x() = Q_0.x() + 0.2*sin(2*0.2*M_PI*t_real); // 
        temp.normalize();
        return temp.toRotationMatrix(); 
    }
    // 获取机身期望的方向导数
    Eigen::Matrix3d Math::get_dRDesiredRotationMatrix(Eigen::Quaterniond Q_0, Eigen::Matrix3d R_cur,double dt, double t_real)
    {
        return (get_RDesiredRotationMatrix(Q_0, t_real) - R_cur)/ dt;
    }
    // 获取机身的速度
    Eigen::Vector3d Math::get_dp_CoM(Eigen::Vector3d com_p_prev,Eigen::Vector3d com_p_cur,double dt)
    {
        return (com_p_cur - com_p_prev )/dt;
    }
    // 获取机身的方向导数
    Eigen::Matrix3d Math::get_dR_CoM(Eigen::Matrix3d R_CoM_prev,Eigen::Matrix3d R_CoM_cur, double dt)
    {
        return (R_CoM_cur - R_CoM_prev)/dt;
    }

}