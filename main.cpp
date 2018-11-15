/************************************************************************/
/* ��DemoΪ����ʾSDK��ʹ�ã�û�и����޸����IP�Ĵ��룬������֮ǰ��
   ��ʹ������ͻ����޸����IP��ַ������������������һ��                 */
/************************************************************************/

#include <GenICam/System.h>
#include <GenICam/Camera.h>
#include <GenICam/GigE/GigECamera.h>
#include <GenICam/GigE/GigEInterface.h>
#include <Infra/PrintLog.h>
#include <Memory/SharedPtr.h>
#include "Application.h"

using namespace Dahua::GenICam;
using namespace Dahua::Infra;

#ifdef _WIN64
#pragma comment(lib,"x64/MVSDKmd.lib")
#else
#pragma comment(lib,"win32/MVSDKmd.lib")
#endif // _WIN32

static void displayCameralInfor(ICameraPtr& cameraSptr)
{
	IGigECameraPtr gigeCameraPtr = IGigECamera::getInstance(cameraSptr);
	if(NULL == gigeCameraPtr)
	{
		return;
	}
	//��ȡGige��������Ϣ
	CString ip = gigeCameraPtr->getIpAddress();
	CString subnetMask = gigeCameraPtr->getSubnetMask();
	CString gateway = gigeCameraPtr->getGateway();
	CString macAddress = gigeCameraPtr->getMacAddress();
	printf("ip address is %s.\r\n", ip.c_str());
	printf("subnetMask is %s.\r\n", subnetMask.c_str());
	printf("gateway is %s.\r\n", gateway.c_str());
	printf("macAddress is %s.\r\n", macAddress.c_str());
	printf("\n");


	//��ȡ��Ӧ�ӿڵ�������Ϣ
	IGigEInterfacePtr gigeInterfaceSPtr = IGigEInterface::getInstance(cameraSptr);
	if(NULL == gigeInterfaceSPtr)
	{
		return;
	}

	CString interfaceIp = gigeInterfaceSPtr->getIpAddress();
	CString interfaceSubnetMask = gigeInterfaceSPtr->getSubnetMask();
	CString interfaceGateway = gigeInterfaceSPtr->getGateway();
	CString interfaceMacAddress = gigeInterfaceSPtr->getMacAddress();
	printf("ip address of interface  is %s.\r\n", interfaceIp.c_str());
	printf("subnetMask of interface is %s.\r\n", interfaceSubnetMask.c_str());
	printf("gateway of interface is %s.\r\n", interfaceGateway.c_str());
	printf("macAddress of interface is %s.\r\n", interfaceMacAddress.c_str());
	printf("\n");
}

static void modifyCamralExposureTime(CSystem &systemObj, ICameraPtr& cameraSptr)
{
	IAcquisitionControlPtr sptrAcquisitionControl = systemObj.createAcquisitionControl(cameraSptr);
	if (NULL == sptrAcquisitionControl)
	{
		return;
	}

	double exposureTimeValue = 0.0;
	CDoubleNode exposureTime = sptrAcquisitionControl->exposureTime();

	exposureTime.getValue(exposureTimeValue);
	printf("before change ,exposureTime is %f. thread ID :%d\n", exposureTimeValue, CThread::getCurrentThreadID());

	exposureTime.setValue(exposureTimeValue + 2);
	exposureTime.getValue(exposureTimeValue);
	printf("after change ,exposureTime is %f. thread ID :%d\n", exposureTimeValue, CThread::getCurrentThreadID());
}

//static bool setSoftTriggerConf(IAcquisitionControlPtr sptrAcquisitionCtl)
//{
//	//CDoubleNode enIntNode = sptrAcquisitionCtl->exposureTime();
//
//	//���ô���ԴΪ����
//	CEnumNode enumNode = sptrAcquisitionCtl->triggerSource();
//	bool bRet = enumNode.setValueBySymbol("Software");
//	if (bRet != true)
//	{
//		printf("set trigger source failed.\n");
//		return false;
//	}
//
//	//���ô�����
//	enumNode = sptrAcquisitionCtl->triggerSelector();
//	bRet = enumNode.setValueBySymbol("FrameStart");
//	if (bRet != true)
//	{
//		printf("set trigger selector failed.\n");
//		return false;
//	}
//
//	//���ô���ģʽ
//	enumNode = sptrAcquisitionCtl->triggerMode();
//	bRet = enumNode.setValueBySymbol("On");
//	if (bRet != true)
//	{
//		printf("set trigger mode failed.\n");
//		return false;
//	}
//	return true;
//}
//IAcquisitionControlPtr sptrAcquisitionControl;
//bool bRet;

void main()
{
	ICameraPtr cameraSptr;
	//�����豸
	CSystem &systemObj = CSystem::getInstance();
	TVector<ICameraPtr> vCameraPtrList;
	bool isDiscoverySuccess = systemObj.discovery(vCameraPtrList);
	if (!isDiscoverySuccess)
	{
		printf("discovery device fail.\n");
		return;
	}
	// print camera info (key, vendor name, model, serial number)
	// ��ӡ���������Ϣ��key, ��������Ϣ, �ͺ�, ���кţ�
	for (int i = 0; i < vCameraPtrList.size(); i++)
	{
		cameraSptr = vCameraPtrList[i];

		printf("Camera[%d] Info :\n", i);
		printf("    key           = [%s]\n", cameraSptr->getKey());
		printf("    vendor name   = [%s]\n", cameraSptr->getVendorName());
		printf("    model         = [%s]\n", cameraSptr->getModelName());
		printf("    serial number = [%s]\n", cameraSptr->getSerialNumber());
	}

	cameraSptr = vCameraPtrList[0];
	displayCameralInfor(cameraSptr);

	//�����豸
	if (!vCameraPtrList[0]->connect())
	{
		printf("connect cameral failed.\n");
		return;
	}

	//����AcquisitionControl����
	IAcquisitionControlPtr sptrAcquisitionControl = systemObj.createAcquisitionControl(cameraSptr);
	if (NULL == sptrAcquisitionControl)
	{
		printf("create AcquisitionControl object fail.\n");
		//ʵ��Ӧ����Ӧ��ʱ�ͷ������Դ����diconnect����ȣ�����ֱ��return
		return;
	}

	//����������
	IStreamSourcePtr streamPtr = systemObj.createStreamSource(cameraSptr);
	if (NULL == streamPtr)
	{
		printf("create stream obj  fail.\r\n");
		return;
	}

	bool isStartGrabbingSuccess = streamPtr->startGrabbing();
	if (!isStartGrabbingSuccess)
	{
		printf("StartGrabbing  fail.\n");
	}

	//CCmdNode cmdNode = sptrAcquisitionControl->triggerSoftware();
	//bRet = cmdNode.execute();

	//����
	Dahua::Memory::TSharedPtr<CApplication> streamThreadSptr(new CApplication(streamPtr));
	if(NULL == streamThreadSptr)
	{
		printf("create thread obj failed.\n");
		return;
	}	
	//streamThreadSptr->start();
	
	HANDLE hThread = GetCurrentThread();
	
	//CApplication app(streamPtr);
	//app.StartRun();
	streamThreadSptr->StartRun();
	//�������߳�
	SuspendThread(hThread);
	//getchar();
	streamThreadSptr->CloseRun();
	//app.CloseRun();
	//ֹͣ�����߳�
	//streamThreadSptr->stop();

	//ֹͣ�������
	streamPtr->stopGrabbing();

	//�޸�����ع�ʱ��
	modifyCamralExposureTime(systemObj, cameraSptr);
	
	//�Ͽ��豸
	if (!cameraSptr->disConnect())
	{
		printf("disConnect cameral failed\n");
		return;
	}
	printf("disConnect successfully thread ID :%d\n", CThread::getCurrentThreadID());

	
}