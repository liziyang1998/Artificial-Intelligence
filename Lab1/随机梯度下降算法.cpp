#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	float matrix[100][5];
	float result[100];
	float theta[5]={0.5,0.5,0.5,0.5,0.5};//随便赋值，初始权值，需要经过优化 
	float loss;//以上变量均未给初值
	loss=0.0;
	srand((unsigned)time(NULL));
	int i;
	for(i=0;i<100;i++)//对上述变量赋予初值 
	{
		int j;
		for(j=0;j<5;j++)
		{
			matrix[i][j]=rand()%100;
		}//五维变量的随机值，待调整 
		
	    result[i]=rand()%2;//真实函数值 
	}
	
	//for(i=0;i<100;i++)
	//{
	//	int j;
	//	for(j=0;j<5;j++)
	//	{
	//		matrix[i][j]=i+1;
	//	}//对五维变量赋值
	//	result[i]=i+1; 
	//} 
	
	
	for(i=0;i<100;i++)//计算初始loss 
	{
		float t;//计算每个点的理论函数值
		t=0.0;//每次循环t从0开始 
		int l;
		for(l=0;l<5;l++)
		{
			t+=theta[l]*matrix[i][l];
		}//理论值计算完毕
		loss+=(result[i]-t)*(result[i]-t);//理论值与实际值误差的平方  
	}
	
	printf("初始的loss为:%f\n\n",loss);//打印初始loss 
	
	
	for(i=0;i<1000&&loss>0.0000001;i++)//迭代次数 
	{
		int j=i%100;//从规模为100的数据集中随机取一个数据 
		float error_sum;//误差 
		error_sum=0;
		float h=0.0;
		for(int k=0;k<5;k++)
		{
			h+=matrix[j][k]*theta[k];//求改点的函数理论值 
    
		}
		error_sum=h-result[j];
		
		for(int k=0;k<5;k++)//用一个点而不是整个数据集来更新权值 
		{
			theta[k] = theta[k]-0.0001*(error_sum)*matrix[j][k];
		}
		
		
	}//迭代完成 
	
	loss=0;
	for(i=0;i<100;i++)//计算最终loss 
	{
		float t;//计算每个点的理论函数值
		t=0.0;
		int l;
		for(l=0;l<5;l++)
		{
			t+=theta[l]*matrix[i][l];
		}//理论值计算完毕
		loss+=(result[i]-t)*(result[i]-t);//理论值与实际值误差的平方  
	} 
	
	printf("最终loss为:%f\n",loss);//打印最终loss 
	
	for(i=0;i<5;i++)
	{
		printf("权值的第%d维经过迭代后最终优化为：%f\n",i,theta[i]);
	}
	
	return 0; 
	
}
