#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osgViewer/Viewer>
#include "Simulator.h"

int main(int argc, char* argv[])
{
	Simulator* simulator = new Simulator();
	simulator->createGroundNode();
	simulator->createCessnaNode();
	simulator->createTruckNode();
	simulator->loadViewer();
	return 0;
}