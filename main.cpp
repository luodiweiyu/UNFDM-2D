/*
非结构有限差分法二维程序（Unstructural Finite Differential Method, UFDM)
程序功能：
1.根据简单的计算域控制参数，自动生成六边形网格
2.利用非结构有限差分进行流场计算
3.可通过控制主程序调用的测试函数，对超声速流动/潜水波方程进行切换
*/
//#include"TestCase/SuperSonicFlow.h"
#include"TestCase/ShallowWater.h"
int main()
{
	//testSuperSonicFlow();/*超声速流动计算,调用此函数需包含对应的头文件*/
	testShallowWater();/*潜水波计算,调用此函数需包含对应的头文件*/
}