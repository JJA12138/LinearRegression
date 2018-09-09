#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H
#include <matrix.h>
using namespace std;



class LinearRegression
{   private:

    public:
        matrix theta;//参数
        matrix X;//训练集X
        matrix Y;//标签集
        matrix pred;//预测集
        int iteration_count=0;//训练次数统计
        double loss=10000;//损失值
        LinearRegression(const matrix&,const matrix&);
        virtual ~LinearRegression();
        void back_propagation(double=0.05);//反向传播
        void run(double=0.05,int=1);//模型训练
        void iteration(double=0.05,int=500,double=0.0001);//迭代器,控制训练迭代次数

    protected:


};

#endif // LINEARREGRESSION_H
