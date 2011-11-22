/**
\file		DGLE2.h
\author		Korotkov Andrey aka DRON
\version	Beta 2
\date		17.03.2011 (c)Korotkov Andrey

\brief		Main DGLE2 engine header.

To use engine you should just include this header to your project.
This header is a part of DGLE2_SDK.
*/

/** 
\mainpage	DGLE2 Main Help Page
 
\section	intro_sec Introduction

- DGLE2 is powerfull crossplatform engine for games and scientific applications.
- DGLE2 is opensource project and free to use(under the terms of license, see below).
- DGLE2 is based on widely spread open standarts and formats such as OpenGL, OpenCL, OGG Vorbis, Lua, Box2D, Bullet physics, e.t.c..

\image html Open_Standarts.png

This file is official engine documentation for C++ programmers(DGLE2 users).
This documentation is also suitable for any supported programming language.

\section	aim_sec The aim of the project

The aim of the project is to create flexible and extensible technology that any user can use.
It should be easy to make great projects only by using editors and scripts(Lua) or go
deeper and use your programming skills of your favorite language(C++, C#, Delphi, e.t.c.)
and create really exciting projects.
Users can also add new formats and functionallity by creating new plugins for engine and share
them with others over the web or just get plugins already made by others.
And when project is complete it can be easily build not only for Windows but also Linux,
MacOS(and iOS) and consoles. Projects can also be a runtime part of the web page to use them in
popular browsers like IE, Firefox, Opera, Chrome and Safari.

\section gstart_sec Getting started

Simple steps to make your first DGLE2 application.

- 1. Include this("DGLE2.h") header to your project.
- 2. Connect DGLE2 namespace to your project(ex. "using namespace DGLE2;").
- 3. Paste "ENG_DYNAMIC_FUNC" or "ENG_STATIC_FUNC" macros to your main source file(ex. "Main.cpp").
- 4. Declare pointer to IEngineCore class like "IEngineCore *pEngineCore".
- 5. Call "GetEngine" function to retrieve IEngineCore pointer. For dynamic library it should be like this "GetEngine("DGLE2.dll",pEngineCore);".
- 6. Now you can use IEngineCore methods. For example, you can initialize engine like this "pEngineCore->InitializeEngine(NULL,"HelloWorld");".
- 7. After engine initialization you should call "pEngineCore->StartEngine();" to start engine.
- 8. When you are done with engine don't forget to call "FreeEngine()" routine before exit.

Please see "HelloWorld" sample code at the "Examples" tab of this help file.

You can browse ".\Source\Samples" folder or go to "Examples" tab of this manual for futher information.

\section license_sec License

DGLE2 is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

DGLE2 is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.

<b>ATTENTION</b>: If you are using DGLE2 in your project you MUST NOT remove DGLE2 splash screen
and you MUST paste link to the official DGLE2 website in your program credits section or elsewhere.
It is the easiest way you can say "Thank you for your work!" to DGLE2 project developers.

<i>Note</i>: The only legal way you can remove DGLE2 logo is to donate the project.

\section additional_sec Additional help and information

Visit official DGLE2 engine website http://dgle.deeprosoft.com/ for additional information.

You can gain help, support project or just say your oppinion at official DGLE2 forum.
http://forum.mirgames.ru/index.php?showforum=74 (Russian)

Feel free to write directly to project leader on e-mail dron@deeprosoft.com.

\example HelloWorld.cpp
This is simplest DGLE2 application.
\note To make this sample work you should copy "DGLE2.h" header to your project source directory and place "DGLE2.dll" in your project output folder. 

*/

#ifndef DGLE2_HEADER
#define DGLE2_HEADER

//Engine version defines//

/** Defines DGLE2 version string. 
	\warning Do not edit!
*/
#define _DGLE2_VER_	"Beta 2"
 
/** Defines DGLE2 version integer. 
	\warning Do not edit!
*/
#define _DGLE2_SDK_VER_ 1

/** Defines the current version of plugin SDK. 
	\warning Do not edit!
*/
#define _DGLE2_PLUGIN_SDK_VER_ _DGLE2_SDK_VER_

//Platform definition macros//

#if defined(_WIN32) || defined(_WIN64)

//Platform Windows//

#include <Windows.h>

/** Intrnal engine define, shows that target platform is Windows.*/
#define PLATFORM_WINDOWS

/** If defined, all interfaces will be derived from IUnknown. */
#define DGLE2_USE_COM

#ifndef _WIN64
/** If defined, all structures will be aligned by 1 byte. */
#define STRUCT_ALIGNMENT_1
#endif //_WIN64

#ifdef _WIN64
#pragma message("Target platform is WIN64.")
#else //_WIN64
#pragma message("Target platform is WIN32.")
#endif

#else//_WIN32 or _WIN64

//Unknown platform//
#error Unknown platform.

#endif

#include "DGLE2_types.h"

/** Engines main namespace. */
namespace DGLE2
{

//Engine Base interface//

	/** Engine base fundamental interface.
		Any engine interface must be derived from this interface.
		\attention On Windows platform IDGLE2_Base is derived from IUnknown for more flexibility and compatibility,
		but DGLE2 doesn't provides real COM technology. The reference counter is always 1,
		"Release" and "AddRef" methods are dummies, "QueryInterface" can return pointer only
		to IUnknown or to the last interface in the inheritance chain.
	*/
	class IDGLE2_Base
#if defined(PLATFORM_WINDOWS) && defined(DGLE2_USE_COM)
		: public IUnknown
#endif
	{
	public:
		/** Returns uniq identifier of the last interface in the inheritance chain.
			\param[out] guid Uniq interface identifier.
			\return Always returnes DGLE2_types.h::S_OK.
		 */		
		virtual HRESULT CALLBACK GetGUID(GUID &guid) = 0;
	};

//Engine SubSystem interface//

	/** Engine subsystems types. */
	enum E_ENGINE_SUB_SYSTEM
	{
		ESS_RENDER = 0,			/**< Main rendering subsystem. \see IRender */
		ESS_INPUT,				/**< Input subsystem. \see IInput */
		ESS_SOUND,				/**< Sound subsystem. \see ISound */
		ESS_RESOURCE_MANAGER,	/**< Resource manager subsystem. \see IResourceManager */
		ESS_FILE_SYSTEM,		/**< Main file system(manager of virtual file systems). \see IMainFileSystem */
	};

	// {C682F875-E0BD-4af9-B79C-E209850025F8}
	static const GUID IID_IEngineSubSystem = 
	{ 0xc682f875, 0xe0bd, 0x4af9, { 0xb7, 0x9c, 0xe2, 0x9, 0x85, 0x0, 0x25, 0xf8 } };

	/** Base interface of any engine subsystem. */
	class IEngineSubSystem : public IDGLE2_Base
	{
	public:
		/** Returns type of subsystem. 
			\param[out] eSubSystemType Type of the subsystem to which you may cast this interface pointer.
			\return Always returnes DGLE2_types.h::S_OK.	
		*/
		virtual HRESULT CALLBACK GetType(E_ENGINE_SUB_SYSTEM &eSubSystemType) = 0;
	};

//Engine Plugin interface//

	// {B94E0E40-8885-41dd-8BC5-4CD663AE5709}
	static const GUID IID_IPlugin = 
	{ 0xb94e0e40, 0x8885, 0x41dd, { 0x8b, 0xc5, 0x4c, 0xd6, 0x63, 0xae, 0x57, 0x9 } };

	/** Base interface of any engine plugin. */
	class IPlugin : public IDGLE2_Base
	{
	public:
		/** Returns structure with plugin description.
			\param[out] stInfo Structure in which plugin description will be stored.
		*/
		virtual HRESULT CALLBACK GetPluginInfo(TPluginInfo &stInfo) = 0;
		/** Returns the name of interface which plugin implements or empty string if it implements nothing.
			\param[out] pcName Pointer to allocated string.
			\param[in] uiCharsCount Count of the chars in allocated string.
			\return E_INVALIDARG must be returned if allocated string is too small. 
		*/
		virtual HRESULT CALLBACK GetPluginInterfaceName(char* pcName, uint uiCharsCount) = 0;
	};

//Engine Base Object interface//

	/** Types of engine objects. */
	enum E_ENG_OBJ_TYPE
	{
		EOT_UNKNOWN = 0,		/**< Undefined or custom object type. */ 
		EOT_TEXTURE,			/**< Texture. \see ITexture*/ 
		EOT_MATERIAL,			/**< Material. \see IMaterial */ 
		EOT_MESH,				/**< Mesh. \see IMesh */ 
		EOT_MODEL,				/**< Model. \see IModel*/ 
		EOT_SHADER,				/**< Pixel or vertex shader. \see IShader*/ 
		EOT_PROGRAM,			/**< Combination of pixel and vertex shaders. \see IProgram */ 
		EOT_BITMAP_FONT,		/**< Bitmap font. \see IBitmapFont */ 
		EOT_PARTICLE_EFFECT,	/**< Particle effect. \see IParticleEffect*/ 
		EOT_SOUND_SAMPLE,		/**< Sound sample \see ISoundSample */ 
		EOT_MUSIC,				/**< Music. \see IMusic*/ 
		EOT_SPRITE,				/**< Sprite. \see ISprite */ 
		EOT_GUI_FORMS			/**< Collection of user interface forms. \see IGUIForms */ 
	};

	// {C010239A-6457-40f5-87EF-FAA3156CE6E2}
	static const GUID IID_IEngBaseObj = 
	{ 0xc010239a, 0x6457, 0x40f5, { 0x87, 0xef, 0xfa, 0xa3, 0x15, 0x6c, 0xe6, 0xe2 } };

	/** Base interface of any engine object. 
		Engine objects are commonly loaded from files by Resource Manager subsystem.
		\see IResourceManager
	*/
	class IEngBaseObj : public IDGLE2_Base
	{
	public:
		/** Releases object and deallocates memory. Also removes it from IResourceManager lists. 
			After calling Free() method you can safely null the pointer to the object.
		*/
		virtual HRESULT CALLBACK Free() = 0;
		/** Returns type of object. 
			\param[out] eObjType Type of the object to which you may cast this interface pointer.
			\return Always returnes DGLE2_types.h::S_OK.	
		*/
		virtual HRESULT CALLBACK GetType(E_ENG_OBJ_TYPE &eObjType) = 0;
	};

//Events Interfaces//

	/** Types of engine events. 
		\see IBaseEvent
	 */
	enum E_EVENT_TYPE
	{
		ET_UNKNOWN = 0,				/**< Undefined or custom event type. */ 
		ET_BEFORE_INIT,				/**< Event occures just before engine will call its initialization routines. \see IEvBeforeInit */ 
		ET_BEFORE_RENDER,			/**< Event occures before every frame. */ 
		ET_AFTER_RENDER,			/**< Event occures after every frame. */ 
		ET_ON_PROFILER_DRAW,		/**< It is a special event on which you can render some text information on screen. \note If you want to output some statistic or profiling information use this event and special RenderProfilerTxt method. \see IEngineCore::RenderProfilerTxt */ 
		ET_ON_WIN_MESSAGE,			/**< Event occures every time when window receives message. Use this event to hook engine window messages. \see IEvWinMessage */ 
		ET_ON_GET_SSYSTEM,			/**< Event occures when someone calls IEngineCore::GetSubSystem method and you can substitute any subsystem by your own realisation. \see IEvGetSubSystem */ 
		ET_ON_ENGINE_FATAL_MESSAGE	/**< Event occures on engine fatal error. \see IEvFatalMessage */ 
	};

	// {6DFEF982-AADF-42e9-A369-378BDB31404A}
	static const GUID IID_IBaseEvent = 
	{ 0x6dfef982, 0xaadf, 0x42e9, { 0xa3, 0x69, 0x37, 0x8b, 0xdb, 0x31, 0x40, 0x4a } };

	/** Base interface of any engine event. 
		\see IEngineCore::AddEventListner, IEngineCore::RemoveEventListner
	 */
	class IBaseEvent : public IDGLE2_Base
	{
	public:
		/** Returns type of event. 
			\param[out] eEvType Type of the event. You may cast this interface pointer to special event interface if such exists.
			\return Always returnes DGLE2_types.h::S_OK.	
		*/
		virtual HRESULT CALLBACK GetEventType(E_EVENT_TYPE &eEvType) = 0;
	};

	// {EB735739-3D12-4522-B6D7-EEE3225DF934}
	static const GUID IID_IEvBeforeInit = 
	{ 0xeb735739, 0x3d12, 0x4522, { 0xb6, 0xd7, 0xee, 0xe3, 0x22, 0x5d, 0xf9, 0x34 } };

	enum E_ENGINE_INIT_FLAGS
#ifdef __CODEGEARC__
    : long
#endif
    ;

	/** Event occures just before engine will call its initialization routines.
		On this event tou can hook engine init parametrs.
		\see ET_BEFORE_INIT, IEngineCore::InitializeEngine, IBaseEvent
	 */
	class IEvBeforeInit : public IBaseEvent
	{
	public:
		/** Sets new engine initialization parametrs.
			\param[in] stWindowParam New engine window structure to replace current.
			\param[in] eInitFlags New engine initialization flags to replace current.
		 */
		virtual HRESULT CALLBACK SetEngParams(const TEngWindow &stWindowParam, E_ENGINE_INIT_FLAGS eInitFlags) = 0;
		/** Retrieves current engine initialization parametrs. 
			\param[in] stWindowParam Current engine window structure.
			\param[in] eInitFlags Current engine initialization flags.
		 */
		virtual HRESULT CALLBACK GetEngParams(TEngWindow &stWindowParam, E_ENGINE_INIT_FLAGS eInitFlags) = 0;
	};
	
	// {DAA4E3BC-C958-4def-B603-F63EEC908226}
	static const GUID IID_IEvFatalMessage = 
	{ 0xdaa4e3bc, 0xc958, 0x4def, { 0xb6, 0x3, 0xf6, 0x3e, 0xec, 0x90, 0x82, 0x26 } };

	/** Event occures on engine fatal error.
		Also application errors such as "Access Violation" are handled by this event if EIF_CATCH_UNHANDLED
		flag is set in IEngineCore::InitializeEngine initialization flags.
		By handling this event 
		\see ET_ON_ENGINE_FATAL_MESSAGE, LT_FATAL, IBaseEvent
	 */
	class IEvFatalMessage : public IBaseEvent
	{
	public:
		/** Returns the fatal message text.
		 \param[out] pcTxt Pointer to allocated string.
		 \param[in] uiCharsCount Count of the chars in allocated string.
		 \return E_INVALIDARG must be returned if allocated string is too small. 
		 */		
		virtual HRESULT CALLBACK GetMessageTxt(char *pcTxt, uint uiCharsCount) = 0;
		/** Suspends all engine threads and pauses all engine routines. 
			\param[in] bFreeze Suspends if true or resumes if fales engine threads and routines.
		 */
		virtual HRESULT CALLBACK FreezeEngine(bool bFreeze) = 0;
		/** Forces engine not to show error message and console. 
			\note If you decided not to show error message you should inform user about error somehow.
		 */
		virtual HRESULT CALLBACK ForceNoMessage() = 0;
		/** Forces engine to ignore current error and tries to continue. 
			\warning Use with care.
		 */
		virtual HRESULT CALLBACK ForceIgnoreError() = 0;
	};

	// {8D718E48-581D-4cbb-9C40-C04998106F8D}
	static const GUID IID_IEvWinMessage = 
	{ 0x8d718e48, 0x581d, 0x4cbb, { 0x9c, 0x40, 0xc0, 0x49, 0x98, 0x10, 0x6f, 0x8d } };

	/** Event occures every time when window receives message. 
		Use this event to hook window messages.
		\see ET_ON_WIN_MESSAGE, IBaseEvent
	 */
	class IEvWinMessage : public IBaseEvent
	{
	public:
		/** Retrieves window message.
			\param[out] stWinMsg Structure with current message information.
		 */
		virtual HRESULT CALLBACK GetWinMessage(TWinMessage &stWinMsg) = 0;
	};

	// {2B6D2547-716E-490c-B1F1-422CB428738F}
	static const GUID IID_IEvGetSubSystem = 
	{ 0x2b6d2547, 0x716e, 0x490c, { 0xb1, 0xf1, 0x42, 0x2c, 0xb4, 0x28, 0x73, 0x8f } };

	/** Event occures when someone calls IEngineCore::GetSubSystem method.
		You can substitute any subsystem by your own realisation on this event.
		\see ET_ON_GET_SSYSTEM, IBaseEvent
	 */
	class IEvGetSubSystem : public IBaseEvent
	{
	public:
		/** Returns subsystem type which user is trying to retrieve. 
			\param[out] eSubSystem Type of retrieving subsystem.
		 */
		virtual HRESULT CALLBACK GetSubSystemType(E_ENGINE_SUB_SYSTEM eSubSystem) = 0;
		/** Substitutes engine subsystem by custom one. 
			\param[int] pSubSystem Pointer to subsystem interface with which retrieving subsystem will be substituted.
		 */		
		virtual HRESULT CALLBACK OverrideSubSystem(IEngineSubSystem *pSubSystem) = 0;
	};

//Main Engine System//

	/** Type of engine callbacks. 
		IEngineCore can register calbacks of these types.
		\see IEngineCore::AddProcedure, IEngineCore::RemoveProcedure
	 */
	enum E_ENGINE_PROCEDURE_TYPE
	{
		EPT_PROCESS = 0,	/**< Procedure is called periodically(like on timer event). Interval of calling is set on engine initialization. In this procedure you should do any application computes. \see IEngineCore::InitializeEngine */
		EPT_RENDER,			/**< Procedure is called when engine decides to draw new frame. In this procedure you can call any rendering routines. */
		EPT_INIT,			/**< Procedure is called before engine will start its main loop. In this procedure you should load all resources needed by your application. */
		EPT_FREE			/**< Procedure is called before engine quits. In this procedure you should release all resources and free memmory. */
	};

	/** Type of engine log message.
		\see IEngineCore::AddToLogEx
	 */
	enum E_LOG_TYPE
	{
		LT_INFO = 0,	/**< Information message do not need user attention. */
		LT_WARNING,		/**< Information message do not need user attention but marks in engine log as warning and increments warnings counter. */
		LT_ERROR,		/**< Error message do not need user attention but marks in engine log as error and increments errors counter. Error message also includes information about source file and line. */
		LT_FATAL		/**< Fatal message displays user error message and then terminates engine with exit code 2. Also ET_ON_ENGINE_FATAL_MESSAGE event is generated. */
	};

	/** Engine initialization flags. 
		\see IEngineCore::InitializeEngine
	 */
	enum E_ENGINE_INIT_FLAGS
#ifdef __CODEGEARC__
	: long
#endif
	{
		EIF_DEFAULT				= 0x00000000,	/**< Use default settings. */
		EIF_CATCH_UNHANDLED		= 0x00000001,	/**< All user callbacks will be executed in safe mode and engine will catch any unhandled errors. Engine will convert cached errors to engine fatal errors. Also ET_ON_ENGINE_FATAL_MESSAGE event is generated. */
		EIF_FORCE_NO_SOUND		= 0x00000002,	/**< Sound subsystem will not be initialized. */
		EIF_LOAD_ALL_PLUGINS	= 0x00000004,	/**< Engine will try to connect any found *.dplug files near it and in "plugins" folder. \note DGLE2_EXT.dplug is connected automatically without this flag as well. */
		EIF_FORCE_API_INPUT		= 0x00000010,	/**< Engine will use window messages based input instead of platform native input system. \note Recommended for embedded and(or) non game applications. */
		EIF_FORCE_LIMIT_FPS		= 0x00000020,	/**< Engine will limit its FPS(frames per second) not to overload CPU. FPS is limited to engine process interval(uiProcessInterval). \note Recommended for casual games and desktop applications. */
		EIF_FORCE_16_BIT_COLOR	= 0x00000040,	/**< Forces engine to use 16 bit color depth instead of 32 bit by default. */
		EIF_DISABLE_SMART_TIMING= 0x00000100,	/**< In some cases engine may call EPT_PROCESS several times at once to reduce lags. This flag will disable this feature. */
		EIF_FORCE_API_SOUND		= 0x00000200	/**< Engine will use simple basic sound api available for current platform. \note Recommended only for non game applications. */
	};

	// {111BB884-2BA6-4e84-95A5-5E4700309CBA}
	static const GUID IID_IEngineCore = 
	{ 0x111bb884, 0x2ba6, 0x4e84, { 0x95, 0xa5, 0x5e, 0x47, 0x0, 0x30, 0x9c, 0xba } };

	/** Main engine interface.
		Pointer to this interface is retrieved directly from DGLE2 library.
		\see ENG_DYNAMIC_FUNC, ENG_STATIC_FUNC
	 */
	class IEngineCore : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK InitializeEngine(TWinHandle stHandle, const char* pcApplicationName, const TEngWindow &stWindowParam = TEngWindow(), uint uiProcessInterval = 33, E_ENGINE_INIT_FLAGS eInitFlags = EIF_DEFAULT ) = 0;
		virtual HRESULT CALLBACK SetProcessInterval(uint uiProcessInterval) = 0;	
		virtual HRESULT CALLBACK StartEngine() = 0;
		virtual HRESULT CALLBACK QuitEngine() = 0;

		virtual HRESULT CALLBACK ConnectPlugin(const char* pcFileName, IPlugin *&prPlugin) = 0;	
		virtual HRESULT CALLBACK DisconnectPlugin(IPlugin *pPlugin) = 0;	
		virtual HRESULT CALLBACK GetPlugin(const char* pcPluginName, IPlugin *&prPlugin) = 0;	

		virtual HRESULT CALLBACK AddProcedure(E_ENGINE_PROCEDURE_TYPE eProcType, void (CALLBACK *pProc)(void *pParametr), void *pParametr = NULL) = 0;
		virtual HRESULT CALLBACK RemoveProcedure(E_ENGINE_PROCEDURE_TYPE eProcType, void (CALLBACK *pProc)(void *pParametr), void *pParametr = NULL) = 0;

		virtual HRESULT CALLBACK AddEventListner(E_EVENT_TYPE eEventType, void (CALLBACK *pListnerProc)(void *pParametr, IBaseEvent *pEvent), void *pParametr = NULL) = 0;
		virtual HRESULT CALLBACK RemoveEventListner(E_EVENT_TYPE eEventType, void (CALLBACK *pListnerProc)(void *pParametr, IBaseEvent *pEvent), void *pParametr = NULL) = 0;

		virtual HRESULT CALLBACK GetSubSystem(E_ENGINE_SUB_SYSTEM eSubSystem, IEngineSubSystem *&prSubSystem) = 0;

		virtual HRESULT CALLBACK RenderProfilerTxt(const char* pcTxt, const TColor4 &stColor = TColor4()) = 0;
		virtual HRESULT CALLBACK GetInstanceIdx(uint &uiIdx) = 0;
		virtual HRESULT CALLBACK GetTimer(uint32 &uiTimer) = 0;
		virtual HRESULT CALLBACK GetSystemInfo(TSystemInfo &stSysInfo) = 0;
		virtual HRESULT CALLBACK GetCurrentWin(TEngWindow &stWin) = 0;
		virtual HRESULT CALLBACK GetFPS(uint &uiFPS) = 0;
		virtual HRESULT CALLBACK GetHandle(TWinHandle &stHandle) = 0;

		virtual HRESULT CALLBACK ChangeWinMode(const TEngWindow &stNewWin) = 0;
		virtual HRESULT CALLBACK AllowPause(bool bAllow) = 0;

		virtual HRESULT CALLBACK AddToLog(const char *pcTxt) = 0;
		virtual HRESULT CALLBACK AddToLogEx(const char *pcTxt, E_LOG_TYPE eType, const char *pcSrcFileName, int iSrcLineNumber) = 0;

		virtual HRESULT CALLBACK ConsoleVisible(bool bIsVisible) = 0;
		virtual HRESULT CALLBACK ConsoleWrite(const char *pcTxt, bool bWriteToPreviousLine = false) = 0;
		virtual HRESULT CALLBACK ConsoleExec(const char *pcCommandTxt) = 0;
		virtual HRESULT CALLBACK ConsoleRegComProc(const char *pcCommandName, const char *pcCommandHelp, void (CALLBACK *pProc)(void *pParametr, const char *pcParam), void *pParametr = NULL) = 0; 
		virtual HRESULT CALLBACK ConsoleRegComValue(const char *pcCommandName, const char *pcCommandHelp, int *piValue, int iMinValue, int iMaxValue, void (CALLBACK *pProc)(void *pParametr, const char *pcParam) = NULL, void *pParametr = NULL) = 0;
		virtual HRESULT CALLBACK ConsoleUnregCom(const char *pcCommandName) = 0;

		virtual HRESULT CALLBACK GetVersion(char* pcBuffer, uint uiBufferSize) = 0;	
	};

//Resource Manager SubSystem//

	class IFile;
	class ITexture;
	class IMaterial;
	class IShader;
	class IProgram;
	class IMesh;

	enum E_TEXTURE_CREATION_FLAGS
	{
		TCF_COLOR_RGB				= 0x00000001,
		TCF_COLOR_RGBA				= 0x00000002,
		TCF_COLOR_ALPHA				= 0x00000004,
		TCF_COLOR_BGR				= 0x00000010,
		TCF_COLOR_BGRA				= 0x00000020,
		TCF_COLOR_COMPRESSED_RGB	= 0x00000040,//DXT1
		TCF_COLOR_COMPRESSED_RGBA	= 0x00000080,//DXT5
		TCF_DEPTH_COMPONENT			= 0x00000008,
		TCF_PIXEL_ALIGNMENT_1		= 0x00000100,//use only if your texture input data is not 4 byte aligned
		TCF_MIPMAPS_PRESENTED		= 0x00001000 //all mip levels must be presented
	};

	enum E_TEXTURE_LOAD_FLAGS
	{
		TLF_FILTERING_NONE			= 0x00000001,
		TLF_FILTERING_BILINEAR		= 0x00000002,
		TLF_FILTERING_TRILINEAR		= 0x00000004,
		TLF_FILTERING_ANISOTROPIC	= 0x00000008,
	
		TLF_DECREASE_QUALITY_MEDIUM	= 0x00000020,
		TLF_DECREASE_QUALITY_HIGH	= 0x00000040,

		TLF_COMPRESS				= 0x00000100,

		TLF_COORDS_REPEAT			= 0x00001000,
		TLF_COORDS_CLAMP			= 0x00002000,
		TLF_COORDS_MIRROR_REPEAT	= 0x00004000,
		TLF_COORDS_MIRROR_CLAMP		= 0x00008000,

		TLF_GENERATE_MIPMAPS		= 0x00040000,

		TLF_ANISOTROPY_2X			= 0x00100000,
		TLF_ANISOTROPY_4X			= 0x00200000,
		TLF_ANISOTROPY_8X			= 0x00400000,
		TLF_ANISOTROPY_16X			= 0x00800000
	};

	enum E_MESH_CREATION_FLAGS
	{
		MCF_ONLY_DEFAULT_DATA		= 0x00000000,//vertex and index arrays must be presented
		MCF_NORMALS_PRESENTED		= 0x00000001,
		MCF_TEXTURE_COORDS_PRESENTED= 0x00000002,
		MCF_TANGENT_SPACE_PRESENTED	= 0x00000004
	};

	enum E_MESH_LOAD_FLAGS
	{
		MLF_EDITABLE				= 0x00000001,
		MLF_FORCE_NO_VBO			= 0x00000002,
		MLF_CALCULATE_TANGENT_SPACE = 0x00000004,
		MLF_CALCULATE_NORMALS		= 0x00000008
	};

	enum E_SHADER_LOAD_FLAGS
	{
		// first bit reserved for shader type
		SLF_IMMEDIATE_COMPILE		= 0x00000002,
		SLF_DEFERRED_COMPILE		= 0x00000004
	};

	enum E_PROGRAM_LOAD_FLAGS
	{
		PLF_IMMEDIATE_LINK			= 0x00000001,
		PLF_DEFERRED_LINK			= 0x00000002
	};

	enum E_SHADER_TYPE
	{
		ST_VERTEX = 0,
		ST_PIXEL
	};

	const uint TEXTURE_LOAD_DEFAULT_2D = (uint)(TLF_FILTERING_BILINEAR | TLF_COORDS_CLAMP);
	const uint TEXTURE_LOAD_DEFAULT_3D = (uint)(TLF_FILTERING_TRILINEAR | TLF_GENERATE_MIPMAPS | TLF_COORDS_REPEAT);

	const uint RES_LOAD_DEFAULT = 0x00000000;

	// {139505B6-5EFC-4f02-A5E8-18CD1FBD69E3}
	static const GUID IID_IResourceManager = 
	{ 0x139505b6, 0x5efc, 0x4f02, { 0xa5, 0xe8, 0x18, 0xcd, 0x1f, 0xbd, 0x69, 0xe3 } };

	class IResourceManager : public IEngineSubSystem
	{
	public:
		virtual HRESULT CALLBACK CreateTexture(ITexture *&prTex, const ubyte *pubtData, uint iuWidth, uint uiHeight, E_TEXTURE_CREATION_FLAGS eCreationFlags, E_TEXTURE_LOAD_FLAGS eLoadFlags) = 0;
		virtual HRESULT CALLBACK CreateMaterial(IMaterial *&prMaterial) throw() = 0;
		virtual HRESULT CALLBACK CreateShader(E_SHADER_TYPE eShaderType, IShader *&prShader, uint uiLogLineOffset = 0) = 0;
		virtual HRESULT CALLBACK CreateProgram(IProgram *&prProgram, bool bOwnShaders = false) = 0;
		virtual HRESULT CALLBACK CreateMesh(IMesh *&prMesh, const ubyte *pubtData, uint uiDataSize, uint uiNumVerts, uint uiNumFaces, E_MESH_CREATION_FLAGS eCreationFlags, E_MESH_LOAD_FLAGS eLoadFlags) = 0;
	
		virtual HRESULT CALLBACK RegisterFileFormat(const char *pcExtension, E_ENG_OBJ_TYPE eObjType, const char *pcDiscription, bool (CALLBACK *pLoadProc)(IFile *pFile, IEngBaseObj *&prObj, uint uiLoadFlags, void *pParametr), void *pParametr = NULL) = 0;
		virtual HRESULT CALLBACK UnregisterFileFormat(const char *pcExtension) = 0;
		virtual HRESULT CALLBACK RegisterDefaultResource(E_ENG_OBJ_TYPE eObjType, IEngBaseObj *pObj) = 0;
		virtual HRESULT CALLBACK UnregisterDefaultResource(E_ENG_OBJ_TYPE eObjType, IEngBaseObj *pObj) = 0;
		virtual HRESULT CALLBACK GetRegisteredExtensions(char *pcTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetExtensionDescription(const char *pcExtension, char *pcTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetExtensionType(const char *pcExtension, E_ENG_OBJ_TYPE &eType) = 0;

		virtual HRESULT CALLBACK GetDefaultResource(E_ENG_OBJ_TYPE eObjType, IEngBaseObj *&prObj) = 0;

		virtual HRESULT CALLBACK Load(const char *pcFileName, IEngBaseObj *&prObj, uint uiLoadFlags = RES_LOAD_DEFAULT) = 0;
		virtual HRESULT CALLBACK Load2(IFile *pFile, IEngBaseObj *&prObj, uint uiLoadFlags = RES_LOAD_DEFAULT) = 0;
	
		virtual HRESULT CALLBACK FreeResource(IEngBaseObj *&prObj) = 0;
		virtual HRESULT CALLBACK AddResource(IEngBaseObj *pObj) = 0;
		virtual HRESULT CALLBACK RemoveResource(IEngBaseObj *pObj, bool &bCanDelete) = 0;
	};

//Render SubSystem//

	class IRender2D;
	class IRender3D;
	class ILight;
	class IPostprocess;

	enum E_GET_POINT3_FLAG
	{
		GP3F_FROM_Z_BUFFER	= 0,
		GP3F_FROM_FAR_PLANE,
		GP3F_FROM_NEAR_PLANE
	};

	enum E_RENDER_SUPPORTED_FEATURES
	{
		RSF_TEXTURE_COMPRESSION = 0,
		RSF_VERTEX_BUFFER_OBJECT,
		RSF_GLSL,
		RSF_TEXTURE_ANISOTROPY
	};

	// {EA03C661-A334-4225-B5DB-4C45452CCC41}
	static const GUID IID_IRender = 
	{ 0xea03c661, 0xa334, 0x4225, { 0xb5, 0xdb, 0x4c, 0x45, 0x45, 0x2c, 0xcc, 0x41 } };

	class IRender : public IEngineSubSystem
	{
	public:
		virtual HRESULT CALLBACK SetClearColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK ClearDepthBuffer() = 0;
		virtual HRESULT CALLBACK ShareWith(IRender *pRender) = 0;
		virtual HRESULT CALLBACK Unbind(E_ENG_OBJ_TYPE eType) = 0; //use EOT_UNKNOWN to unbind all
		virtual HRESULT CALLBACK EnableScissor(const TRectF &stArea) = 0;	
		virtual HRESULT CALLBACK DisableScissor() = 0;
		virtual HRESULT CALLBACK SetRenderTarget(ITexture* pTargetTex = NULL) = 0;
		virtual HRESULT CALLBACK IsSupported(E_RENDER_SUPPORTED_FEATURES eFeature, bool &bSupported) = 0;
		virtual HRESULT CALLBACK ScreenshotBMP(const char* pFileName) = 0;
		virtual HRESULT CALLBACK CreatePostProcess(IPostprocess *&pPP) = 0;
		virtual HRESULT CALLBACK ToggleStateCache(bool bEnable) = 0;
		
		virtual HRESULT CALLBACK GetRender2D(IRender2D *&prRender2D) = 0;
		virtual HRESULT CALLBACK GetRender3D(IRender3D *&prRender3D) = 0;
	};

	//Render2D interface//

	//Flags for Primitives
	enum E_PRIMITIVE2D_FLAGS
	{
		PF_DEFAULT			= 0x00000000,
		PF_FILL				= 0x00000001, 
		PF_SMOOTH			= 0x00000002, 
		PF_VCA				= 0x00000004
	};

	//Flags for Effects
	enum E_EFFECT2D_FLAGS
	{
		EF_DEFAULT			= 0x00000000,
		EF_BLEND			= 0x00000001, 
		EF_FLIPX			= 0x00000002, 
		EF_FLIPY			= 0x00000004, 
		EF_COLORMIX			= 0x00000008, 
		EF_SCALE			= 0x00000010,  
		EF_VERTICES_OFFSET	= 0x00000020, 
		EF_VERTICES_COLOR	= 0x00000040, 
		EF_ROTATEPT			= 0x00000080
	};

	//Flags for Effects Blend mode
	enum E_EFFECT2D_BLENDING_FLAGS
	{
		EBF_NONE			= 0x00000000,
		EBF_NORMAL			= 0x00000001, 
		EBF_ADD				= 0x00000002, 
		EBF_MULT			= 0x00000004, 
		EBF_BLACK			= 0x00000008,
		EBF_WHITE			= 0x00000010,
		EBF_MASK			= 0x00000020
	};

	enum E_BATCH_MODE2D
	{
		BM_AUTO	= 0,
		BM_DISABLED,
		BM_ENABLED_UEP,//update batches every process tick
		BM_ENABLED_UER //update batches every render frame
	};

	// {F5F3257A-F8B8-4d91-BA67-451167A8D63F}
	static const GUID IID_IRender2D = 
	{ 0xf5f3257a, 0xf8b8, 0x4d91, { 0xba, 0x67, 0x45, 0x11, 0x67, 0xa8, 0xd6, 0x3f } };

	class IRender2D : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK Begin2D() = 0;
		virtual HRESULT CALLBACK End2D() = 0;
		//Note: Only one pair Begin2D-End2D per frame is allowed or batching must be disabled.
		virtual HRESULT CALLBACK BatchRender(E_BATCH_MODE2D eMode) = 0;
		virtual HRESULT CALLBACK SetResolutionCorrection(uint uiResX, uint uiResY, bool bConstaintProportions = true) = 0; //Set resx and resy to current screen size to turn off correction
		virtual HRESULT CALLBACK SetCamera(const TPoint2 &stCenter, float fAngle = 0.f, const TPoint2 &stScale = TPoint2(1.f,1.f)) = 0;

		// 2D Primitives
		virtual HRESULT CALLBACK LineWidth(uint uiWidth) = 0;
		virtual HRESULT CALLBACK DrawPoint(const TPoint2 &stCoords, const TColor4 &stColor = TColor4(), uint uiSize = 1) = 0;
		virtual HRESULT CALLBACK DrawLine(const TPoint2 &stCoords1, const TPoint2 &stCoords2, const TColor4 &stColor = TColor4(), E_PRIMITIVE2D_FLAGS eFlags = PF_DEFAULT) = 0;
		virtual HRESULT CALLBACK DrawRect(const TRectF &stRect, const TColor4 &stColor = TColor4(), E_PRIMITIVE2D_FLAGS eFlags = PF_DEFAULT) = 0;
		virtual HRESULT CALLBACK DrawCircle(const TPoint2 &stCoords, uint uiRadius, uint uiQuality, const TColor4 &stColor = TColor4(), E_PRIMITIVE2D_FLAGS eFlags = PF_DEFAULT) = 0;
		virtual HRESULT CALLBACK DrawEllipse(const TPoint2 &stCoords, const TPoint2 &stRadius, uint uiQuality, const TColor4 &stColor = TColor4(), E_PRIMITIVE2D_FLAGS eFlags = PF_DEFAULT) = 0;
		virtual HRESULT CALLBACK DrawPolygon(ITexture *pTexture, TVertex2 *pstVertices, uint uiVerticesCount, E_PRIMITIVE2D_FLAGS eFlags = PF_DEFAULT) = 0;
	
		// 2D Sprites		
		virtual HRESULT CALLBACK DrawSpriteS(ITexture *pTexture, const TPoint2 &stCoords, const TPoint2 &stDimensions, float fAngle = 0.f, E_EFFECT2D_FLAGS eFlags = EF_DEFAULT) = 0;
		virtual HRESULT CALLBACK DrawSpriteA(ITexture *pTexture, const TPoint2 &stCoords, const TPoint2 &stDimensions, uint uiFrameIndex, float fAngle = 0.f, E_EFFECT2D_FLAGS eFlags = EF_DEFAULT) = 0;
		virtual HRESULT CALLBACK DrawSpriteC(ITexture *pTexture, const TPoint2 &stCoords, const TPoint2 &stDimensions, const TRectF &stRect, float fAngle = 0.f, E_EFFECT2D_FLAGS eFlags = EF_DEFAULT) = 0;

		// Extra
		virtual HRESULT CALLBACK DrawTriangles(ITexture *pTexture, TVertex2 *pstVertices, uint uiVerticesCount, E_PRIMITIVE2D_FLAGS eFlags = PF_DEFAULT) = 0;
		virtual HRESULT CALLBACK DrawMesh(IMesh *pMesh, ITexture *pTexture, const TPoint2 &stCoords, const TPoint3 &stDimensions, const TPoint3 &stAxis = TPoint3(), float fAngle = 0.f, bool bClip = true, float fFovY = 90.f, E_EFFECT2D_FLAGS eFlags = EF_DEFAULT) = 0;

		//Effects
		virtual HRESULT CALLBACK SetRotationPoint(const TPoint2 &stCoords) = 0;//In texture coord system
		virtual HRESULT CALLBACK SetScale(const TPoint2 &stScale) = 0;
		virtual HRESULT CALLBACK SetColorMix(const TColor4 &stColor = TColor4()) = 0;
		virtual HRESULT CALLBACK SetBlendMode(E_EFFECT2D_BLENDING_FLAGS eMode = EBF_NORMAL) = 0;
		virtual HRESULT CALLBACK SetVerticesOffset(const TPoint2 &stCoords1, const TPoint2 &stCoords2, const TPoint2 &stCoords3, const TPoint2 &stCoords4) = 0;
		virtual HRESULT CALLBACK SetVerticesColors(const TColor4 &stColor1, const TColor4 &stColor2, const TColor4 &stColor3 = TColor4(), const TColor4 &stColor4 = TColor4()) = 0;
	};

	//Render3D interface//

	enum E_PUSH_STATES_FLAGS
	{
		PSF_ALL		= 0x00000000,
		PSF_MATRIX	= 0x00000001,
		PSF_STATES	= 0x00000002
	};

	// {5275F43A-4FF9-48b2-B88E-B2F842461AB3}
	static const GUID IID_IRender3D = 
	{ 0x5275f43a, 0x4ff9, 0x48b2, { 0xb8, 0x8e, 0xb2, 0xf8, 0x42, 0x46, 0x1a, 0xb3 } };

	class IRender3D : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK SetPerspective(float fFovAngle, float fZNear, float fZFar) = 0;
	
		virtual HRESULT CALLBACK SetColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetBlendMode(E_EFFECT2D_BLENDING_FLAGS eMode = EBF_NORMAL) = 0;
		virtual HRESULT CALLBACK ToggleAlphaTest(bool bEnabled, float fAlphaMinTreshold = 0.25) = 0;

		virtual HRESULT CALLBACK SetMatrix(const TMatrix &stMatrix, bool bMult) = 0;
		virtual HRESULT CALLBACK GetMatrix(TMatrix &stMatrix) = 0;

		virtual HRESULT CALLBACK DrawAxes(float fSize = 1.f, bool bNoDepthTest = false) = 0;

		virtual HRESULT CALLBACK PushStates(E_PUSH_STATES_FLAGS eStates = PSF_MATRIX) = 0;
		virtual HRESULT CALLBACK PopStates() = 0;

		virtual HRESULT CALLBACK GetPoint3(const TPoint2 &stPointOnScreen, TPoint3 &stResultPoint, E_GET_POINT3_FLAG eFlag = GP3F_FROM_Z_BUFFER) = 0;
		virtual HRESULT CALLBACK GetPoint2(const TPoint3 &stPoint, TPoint2 &stResultPointOnScreen) = 0;

		virtual HRESULT CALLBACK FrustumSetup() = 0;
		virtual HRESULT CALLBACK CullPoint(const TPoint3 &stCoords, bool &bCull) = 0;
		virtual HRESULT CALLBACK CullSphere(const TPoint3 &stCoords, float fRadius, bool &bCull) = 0;
		virtual HRESULT CALLBACK CullBox(const TPoint3 &stCenterCoords, const TPoint3 &stExtents, bool &bCull) = 0;

		virtual HRESULT CALLBACK CreateLight(ILight *&prLight) throw() = 0;
		virtual HRESULT CALLBACK EnableLighting(bool enable) throw() = 0;
		virtual HRESULT CALLBACK SetAmbient(const TColor4 &color) throw() = 0;
		virtual HRESULT CALLBACK GetAmbient(TColor4 &color) const throw() = 0;
	};

	//Light interface//

	enum E_LIGHT_TYPE
	{
		LT_DIRECTIONAL = 0,
		LT_POINT
	};

	// {EB73AC84-A465-4554-994D-8BED29744C9D}
	static const GUID IID_ILight = 
	{ 0xeb73ac84, 0xa465, 0x4554, { 0x99, 0x4d, 0x8b, 0xed, 0x29, 0x74, 0x4c, 0x9d } };

	class ILight: public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK SetEnabled(bool bEnabled) = 0;
		virtual HRESULT CALLBACK SetDiffuseColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetSpecularColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetPos(const TPoint3 &stPos) = 0;
		virtual HRESULT CALLBACK SetDir(const TPoint3 &stDir) = 0;
		virtual HRESULT CALLBACK SetRange(float range) = 0;
		virtual HRESULT CALLBACK SetConstantAttenuation(float attenuation) = 0;
		virtual HRESULT CALLBACK SetLinearAttenuation(float attenuation) = 0;
		virtual HRESULT CALLBACK SetQuadraticAttenuation(float attenuation) = 0;
		virtual HRESULT CALLBACK SetType(E_LIGHT_TYPE eType) = 0;
		
		virtual HRESULT CALLBACK GetEnabled(bool &bEnabled) = 0;
		virtual HRESULT CALLBACK GetDiffuseColor(TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK GetSpecularColor(TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK GetPos(TPoint3 &stPos) = 0;
		virtual HRESULT CALLBACK GetDir(TPoint3 &stDir) = 0;
		virtual HRESULT CALLBACK GetRange(float &range) = 0;
		virtual HRESULT CALLBACK GetConstantAttenuation(float &attenuation) = 0;
		virtual HRESULT CALLBACK GetLinearAttenuation(float &attenuation) = 0;
		virtual HRESULT CALLBACK GetQuadraticAttenuation(float &attenuation) = 0;
		
		virtual HRESULT CALLBACK GetType(E_LIGHT_TYPE &eType) = 0;
		virtual HRESULT CALLBACK Free() = 0;
	};

	//Texture interface//

	// {85BDDBC2-F126-4cae-946D-7D6B079E5CCE}
	static const GUID IID_ITexture = 
	{ 0x85bddbc2, 0xf126, 0x4cae, { 0x94, 0x6d, 0x7d, 0x6b, 0x7, 0x9e, 0x5c, 0xce } };

	class ITexture : public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK GetDimensions(uint &uiWidth, uint &uiHeight) = 0;
		virtual HRESULT CALLBACK SetFrameSize(uint uiFrameWidth, uint uiFrameHeight) = 0;
		virtual HRESULT CALLBACK GetFrameSize(uint &uiFrameWidth, uint &uiFrameHeight) = 0;

		virtual HRESULT CALLBACK GetGLTexIdent(uint &uiIdent) = 0;
		virtual HRESULT CALLBACK GetGLTexSize(uint &uiWidth, uint &uiHeight) = 0;
		virtual HRESULT CALLBACK GetTexCrFlags(E_TEXTURE_CREATION_FLAGS &eCrFlags) = 0;

		virtual HRESULT CALLBACK GetPixelData(ubyte *pubtData) = 0;
		virtual HRESULT CALLBACK SetPixelData(ubyte *pubtData) = 0;

		virtual HRESULT CALLBACK Draw2DSimple(int iX, int iY) = 0;
		virtual HRESULT CALLBACK Draw2D(int iX, int iY, uint uiWidth, uint uiHeight, float fAngle = 0.f, uint uiFrameIndex = 0) = 0;
		virtual HRESULT CALLBACK Draw3D(uint uiFrameIndex = 0) = 0;

		virtual HRESULT CALLBACK Bind(uint uiMTextureLayer = 0) = 0;
	};

	//Material interface//

	enum E_TEX_MAPPING
	{
		TM_STD = 0,
		TM_OBJ_SPACE = 1
	};

	enum E_NORMAL_TECHNIQUE
	{
		NT_UNPERTURBED = 0,
		NT_NORMAL_MAP_3_COMPONENT = 1,
		NT_HEIGHT_MAP_HW_DIFF = 3
	};

	enum E_PARALLAX_TECHNIQUE
	{
		PT_NONE = 0,
		PT_SPHERE = 1,
		PT_PLANE = 2
	};

	// {B6506749-BB41-423d-B6C0-982081EF63F9}
	static const GUID IID_IMaterial = 
	{ 0xb6506749, 0xbb41, 0x423d, { 0xb6, 0xc0, 0x98, 0x20, 0x81, 0xef, 0x63, 0xf9 } };

	class IMaterial: public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK SetAmbientColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetDiffuseColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetSpecularColor(const TColor4 &stColor) = 0;
		virtual HRESULT CALLBACK SetHeightScale(float scale) = 0;
		virtual HRESULT CALLBACK SetEnvAmount(float amount) = 0;
		virtual HRESULT CALLBACK SetShininess(float shininess) = 0;
		virtual HRESULT CALLBACK SetTexMappingMode(E_TEX_MAPPING eTexMapping) = 0;
		virtual HRESULT CALLBACK SetDiffuseTexture(ITexture *pTexture) = 0;
		virtual HRESULT CALLBACK SetSpecularTexture(ITexture *pTexture) = 0;
		virtual HRESULT CALLBACK SetNormalTexture(ITexture *pTexture) = 0;
		virtual HRESULT CALLBACK SetHeightTexture(ITexture *pTexture) = 0;
		virtual HRESULT CALLBACK SetEnvTexture(ITexture *pTexture) = 0;
		virtual HRESULT CALLBACK SetEnvMask(ITexture *pTexture) = 0;
		virtual HRESULT CALLBACK SetNormalTechnique(E_NORMAL_TECHNIQUE technique) = 0;
		virtual HRESULT CALLBACK SetParallaxTechnique(E_PARALLAX_TECHNIQUE technique) = 0;
		
		virtual HRESULT CALLBACK GetAmbientColor(TColor4 &stColor) const = 0;
		virtual HRESULT CALLBACK GetDiffuseColor(TColor4 &stColor) const = 0;
		virtual HRESULT CALLBACK GetSpecularColor(TColor4 &stColor) const = 0;
		virtual HRESULT CALLBACK GetHeightScale(float &scale) const = 0;
		virtual HRESULT CALLBACK GetEnvAmount(float &amount) const = 0;
		virtual HRESULT CALLBACK GetShininess(float &shininess) const = 0;
		virtual HRESULT CALLBACK GetTexMappingMode(E_TEX_MAPPING &eTexMapping) const = 0;
		virtual HRESULT CALLBACK GetDiffuseTexture(ITexture *&pTexture) const = 0;
		virtual HRESULT CALLBACK GetSpecularTexture(ITexture *&pTexture) const = 0;
		virtual HRESULT CALLBACK GetNormalTexture(ITexture *&pTexture) const = 0;
		virtual HRESULT CALLBACK GetHeightTexture(ITexture *&pTexture) const = 0;
		virtual HRESULT CALLBACK GetEnvTexture(ITexture *&pTexture) const = 0;
		virtual HRESULT CALLBACK GetEnvMask(ITexture *&pTexture) const = 0;
		virtual HRESULT CALLBACK GetNormalTechnique(E_NORMAL_TECHNIQUE &technique) const = 0;
		virtual HRESULT CALLBACK GetParallaxTechnique(E_PARALLAX_TECHNIQUE &technique) const = 0;
		
		virtual HRESULT CALLBACK Bind() const = 0;
	};

	//Shaders interfaces//
	
	enum E_UNIFORM_TYPE
	{
		UT_FLOAT1 = 0,
		UT_FLOAT2,
		UT_FLOAT3,
		UT_FLOAT4,
		UT_FLOAT2X2,
		UT_FLOAT3X3,
		UT_FLOAT4X4,
		UT_INT1,
		UT_INT2,
		UT_INT3,
		UT_INT4,
		UT_BOOL1,
		UT_BOOL2,
		UT_BOOL3,
		UT_BOOL4,
		UT_SAMPLER_1D,
		UT_SAMPLER_2D, 
		UT_SAMPLER_3D,
		UT_SAMPLER_CUBE,
		UT_SAMPLER_1D_SHADOW,
		UT_SAMPLER_2D_SHADOW,
		UT_SAMPLER_2D_RECT,
		UT_SAMPLER_2D_RECT_SHADOW
	};

	enum E_ATTRIBUTE_TYPE
	{
		AT_FLOAT1 = 0,
		AT_FLOAT2,
		AT_FLOAT3,
		AT_FLOAT4,
		AT_FLOAT2X2,
		AT_FLOAT3X3,
		AT_FLOAT4X4
	};

	// {03688B6E-A231-4125-97EA-620C3B7FCEA1}
	static const GUID IID_IUniform = 
	{ 0x3688b6e, 0xa231, 0x4125, { 0x97, 0xea, 0x62, 0xc, 0x3b, 0x7f, 0xce, 0xa1 } };

	class IUniform: public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK SetF(E_UNIFORM_TYPE eType, uint uiCount, const float *pfValue) = 0;
		virtual HRESULT CALLBACK SetI(E_UNIFORM_TYPE eType, uint uiCount, const int *piValue) = 0;
		virtual HRESULT CALLBACK SetM(E_UNIFORM_TYPE eType, uint uiCount, bool bTranspose, const float *pfValue) = 0;

		virtual HRESULT CALLBACK GetF(float *pfParams) = 0;
		virtual HRESULT CALLBACK GetI(int *piParams) = 0;

		virtual HRESULT CALLBACK Validate() = 0;
		virtual HRESULT CALLBACK Free() = 0;
	};

	// {600DE9DC-7C00-4f74-82C9-653EA6C7F2B4}
	static const GUID IID_IShader = 
	{ 0x600de9dc, 0x7c00, 0x4f74, { 0x82, 0xc9, 0x65, 0x3e, 0xa6, 0xc7, 0xf2, 0xb4 } };

	class IShader: public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK SetSource(const char *pcTxt) = 0;
		virtual HRESULT CALLBACK GetSource(char *pTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetSourceLength(uint &uiCharsCount) = 0;
		virtual HRESULT CALLBACK Compile() = 0;
	};

	// {67AD00B9-E613-43d5-8F35-1606D9A90206}
	static const GUID IID_IProgram = 
	{ 0x67ad00b9, 0xe613, 0x43d5, { 0x8f, 0x35, 0x16, 0x6, 0xd9, 0xa9, 0x2, 0x6 } };

	class IProgram: public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK AttachShader(IShader *pShader) = 0;
		virtual HRESULT CALLBACK DetachShader(E_SHADER_TYPE eShaderType) = 0;
		virtual HRESULT CALLBACK GetShader(E_SHADER_TYPE eShaderType, IShader *&pShader) const = 0;
		virtual HRESULT CALLBACK Link() = 0;
		virtual HRESULT CALLBACK Validate(bool &bValid) const = 0;

		virtual HRESULT CALLBACK GetUniformsCount(uint &uiCount) = 0;
		virtual HRESULT CALLBACK GetUniformsMaxNameLength(uint &uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetUniformInfo(uint uiIndex, uint &uiSize, E_UNIFORM_TYPE &eType, char *pcName, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetUniform(const char *pcName, IUniform *&pUniform) = 0;
		virtual HRESULT CALLBACK GetAttribInfo(uint uiIndex, uint &uiSize, E_ATTRIBUTE_TYPE &eType, char *pcName, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetAttribsCount(uint &uiCount) = 0;
		virtual HRESULT CALLBACK GetAttribsMaxNameLength(uint &uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetAttribLocation(const char *pcName, uint &uiIndex) = 0;
		virtual HRESULT CALLBACK BindAttribLocation(const char *pcName, uint uiIndex) = 0;
		virtual HRESULT CALLBACK Bind() = 0;
	};

	//BitmapFont interface//

	// {0B03E8D7-23A3-4c79-9E82-5BC6E50E1EBA}
	static const GUID IID_IBitmapFont = 
	{ 0xb03e8d7, 0x23a3, 0x4c79, { 0x9e, 0x82, 0x5b, 0xc6, 0xe5, 0xe, 0x1e, 0xba } };

	class IBitmapFont : public IEngBaseObj
	{
	public: 	
		virtual HRESULT CALLBACK GetTexture(ITexture *&prTexture) = 0;
		virtual HRESULT CALLBACK SetScale(float fScale) = 0;
		virtual HRESULT CALLBACK GetScale(float &fScale) = 0;
		virtual HRESULT CALLBACK GetTextDimensions(const char *pcTxt, uint &uiWidth, uint &uiHeight) = 0;
		virtual HRESULT CALLBACK Draw2D(int iX, int iY, const char *pcTxt, const TColor4 &stColor = TColor4(), int iAngle = 0, bool bVerticesColors = false) = 0;
		virtual HRESULT CALLBACK Draw3D(const char *pcTxt) = 0;
	};

	//3D Objects interfaces//
	
	//Mesh interface//

	// {85E360A8-07B3-4f22-AA29-07C7FC7C6893}
	static const GUID IID_IMesh = 
	{ 0x85e360a8, 0x7b3, 0x4f22, { 0xaa, 0x29, 0x7, 0xc7, 0xfc, 0x7c, 0x68, 0x93 } };

	class IMesh : public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK Draw() = 0;
		virtual HRESULT CALLBACK GetCenter(TPoint3 &stCenter) = 0;
		virtual HRESULT CALLBACK GetExtents(TPoint3 &stExtents) = 0;
		virtual HRESULT CALLBACK GetTrianglesCount(uint &uiTriCnt) = 0;
		virtual HRESULT CALLBACK GetGeometryInfo(uint &uiVertsCount, uint &uiFacesCount, uint &uiDataSize, E_MESH_CREATION_FLAGS &eCreationFlags) = 0;
		/*Format x,y,z*vertex_count, nx,ny,nz*vertex_count s,q*vertex_count tx,ty,tz,bx,by,bz*vertex_count int16*uiFacesCount*/
		virtual HRESULT CALLBACK GetGeometry(ubyte *pubtData) = 0;
		virtual HRESULT CALLBACK SetGeometry(ubyte *pubtData) = 0;
	};

	//Skeleton xform interface//

	// {1D12C62F-9974-4219-8F12-DA92A4CC259F}
	static const GUID IID_ISkeletonXform = 
	{ 0x1d12c62f, 0x9974, 0x4219, { 0x8f, 0x12, 0xda, 0x92, 0xa4, 0xcc, 0x25, 0x9f } };

	class ISkeletonXform: public IEngBaseObj
	{
	public:
	};

	//Model interface//

	// {6107C296-FC07-48d1-B6A7-F88CC2DAE897}
	static const GUID IID_IModel = 
	{ 0x6107c296, 0xfc07, 0x48d1, { 0xb6, 0xa7, 0xf8, 0x8c, 0xc2, 0xda, 0xe8, 0x97 } };

	class IModel : public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK MeshsCount(uint &uiCount) = 0;
		virtual HRESULT CALLBACK GetMesh(uint uiIdx, IMesh *&prMesh) = 0;
		virtual HRESULT CALLBACK Draw(float fFrameIdx) = 0;
	};

	//Postprocess interface//

	// {DC6E4812-6B06-4de8-9DEF-2A13740BC45E}
	static const GUID IID_IPostprocess = 
	{ 0xdc6e4812, 0x6b06, 0x4de8, { 0x9d, 0xef, 0x2a, 0x13, 0x74, 0xb, 0xc4, 0x5e } };

	class IPostprocess: public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK Free() = 0;

		virtual HRESULT CALLBACK SetTargets(ITexture *pSrc, ITexture *pDst) = 0;
		virtual HRESULT CALLBACK SetBlurAmount(float fBlur) = 0;
		virtual HRESULT CALLBACK SetBloomAmount(float fBloom) = 0;
		virtual HRESULT CALLBACK SetBloomThreshold(float fThreshold) = 0;
		virtual HRESULT CALLBACK ToggleMonochrome(bool bEnable) = 0;
		virtual HRESULT CALLBACK Perform() = 0;
	};

//Input Subsystem//
	
	enum E_INPUT_CONFIGURATION_FLAGS
	{
		ICF_DEFAULT					= 0x00000000,
		ICF_EXCLUSIVE				= 0x00000001,
		ICF_BLOCK_WINKEYS			= 0x00000002,
		ICF_HIDE_CURSOR				= 0x00000004,
		ICF_CURSOR_BEYOND_SCREEN	= 0x00000008
	};

	// {64DAAF7F-F92C-425f-8B92-3BE40D8C6666}
	static const GUID IID_IInput = 
	{ 0x64daaf7f, 0xf92c, 0x425f, { 0x8b, 0x92, 0x3b, 0xe4, 0xd, 0x8c, 0x66, 0x66 } };

	class IInput : public IEngineSubSystem
	{
	public:
		virtual HRESULT CALLBACK Configure(E_INPUT_CONFIGURATION_FLAGS eFlags = ICF_DEFAULT) = 0;
	
		virtual HRESULT CALLBACK GetMouseStates(TMouseStates &stMStates) = 0;
		virtual HRESULT CALLBACK GetKey(E_KEYBOARD_KEY_CODES eKeyCode, bool &bPressed) = 0;
		virtual HRESULT CALLBACK GetKeyName(E_KEYBOARD_KEY_CODES eKeyCode, uchar &cASCIICode) = 0;

		virtual HRESULT CALLBACK BeginTextInput(char* pcBuffer, uint uiBufferSize) = 0;
		virtual HRESULT CALLBACK EndTextInput() = 0;
		
		virtual HRESULT CALLBACK GetJoystickCount(uint &uiCount) = 0;
		virtual HRESULT CALLBACK GetJoystickStates(uint uiJoyId, TJoystickStates &stJoyStates) = 0;
		virtual HRESULT CALLBACK GetJoystickButtonPressed(uint uiJoyId, uint uiNumber, bool &bPressed) = 0; // 128 buttons [num 0..127]	
	};

//Sound SubSystem interfaces//

	// {054C07EE-2724-42f2-AC2B-E81FCF5B4ADA}
	static const GUID IID_ISound = 
	{ 0x54c07ee, 0x2724, 0x42f2, { 0xac, 0x2b, 0xe8, 0x1f, 0xcf, 0x5b, 0x4a, 0xda } };

	class ISound : public IEngineSubSystem
	{
	public:
		virtual HRESULT CALLBACK SetMasterVolume(uint uiVolume) = 0;
		virtual HRESULT CALLBACK PauseAllChannels(bool bPaused) = 0;
		virtual HRESULT CALLBACK StopAllChannels() = 0;
		virtual HRESULT CALLBACK SetMaxChannelsCount(uint uiCount) = 0;
		virtual HRESULT CALLBACK SetListnerPosition(const TPoint3 &stCoords) = 0;
		virtual HRESULT CALLBACK GetListnerPosition(TPoint3 &stCoords) = 0;
		virtual HRESULT CALLBACK SetListnerOrientation(const TPoint3 &stDir, const TPoint3 &stUp) = 0;
		virtual HRESULT CALLBACK GetListnerOrientation(TPoint3 &stDir, TPoint3 &stUp) = 0;
	};

	//SoundSample interface//

	enum E_SOUND_CHANNEL_EFFECTS
	{
		SCE_NONE		= 0x00000000,
		SCE_CHORUS 		= 0x00000001,
		SCE_COMPRESSOR 	= 0x00000002,
		SCE_DISTORTION 	= 0x00000004,
		SCE_ECHO 		= 0x00000008,
		SCE_FLANGER 	= 0x00000010,
		SCE_GARGLE 		= 0x00000020,
		SCE_REVERB 		= 0x00000040
	};

	// {DE6F7CDD-8262-445c-8D20-68E3324D99A6}
	static const GUID IID_ISoundChannel = 
	{ 0xde6f7cdd, 0x8262, 0x445c, { 0x8d, 0x20, 0x68, 0xe3, 0x32, 0x4d, 0x99, 0xa6 } };

	class ISoundChannel : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK PlayOrPause() = 0;
		virtual HRESULT CALLBACK Stop() = 0;
		virtual HRESULT CALLBACK IsPlaying(bool &bIsPlaying) = 0;
		virtual HRESULT CALLBACK SetVolume(uint uiVolume) = 0; //from 0 to 100
		virtual HRESULT CALLBACK GetVolume(uint &uiVolume) = 0;
		virtual HRESULT CALLBACK SetPan(int iPan) = 0; //from -100 to 100
		virtual HRESULT CALLBACK GetPan(int &iPan) = 0;
		virtual HRESULT CALLBACK SetFrequency(uint32 uiFreq) = 0;//from 10 to 10000
		virtual HRESULT CALLBACK GetFrequency(uint32 &uiFreq) = 0;
		virtual HRESULT CALLBACK SetPosition(const TPoint3 &stCoords) = 0;
		virtual HRESULT CALLBACK GetPosition(TPoint3 &stCoords) = 0;
		virtual HRESULT CALLBACK SetEffects(E_SOUND_CHANNEL_EFFECTS eFlags) = 0;
		virtual HRESULT CALLBACK Unaquire() = 0;
	};
	
	enum E_SOUND_SAMPLE_PARAMS
	{
		SSP_NONE			= 0x00000000,
		SSP_LOOP			= 0x00000001,
		SSP_CONTROL_3D		= 0x00000002,
		SSP_ALLOW_EFFECTS	= 0x00000004

	};

	// {30DD8C94-D3FA-40cf-9C49-649211424919}
	static const GUID IID_ISoundSample = 
	{ 0x30dd8c94, 0xd3fa, 0x40cf, { 0x9c, 0x49, 0x64, 0x92, 0x11, 0x42, 0x49, 0x19 } };

	class ISoundSample : public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK Play() = 0;
		virtual HRESULT CALLBACK PlayEx(ISoundChannel *&pSndChnl, E_SOUND_SAMPLE_PARAMS eFlags = SSP_NONE) = 0; //pSndChnl must be checked on nul
	};

	//Music interface//

	// {81F1E67B-3FEB-4ab1-9AD2-D27C4E662164}
	static const GUID IID_IMusic = 
	{ 0x81f1e67b, 0x3feb, 0x4ab1, { 0x9a, 0xd2, 0xd2, 0x7c, 0x4e, 0x66, 0x21, 0x64 } };

	class IMusic : public IEngBaseObj
	{
	public:
		virtual HRESULT CALLBACK Play(bool bLooped = true) = 0;
		virtual HRESULT CALLBACK Pause(bool bPaused) = 0;
		virtual HRESULT CALLBACK Stop() = 0;
		virtual HRESULT CALLBACK IsPlaying(bool &bIsPlaying) = 0;
		virtual HRESULT CALLBACK SetVolume(uint uiVolume) = 0;
		virtual HRESULT CALLBACK GetVolume(uint &uiVolume) = 0;
		virtual HRESULT CALLBACK SetCurrentPosition(uint uiPos) = 0;
		virtual HRESULT CALLBACK GetCurrentPosition(uint &uiPos) = 0;
		virtual HRESULT CALLBACK GetLength(uint &uiLength) = 0;
	};

//FileSystem interfaces//

	class IFileSystem;

	// {4850286F-4770-4bcf-A90A-33D7BE41E686}
	static const GUID IID_IMainFileSystem = 
	{ 0x4850286f, 0x4770, 0x4bcf, { 0xa9, 0xa, 0x33, 0xd7, 0xbe, 0x41, 0xe6, 0x86 } };

	class IMainFileSystem : public IEngineSubSystem
	{
	public:
		virtual HRESULT CALLBACK LoadFile(const char* pcFileName, IFile *&prFile) = 0;// c:\data.zip|img.jpg
		virtual HRESULT CALLBACK GetVirtualFileSystem(const char *pcVFSExtension/*NULL to get HDD file system*/, IFileSystem *&prVFS) = 0;
		virtual HRESULT CALLBACK RegisterVirtualFileSystem(const char* pcVFSExtension, const char *pcDiscription, IFileSystem *pVFS, void (CALLBACK *pDeleteCallback)(void *pParametr, IFileSystem *pVFS), void *pParametr = NULL) = 0;
		virtual HRESULT CALLBACK UnregisterVirtualFileSystem(const char* pcVFSExtension) = 0;
		virtual HRESULT CALLBACK GetRegisteredVirtualFileSystems(char* pcTxt, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetVirtualFileSystemDescription(const char* pcVFSExtension, char* pcTxt, uint uiCharsCount) = 0;
	};

	enum E_FIND_FLAGS
	{
		FF_RECURSIVE = 1
	};

	enum E_FILE_SYSTEM_OPEN_FLAGS
	{
		FSOF_READ	= 0x00000001,	
		FSOF_WRITE	= 0x00000002,	
		FSOF_TRUNK	= 0x00000004,	
		FSOF_BINARY	= 0x00000008	
	};

	enum E_FILE_SYSTEM_SEEK_FLAG
	{
		FSSF_BEGIN = 0,
		FSSF_CURRENT,
		FSSF_END
	};

	//File interface//

	// {AE6E8AE7-3E5B-4bc4-A512-42E1CF1DF005}
	static const GUID IID_IFile = 
	{ 0xae6e8ae7, 0x3e5b, 0x4bc4, { 0xa5, 0x12, 0x42, 0xe1, 0xcf, 0x1d, 0xf0, 0x5 } };

	class IFile : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK Read(void *pBuffer, uint uiCount, uint &uiRead) = 0;
		virtual HRESULT CALLBACK Write(const void *pBuffer, uint uiCount, uint &uiWritten) = 0;
		virtual HRESULT CALLBACK Seek(uint uiOffset, E_FILE_SYSTEM_SEEK_FLAG eWay, uint &uiPosition) = 0;
		virtual HRESULT CALLBACK GetSize(uint &uiSize) = 0;
		virtual HRESULT CALLBACK IsOpen(bool &bOpened) = 0;
		virtual HRESULT CALLBACK GetName(char *pcName, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK GetPath(char *pcPath, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK Free() = 0;
	};

	//FileIterator interface//

	// {5D73F249-0E74-4cc5-9646-270CB1E22750}
	static const GUID IID_IFileIterator = 
	{ 0x5d73f249, 0xe74, 0x4cc5, { 0x96, 0x46, 0x27, 0xc, 0xb1, 0xe2, 0x27, 0x50 } };

	class IFileIterator : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK FileName(char *pcName, uint uiCharsCount) = 0;
		virtual HRESULT CALLBACK Next() = 0;
		virtual HRESULT CALLBACK Free() = 0;
	};

	//FileSystem interface//

	// {2DAE578E-9636-4fae-BABB-7D835EEA7518}
	static const GUID IID_IFileSystem = 
	{ 0x2dae578e, 0x9636, 0x4fae, { 0xba, 0xbb, 0x7d, 0x83, 0x5e, 0xea, 0x75, 0x18 } };

	class IFileSystem : public IDGLE2_Base
	{
	public:
		virtual HRESULT CALLBACK OpenFile(const char* pcName, E_FILE_SYSTEM_OPEN_FLAGS eFlags, IFile *&prFile) = 0;	//если передан только путь "C:\MyFolder\" то создаст папку
		virtual HRESULT CALLBACK DeleteFile(const char* pcName) = 0; //≈сли передан только путь то удалит папку
		virtual HRESULT CALLBACK FileExists(const char* pcName, bool &bExists) = 0;//если передан только путь, то провер€ет существование папки
		virtual HRESULT CALLBACK Find(const char* pcMask, E_FIND_FLAGS eFlags, IFileIterator *&prIterator) = 0;
	};

}// end of namespace

	enum E_GET_ENGINE_FLAGS
	{
		GEF_DEFAULT				= 0x00000000,	
		GEF_FORCE_SINGLE_THREAD	= 0x00000001,	
		GEF_FORCE_NO_LOG_FILE	= 0x00000002,
		GEF_FORCE_QUIT			= 0x00000004
	};

//Include one of these defines once to main CPP file//

#define ENG_STATIC_FUNC \
extern bool CALLBACK CreateEngine(DGLE2::IEngineCore *&pEngineCore, E_GET_ENGINE_FLAGS eFlags = GEF_DEFAULT, DGLE2::ubyte ubtSDKVer = _DGLE2_SDK_VER_);\
extern bool	CALLBACK FreeEngine(DGLE2::IEngineCore *pEngineCore);

#define ENG_DYNAMIC_FUNC \
extern"C" bool (CALLBACK *pCreateEngine)(DGLE2::IEngineCore *&pEngineCore, E_GET_ENGINE_FLAGS eFlags, DGLE2::ubyte ubtSDKVer) = NULL;\
extern"C" bool (CALLBACK *pFreeEngine)(DGLE2::IEngineCore *pEngineCore) = NULL;\
HMODULE hServer = NULL;\
bool CreateEngine(DGLE2::IEngineCore *&pEngineCore, E_GET_ENGINE_FLAGS eFlags = GEF_DEFAULT)\
{\
	if(pCreateEngine == NULL)\
		return false;\
	return (*pCreateEngine)(pEngineCore, eFlags, _DGLE2_SDK_VER_);\
}\
bool FreeEngine(DGLE2::IEngineCore *pEngineCore = NULL, bool bFreeDLL = true)\
{\
	if(pEngineCore)\
		(*pFreeEngine)(pEngineCore);\
	if(bFreeDLL && hServer)\
	{\
		FreeLibrary(hServer);\
		hServer = NULL;\
		pCreateEngine = NULL;\
		pFreeEngine = NULL;\
	}\
	return true;\
}\
bool GetEngine(const char *pcDllFileName, DGLE2::IEngineCore *&pEngineCore, E_GET_ENGINE_FLAGS eFlags = GEF_DEFAULT)\
{\
	if(hServer == NULL)\
	{\
		pEngineCore = NULL;\
		if(hServer == NULL)\
		{\
			hServer = ::LoadLibraryA(pcDllFileName);\
			if(hServer == NULL) return false;\
		}\
		if(pCreateEngine == NULL && pFreeEngine == NULL)\
		{\
			pCreateEngine = reinterpret_cast<bool (CALLBACK *)(DGLE2::IEngineCore *&, E_GET_ENGINE_FLAGS, DGLE2::ubyte)>\
				(::GetProcAddress(hServer,("CreateEngine")));\
			pFreeEngine = reinterpret_cast<bool (CALLBACK *)(DGLE2::IEngineCore *)>\
				(::GetProcAddress(hServer,("FreeEngine")));\
			if(pCreateEngine == NULL || pFreeEngine == NULL)\
			{\
				FreeLibrary(hServer);\
				hServer = NULL;\
				return false;\
			}\
		}\
	}\
	if(hServer) return CreateEngine(pEngineCore, eFlags);\
	return false;\
}

#endif//DGLE2_HEADER