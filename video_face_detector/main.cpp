#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const bool using_camera = false;

void main()
{

	const string filepath = "Resources/face_rotating.mp4";

#ifdef using_camera

	const int camera_index = 0; 

	VideoCapture video(camera_index);

#else

	VideoCapture video(filepath);

#endif


	CascadeClassifier faceCascade;
	faceCascade.load("Resources/haarcascade_frontalface_default.xml");
	if(faceCascade.empty()) { cout << "XML file not loaded" << endl; }

	Mat img;

	while(video.isOpened())
	{
		for(int skip = 0; skip < 5 && video.isOpened(); skip++)
			video.read(img);

		vector<Rect> faces;
		faceCascade.detectMultiScale(img, faces, 1.1, 10);

		for(size_t i = 0; i < faces.size(); i++)
			rectangle(img, faces[i].tl(), faces[i].br(), Scalar(66, 255, 66), 3);

		imshow("Image", img);
		waitKey(1);
	}
}