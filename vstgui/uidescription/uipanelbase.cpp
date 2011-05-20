//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework not only for VST plugins : 
//
// Version 4.0
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2011, Steinberg Media Technologies, All Rights Reserved
//-----------------------------------------------------------------------------
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
//   * Redistributions of source code must retain the above copyright notice, 
//     this list of conditions and the following disclaimer.
//   * Redistributions in binary form must reproduce the above copyright notice,
//     this list of conditions and the following disclaimer in the documentation 
//     and/or other materials provided with the distribution.
//   * Neither the name of the Steinberg Media Technologies nor the names of its
//     contributors may be used to endorse or promote products derived from this 
//     software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A  PARTICULAR PURPOSE ARE DISCLAIMED. 
// IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
// LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
// OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  OF THIS SOFTWARE, EVEN IF ADVISED
// OF THE POSSIBILITY OF SUCH DAMAGE.
//-----------------------------------------------------------------------------

#include "uipanelbase.h"

#if VSTGUI_LIVE_EDITING

namespace VSTGUI {

//-----------------------------------------------------------------------------
IdStringPtr UIPanelBase::kMsgWindowClosed = "kMsgWindowClosed";

//-----------------------------------------------------------------------------
UIPanelBase::UIPanelBase (CBaseObject* owner, void* parentPlatformWindow)
: platformWindow (0)
, owner (owner)
, parentPlatformWindow (parentPlatformWindow)
{
}

//-----------------------------------------------------------------------------
UIPanelBase::~UIPanelBase ()
{
	owner = 0;
	if (frame)
		frame->close ();
	windowClosed (platformWindow);
}

//-----------------------------------------------------------------------------
bool UIPanelBase::init (const CRect& initialSize, UTF8StringPtr title, int32_t windowStyle)
{
	platformWindow = PlatformWindow::create (initialSize, title, PlatformWindow::kPanelType, windowStyle, this);
	if (platformWindow)
	{
		#if MAC_CARBON && MAC_COCOA
		CFrame::setCocoaMode (true);
		#endif
		frame = createFrame (platformWindow->getPlatformHandle (), initialSize.getWidth (), initialSize.getHeight ());
		CRect r (frame->getViewSize ());
		r.offset (initialSize.left, initialSize.top);
		platformWindow->setSize (r);
		return true;
	}
	return false;
}

// IPlatformWindowDelegate
//-----------------------------------------------------------------------------
void UIPanelBase::windowSizeChanged (const CRect& newSize, PlatformWindow* platformWindow)
{
	frame->setSize (newSize.getWidth (), newSize.getHeight ());
}

//-----------------------------------------------------------------------------
void UIPanelBase::windowClosed (PlatformWindow* _platformWindow)
{
	if (platformWindow && _platformWindow == platformWindow)
	{
		platformWindow->forget ();
		platformWindow = 0;
	}
	if (owner)
		owner->notify (this, kMsgWindowClosed);
	if (getNbReference () >= 1)
		forget ();
}

//-----------------------------------------------------------------------------
void UIPanelBase::checkWindowSizeConstraints (CPoint& size, PlatformWindow* platformWindow)
{
}

} // namespace

#endif // VSTGUI_LIVE_EDITING