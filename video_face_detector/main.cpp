#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

const bool using_camera = false;

int main()
{

       const string filepath = "Resources/face_rotating_2.mp4";

#ifdef using_camera

       const int camera_index = 0;

       VideoCapture video(camera_index);

#else

       VideoCapture video(filepath);

#endif

       bool front_face = false, profile_face = false;

       CascadeClassifier faceCascade;
       Mat img;
       ////////////////////// Check the face from front side ////////////////////////////////

       faceCascade.load("Resources/haarcascade_frontalface_default.xml");
       if(faceCascade.empty())
              cout << "Frontalface XML file not loaded" << endl;

       while(video.isOpened())
       {
              for(int skip = 0; skip < 2 && video.isOpened(); skip++)
                     video.read(img);

              if(img.empty())
                     break;

              vector<Rect> faces;
              faceCascade.detectMultiScale(img, faces, 1.1, 3, 0, Size(250, 250));

              for(size_t i = 0; i < faces.size(); i++)
              {
                     for(int j = 0; j < 1e7; j++);
                     rectangle(img, faces[i].tl(), faces[i].br(), Scalar(66, 255, 66), 3);
              }

              front_face |= !faces.empty();

              imshow("Image", img);

              waitKey(1);
       }

       ////////////////////// Check the face from front side FINISHED ////////////////////////////////



       ////////////////////// Check the face profile ////////////////////////////////

       // video has been finished so reopen it
       video.open(filepath);
       //faceCascade.load("Resources/haarcascade_profileface.xml");
       CascadeClassifier faceCascade2;
       faceCascade2.load("Resources/right_profile_face.xml");
       if(faceCascade2.empty())
              cout << "Profileface XML file not loaded" << endl;


       while(video.isOpened())
       {
              for(int skip = 0; skip < 2 && video.isOpened(); skip++)
                     video.read(img);

              if(img.empty())
                     break;
              
              // original version 

              vector<Rect> faces;
              faceCascade2.detectMultiScale(img, faces, 1.1, 3, 0, Size(250, 250));

              for(size_t i = 0; i < faces.size(); i++)
              {
                     waitKey(100);
                     rectangle(img, faces[i].tl(), faces[i].br(), Scalar(66, 255, 66), 3);
              }

              profile_face |= !faces.empty();

              imshow("Image", img);

              waitKey(1);
#if 0
              // do it now with the flipped one

              flip(img, img, 1);
              faces.clear();

              faceCascade2.detectMultiScale(img, faces, 1.1, 3, 0, Size(250, 250));

              for(size_t i = 0; i < faces.size(); i++)
              {
                     waitKey(100);
                     rectangle(img, faces[i].tl(), faces[i].br(), Scalar(66, 255, 66), 3);
              }

              profile_face |= !faces.empty();

              imshow("Image", img);

              waitKey(1);
#endif
       }


       // flipped version
       // video has been finished so reopen it
       video.open(filepath);
       
       while(video.isOpened())
       {
              for(int skip = 0; skip < 2 && video.isOpened(); skip++)
                     video.read(img);

              if(img.empty())
                     break;

              // flipped version 
              flip(img, img, 1);
              vector<Rect> faces;
              faceCascade2.detectMultiScale(img, faces, 1.1, 3, 0, Size(250, 250));

              for(size_t i = 0; i < faces.size(); i++)
              {
                     waitKey(100);
                     rectangle(img, faces[i].tl(), faces[i].br(), Scalar(66, 255, 66), 3);
              }

              profile_face |= !faces.empty();

              imshow("Image", img);

              waitKey(1);
       }

       ////////////////////// Check the face from profile FINISHED ////////////////////////////////


       if(front_face && profile_face)
              cout << "Face was found and it was rotated!" << endl;
       else
       {
              if(!front_face && profile_face)
                     cout << "Front face was found but we couldn't detect it from profile view!" << endl;
              else if(front_face && profile_face)
                     cout << "Front face was found but we couldn't detect it from profile view!" << endl;
              else
                     cout << "No faces were detected!" << endl;
       }
       return 0;
}