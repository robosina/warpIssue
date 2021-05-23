#include "opencv2/opencv_modules.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/timelapsers.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"
#include <iostream>
using namespace std;
using namespace cv;
using namespace cv::detail;

float data_k[9] = { 1.2341799f,          0, 0,
                    0,          1.2341799f, 0,
                    0,                   0, 1 };

float data_R[9] = { 0.97279942f,   0.033378981f, -78.555443f,
                    -0.033378981f,   0.97279942,   195.70378,
                    0,                        0, 1 };

Ptr <RotationWarper> initializeData(Mat&K, Mat&R, Ptr <WarperCreator> warper_creator);

int main(int argc, char *argv[])
{
   cv::Mat img = cv::imread("4.jpg");
   cv::Mat K(3, 3, CV_32F), R;


   //prepare data and warper
   Ptr <WarperCreator>  warper_creator = makePtr <cv::AffineWarper>();
   Ptr <RotationWarper> warper         = initializeData(K, R, warper_creator);

   //do warper on the original image
   cv::Mat   img_warped;
   cv::Point dst_roi = warper->warp(img, K, R, INTER_CUBIC, BORDER_CONSTANT, img_warped);

   //plot a point in original image
   cv::Point2f p(504, 298);
   cv::circle(img, p, 6, cv::Scalar(255, 255, 0), cv::FILLED);
   //warp the point to the new image
   cv::Point2f p2 = warper->warpPoint(p, K, R);
   p2.x -= dst_roi.x;
   p2.y -= dst_roi.y;
   cv::circle(img_warped, p2, 6, cv::Scalar(255, 255, 0), cv::FILLED);
   //plot images
   cv::imshow("image", img);
   cv::imshow("warped", img_warped);
   cv::waitKey(0);
}

Ptr <RotationWarper> initializeData(Mat&K, Mat&R, Ptr <WarperCreator> warper_creator)
{
   K = cv::Mat(3, 3, CV_32F, data_k);
   R = cv::Mat(3, 3, CV_32F, data_R);

   float warped_image_scale = 1;
   float seam_work_aspect   = 1.2;
   return(warper_creator->create(static_cast <float>(warped_image_scale * seam_work_aspect)));
}
