#include<opencv2/opencv.hpp>
#include<iostream>
#include<time.h>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//打开摄像头方法一：
	VideoCapture camera_Video;
	camera_Video.open(0);
	//打开摄像头方法二：
	//VideoCapture camera_Video(0);
	if (!camera_Video.isOpened())
	{//判断摄像头是否正常
		cout << "Falied to open the camera!Please check whether the camera is broken." << endl;
		return -1;
	}

	Mat frame;//用于存储帧图像
	VideoWriter avi;//用于存储后续生成的视频
	String output_Path = "D:/OpenCV_Learning/考核任务/1.完成《任务文档》内的任务一/4.视频读写以及摄像头读写/(2)打开手提前置摄像头，并用窗口显示，录制摄像头视频30s并保存/效果视频";
		//输出路径
	int fourcc = VideoWriter::fourcc('M', 'J', 'P', 'G'); //编解码器代码，参照表见《OpenCV4快速入门》P46表2-7
	double fps = 30.0;//设置生成视频的帧率
	camera_Video >> frame;//先获取一帧摄像头视频，用于后续avi对象调用open时选择合适的视频尺寸
	if (frame.empty())
	{//判断是否正常读取视频帧
		cout << "Falied to get the frame!" << endl;
		return -1;
	}
	avi.open(output_Path + "/Video(30s).avi", fourcc, fps, frame.size(), true);
		//生成一个待存入视频帧的视频文件
			//生成的视频存到output_Path路径下并存为Video(30s).avi
			//编码器代码为fourcc
			//生成的视频帧率为fps
			//生成的视频要为彩色(true)
	if (!avi.isOpened())
	{//判断待生成的视频文件是否创建成功
		cout << "Failed to create video file!" << endl;
		return -1;
	}
	time_t start_Time = time(NULL);//记录程序运行至此处时的系统时间
	while (difftime(time(NULL), start_Time) <= 30)
	{//逐帧操作，如果程序已运行30s则终止，即停止录像
		camera_Video >> frame;//导入图像至frame
		if (frame.empty())
		{//判断是否正常读取视频帧
			cout << "Falied to get the frame!" << endl;
			break;
		}

		////该部分代码参考《OpenCV4快速入门》P46代码清单2-34
		//if (!camera_Video.read(frame))
		//{//从camera_Video导入图像至frame，并判断能否继续从摄像头或者视频文件中读出一帧图像
		//		cout << "摄像头断开连接或者视频读取完成" << endl;
		//		break;
		//}

		avi << frame;//将视频帧写入avi视频流中
		//avi.write(frame);//第二种写入方式
		
		imshow("Camera", frame);
		if(27 == waitKey(1))	//每帧1ms(此时帧率应该完全取决于摄像头的拍摄帧率，详见同文档中"小思考.txt"的解释)
			break;					//如若在此图像显示期间按下ESC键则退出显示循环
	}

	//关闭视频流//该解释参考《OpenCV4快速入门》P46代码清单2-34
	camera_Video.release();
	avi.release();
	destroyAllWindows();
	return 0;
}
