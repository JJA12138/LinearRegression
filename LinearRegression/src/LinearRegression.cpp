/***********************************
 * 文件名：线性回归
 * 创建人：姜佳琪
 * 日  期：2018-9-8
 * 描  述：第一版实现线性回归，下一版实现多层神经网络并提高运行速度
 * 版  本：12138.1
 **********************************/
 #include "LinearRegression.h"
 #include <matrix.h>
 #include <iostream>
using namespace std;

//根据传入矩阵初始化成员变量
LinearRegression::LinearRegression(const matrix& X,const matrix& Y)
{   //初始化theta
    this->theta.delete_ptr();
    this->theta.size_n=X.size_m;
    this->theta.size_m=1;
    this->theta._ptr=theta.create(1);
    this->theta.name="thea";

    //初始化theta
    this->X.delete_ptr();
    this->X.size_n=X.size_n;
    this->X.size_m=X.size_m;
    this->X._ptr=X._ptr;
    this->X.name="X";

    //初始化theta
    this->Y.delete_ptr();
    this->Y.size_n=Y.size_n;
    this->Y.size_m=Y.size_m;
    this->Y._ptr=Y._ptr;
    this->Y.name="Y";

    this->pred.delete_ptr();
    this->pred.size_n=Y.size_n;
    this->pred.size_m=Y.size_m;
    this->pred._ptr=pred.create(1);
    this->pred.name="pred";
    //ctor
}

//模型结束后清空指针指向的内存
LinearRegression::~LinearRegression()
{   this->theta.delete_ptr();
    this->X.delete_ptr();
    this->Y.delete_ptr();
    //dtor
}

//反向传播,更新theta,loss
void LinearRegression::back_propagation(double alpha)
{   double _J;//求导和
    double pred_minus_Y;
    this->loss=0;
    this->pred.delete_ptr();
    this->pred._ptr=this->X.multiply(this->theta)._ptr;
    for(int i=0;i<this->theta.size_n;i++){
        for(int j=0;j<this->theta.size_m;j++){
            _J=0;
            for(int k=0;k<this->X.size_n;k++){
                pred_minus_Y=this->pred._ptr[k][0]-this->Y._ptr[k][0];
                _J=_J+2*this->X._ptr[k][i]*(pred_minus_Y);//求导
                this->loss=this->loss+pred_minus_Y*pred_minus_Y;
            }
            _J=_J/this->X.size_n;
            this->loss=this->loss/X.size_n;
            this->theta._ptr[i][j]=this->theta._ptr[i][j]-alpha*_J;
        }
    }
}

//模型启动
void LinearRegression::run(double alpha,int loss_print_switch)
{   this->iteration(alpha);
}

//迭代控制器,控制参数学习速率alpha,迭代次数max_iteration_times,以及最小迭代min_loss_update_value。
void LinearRegression::iteration(double alpha,int max_iteration_times,double min_loss_update_value)
{
    double last_loss=2*this->loss;
    for(int i=0;i<max_iteration_times;i++){
        this->back_propagation(alpha);
        cout<<"loss:"<<this->loss<<endl;
        if((last_loss-this->loss)>min_loss_update_value){
            last_loss=this->loss;
            this->iteration_count=i;
        }else{
            this->iteration_count=i;
            break;
        }
    }

}






