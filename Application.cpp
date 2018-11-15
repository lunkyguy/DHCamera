#include "Application.h"

CApplication *CApplication::s_pAppliction;
CApplication::CApplication(IStreamSourcePtr& streamSptr)
	: m_streamSptr(streamSptr)
{
	s_pAppliction = this;
	m_pRetrieveThread = new Dahua::Infra::CThreadLite(retrieveProc, "Retrieve");
	m_pDivideThread = new Dahua::Infra::CThreadLite(divideProc, "Divide");
	for (int i = 0; i < 8; i++)
		m_vDetectThreads.push_back(new Dahua::Infra::CThreadLite(detectProc, "Detect"));
}

CApplication::~CApplication()
{
	if (m_pRetrieveThread)
		delete m_pRetrieveThread;
	if (m_pDivideThread)
		delete m_pDivideThread;
	std::vector<Dahua::Infra::CThreadLite*>::iterator i;
	for (i = m_vDetectThreads.begin(); i != m_vDetectThreads.end(); i++)
		delete (*i);
}

bool CApplication::StartRun()
{
	m_isRetrieveLoop = true;
	m_isDivideLoop = true;
	m_isDetectLoop = true;
	m_pRetrieveThread->createThread();
	m_pDivideThread->createThread();
	std::vector<Dahua::Infra::CThreadLite*>::iterator i;
	for (i = m_vDetectThreads.begin(); i != m_vDetectThreads.end(); i++)
		(*i)->createThread();
	return 0;
}

bool CApplication::CloseRun()
{
	m_isRetrieveLoop = false;
	m_isDivideLoop = false;
	m_isDetectLoop = false;
	m_pRetrieveThread->destroyThread();
	m_pDivideThread->destroyThread();
	std::vector<Dahua::Infra::CThreadLite*>::iterator i;
	for (i = m_vDetectThreads.begin(); i != m_vDetectThreads.end(); i++)
		(*i)->destroyThread();
	return 0;
}

void CApplication::retrieveProc(Dahua::Infra::CThreadLite& p)
{
	s_pAppliction->retrieveProc();
}

void CApplication::divideProc(Dahua::Infra::CThreadLite& p)
{
	s_pAppliction->divideProc();
}

void CApplication::detectProc(Dahua::Infra::CThreadLite& p)
{
	s_pAppliction->detectProc();
}

void CApplication::retrieveProc()
{
	while (m_isRetrieveLoop)
	{
		//获取一帧
		if (!m_streamSptr)
		{
			printf("m_streamPtr is NULL.\n");
			return;
		}
		
#if 1
		ImageFrame *frame = new ImageFrame();
		bool isSuccess = m_streamSptr->getFrame(frame->m_frame, 100);
		
		printf("get Frame  %d.\n", frame->m_frame.getBlockId());

		if (!isSuccess)
		{
			printf("get Frame  fail.\n");
			delete frame;
			continue;
		}

		//判断帧的有效性
		bool isValid = frame->m_frame.valid();
		if (!isValid)
		{
			printf("frame is invalid!\n");
			delete frame;
			continue;
		}
#else
		CFrame frameBuf;
		m_streamSptr->getFrame(frameBuf, 100);
		if (!frameBuf.valid())
		{
			continue;
		}
		printf("get Frame  %d.\n", frameBuf.getBlockId());
#endif
		//m_mImageLock.lock();
		//m_lImageFrames.push_back(frame);
		static cv::Mat img = cv::Mat::zeros(cv::Size(frame->m_frame.getImageWidth(), frame->m_frame.getImageHeight()), CV_8UC1);
		memcpy(img.data, (uchar*)frame->m_frame.getImage(), frame->m_frame.getImageWidth()*frame->m_frame.getImageHeight());
		//frame->m_frame.clone();
		//m_mImageLock.unlock();
		delete frame;
	}
}

void CApplication::divideProc()
{
	while (m_isDivideLoop)
	{
		ImageFrame *pImageFrame = 0;
		m_mImageLock.lock();
		if (!m_lImageFrames.empty())
		{
			pImageFrame = m_lImageFrames.front();
			m_lImageFrames.pop_front();
		}		
		m_mImageLock.unlock();

		if (pImageFrame == 0)
		{
			CThread::sleep(100);
			continue;
		}

		DivideFrame *frame = new DivideFrame();
		
		m_mFrameLock.lock();
		m_lDivideFrames.push_back(frame);
		m_mFrameLock.unlock();
	}
}

void CApplication::detectProc()
{
	while (m_isDetectLoop)
	{
		DivideFrame *pDivideFrame = 0;
		m_mFrameLock.lock();
		if (!m_lDivideFrames.empty())
		{
			pDivideFrame = m_lDivideFrames.front();
			m_lDivideFrames.pop_front();
		}
		m_mFrameLock.unlock();

		if (pDivideFrame == 0)
		{
			CThread::sleep(100);
			continue;
		}
	}
}