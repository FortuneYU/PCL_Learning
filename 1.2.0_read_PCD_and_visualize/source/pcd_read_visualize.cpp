#include<iostream>
#include<string>

// console parser
#include <pcl/console/parse.h>


#include<pcl/io/pcd_io.h>
#include<pcl/point_types.h>
#include<pcl/point_cloud.h>
#include<pcl/visualization/cloud_viewer.h>

using namespace std;


// output usage message
void usage(char** argv)
{
	std::cout << "usage: " << argv[0]
		<< " file_name.pcd " << std::endl << std::endl
		<< "-h, --help        show this help and exit" << std::endl << std::endl;

	return;
}



int main(int argc, char *argv[])
{
	int max_num_args = 2;
	// get host
	if (argc < 2 || argc > max_num_args || pcl::console::find_switch(argc, argv, "-h") ||
		pcl::console::find_switch(argc, argv, "--help"))
	{
		usage(argv);
		return (0);
	}

	string pcdFileName = argv[1];
	pcl::PointCloud<pcl::PointXYZRGB>::Ptr  cloud(new pcl::PointCloud<pcl::PointXYZRGB>);
	//pcl::io::loadPCDFile<pcl::PointXYZRGB>("../../example_pcd/test_pcd.pcd", *cloud);
	pcl::io::loadPCDFile<pcl::PointXYZRGB>(pcdFileName, *cloud);

	//if (pcl::io::loadPCDFile<pcl::PointXYZRGB>("../../example_pcd/test_pcd.pcd", *cloud) == -1)
	if (pcl::io::loadPCDFile<pcl::PointXYZRGB>(pcdFileName, *cloud) == -1)
	{
		std::cout << "Point cloud file  " <<argv[1]<<" reading failed. Please check your file name." << std::endl << std::endl;
		return (-1);
	}

	//std::cout << cloud->width << std::endl;
	//std::cout << cloud->height;

	for (std::size_t i = 0; i < cloud->points.size(); ++i)
		std::cout   << "    " << cloud->points[i].x
					<< " " << cloud->points[i].y
					<< " " << cloud->points[i].z
					<< " " << cloud->points[i].rgb << std::endl;




	pcl::visualization::CloudViewer viewer("Simple Cloud Viewer");
	viewer.showCloud(cloud);
	while (!viewer.wasStopped())
	{
	}
	system("pause");
	return (0);

}
