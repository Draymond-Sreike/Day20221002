#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat original_Image = imread("D:/OpenCV_Learning/考核任务/1.完成《任务文档》内的任务一/微信图片_20211103234539.jpg"
												   , IMREAD_COLOR);
	Mat hsv_Image;//存储将原图转换位HSV色彩空间后的图像
	Mat process_Image;//存储二值化处理后的图像
	if (original_Image.empty())
	{
		cout << "error:读取图像不存在！" << endl;
		return -1;
	}
	cvtColor(original_Image, hsv_Image, COLOR_BGR2HSV);
	//将原图转为HSV色彩空间，便于后续对图像进行选取特定阈值后的二值化处理
	imshow("Original", original_Image);
	imshow("hsv_Image", hsv_Image);

	/* threshold()函数功能:二值化处理
	*	param1: 原图
	*	param2: 处理所得图
	*	param3:灰度处理分界值(阈值)
	*	param4:二值化处理最大值(255为白，0为黑)
	*	param5:处理模式(详见《OpenCV快速入门》P71-P72)
	*/
	//threshold(original_Image, process_Image, 127, 255,THRESH_BINARY);
	//使用该函数不可行，因为红色的灰度值居中,使用该函数进行图像二值化时
		//绿、黄部分也在红色的二值化范围内，导致红色部分的二值化提取夹杂了其他颜色的二值化
		//故将该方法摒弃，寻找其他可对特定阈值范围进行二值化处理的方法:inRange()
	

	Scalar hsv_Red_Low = Scalar(156, 127, 150);
	Scalar hsv_Red_High = Scalar(180, 255, 255);
	//参考HSV色彩阈值表，并经实践调试后选定红色HSV阈值范围如上

	//这样给hsv_Red_Low、hsv_Red_High赋值是不可行的
	//Scalar hsv_Red_Low = (0, 43, 46);
	//Scalar hsv_Red_High = (10, 255, 255);

	/*	inRange()
	*	函数功能:特定阈值范围的二值化处理（处于阈值范围内的像素点变为白色）
	*	param1: 原图（这里选择对HSV色彩空间的图像进行处理）
	*	param2: 待处理的HSV阈值下限
	*	param3: 待处理的HSV阈值上限
	*	param4: 处理后所得图像
	*	PS: 参考CSDN博主Vaccae文章《C++ OpenCV使用InRange对HSV颜色进行分割》
	*   文章链接:https://blog.csdn.net/Vaccae/article/details/111596031?ops_request_misc=%257B%2522request%255Fid%2522%253A%2522166468003216800186568847%2522%252C%2522scm%2522%253A%252220140713.130102334..%2522%257D&request_id=166468003216800186568847&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~baidu_landing_v2~default-1-111596031-null-null.142^v51^control,201^v3^control_2&utm_term=inrange%E5%87%BD%E6%95%B0c%2B%2B&spm=1018.2226.3001.4187
	*/
	inRange(hsv_Image, hsv_Red_Low, hsv_Red_High, process_Image);
	imshow("Process", process_Image);
	imwrite("D:/OpenCV_Learning/考核任务/1.完成《任务文档》内的任务一/2.色彩分割/效果图/Process_Image.png", process_Image);

	waitKey(0);
	destroyAllWindows();
	return 0;
}
