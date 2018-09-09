#ifndef MATRIX_H
#define MATRIX_H
#include <string>
using namespace std;

static int ID=0;

class matrix
{   private:
    public:
        string name;
        int size_n;//矩阵维度n
        int size_m;//矩阵维度m
        double** _ptr;//矩阵指针(二维数组指针)
        matrix(int=1, int=1, int=1);//初始化
        virtual ~matrix();
        void delete_ptr();//释放指针
        double** create(int);//生成矩阵
        void print();//打印矩阵
        matrix select(int,int);//按行数提取子矩阵
        matrix multiply(const matrix&);//矩阵相乘
        matrix add(const matrix&);//矩阵相加
        matrix sum(string="row");//矩阵求和统计
        matrix matrix_sqrt();//开根号
        matrix cbind(const matrix&);//矩阵列合并
        matrix rbind(const matrix&);//矩阵行合并
        matrix operator+(const matrix&);//矩阵相加重载
        matrix operator+(double);
        matrix operator-(const matrix&);//矩阵相减重载
        matrix operator-(double);
        matrix operator*(const matrix&);//矩阵*重载
        matrix operator*(double);
        matrix operator/(const matrix&);//矩阵/重载
        matrix operator/(double);
        void set_size_n(int);//设置size_n,暂时不太需要
        matrix T(); //转置
        void normaliztion();//标准化
    protected:

};

#endif // MATRIX_H
