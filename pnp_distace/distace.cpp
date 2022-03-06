//#include <opencv2/opencv.hpp>
//#include <iostream>

//using namespace cv;
//using namespace std;


//void drawRotatedRect(cv::Mat &img, const cv::RotatedRect &rect, const cv::Scalar &color, int thickness)
//{
//    cv::Point2f Vertex[4];
//         rect.points(Vertex);
//         for(int i = 0 ; i < 4 ; i++)
//         {
//             cv::line(img , Vertex[i] , Vertex[(i + 1) % 4] , color , thickness);
//         }
//}
//void getTarget2dPoints(cv::RotatedRect object_rect,std::vector<Point2f> &object2d_point)
//{
//    cv::Point2f vertices[4];
//    object_rect.points(vertices);
//    cv::Point2f lu, ld, ru, rd;
//    std::sort(vertices, vertices + 4, [](const cv::Point2f & p1, const cv::Point2f & p2) { return p1.x < p2.x; });
//    if (vertices[0].y < vertices[1].y) {
//        lu = vertices[0];
//        ld = vertices[1];
//    } else {
//        lu = vertices[1];
//        ld = vertices[0];
//    }
//    if (vertices[2].y < vertices[3].y) {
//        ru = vertices[2];
//        rd = vertices[3];
//    } else {
//        ru = vertices[3];
//        rd = vertices[2];
//    }

//    object2d_point.clear();
//    object2d_point.push_back(lu);
//    object2d_point.push_back(ru);
//    object2d_point.push_back(rd);
//    object2d_point.push_back(ld);
//}

//int main()
//{
//    VideoCapture cap;
//    cap.open(1);
//    Mat frame;
//    while(true)
//    {
//        cap >>frame;
//        Mat gray;
//        Mat binImg;
//        cvtColor(frame,gray,COLOR_BGR2GRAY);
//        threshold(gray,binImg,40,255,THRESH_BINARY_INV);
//        vector<vector<cv::Point>> bin_contours;
//        cv::findContours(binImg,bin_contours,RETR_EXTERNAL,CHAIN_APPROX_SIMPLE);


//        for (uint i = 0;i < bin_contours.size();i++)
//        {
//            cv::RotatedRect RRect = minAreaRect(bin_contours[i]);
//            if (RRect.size.area()<1000 || RRect.size.area()>100000)
//                continue;
//            if (max(RRect.size.width,RRect.size.height) / min(RRect.size.width,RRect.size.height) > 1.3)
//                continue;
//            drawRotatedRect(frame,RRect,cv::Scalar(255,0,0),2);//画出最小旋转矩形

//            Mat rot_vector,translation_vector;
//            vector<Point2f> object2d_point;
//            getTarget2dPoints(RRect, object2d_point);

//            std::vector<cv::Point3f> point3d;

//            float half_x = 12.5f/2.0f;
//            float half_y = 13.0f/2.0f;  //height_target / 2.0;

//            point3d.push_back(Point3f(-half_x, half_y, 0));
//            point3d.push_back(Point3f(half_x, half_y, 0));
//            point3d.push_back(Point3f(half_x, -half_y, 0));
//            point3d.push_back(Point3f(-half_x, -half_y, 0));
//            cv::Mat rot;
//            cv::Mat trans;
//            Mat cam_matrix = (Mat_<double>(3,3)<<578.6274,0,334.7460, 0, 576.9578, 214.0938, 0, 0, 1);//1981.3, -6.2, 684, 0, 2006.7, 504, 0, 0, 1
//            Mat distortion_coeff = (Mat_<double>(5,1)<<-0.4290,  0.2780,  0,  0,  0);//-0.1029, 0.0058, -0.0030, 0.0047,0
//            cv::solvePnP(point3d, object2d_point, cam_matrix, distortion_coeff, rot, trans);
//            double tx = trans.at<double>(0,0);
//            double ty = trans.at<double>(1,0);
//            double tz = trans.at<double>(2,0);
//            double dis  =sqrt(tx*tx+ty*ty+ tz*tz);
//            cout<<"dis:"<<dis<<endl;
//            putText(frame,to_string(dis)+"cm",Point(50,50),1,2,Scalar(0,255,100),2);
//        }
//        imshow("1",frame);
//        imshow("2",binImg);
//        if (waitKey(10)=='q')
//            break;

//    }
//}
