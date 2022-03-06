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
//@param File_Directory Ϊ�ļ���Ŀ¼
//@param FileType Ϊ��Ҫ���ҵ��ļ�����
//@param FilesName Ϊ����ļ���������
//*/
//void getFilesName(string& File_Directory, string& FileType, vector<string>& FilesName)
//{
//    string buffer = File_Directory + "\\*" + FileType;

//    _finddata_t c_file;   // ����ļ����Ľṹ��

//    intptr_t hFile;
//    hFile = _findfirst(buffer.c_str(), &c_file);   //�ҵ�һ���ļ���

//    if (hFile == -1L)   // ����ļ���Ŀ¼�´�����Ҫ���ҵ��ļ�
//        printf("No files in current directory!\n");
//    else
//    {
//        string fullFilePath;
//        do
//        {
//            fullFilePath.clear();

//            //����
//            fullFilePath = File_Directory + "\\" + c_file.name;
//            cout << fullFilePath << endl;
//            FilesName.push_back(fullFilePath);

//        } while (_findnext(hFile, &c_file) == 0);  //����ҵ��¸��ļ������ֳɹ��Ļ��ͷ���0,���򷵻�-1
//        _findclose(hFile);
//    }
//}




//void m_calibration(vector<string>& FilesName, Size board_size, Size square_size, Mat& cameraMatrix, Mat& distCoeffs, vector<Mat>& rvecsMat, vector<Mat>& tvecsMat)
//{
////	ofstream ffout("caliberation_result.txt");                       // ����궨������ļ�

//    cout << "start������������" << endl;
//    int image_count = 0;                                            // ͼ������
//    Size image_size;                                                // ͼ��ĳߴ�

//    vector<Point2f> image_points;                                   // ����ÿ��ͼ���ϼ�⵽�Ľǵ�
//    vector<vector<Point2f>> image_points_seq;                       // �����⵽�����нǵ�

//    for (int i = 0; i < FilesName.size(); i++)
//    {
//        image_count++;

//        // ���ڹ۲�������
//        cout << "image_count = " << image_count << endl;
//        Mat imageInput = imread(FilesName[i]);
//        if (image_count == 1)  //�����һ��ͼƬʱ��ȡͼ������Ϣ
//        {
//            image_size.width = imageInput.cols;
//            image_size.height = imageInput.rows;
//            cout << "image_size.width = " << image_size.width << endl;
//            cout << "image_size.height = " << image_size.height << endl;
//        }

//        /* ��ȡ�ǵ� */
//        bool ok = findChessboardCorners(imageInput, board_size, image_points, CALIB_CB_ADAPTIVE_THRESH | CALIB_CB_NORMALIZE_IMAGE);
//        if (0 == ok)
//        {
//            cout << "��" << image_count << "����Ƭ��ȡ�ǵ�ʧ�ܣ���ɾ�������±궨��" << endl; //�Ҳ����ǵ�
//            imshow("ʧ����Ƭ", imageInput);
//            waitKey(0);
//        }
//        else
//        {
//            Mat view_gray;
//            cout << "imageInput.channels()=" << imageInput.channels() << endl;
//            cvtColor(imageInput, view_gray, COLOR_BGR2GRAY);

//            /* �����ؾ�ȷ�� */
//            //find4QuadCornerSubpix(view_gray, image_points, Size(5, 5)); //�Դ���ȡ�Ľǵ���о�ȷ��
//            cv::cornerSubPix(view_gray, image_points, cv::Size(11, 11), cv::Size(-1, -1), cv::TermCriteria(TermCriteria::EPS+TermCriteria::COUNT, 20, 0.01));

//            image_points_seq.push_back(image_points);  //���������ؽǵ�

//            /* ��ͼ������ʾ�ǵ�λ�� */
//            drawChessboardCorners(view_gray, board_size, image_points, true);

//            imshow("Camera Calibration", view_gray);//��ʾͼƬ
//            waitKey(100);//��ͣ0.1S
//        }
//    }
//    cout << "�ǵ���ȡ��ɣ�����" << endl;


//    /*������ά��Ϣ*/
//    vector<vector<Point3f>> object_points_seq;                     // ����궨���Ͻǵ����ά����

//    for (int t = 0; t < image_count; t++)
//    {
//        vector<Point3f> object_points;
//        for (int i = 0; i < board_size.height; i++)
//        {
//            for (int j = 0; j < board_size.width; j++)
//            {
//                Point3f realPoint;
//                /* ����궨�������������ϵ��z=0��ƽ���� */
//                realPoint.x = i * square_size.width;
//                realPoint.y = j * square_size.height;
//                realPoint.z = 0;
//                object_points.push_back(realPoint);
//            }
//        }
//        object_points_seq.push_back(object_points);
//    }

//    /* ���б궨���� */
//    double err_first = calibrateCamera(object_points_seq, image_points_seq, image_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat, CALIB_FIX_K3);
//    cout << "��ͶӰ���1��" << err_first << "����" << endl << endl;
//    cout << "�궨��ɣ�����" << endl;


//    cout << "��ʼ���۱궨���������������";
//    double total_err = 0.0;            // ����ͼ���ƽ�������ܺ�
//    double err = 0.0;                  // ÿ��ͼ���ƽ�����
//    double totalErr = 0.0;
//    double totalPoints = 0.0;
//    vector<Point2f> image_points_pro;     // �������¼���õ���ͶӰ��

//    for (int i = 0; i < image_count; i++)
//    {

//        projectPoints(object_points_seq[i], rvecsMat[i], tvecsMat[i], cameraMatrix, distCoeffs, image_points_pro);   //ͨ���õ������������������Խǵ�Ŀռ���ά�����������ͶӰ����

//        err = norm(Mat(image_points_seq[i]), Mat(image_points_pro), NORM_L2);

//        totalErr += err * err;
//        totalPoints += object_points_seq[i].size();

//        err /= object_points_seq[i].size();
//        //fout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
//        total_err += err;
//    }
//    cout << "��ͶӰ���2��" << sqrt(totalErr / totalPoints) << "����" << endl << endl;
//    cout << "��ͶӰ���3��" << total_err / image_count << "����" << endl << endl;


//    //���涨����
//    cout << "��ʼ���涨����������������" << endl;
//    Mat rotation_matrix = Mat(3, 3, CV_32FC1, Scalar::all(0)); /* ����ÿ��ͼ�����ת���� */
//    cout << "����ڲ�������" << endl;
//    cout << cameraMatrix << endl << endl;
//    cout << "����ϵ����\n";
//    cout << distCoeffs << endl << endl << endl;
//    for (int i = 0; i < image_count; i++)
//    {
//        cout << "��" << i + 1 << "��ͼ�����ת������" << endl;
//        cout << rvecsMat[i] << endl;

//        /* ����ת����ת��Ϊ���Ӧ����ת���� */
//        Rodrigues(rvecsMat[i], rotation_matrix);
//        cout << "��" << i + 1 << "��ͼ�����ת����" << endl;
//        cout << rotation_matrix << endl;
//        cout << "��" << i + 1 << "��ͼ���ƽ��������" << endl;
//        cout << tvecsMat[i] << endl << endl;
//    }
//    cout << "��������ɱ��棡����" << endl;
//    cout << endl;
//}

//void m_undistort(vector<string>& FilesName, Size image_size, Mat& cameraMatrix, Mat& distCoeffs)
//{

//    Mat mapx = Mat(image_size, CV_32FC1);   //X ������ӳ�����
//    Mat mapy = Mat(image_size, CV_32FC1);   //Y ������ӳ�����
//    Mat R = Mat::eye(3, 3, CV_32F);
//    cout << "�������ͼ��" << endl;
//    string imageFileName;                  //У����ͼ��ı���·��
//    stringstream StrStm;
//    string temp;

//    for (int i = 0; i < FilesName.size(); i++)
//    {
//        Mat imageSource = imread(FilesName[i]);

//        Mat newimage = imageSource.clone();

//        //����һ��ʹ��initUndistortRectifyMap��remap�����������ʵ��
//        //initUndistortRectifyMap(cameraMatrix,distCoeffs,R, Mat(),image_size,CV_32FC1,mapx,mapy);
//        //	remap(imageSource,newimage,mapx, mapy, INTER_LINEAR);

//        //������������Ҫת������ķ�ʽ��ʹ��undistort����ʵ��
//        undistort(imageSource, newimage, cameraMatrix, distCoeffs);

//        StrStm << i + 1;
//        StrStm >> temp;
//        imageFileName = "������ͼ��//" + temp + "_d.jpg";
//        imwrite(imageFileName, newimage);

//        StrStm.clear();
//        imageFileName.clear();
//    }
//    std::cout << "�������" << endl;
//}

//int main()
//{
//    string File_Directory1 = "E:\\project\\DL\\OpenCV\\pic";   //�ļ���Ŀ¼1

//    string FileType = ".png";    // ��Ҫ���ҵ��ļ�����

//    //����ļ���������
//    //vector<string>FilesName1 = { "left01.jpg","left03.jpg" };
//    vector<string>FilesName1;
//    getFilesName(File_Directory1, FileType, FilesName1);   // �궨����ͼ���ļ���·��
//    //cout << FilesName1.size();

//    Size board_size = Size(8, 6);                         // �궨����ÿ�С��еĽǵ���
//    Size square_size = Size(25, 25);                       // ʵ�ʲ����õ��ı궨����ÿ�����̸������ߴ磬��λmm

//    Mat cameraMatrix = Mat(3, 3, CV_32FC1, Scalar::all(0));        // ������ڲ�������
//    Mat distCoeffs = Mat(1, 5, CV_32FC1, Scalar::all(0));          // �������5������ϵ����k1,k2,p1,p2,k3
//    vector<Mat> rvecsMat;                                          // �������ͼ�����ת������ÿһ��ͼ�����ת����Ϊһ��mat
//    vector<Mat> tvecsMat;                                          // �������ͼ���ƽ��������ÿһ��ͼ���ƽ������Ϊһ��mat

//    m_calibration(FilesName1, board_size, square_size, cameraMatrix, distCoeffs, rvecsMat, tvecsMat);

//    //m_undistort(FilesName1, image_size, cameraMatrix, distCoeffs);
//    waitKey(0);
//    return 0;
//}
