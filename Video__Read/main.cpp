#include<opencv2/opencv.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	String input_Video_Path = "D:/OpenCV_Learning/考核任务/1.完成《任务文档》内的任务一/4.视频读写以及摄像头读写/能量机关.mp4";

	//视频读取方法一：
	//VideoCapture video;
	//video.open(input_Video_Path);
	//视频读取方法二：
	VideoCapture video(input_Video_Path);

	int videoFPS;//用于获取视频的帧率

	if (video.isOpened())
	{//若视频读取路径正确
		cout << "Video Current Position:" << video.get(CAP_PROP_POS_MSEC) << endl;//视频的当前播放位置
		cout << "Video Height:" << video.get(CAP_PROP_FRAME_HEIGHT) << endl;//视频的高度（宽度）
		cout << "Video Width:" << video.get(CAP_PROP_FRAME_WIDTH) << endl;//视频的宽度（长度）
		cout << "Video FPS:" << (videoFPS = video.get(CAP_PROP_FPS)) << endl;//视频的帧率
		cout << "Video Totalframes:" << video.get(CAP_PROP_FRAME_COUNT) << endl;//视频总帧数
	}
	else
	{//若视频读取路径有误
		cout << "Video reading failure!Please check whether the read path is correct!" << endl;
	}
	
	Mat frame;//用于存储视频中的每一帧图像
	int frameTime = 1000 / videoFPS;//获得每一帧图像的正常停留时间
		//若改为：500 / videoFPS 则相当于2倍速播放
		//若改为：2000 / videoFPS 则相当于0.5倍速播放

	while(1)
	{//逐帧读取视频
		video >> frame;//读取视频帧
		if (frame.empty())
		{//判断所读帧是否为空
			cout << "Video reading completed!" << endl;
			break;//若为空说明视频已读取（播放）完毕，此时跳出读取循环
		}
		imshow("video", frame);//将视频帧进行窗口显示
		waitKey(frameTime); //让每帧图像停留相应的帧时长
	}

	waitKey(0);
	destroyAllWindows();
	return 0;
}
