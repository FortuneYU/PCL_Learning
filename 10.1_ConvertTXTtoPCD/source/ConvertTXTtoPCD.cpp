//原文链接：https://blog.csdn.net/qq_42570058/article/details/82989794
// Convert TXT to PCD


#include<iostream>
 
#include<fstream>
#include<vector>
#include<string>
#include<pcl\io\pcd_io.h>
#include<pcl\point_types.h>
using namespace std;
 
int main()
{
	//定义一种类型表示TXT中xyz
	typedef struct TXT_Point_XYZRGB
	{
		double x;
		double y;
		double z;
		double rgb;
	}TOPOINT_XYZRGB;

	//读取txt文件
	int num_txt;
	FILE *fp_txt;
	TXT_Point_XYZRGB txt_points;
	vector<TXT_Point_XYZRGB> my_vTxtPoints;
	fp_txt = fopen("test_pcd.txt", "r");

	if (fp_txt)
	{
		while (fscanf(fp_txt, "%lf %lf %lf %lf", &txt_points.x, &txt_points.y, &txt_points.z, &txt_points.rgb) != EOF)
		{//将点存入容器尾部
			my_vTxtPoints.push_back(txt_points);
		}
	}
	else
		cout << "读取txt文件失败" << endl;

	num_txt = my_vTxtPoints.size();

	for (int i = 0; i < my_vTxtPoints.size(); ++i)
	{
		cout << "    " << my_vTxtPoints[i].x
			<< " " << my_vTxtPoints[i].y
			<< " " << my_vTxtPoints[i].z
			<< " " << my_vTxtPoints[i].rgb << endl;
	}

	

	//写入点云数据
	pcl::PointCloud<pcl::PointXYZRGB> ::Ptr cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	cloud->width = num_txt;
	cloud->height = 1;
	cloud->is_dense = false;
	cloud->points.resize(cloud->width*cloud->height);
	for (int i = 0; i < cloud->points.size(); ++i)
	{
		cloud->points[i].x = my_vTxtPoints[i].x;
		cloud->points[i].y = my_vTxtPoints[i].y;
		cloud->points[i].z = my_vTxtPoints[i].z;
		cloud->points[i].rgb = my_vTxtPoints[i].rgb;
	}
	pcl::io::savePCDFileASCII("test_pcd.pcd", *cloud);
	cout << "从 txt_pcd.txt读取" << cloud->points.size() << "点写入txt_pcd.pcd" << endl;

	//打印出写入的点
	cout << "_________________________________" << endl;
	for (size_t i = 0; i < cloud->points.size(); ++i)
		cout << "    " << cloud->points[i].x
		<< " " << cloud->points[i].y
		<< " " << cloud->points[i].z
		<< " " << cloud->points[i].rgb << endl;

	return 0;

}
