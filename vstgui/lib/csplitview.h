//-----------------------------------------------------------------------------
// VST Plug-Ins SDK
// VSTGUI: Graphical User Interface Framework not only for VST plugins : 
//
// Version 4.0
//
//-----------------------------------------------------------------------------
// VSTGUI LICENSE
// (c) 2010, Steinberg Media Technologies, All Rights Reserved
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

#ifndef __csplitview__
#define __csplitview__

#include "cviewcontainer.h"

namespace VSTGUI {

class CBitmap;
class ISplitViewSeparatorDrawer;
class CSplitViewSeparatorView;

//-----------------------------------------------------------------------------
/** TODO: Doc  
*/
//-----------------------------------------------------------------------------
class CSplitView : public CViewContainer
{
public:
	enum Style {
		kHorizontal,
		kVertical
	};

	enum ResizeMethod {
		kResizeFirstView,
		kResizeLastView,
		kResizeAllViews,
	};
	
	CSplitView (const CRect& size, Style style = kHorizontal, CCoord separatorWidth = 10., ISplitViewSeparatorDrawer* drawer = 0);
	~CSplitView ();

	virtual void setStyle (Style s);
	Style getStyle () const { return style; }

	virtual void setResizeMethod (ResizeMethod method);
	ResizeMethod getResizeMethod () const { return resizeMethod; }

	virtual void setSeparatorWidth (CCoord width);
	CCoord getSeparatorWidth () const { return separatorWidth; }
	
	// overrides
	virtual bool addView (CView* pView);
	virtual bool addView (CView* pView, const CRect& mouseableArea, bool mouseEnabled = true);
	virtual bool addView (CView* pView, CView* pBefore);
	virtual bool removeView (CView* pView, bool withForget = true);
	virtual bool removeAll (bool withForget = true);
	virtual void setViewSize (const CRect& rect, bool invalid = true);
	virtual bool sizeToFit ();
	virtual bool removed (CView* parent);
	virtual bool attached (CView* parent);

	bool requestNewSeparatorSize (CSplitViewSeparatorView* separatorView, const CRect& newSize);
	void onSeparatorDoubleClick (CSplitViewSeparatorView* separatorView);
//-----------------------------------------------------------------------------
protected:
	void resizeFirstView (CPoint diff);
	void resizeLastView (CPoint diff);
	void resizeViewsEqual (CPoint diff);

	Style style;
	ResizeMethod resizeMethod;
	CCoord separatorWidth;
	ISplitViewSeparatorDrawer* separatorDrawer;
};

//-----------------------------------------------------------------------------
/** Extension to IController 
	TODO: Doc
*/
//-----------------------------------------------------------------------------
class ISplitViewController
{
public:
	/** TODO: Doc 
	*/
	virtual bool getSplitViewSizeConstraint (int32_t index, CCoord& minWidth, CCoord& maxWidth, CSplitView* splitView) = 0;
	/** TODO: Doc 
	*/
	virtual ISplitViewSeparatorDrawer* getSplitViewSeparatorDrawer () = 0;
	/** TODO: Doc 
	*/
	virtual bool storeViewSize (int32_t index, const CCoord& size, CSplitView* splitView) = 0;
	/** TODO: Doc 
	*/
	virtual bool restoreViewSize (int32_t index, CCoord& size, CSplitView* splitView) = 0;
};

//-----------------------------------------------------------------------------
/** TODO: Doc 
*/
//-----------------------------------------------------------------------------
class ISplitViewSeparatorDrawer
{
public:
	enum Flags {
		kMouseOver = 1 << 0,
	};
	/** TODO: Doc 
	*/
	virtual void drawSplitViewSeparator (CDrawContext* context, const CRect& size, int32_t flags, CSplitView* splitView) = 0;
};

}

#endif // __csplitview__