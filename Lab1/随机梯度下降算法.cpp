#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>
int main()
{
	float matrix[100][5];
	float result[100];
	float theta[5]={0.5,0.5,0.5,0.5,0.5};//��㸳ֵ����ʼȨֵ����Ҫ�����Ż� 
	float loss;//���ϱ�����δ����ֵ
	loss=0.0;
	srand((unsigned)time(NULL));
	int i;
	for(i=0;i<100;i++)//���������������ֵ 
	{
		int j;
		for(j=0;j<5;j++)
		{
			matrix[i][j]=rand()%100;
		}//��ά���������ֵ�������� 
		
	    result[i]=rand()%2;//��ʵ����ֵ 
	}
	
	//for(i=0;i<100;i++)
	//{
	//	int j;
	//	for(j=0;j<5;j++)
	//	{
	//		matrix[i][j]=i+1;
	//	}//����ά������ֵ
	//	result[i]=i+1; 
	//} 
	
	
	for(i=0;i<100;i++)//�����ʼloss 
	{
		float t;//����ÿ��������ۺ���ֵ
		t=0.0;//ÿ��ѭ��t��0��ʼ 
		int l;
		for(l=0;l<5;l++)
		{
			t+=theta[l]*matrix[i][l];
		}//����ֵ�������
		loss+=(result[i]-t)*(result[i]-t);//����ֵ��ʵ��ֵ����ƽ��  
	}
	
	printf("��ʼ��lossΪ:%f\n\n",loss);//��ӡ��ʼloss 
	
	
	for(i=0;i<1000&&loss>0.0000001;i++)//�������� 
	{
		int j=i%100;//�ӹ�ģΪ100�����ݼ������ȡһ������ 
		float error_sum;//��� 
		error_sum=0;
		float h=0.0;
		for(int k=0;k<5;k++)
		{
			h+=matrix[j][k]*theta[k];//��ĵ�ĺ�������ֵ 
    
		}
		error_sum=h-result[j];
		
		for(int k=0;k<5;k++)//��һ����������������ݼ�������Ȩֵ 
		{
			theta[k] = theta[k]-0.0001*(error_sum)*matrix[j][k];
		}
		
		
	}//������� 
	
	loss=0;
	for(i=0;i<100;i++)//��������loss 
	{
		float t;//����ÿ��������ۺ���ֵ
		t=0.0;
		int l;
		for(l=0;l<5;l++)
		{
			t+=theta[l]*matrix[i][l];
		}//����ֵ�������
		loss+=(result[i]-t)*(result[i]-t);//����ֵ��ʵ��ֵ����ƽ��  
	} 
	
	printf("����lossΪ:%f\n",loss);//��ӡ����loss 
	
	for(i=0;i<5;i++)
	{
		printf("Ȩֵ�ĵ�%dά���������������Ż�Ϊ��%f\n",i,theta[i]);
	}
	
	return 0; 
	
}
