#define NOMINMAX

//Podo
#include "Podo.h"
#include "Debug.h"

//Win32
#include <windows.h>

//C++
#include <stdexcept>

void Podo::FlushCommandQueue()
{
	if (m_fenceEvent == nullptr || m_fence == nullptr || m_commandQueue == nullptr)
	{
		return;
	}

	m_fenceCurrent++;

	ThrowIfFailed(m_commandQueue->Signal(m_fence.Get(), m_fenceCurrent));
	ThrowIfFailed(m_fence->SetEventOnCompletion(m_fenceCurrent, m_fenceEvent));

	auto waitResult = WaitForSingleObject(m_fenceEvent, INFINITE);
	if (waitResult != WAIT_OBJECT_0)
	{
		throw std::runtime_error("wait fence failed");
	}
}

void Podo::SaveWindow()
{
	if (m_optionFullScreen.IsActive() == false)
	{
		RECT windowRect = {};
		ThrowIfFalse(GetWindowRect(m_hWnd, &windowRect));
		m_optionWindowSave.SetWindowRect(windowRect);
	}
}