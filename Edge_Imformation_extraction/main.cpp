#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Mat original_Image = imread("D:/OpenCV_Learning/考核任务/1.完成《任务文档》内的任务一/微信图片_20211103234539.jpg"
		, IMREAD_COLOR);
	Mat hsv_Image;//存储将原图转换位HSV色彩空间后的图像
	Mat segmentation_Image;//存储二值化处理后的色彩分割图像
	Mat edge_Image;//存储边缘提取图像
	Mat edge_Green_Image;//存储边缘提取后，将其更改为绿色后的图像
	if (original_Image.empty())
	{
		cout << "error:读取图像不存在！" << endl;
		return -1;
	}
	cvtColor(original_Image, hsv_Image, COLOR_BGR2HSV);
		//将原图转为HSV色彩空间，便于后续对图像使用inRange()函数选取特定阈值后的二值化处理

	Scalar hsv_Red_Low = Scalar(156, 127, 150);
	Scalar hsv_Red_High = Scalar(180, 255, 255);
		//参考HSV色彩阈值表，并经实践调试后选定红色HSV阈值范围如上

		/*	inRange()
		*	函数功能:特定阈值范围的二值化处理（处于阈值范围内的像素点变为白色）
		*	param1: 原图（这里选择对HSV色彩空间的图像进行处理）
		*	param2: 待处理的HSV阈值下限
		*	param3: 待处理的HSV阈值上限
		*	param4: 处理后所得图像(单通道)
		*/
	inRange(hsv_Image, hsv_Red_Low, hsv_Red_High, segmentation_Image);
	//cout << hsv_Image.channels() << endl;//3
	//cout << segmentation_Image.channels() << endl;//1

		/*	Canny()
		*	函数功能:特定阈值范围的二值化处理（处于阈值范围内的像素点变为白色）
		*	param1: 原图（这里选择对HSV色彩空间的图像进行处理）
		*	param2: 待处理的HSV阈值下限
		*	param3: 待处理的HSV阈值上限
		*	param4: 处理后所得图像(仍为单通道)
		*/
	Canny(segmentation_Image, edge_Image, 100, 300);
	//cout << edge_Image.channels() << endl;//1
	//imshow("Edge1", edge_Image);

	cvtColor(edge_Image, edge_Green_Image, COLOR_GRAY2BGR);
		//将边缘提取后的图像色彩空间转为BGR，便于后续对边缘部分上色
	//cout << edge_Green_Image.channels() << endl;//3
	//imshow("Edge2", edge_Green_Image);//转换后的图像仍然保持与转换前相同

	int width = edge_Green_Image.rows;//获取图像竖像素点总数
	int length = edge_Green_Image.cols;//获取图像横像素点总数
	for (int row = 0; row < width; ++row)
		for (int col = 0; col < length; ++col)
		{
			//Vec3b用于获取每个像素点的三个通道值，可以理解为一个数组存储[B, G, R]
			if (edge_Green_Image.at<Vec3b>(row, col) == Vec3b(255, 255, 255))//判断是否为边缘点（白点）
				edge_Green_Image.at<Vec3b>(row, col) = Vec3b(0, 255, 0);//对边缘点上色（绿点）
		}
	imshow("Origin", original_Image);
	imshow("Edge1", edge_Image);
	imshow("Edge2", edge_Green_Image);

	imwrite("D:/OpenCV_Learning/考核任务/1.完成《任务文档》内的任务一/3.边缘信息提取/效果图/Edge_Image.png", edge_Image);
	imwrite("D:/OpenCV_Learning/考核任务/1.完成《任务文档》内的任务一/3.边缘信息提取/效果图/Edge_Green_Image.png", edge_Green_Image);
	waitKey(0);
	destroyAllWindows();
	return 0;
}
