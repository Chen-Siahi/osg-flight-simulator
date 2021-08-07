#include <osg/AnimationPath>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgShadow/ShadowedScene>
#include <osgShadow/ShadowMap>
#include <osgViewer/Viewer>

class ModelController : public osgGA::GUIEventHandler
{
public:
	ModelController(osg::MatrixTransform* node)	: _model(node) {}
	virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
protected:
	osg::ref_ptr<osg::MatrixTransform> _model;
};
bool ModelController::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (!_model) return false;
	_sleep(10);
	osg::Matrix matrix = _model->getMatrix();
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::KEYDOWN:

		switch (ea.getKey())
		{
		//directions
		case 65361:
			matrix *= osg::Matrix::rotate(-0.1f, osg::Z_AXIS);
			break;
		case 65363:
			matrix *= osg::Matrix::rotate(0.1f, osg::Z_AXIS);
			break;
		case 65362:
			matrix *= osg::Matrix::rotate(-0.1f, osg::X_AXIS);
			break;
		case 65364:
			matrix *= osg::Matrix::rotate(0.1f, osg::X_AXIS);
			break;
		//airplane landing
		case 's': {
			matrix *= osg::Matrix::inverse(osg::Matrix::translate(osg::Vec3(-0.1f, 1.0f, 1.0f)));
		}
		default:
			break;
		}
		_model->setMatrix(matrix);
		break;
	default:
		break;
	}
	return false;
}
