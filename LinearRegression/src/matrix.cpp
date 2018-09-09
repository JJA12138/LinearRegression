/***********************************
 * 文件名：矩阵
 * 创建人：姜佳琪
 * 日  期：2018-09-08
 * 描  述：矩阵实现(二维数组)，运算实现，目前已实现相乘，相加，统计求和，转置。
 * 版  本：12138.1
 **********************************/
#include "matrix.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
using namespace std;

//动态初始化二维数组指针
matrix::matrix(int n, int m, int rand_init)
{   this->size_n = n;
    this->size_m = m;
    this->name=to_string(ID);
    this->_ptr=create(rand_init);
    ID++;
    //ctor
}

matrix::~matrix()
{

    /*
    if((this->ptr_delete==1)&&(this->_ptr!=nullptr)){
        this->delete_ptr();
    }
    */
    //dtor
}

//释放矩阵指针
void matrix::delete_ptr()
{
    if(this->_ptr!=nullptr){
        for(int i=0;i<this->size_n;i++){
            delete []this->_ptr[i];
        }
        delete []this->_ptr;
        this->_ptr=nullptr;
        cout<<this->name<<"内存已释放"<<endl;
    }
}


double** matrix::create(int rand_init)
{   srand((unsigned)time(NULL));
    //创建二维指针
    double **p = new double *[this->size_n];
    for(int i=0;i<this->size_n;i++){
        try{
            p[i]=new double [this->size_m];
        }
        catch(std::bad_alloc){
            cout<<"第"<<i<<"行内存分配出错"<<endl;

            break;
        }

    }

    //给数组随机赋值0~1
    if(rand_init==1){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                p[i][j]=rand()%1000/double(1000);
            }

        }
    }
    return p;
}

//修改矩阵长度
void matrix::set_size_n(int num)
{
    this->size_n=num;
}

//打印矩阵
void matrix::print()
{
    for(int i=0;i<this->size_n;i++){
        for(int j=0;j<this->size_m;j++){
            cout<<"第"<<i<<"行"<<"第"<<j<<"列："<<this->_ptr[i][j]<<"\t";
        }
        cout<<endl;
    }

}

//提取子矩阵,暂时只支持按行提取
matrix matrix::select(int num_start,int num_end)
{   matrix result(num_end-num_start,this->size_m);
    int c=0;
    for(int i=num_start;i<num_end;i++){
        for(int j=0;j<this->size_m;j++){
            result._ptr[c][j]=this->_ptr[i][j];

        }
        c++;
    }
    return result;
}

//矩阵相乘
matrix matrix::multiply(const matrix& array2_mul)
{
    matrix result(this->size_n,array2_mul.size_m);
    double sum=0;
    if(this->size_m==array2_mul.size_n){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<array2_mul.size_m;j++){
                sum=0;
                for(int k=0;k<this->size_m;k++){
                    sum=sum+this->_ptr[i][k]*array2_mul._ptr[k][j];
                }
                result._ptr[i][j]=sum;
            }
        }
        return result;
    }else{
        cout<<"数组维度不一致，无法相乘！"<<endl;
        exit(99);
    }

}

//矩阵相加
matrix matrix::add(const matrix& array2_add)
{
    matrix result(this->size_n,this->size_m);

    if((this->size_n==array2_add.size_n)&&(this->size_m==array2_add.size_m)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]+array2_add._ptr[i][j];
            }
        }
    }else{
        cout<<"数组维度不一致，无法相加！"<<endl;
        exit(99);
    }
    return result;
}


//矩阵求和，对列,行，或者所有值求和
matrix matrix::sum(string add_way)
{   double _sum;
    if(add_way=="row"){
        matrix array_sum(this->size_n,1);
        for(int i=0;i<this->size_n;i++){
            _sum=0;
            for(int j=0;j<this->size_m;j++){
                _sum=_sum+this->_ptr[i][j];
            }
            array_sum._ptr[i][0]=_sum;
            //cout<<_sum<<endl;
        }
        return array_sum;
    }else if(add_way=="column"){
        matrix array_sum(1,this->size_m);
        for(int j=0;j<this->size_m;j++){
            _sum=0;
            for(int i=0;i<this->size_n;i++){
                _sum=_sum+this->_ptr[i][j];
            }
            array_sum._ptr[0][j]=_sum;
        }
        return array_sum;
    }else if(add_way=="all"){
        matrix array_sum(1,1);
        _sum=0;
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                _sum=_sum+this->_ptr[i][j];
            }
        }
        array_sum._ptr[0][0]=_sum;
        return array_sum;
    }else {cout<<"请输入参数row,column,all确定求和方式！"<<endl;}



}

//矩阵转置
matrix matrix::T()
{
    matrix matrix_T(this->size_m,this->size_n);
    for(int i=0;i<this->size_n;i++){
        for(int j=0;j<this->size_m;j++){
            matrix_T._ptr[j][i]<-this->_ptr[i][j];
        }
    }
    return matrix_T;
}

//矩阵开方,暂未加入正数验证
matrix matrix::matrix_sqrt()
{
    matrix result(this->size_n,this->size_m);
    for(int i=0;i<this->size_n;i++){
        for(int j=0;j<this->size_m;j++){
            result._ptr[i][j]=sqrt(this->_ptr[i][j]);
        }
    }
    return result;

};

//矩阵按列合并
matrix matrix::cbind(const matrix& cbind_matrix)
{   matrix result(this->size_n,this->size_m+cbind_matrix.size_m);
    for(int i=0;i<result.size_n;i++){
        for(int j=0;j<result.size_m;j++){
            if(j<this->size_m){
                result._ptr[i][j]=this->_ptr[i][j];
            }else {
                result._ptr[i][j]=cbind_matrix._ptr[i][j-this->size_m];
            }
        }
    }
    return result;

}

//矩阵按行合并
matrix matrix::rbind(const matrix& cbind_matrix)
{   matrix result(this->size_n,this->size_m+cbind_matrix.size_m);
    for(int i=0;i<result.size_n;i++){
        for(int j=0;j<result.size_m;j++){
            if(j<this->size_m){
                result._ptr[i][j]=this->_ptr[i][j];
            }else {
                result._ptr[i][j]=cbind_matrix._ptr[i][j-this->size_m];
            }
        }
    }
    return result;
}


//目前对于矩阵维度不一致的情况，只做了，一行多列，或者一列多行的。
matrix matrix::operator+(const matrix& array2_add)
{   matrix result(this->size_n,this->size_m);
    if((this->size_n==array2_add.size_n)&&(this->size_m==array2_add.size_m)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]+array2_add._ptr[i][j];
            }
        }

        return result;
    }else if((this->size_n==array2_add.size_n)&&(array2_add.size_m==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]+array2_add._ptr[i][0];
            }
        }

        return result;
    }else if((this->size_m==array2_add.size_m)&&(array2_add.size_n==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]+array2_add._ptr[0][j];
            }
        }

        return result;
    }else{
        cout<<"矩阵维度不一致！"<<endl;
        exit(99);
    }
};

matrix matrix::operator+(double add_num)
{   matrix result(this->size_n,this->size_m);
    for(int i=0;i<this->size_n;i++){
        for(int j=0;j<this->size_m;j++){
            result._ptr[i][j]=this->_ptr[i][j]+add_num;
        }
    }

    return result;
};


matrix matrix::operator-(const matrix& array2_add)
{   matrix result(this->size_n,this->size_m);
    if((this->size_n==array2_add.size_n)&&(this->size_m==array2_add.size_m)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]-array2_add._ptr[i][j];
            }
        }

        return result;
    }else if((this->size_n==array2_add.size_n)&&(array2_add.size_m==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]-array2_add._ptr[i][0];
            }
        }

        return result;
    }else if((this->size_m==array2_add.size_m)&&(array2_add.size_n==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]-array2_add._ptr[0][j];
            }
        }

        return result;
    }else{
        cout<<"矩阵维度不一致！"<<endl;
        exit(99);
    }
}

matrix matrix::operator-(double minus_num)
{
    return this->operator+(-minus_num);
}

matrix matrix::operator*(double multiplier)
{   matrix result(this->size_n,this->size_m);
    for(int i=0;i<this->size_n;i++){
        for(int j=0;j<this->size_m;j++){
            result._ptr[i][j]=this->_ptr[i][j]*multiplier;
        }
    }

    return result;
}

matrix matrix::operator*(const matrix& array2_mul)
{   matrix result(this->size_n,this->size_m);
    if((this->size_n==array2_mul.size_n)&&(this->size_m==array2_mul.size_m)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]*array2_mul._ptr[i][j];
            }
        }

        return result;
    }else if((this->size_n==array2_mul.size_n)&&(array2_mul.size_m==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]*array2_mul._ptr[i][0];
            }
        }

        return result;
    }else if((this->size_m==array2_mul.size_m)&&(array2_mul.size_n==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]*array2_mul._ptr[0][j];
            }
        }

        return result;
    }else{
        cout<<"矩阵维度不一致！"<<endl;
        exit(99);
    }
};



matrix matrix::operator/(double divisor)
{   return this->operator*(1/divisor);
}

matrix matrix::operator/(const matrix& array2_mul)
{   matrix result(this->size_n,this->size_m);
    if((this->size_n==array2_mul.size_n)&&(this->size_m==array2_mul.size_m)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]/array2_mul._ptr[i][j];
            }
        }

        return result;
    }else if((this->size_n==array2_mul.size_n)&&(array2_mul.size_m==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]/array2_mul._ptr[i][0];
            }
        }

        return result;
    }else if((this->size_m==array2_mul.size_m)&&(array2_mul.size_n==1)){
        for(int i=0;i<this->size_n;i++){
            for(int j=0;j<this->size_m;j++){
                result._ptr[i][j]=this->_ptr[i][j]/array2_mul._ptr[0][j];
            }
        }

        return result;
    }else{
        cout<<"矩阵维度不一致！"<<endl;
        exit(99);
    }
};

void matrix::normaliztion()
{
    //Z-SCORE标准化
    matrix columns_sum = this->sum("column");//每列的和
    matrix columns_mean = columns_sum/this->size_n;//每列的平均值
    columns_sum.delete_ptr();//释放指针

    matrix mean_deviation=this->operator-(columns_mean);
    matrix mean_deviation2=(mean_deviation)*(mean_deviation);
    mean_deviation.delete_ptr();//释放指针

    matrix variance=mean_deviation2.sum("column")/this->size_n;//方差
    mean_deviation2.delete_ptr();//释放指针

    matrix standard_deviation = variance.matrix_sqrt();
    variance.delete_ptr();//释放指针
    matrix normal=(this->operator-(columns_mean))/standard_deviation;//
    this->_ptr=normal._ptr;
    standard_deviation.delete_ptr();
    //min-max标准化

}
































