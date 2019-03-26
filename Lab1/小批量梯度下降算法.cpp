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
		int j;
		float error_sum;//误差 
		error_sum=0;
		float cost[5]={0.0,0.0,0.0,0.0,0.0};//每一维变量对应的变量与误差的乘积 
		for(int t=0;t<50;t++)//数据集规模为100，但是每次只取数据集中的50个 
		{
			float h=0.0;
			j=rand()%100;//在数据集中任取一个数据 
			int k;
			for(k=0;k<5;k++)
			{
				h+=theta[k]*matrix[j][k];//计算在当前权值w下的理论函数值 
			}
			error_sum=h-result[j];//理论函数值与实际函数值的误差
			
			for(k=0;k<5;k++)//计算代价函数的导数 
			{
				cost[k]+=error_sum*matrix[j][k];
			} 
			
			//for(k=0;k<5;k++)
			//{
			//	theta[k]=theta[k]-0.04*//0.04为学习率 
			//}
			
		
		}//对100个数据进行循环 
		for(int k=0;k<5;k++)
		{
			theta[k]=theta[k]-0.0001*cost[k]/100;//0.01为学习率 
		}//对权值进行更新 
		
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
