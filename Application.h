#pragma once

#include "Infra/Thread.h"
#include "GenICam/Frame.h"
#include "GenICam/StreamSource.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>  
#include <opencv2/highgui/highgui.hpp> 

#include <list>
#include <vector>
#include <mutex>

using namespace Dahua::GenICam;
using namespace Dahua::Infra;


class CApplication
{
public:
	CApplication(IStreamSourcePtr& streamSptr);
	~CApplication();

	struct ImageFrame
	{
		CFrame m_frame;
	};

	struct DivideFrame
	{
		std::vector<cv::Mat> m_divide;
	};


public:
	bool StartRun();
	bool CloseRun();

protected:
	static void retrieveProc(Dahua::Infra::CThreadLite& p);
	static void divideProc(Dahua::Infra::CThreadLite& p);
	static void detectProc(Dahua::Infra::CThreadLite& p);

	void retrieveProc();
	void divideProc();
	void detectProc();

protected:
	Dahua::Infra::CThreadLite* m_pRetrieveThread;
	Dahua::Infra::CThreadLite* m_pDivideThread;
	std::vector<Dahua::Infra::CThreadLite*> m_vDetectThreads;
	std::list<ImageFrame*> m_lImageFrames;
	std::list<DivideFrame*> m_lDivideFrames;
	std::map<int, DivideFrame*> m_mDivideFrames;
	std::mutex m_mImageLock;
	std::mutex m_mFrameLock;
	std::mutex m_mDivideLock;

	bool m_isRetrieveLoop;
	bool m_isDivideLoop;
	bool m_isDetectLoop;
	IStreamSourcePtr m_streamSptr;

	static CApplication *s_pAppliction;
};

