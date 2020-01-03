#define PCL_NO_PRECOMPILE
#include <pcl/pcl_macros.h>

#include<iostream>
#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/point_cloud.h>
#include<pcl/visualization/cloud_viewer.h>
#include "../include/quanergy/common/point_xyzir.h"
//#include "../include/quanergy/common/pointcloud_types.h"

// http://www.pointclouds.org/documentation/tutorials/adding_custom_ptype.php#adding-custom-ptype

struct MyPointType
{
	PCL_ADD_POINT4D;                  // preferred way of adding a XYZ+padding
	float intensity;
	uint16_t ring;
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW    // make sure our new allocators are aligned PCL_MAKE_ALIGNED_OPERATOR_NEW 
} EIGEN_ALIGN16;                    // enforce SSE padding for correct memory alignment

POINT_CLOUD_REGISTER_POINT_STRUCT(MyPointType,           // here we assume a XYZ + "test" (as fields)
(float, x, x)
(float, y, y)
(float, z, z)
(float, intensity, intensity)
(uint16_t, ring, ring)
)




int main(int argc, char *argv[])
{
	//pcl::PointCloud<pcl::PointXYZI>::Ptr  cloud(new pcl::PointCloud<pcl::PointXYZI>);//PCL自带的数据结构 PointXYZI
	
	
	pcl::PointCloud<MyPointType>::Ptr  cloud(new pcl::PointCloud<MyPointType>); //自定义格式
	//pcl::PointCloud<quanergy::PointXYZIR>::Ptr  cloud(new pcl::PointCloud<quanergy::PointXYZIR>); //quanergy头文件


	/* cloudView 显示自定义的数据结构
	boost::shared_ptr<pcl::PointCloud<MyPointType>> cloud;
	cloud = boost::make_shared <pcl::PointCloud<MyPointType>>(new pcl::PointCloud<MyPointType>);
	*/



	pcl::io::loadPCDFile<MyPointType>("./test_pcd.pcd", *cloud);

	if (pcl::io::loadPCDFile<MyPointType>("./test_pcd.pcd", *cloud) == -1)
	{
		std::cout << "Cloud reading failed." << std::endl;
		return (-1);
	}

	//std::cout << cloud->width << std::endl;
	//std::cout << cloud->height;

	for (std::size_t i = 0; i < cloud->points.size(); ++i)
		std::cout << "    " << cloud->points[i].x
		<< " " << cloud->points[i].y
		<< " " << cloud->points[i].z 
		<< " " << cloud->points[i].intensity
		<< " " << cloud->points[i].ring<< std::endl;

	/*
	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloud);
	while (!viewer.wasStopped())
	{
	}
	*/

	return (0);

}
