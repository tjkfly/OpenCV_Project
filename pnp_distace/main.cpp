//#include <iostream>
//#include <vector>
//#include <iterator>
//#include <tuple>
//#include <set>

//#include<opencv2/opencv.hpp>
//#define _CRT_SECURE_NO_WARNINGS
//#define _SCL_SECURE_NO_DEPRECATE
//#pragma warning(disable:4996)
//#include <stdio.h>

//#include <ctime>
//#include<typeinfo>
//#include <io.h>


//using namespace cv;
//using namespace std;

///*
//@param File_Directory 为文件夹目录
//@param FileType 为需要查找的文件类型
//@param FilesName 为存放文件名的容器
//*/
//void getFilesName(string& File_Directory, string& FileType, vector<string>& FilesName)
//{
//    string buffer = File_Directory + "\\*" + FileType;

//    _finddata_t c_file;   // 存放文件名的结构体

//    intptr_t hFile;
//    hFile = _findfirst(buffer.c_str(), &c_file);   //找第一个文件命

//    if (hFile == -1L)   // 检查文件夹目录下存在需要查找的文件
//        printf("No files in current directory!\n");
//    else
//    {
//        string fullFilePath;
//        do
//        {
//            fullFilePath.clear();

//            //名字
//            fullFilePath = File_Directory + "\\" + c_file.name;
//            cout << fullFilePath << endl;
//            FilesName.push_back(fullFilePath);

//        } while (_findnext(hFile, &c_file) == 0);  //如果找到下个文件的名字成功的话就返回0,否则返回-1
//        _findclose(hFile);
//    }
//}




//void m_calibration(vector<string>& FilesName, Size board_size, Size square_size, Mat& cameraMatrix, Mat& distCoeffs, vector<Mat>& rvecsMat, vector<Mat>& tvecsMat)
//{
////	ofstream ffout("caliberation_result.txt");                       // 保存标定结果的文件

//    cout << "start………………" << endl;
//    int image_count = 0;                                            // 图像数量
//    Size image_size;                                                // 图像的尺寸

//    vector<Point2f> image_points;                                   // 缓存每幅图像上检测到的角点
//    vector<vector<Point2f>> image_points_seq;                       // 保存检测到的所有角点

//    for (int i = 0; i < FilesName.size(); i++)
//    {
//        image_count++;

//        // 用于观察检验输出
//        cout << "image_count = " << image_count << endl;
//        Mat imageInput = imread(FilesName[i]);
//        if (image_count == 1)  //读入第一张图片时获取图像宽高信息
//        {
//            image_size.width = imageInput.cols;
//            image_size.height = imageInput.rows;
//            cout << "image_size.width = " << image_size.width << endl;
//            cout << "image_size.height = " << image_size.height << endl;
//        }

//        /* 提取角点 */
//        bool ok = findChessboardCorners(imageInput, board_size, image_points, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
//        if (0 == ok)
//        {
//            cout << "第" << image_count << "张照片提取角点失败，请删除后，重新标定！" << endl; //找不到角点
//            imshow("失败照片", imageInput);
//            waitKey(0);
//        }
//        else
//        {
//            Mat view_gray;
//            cout << "imageInput.channels()=" << imageInput.channels() << endl;
//            cvtColor(imageInput, view_gray, COLOR_BGR2GRAY);

//            /* 亚像素精确化 */
//            //find4QuadCornerSubpix(view_gray, image_points, Size(5, 5)); //对粗提取的角点进行精确化
//            cv::cornerSubPix(view_gray, image_points, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 20, 0.01));

//            image_points_seq.push_back(image_points);  //保存亚像素角点

//            /* 在图像上显示角点位置 */
//            drawChessboardCorners(view_gray, board_size, image_points, true);

//            imshow("Camera Calibration", view_gray);//显示图片
//            waitKey(100);//暂停0.1S
//        }
//    }
//    cout << "角点提取完成！！！" << endl;


//    /*棋盘三维信息*/
//    vector<vector<Point3f>> object_points_seq;                     // 保存标定板上角点的三维坐标

//    for (int t = 0; t < image_count; t++)
//    {
//        vector<Point3f> object_points;
//        for (int i = 0; i < board_size.height; i++)
//        {
//            for (int j = 0; j < board_size.width; j++)
//            {
//                Point3f realPoint;
//                /* 假设标定板放在世界坐标系中z=0的平面上 */
//                realPoint.x = i * square_size.width;
//                realPoint.y = j * square_size.height;
//                realPoint.z = 0;
//                object_points.push_back(realPoint);
//            }
//        }
//        object_points_seq.push_back(object_points);
//    }

//    /* 运行标定函数 */
//    double err_first = calibrateCamera(object_points_seq, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, CALIB_FIX_K3);
//    cout << "重投影误差1：" << err_first << "像素" << endl << endl;
//    cout << "标定完成！！！" << endl;


//    cout << "开始评价标定结果………………";
//    double total_err = 0.0;            // 所有图像的平均误差的总和
//    double err = 0.0;                  // 每幅图像的平均误差
//    double totalErr = 0.0;
//    double totalPoints = 0.0;
//    vector<Point2f> image_points_pro;     // 保存重新计算得到的投影点

//    for (int i = 0; i < image_count; i++)
//    {

//        projectPoints(object_points_seq[i], rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points_pro);   //通过得到的摄像机内外参数，对角点的空间三维坐标进行重新投影计算

//        err = norm(Mat(image_points_seq[i]), Mat(image_points_pro), NORM_L2);

//        totalErr += err * err;
//        totalPoints += object_points_seq[i].size();

//        err /= object_points_seq[i].size();
//        //fout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
//        total_err += err;
//    }
//    cout << "重投影误差2：" << sqrt(totalErr / totalPoints) << "像素" << endl << endl;
//    cout << "重投影误差3：" << total_err / image_count << "像素" << endl << endl;


//    //保存定标结果
//    cout << "开始保存定标结果………………" << endl;
//    Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* 保存每幅图像的旋转矩阵 */
//    cout << "相机内参数矩阵：" << endl;
//    cout << cameraMatrix << endl << endl;
//    cout << "畸变系数：\n";
//    cout << distCoeffs << endl << endl << endl;
//    for (int i = 0; i < image_count; i++)
//    {
//        cout << "第" << i + 1 << "幅图像的旋转向量：" << endl;
//        cout << rvecsMat[i] << endl;

//        /* 将旋转向量转换为相对应的旋转矩阵 */
//        Rodrigues(rvecsMat[i], rotation_matrix);
//        cout << "第" << i + 1 << "幅图像的旋转矩阵：" << endl;
//        cout << rotation_matrix << endl;
//        cout << "第" << i + 1 << "幅图像的平移向量：" << endl;
//        cout << tvecsMat[i] << endl << endl;
//    }
//    cout << "定标结果完成保存！！！" << endl;
//    cout << endl;
//}

//void m_undistort(vector<string>& FilesName, Size image_size, Mat& cameraMatrix, Mat& distCoeffs)
//{

//    Mat mapx = Mat(image_size, CV_32FC1);   //X 坐标重映射参数
//    Mat mapy = Mat(image_size, CV_32FC1);   //Y 坐标重映射参数
//    Mat R = Mat::eye(3, 3, CV_32F);
//    cout << "保存矫正图像" << endl;
//    string imageFileName;                  //校正后图像的保存路径
//    stringstream StrStm;
//    string temp;

//    for (int i = 0; i < FilesName.size(); i++)
//    {
//        Mat imageSource = imread(FilesName[i]);

//        Mat newimage = imageSource.clone();

//        //方法一：使用initUndistortRectifyMap和remap两个函数配合实现
//        //initUndistortRectifyMap(cameraMatrix,distCoeffs,R, Mat(),image_size,CV_32FC1,mapx,mapy);
//        //	remap(imageSource,newimage,mapx, mapy, INTER_LINEAR);

//        //方法二：不需要转换矩阵的方式，使用undistort函数实现
//        undistort(imageSource, newimage, cameraMatrix, distCoeffs);

//        StrStm << i + 1;
//        StrStm >> temp;
//        imageFileName = "矫正后图像//" + temp + "_d.jpg";
//        imwrite(imageFileName, newimage);

//        StrStm.clear();
//        imageFileName.clear();
//    }
//    std::cout << "保存结束" << endl;
//}

//int main()
//{
//    string File_Directory1 = "E:\\project\\DL\\OpenCV\\pic";   //文件夹目录1

//    string FileType = ".png";    // 需要查找的文件类型

//    //存放文件名的容器
//    //vector<string>FilesName1 = { "left01.jpg","left03.jpg" };
//    vector<string>FilesName1;
//    getFilesName(File_Directory1, FileType, FilesName1);   // 标定所用图像文件的路径
//    //cout << FilesName1.size();

//    Size board_size = Size(8, 6);                         // 标定板上每行、列的角点数
//    Size square_size = Size(25, 25);                       // 实际测量得到的标定板上每个棋盘格的物理尺寸，单位mm

//    Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));        // 摄像机内参数矩阵
//    Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));          // 摄像机的5个畸变系数：k1,k2,p1,p2,k3
//    vector<Mat> rvecsMat;                                          // 存放所有图像的旋转向量，每一副图像的旋转向量为一个mat
//    vector<Mat> tvecsMat;                                          // 存放所有图像的平移向量，每一副图像的平移向量为一个mat

//    m_calibration(FilesName1, board_size, square_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat);

//    //m_undistort(FilesName1, image_size, cameraMatrix, distCoeffs);
//    waitKey(0);
//    return 0;
//}
