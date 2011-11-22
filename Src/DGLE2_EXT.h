#ifndef _DGLE2_EXT
#define _DGLE2_EXT
#include "DGLE2.h"
#include "DGLE2_helpers.h"

namespace DGLE2
{
	class ISpriteEngine;
	class IGUIEngine;
	// {6F1E8EA6-55BD-4668-936D-294913576D76}
	static const GUID IID_IExtensionPlugin = 
	{ 0x6f1e8ea6, 0x55bd, 0x4668, { 0x93, 0x6d, 0x29, 0x49, 0x13, 0x57, 0x6d, 0x76 } };

	class IExtensionPlugin : public IPlugin
	{
	public:
		virtual HRESULT CALLBACK GetSpriteEngine(ISpriteEngine *&pSpriteEngine) = 0;
		virtual HRESULT CALLBACK GetGuiEngine(IGUIEngine *&pGuiEngine) = 0;
	};

	// ParticleEffect interface//

	// {1556CB3D-44F9-4f3a-BF1C-D6E5709B42E7}
	static const GUID IID_IParticleEmitter = 
	{ 0x1556cb3d, 0x44f9, 0x4f3a, { 0xbf, 0x1c, 0xd6, 0xe5, 0x70, 0x9b, 0x42, 0xe7 } };

	class IParticleEmitter : public IDGLE2_Base
	{  
	public:
		virtual HRESULT CALLBACK SetPosition(const TPoint3 &stPos, bool bMoveOldParticls = false) = 0;
		virtual HRESULT CALLBACK SetScale(float fScale)= 0;
		virtual HRESULT CALLBACK GetPosition(TPoint3 &stPos) = 0;
		virtual HRESULT CALLBACK GetScale(float &fScale) = 0; 
		virtual HRESULT CALLBACK Reset() = 0;
	};

	// {BA42B3E6-E79A-4b1a-B674-3E18F6DEB58D}
	static const GUID IID_IParticleEffect = 
	{ 0xba42b3e6, 0xe79a, 0x4b1a, { 0xb6, 0x74, 0x3e, 0x18, 0xf6, 0xde, 0xb5, 0x8d } };

	class IParticleEffect: public IEngBaseObj
	{  
	public:
		virtual HRESULT CALLBACK CreateEmitter(IParticleEmitter *&prPEmitter, bool bDeleteIfInactive = true) = 0;
		virtual HRESULT CALLBACK Is3D(bool &b3D) = 0;
		virtual HRESULT CALLBACK Draw2D() = 0;
		virtual HRESULT CALLBACK Draw3D() = 0;
		virtual HRESULT CALLBACK KillEmitter(IParticleEmitter *pPEmitter) = 0;
		virtual HRESULT CALLBACK KillAllEmitters() = 0;
		virtual HRESULT CALLBACK EmitterExist(IParticleEmitter *pPEmitter, bool &bExists) = 0;
	};

	//Sprite interface//
	class ISpriteCallback;
	// {9D487BD4-D8BC-4870-9726-090E72E07282}
	static const GUID IID_ISprite = 
	{ 0x9d487bd4, 0xd8bc, 0x4870, { 0x97, 0x26, 0x9, 0xe, 0x72, 0xe0, 0x72, 0x82 } };
	class ISprite:public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK  RegistCallback(ISpriteCallback *pMetods) = 0;

		virtual HRESULT CALLBACK  AddSprite(ISprite *pSprite) = 0;
		virtual HRESULT CALLBACK  GetSprite(const char* strName, ISprite *&prSprite) = 0;
		virtual HRESULT CALLBACK  RemoveSprite(ISprite *pSprite) = 0;
		virtual HRESULT CALLBACK  RemoveAllSprite() = 0;
		virtual HRESULT CALLBACK  Draw() = 0;
		
		virtual HRESULT CALLBACK  AnimationReset() = 0;
		virtual HRESULT CALLBACK  SetAnimationFromName(const char* strAnimationName, bool bFlipX = false, bool bFlipY = false, float fAngle = 0.f) = 0;
		virtual HRESULT CALLBACK  SetAnimationFromIndex(uint uiIndex, bool bFlipX = false, bool bFlipY = false, float fAngle = 0.f) = 0;
		virtual HRESULT CALLBACK  SetPixelCheck(bool bPixelCheck) = 0;
		virtual HRESULT CALLBACK  SetCollision(bool bCollision) = 0;
		virtual HRESULT CALLBACK  SetVisible(bool bVisible) = 0;
		virtual HRESULT CALLBACK  SetPosition(TPoint2 pointPosition) = 0;
		virtual HRESULT CALLBACK  SetDimensions(TPoint2 pointDimension) = 0;
		virtual HRESULT CALLBACK  SetCollisionRect(TRectF rectCollisionRect) = 0;
		virtual HRESULT CALLBACK  SetZ(int iZ) = 0;
		virtual HRESULT CALLBACK  SetDead(bool bDead) = 0;
		virtual HRESULT CALLBACK  SetBlend(E_EFFECT2D_BLENDING_FLAGS eBlend) = 0;

		virtual HRESULT CALLBACK  GetName(char *pcTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK  GetPixelCheck(bool &rbPixelChaeck) = 0;
		virtual HRESULT CALLBACK  GetCollision(bool &rbCollision) = 0;
		virtual HRESULT CALLBACK  GetVisible(bool &rbVisible) = 0;
		virtual HRESULT CALLBACK  GetMoved(bool &rbMoved) = 0;
		virtual HRESULT CALLBACK  GetPosition(TPoint2 &stPosition) = 0;
		virtual HRESULT CALLBACK  GetDimensions(TPoint2 &stDimension) = 0;
		virtual HRESULT CALLBACK  GetCollisionRect(TRectF &stCoollisionRect) = 0;
		virtual HRESULT CALLBACK  GetZ(int &iZ) = 0;
		virtual HRESULT CALLBACK  IsDead(bool &rbDead) = 0;
		virtual HRESULT CALLBACK  IsAnimationEnded(bool &rbIsAnimated) = 0;
		virtual HRESULT CALLBACK  CurrentAnimation(char *pcTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK  IsCollision(bool &bCollision) = 0;
		virtual HRESULT CALLBACK  GetAnimationsCount(int &iCount) = 0;
		virtual HRESULT CALLBACK  GetAnimationName(char *pcTxt, uint uiCharsCount) = 0;
	};

	class ISpriteCallback
	{
	public:
		virtual HRESULT CALLBACK Draw(ISprite *pSelf) = 0;
		virtual HRESULT CALLBACK Move(ISprite *pSelf) = 0;
		virtual HRESULT CALLBACK Collision(ISprite *pSprite, ISprite *pSelf) = 0;
	};

	// {510F544D-3915-44ed-9F9C-948C28610836}
	static const GUID IID_ISpriteEngine = 
	{ 0x510f544d, 0x3915, 0x44ed, { 0x9f, 0x9c, 0x94, 0x8c, 0x28, 0x61, 0x8, 0x36 } };

	class ISpriteEngine: public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK Draw() = 0;
		virtual HRESULT CALLBACK AddSprite(ISprite *pSprite) = 0;
		virtual HRESULT CALLBACK RemoveSprite(ISprite *pSprite) = 0;
		virtual HRESULT CALLBACK RemoveAllSprites() = 0;
	};


	enum E_GUI_COMPONENT_EVENT
	{
		GCE_ON_CLICK = 0,
		GCE_ON_CHANGE,
		GCE_ON_DRAGGED,
		GCE_ON_DROPPED,
		GCE_ON_MOUSE_MOVE,
		GCE_ON_MOUSE_ENTERED,
		GCE_ON_MOUSE_EXITED,
		GCE_ON_MOUSE_PRESSED,
		GCE_ON_MOUSE_RELEASED,
		GCE_ON_MOUSE_WHEEL,
		GCE_ON_KEY_PRESSED,
		GCE_ON_KEY_DOWN,
		GCE_ON_KEY_RELEASED,
		GCE_ON_STYLE_CHANGED
	};

	enum E_TEXT_ALIGN
	{
		TA_LEFT_TOP = 0,
		TA_RIGHT_TOP,
		TA_CENTER_TOP,
		TA_LEFT_MIDDLE,
		TA_RIGHT_MIDDLE,
		TA_CENTER_MIDDLE,
		TA_LEFT_DOWN,
		TA_RIGHT_DOWN,
		TA_CENTER_DOWN,
	};
	
	class IDCStyleProvider;
	
	// {1CC1E3C7-54BD-488a-AC84-DA8FE2D51B93}
	static const GUID IID_IDCComponent = 
	{ 0x1cc1e3c7, 0x54bd, 0x488a, { 0xac, 0x84, 0xda, 0x8f, 0xe2, 0xd5, 0x1b, 0x93 } };
	
	class IDCComponent:public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK  AddEventListner(E_GUI_COMPONENT_EVENT eEvent, void (CALLBACK *pProc)(void *pSelf, void *pParametr)) = 0;
		virtual HRESULT CALLBACK  GetComponent(const char *pcName, IDCComponent *&prDCComponent) = 0;

		virtual HRESULT CALLBACK  SetVisible(bool bVisible) = 0;
		virtual HRESULT CALLBACK  SetPosition(TPoint2 pointPosition) = 0;
		virtual HRESULT CALLBACK  SetDimension(TPoint2 pointDimension) = 0;
		virtual HRESULT CALLBACK  SetEnabledColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK  SetZ(int iZ) = 0;
		virtual HRESULT CALLBACK  SetEnabled(bool bEnabled) = 0;
		virtual HRESULT CALLBACK  SetStyleProvider(IDCStyleProvider *styleProvider) = 0;
		virtual HRESULT CALLBACK  GetStyleProvider(IDCStyleProvider *&styleProvider) = 0;

		virtual HRESULT CALLBACK  GetName(char *pcTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK  GetVisible(bool &bVisible) = 0;
		virtual HRESULT CALLBACK  GetPosition(TPoint2 &stPosition) = 0;
		virtual HRESULT CALLBACK  GetDimension(TPoint2 &stDimension) = 0;
		virtual HRESULT CALLBACK  GetZ(int &iZ) = 0;
		virtual HRESULT CALLBACK  GetEnabled(bool &bEnabled) = 0;
		virtual HRESULT CALLBACK  GetActive(bool &bActive) = 0;
	};

	class IDCForm;

	// {DF475D2D-F370-4b01-A744-413FB6F030FA}
	static const GUID IID_IGUIForms = 
	{ 0xdf475d2d, 0xf370, 0x4b01, { 0xa7, 0x44, 0x41, 0x3f, 0xb6, 0xf0, 0x30, 0xfa } };

	class IGUIForms: public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK SetFormStyles() = 0;
		virtual HRESULT CALLBACK GetStyleFromName(const char *pcName, IDCStyleProvider *&prStyle) = 0;
		virtual HRESULT CALLBACK GetFormFromName(const char *pcName, IDCForm *&prForm) = 0;
		virtual HRESULT CALLBACK GetFormFromIndex(uint uiIndex, IDCForm *&prForm) = 0;
		virtual HRESULT CALLBACK GetFormsCount(int &iCount) = 0;
	};

	// {F8D4701B-DAB2-467f-9F4B-0354B2F38694}
	static const GUID IID_IGUIEngine = 
	{ 0xf8d4701b, 0xdab2, 0x467f, { 0x9f, 0x4b, 0x3, 0x54, 0xb2, 0xf3, 0x86, 0x94 } };

	class IGUIEngine: public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK Draw() = 0;
		virtual HRESULT CALLBACK AddForm(IDCForm *pForm, bool bDrag = true) = 0;
		virtual HRESULT CALLBACK RemoveForm(IDCComponent *pForm) = 0;
	};

	// {0C130B94-E387-4709-980B-092DC4C7F4E6}
	static const GUID IID_IDCTextComponent = 
	{ 0xc130b94, 0xe387, 0x4709, { 0x98, 0xb, 0x9, 0x2d, 0xc4, 0xc7, 0xf4, 0xe6 } };

	class IDCTextComponent: public IDCComponent
	{
	public:
		virtual HRESULT CALLBACK SetCaption(const char *pcName) = 0;
		virtual HRESULT CALLBACK SetCaptionVisible(bool bCaptionVisible) = 0;
		virtual HRESULT CALLBACK UseVerticesColors(bool bVerticesColors) = 0;
		virtual HRESULT CALLBACK SetVerticesColors(const TColor4 &stColor1, const TColor4 &stColor2, const TColor4 &stColor3 = TColor4(), const TColor4 &stColor4 = TColor4()) = 0;
		virtual HRESULT CALLBACK SetTextColor(const TColor4 &rtTextcolor) = 0;
		virtual HRESULT CALLBACK SetTextAlign(E_TEXT_ALIGN eTextAlign) = 0;
		virtual HRESULT CALLBACK SetTextSize(float fSize) = 0;

		virtual HRESULT CALLBACK GetCaption(char *pcTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetCaptionVisible(bool &bCaptionVisible) = 0;
		virtual HRESULT CALLBACK GetVerticesColorsUse(bool &bVerticesColors) = 0;
		virtual HRESULT CALLBACK GetTextColor(TColor4 &tTextColor) = 0;
		virtual HRESULT CALLBACK GetTextAlign(E_TEXT_ALIGN &eTextAlign) = 0;
		virtual HRESULT CALLBACK GetTextSize(float &fSize) = 0;
	};

	// {41EBE3B8-D26A-4401-AC4B-40F548F82FF6}
	static const GUID IID_IDCBorderComponent = 
	{ 0x41ebe3b8, 0xd26a, 0x4401, { 0xac, 0x4b, 0x40, 0xf5, 0x48, 0xf8, 0x2f, 0xf6 } };

	class IDCBorderComponent: public IDCTextComponent
	{
	public:
		virtual HRESULT CALLBACK SetBorderColor(const TColor4 &stBorderColor) = 0;
		virtual HRESULT CALLBACK GetBorderColor(TColor4 &stBorderColor) = 0;
	};

	// {53A91720-B48D-44b5-9C77-2538EC64E832}
	static const GUID IID_IDCImageComponent = 
	{ 0x53a91720, 0xb48d, 0x44b5, { 0x9c, 0x77, 0x25, 0x38, 0xec, 0x64, 0xe8, 0x32 } };

	class IDCImageComponent: public IDCBorderComponent
	{
	public:
		virtual HRESULT CALLBACK SetImageDraw(bool bImageDraw) = 0;
		virtual HRESULT CALLBACK SetImageTiling(bool bImageTiling) = 0;
		virtual HRESULT CALLBACK GetImageDraw(bool &bImageDraw) = 0;
		virtual HRESULT CALLBACK GetImageTiling(bool &bImageTiling) = 0;
	};

	// {E24290B1-4AA8-486f-B1FA-A70DF126C113}
	static const GUID IID_IDCButton = 
	{ 0xe24290b1, 0x4aa8, 0x486f, { 0xb1, 0xfa, 0xa7, 0xd, 0xf1, 0x26, 0xc1, 0x13 } };

	class IDCButton: public IDCImageComponent
	{
	public:
		virtual HRESULT CALLBACK SetDown(bool bDown) = 0;
		virtual HRESULT CALLBACK GetDown(bool &bDown) = 0;
	};

	// {83A114B1-232C-42a9-8E92-4A6EC7C0072A}
	static const GUID IID_IDCForm = 
	{ 0x83a114b1, 0x232c, 0x42a9, { 0x8e, 0x92, 0x4a, 0x6e, 0xc7, 0xc0, 0x7, 0x2a } };

	class IDCForm: public IDCImageComponent
	{
	public:
		virtual HRESULT CALLBACK SetHeader(bool bHeader) = 0;
		virtual HRESULT CALLBACK SetCross(bool bCross) = 0;
		virtual HRESULT CALLBACK SetDrag(bool bDrag) = 0;
		virtual HRESULT CALLBACK SetHeaderColor(const TColor4 &stHeaderColor) = 0;
		virtual HRESULT CALLBACK GetHeader(bool &bHeader) = 0;
		virtual HRESULT CALLBACK GetCross(bool &bCross) = 0;
		virtual HRESULT CALLBACK GetDrag(bool &bDrag) = 0;
		virtual HRESULT CALLBACK GetHeaderColor(TColor4 &stHeaderColor) = 0;
	};

	// {77D94C72-80AA-4a60-83E5-5A3753C1E1CA}
	static const GUID IID_IDCPanel = 
	{ 0x77d94c72, 0x80aa, 0x4a60, { 0x83, 0xe5, 0x5a, 0x37, 0x53, 0xc1, 0xe1, 0xca } };

	class IDCPanel: public IDCImageComponent {};

	// {2DE9AE0E-D39A-4772-BD79-8D58AC655E19}
	static const GUID IID_IDCLabel = 
	{ 0x2de9ae0e, 0xd39a, 0x4772, { 0xbd, 0x79, 0x8d, 0x58, 0xac, 0x65, 0x5e, 0x19 } };

	class IDCLabel: public IDCTextComponent	{};

	// {B79E7C67-D2F4-470e-BD87-53CCF9FD654D}
	static const GUID IID_IDCEdit = 
	{ 0xb79e7c67, 0xd2f4, 0x470e, { 0xbd, 0x87, 0x53, 0xcc, 0xf9, 0xfd, 0x65, 0x4d } };

	class IDCEdit: public IDCBorderComponent	{};

	// {EA5947D1-E61F-4e03-9AE0-38512B15EC2C}
	static const GUID IID_IDCCheckBox = 
	{ 0xea5947d1, 0xe61f, 0x4e03, { 0x9a, 0xe0, 0x38, 0x51, 0x2b, 0x15, 0xec, 0x2c } };

	class IDCCheckBox: public IDCImageComponent
	{
	public:
		virtual HRESULT CALLBACK SetCheckedColor(const TColor4 &stCheckedColor) = 0;
		virtual HRESULT CALLBACK SetChecked(bool bChecked) = 0;
		virtual HRESULT CALLBACK SetCheckedSize(uint uiCheckedSize) = 0;
		virtual HRESULT CALLBACK GetCheckedColor(TColor4 &stCheckedColor) = 0;
		virtual HRESULT CALLBACK GetChecked(bool &bChecked) = 0;
		virtual HRESULT CALLBACK GetCheckedSize(uint &uiCheckedSize) = 0;
	};

	// {B1D736CC-8684-4d99-83B7-470B54C5EC0D}
	static const GUID IID_IDCRadioButton = 
	{ 0xb1d736cc, 0x8684, 0x4d99, { 0x83, 0xb7, 0x47, 0xb, 0x54, 0xc5, 0xec, 0xd } };

	class IDCRadioButton: public IDCImageComponent
	{
	public:
		virtual HRESULT CALLBACK SetCheckedColor(const TColor4 &stCheckedColor) = 0;
		virtual HRESULT CALLBACK SetChecked(bool bChecked) = 0;
		virtual HRESULT CALLBACK SetCheckedSize(uint uiCheckedSize) = 0;
		virtual HRESULT CALLBACK GetCheckedColor(TColor4 &stCheckedColor) = 0;
		virtual HRESULT CALLBACK GetChecked(bool &bChecked) = 0;
		virtual HRESULT CALLBACK GetCheckedSize(uint &uiCheckedSize) = 0;
	};

	// {5F4922F8-D663-414c-AE7E-514A0E9AE37F}
	static const GUID IID_IDCTrackBar = 
	{ 0x5f4922f8, 0xd663, 0x414c, { 0xae, 0x7e, 0x51, 0x4a, 0xe, 0x9a, 0xe3, 0x7f } };

	class IDCTrackBar: public IDCBorderComponent
	{
	public:
		virtual HRESULT CALLBACK SetValue(int iValue) = 0;
		virtual HRESULT CALLBACK SetMinValue(int iMinValue) = 0;
		virtual HRESULT CALLBACK SetMaxValue(int iMaxValue) = 0;
		virtual HRESULT CALLBACK SetHorizontal(bool bHorizontal) = 0;
		virtual HRESULT CALLBACK GetValue(int &iValue) = 0;
		virtual HRESULT CALLBACK GetMinValue(int &iMinValue) = 0;
		virtual HRESULT CALLBACK GetMaxValue(int &iMaxValue) = 0;
		virtual HRESULT CALLBACK GetHorizontal(bool &bHorizontal) = 0;
	};

	// {4F54FE27-61DF-47a6-8003-470FDC16D2A5}
	static const GUID IID_IDCProgressBar = 
	{ 0x4f54fe27, 0x61df, 0x47a6, { 0x80, 0x3, 0x47, 0xf, 0xdc, 0x16, 0xd2, 0xa5 } };

	class IDCProgressBar: public IDCBorderComponent
	{
	public:
		virtual HRESULT CALLBACK SetValue(float fValue) = 0;
		virtual HRESULT CALLBACK SetMaxValue(float fMaxValue) = 0;
		virtual HRESULT CALLBACK SetQuantityQuads(int iQuantityQuads) = 0;
		virtual HRESULT CALLBACK SetHorizontal(bool bHorizontal) = 0;
		virtual HRESULT CALLBACK GetValue(float &fValue) = 0;
		virtual HRESULT CALLBACK GetMaxValue(float &fMaxValue) = 0;
		virtual HRESULT CALLBACK GetQuantityQuads(int &iQuantityQuads) = 0;
		virtual HRESULT CALLBACK GetHorizontal(bool &bHorizontal) = 0;
	};

	// {63843DD2-019D-4a57-AF0F-CE4B9433D56D}
	static const GUID IID_IDCListBox = 
	{ 0x63843dd2, 0x19d, 0x4a57, { 0xaf, 0xf, 0xce, 0x4b, 0x94, 0x33, 0xd5, 0x6d } };

	class IDCListBox: public IDCBorderComponent
	{
	public:
		virtual HRESULT CALLBACK SetSelectedIndex(uint uiIndex) = 0;
		virtual HRESULT CALLBACK SetItemText(const char* pcTxt, int iIndex = -1) = 0;

		virtual HRESULT CALLBACK GetSelectedIndex(int &iIndex) = 0;
		virtual HRESULT CALLBACK GetItemsCount(uint &uiCount) = 0;
		virtual HRESULT CALLBACK GetItemText(char *pcTxt, uint uiCharsCount, int iIndex = -1) = 0;

		virtual HRESULT CALLBACK AddItem(const char* pcTxt) = 0;
		virtual HRESULT CALLBACK RemoveItem(int iIndex = -1) = 0;
		virtual HRESULT CALLBACK Clear() = 0;
	};

	// {001D1C0D-573F-4844-87D2-A577D00F9AC2}
	static const GUID IID_IDCComboBox = 
	{ 0x1d1c0d, 0x573f, 0x4844, { 0x87, 0xd2, 0xa5, 0x77, 0xd0, 0xf, 0x9a, 0xc2 } };

	class IDCComboBox: public IDCBorderComponent
	{
	public:
		virtual HRESULT CALLBACK SetListDown(bool bListDown) = 0;
		virtual HRESULT CALLBACK GetListDown(bool &bListDown) = 0;

		virtual HRESULT CALLBACK SetSelectedIndex(uint uiIndex) = 0;
		virtual HRESULT CALLBACK SetItemText(const char* pcTxt, int iIndex = -1) = 0;

		virtual HRESULT CALLBACK GetSelectedIndex(int &iIndex) = 0;
		virtual HRESULT CALLBACK GetItemsCount(uint &uiCount) = 0;
		virtual HRESULT CALLBACK GetItemText(char *pcTxt, uint uiCharsCount, int iIndex = -1) = 0;

		virtual HRESULT CALLBACK AddItem(const char* pcTxt) = 0;
		virtual HRESULT CALLBACK RemoveItem(int iIndex = -1) = 0;
		virtual HRESULT CALLBACK Clear() = 0;
	};

	// {0C9714A6-F6D4-4945-A88B-5EDC1E840F53}
	static const GUID IID_IDCStyleProvider = 
	{ 0xc9714a6, 0xf6d4, 0x4945, { 0xa8, 0x8b, 0x5e, 0xdc, 0x1e, 0x84, 0xf, 0x53 } };

	class IDCStyleProvider : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK UseVerticesColors(bool bVerticesColors) = 0;
		virtual HRESULT CALLBACK SetEnabledColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetDisabledColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetTextColor(const TColor4 &stTextColor) = 0;
		virtual HRESULT CALLBACK SetBorderColor(const TColor4 &stBorderColor) = 0;
		virtual HRESULT CALLBACK SetVerticesColors(const TColor4 &stColor1, const TColor4 &stColor2, const TColor4 &stColor3, const TColor4 &stColor4) = 0;
		virtual HRESULT CALLBACK SetCheckedColor(const TColor4 &stCheckedColor) = 0;
		virtual HRESULT CALLBACK SetHeaderColor(const TColor4 &stHeaderColor) = 0;

		virtual HRESULT CALLBACK GetVerticesColorsUse(bool &rbVerticesColors) = 0;
		virtual HRESULT CALLBACK GetEnabledColor(TColor4 &rtColor) = 0;
		virtual HRESULT CALLBACK GetDisabledColor(TColor4 &rtColor) = 0;
		virtual HRESULT CALLBACK GetTextColor(TColor4 &rtTextColor) = 0;
		virtual HRESULT CALLBACK GetBorderColor(TColor4 &rtBorderColor) = 0;
		virtual HRESULT CALLBACK GetCheckedColor(TColor4 &rtCheckedColor) = 0;
		virtual HRESULT CALLBACK GetHeaderColor(TColor4 &rtHeaderColor) = 0;
	};
	
}
#endif //_DGLE2_EXT