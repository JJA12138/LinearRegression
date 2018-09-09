#include <iostream>
#include <matrix.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <LinearRegression.h>

using namespace std;

int main()
{   //创建训练集模拟
    matrix X_init(20,4);
    matrix Y(20);
    matrix b(20,1);
    double S=0;
    for(int i=0;i<20;i++){
        S=0;
        for(int j=0;j<4;j++){
            S=S+X_init._ptr[i][j]*(j+1);//+rand()%1000/double(10000);

        }
        Y._ptr[i][0]=S+0.3;
        b._ptr[i][0]=1;
    }

    X_init.normaliztion();
    matrix X=X_init.cbind(b);

    //创建模型,载入数据
    LinearRegression L(X,Y);
    //L.theta.print();//打印theta
    //L.X.print();
    //L.Y.print();
    L.run();//启动模型训练
    cout<<"pred: "<<endl;
    L.X.multiply(L.theta).print();
    cout<<"Y: "<<endl;
    Y.print();
    cout<<"theta: "<<endl;
    L.theta.print();
    cout<<"迭代次数: "<<L.iteration_count<<endl;

    return 0;


}















