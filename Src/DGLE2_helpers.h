/**
\file		DGLE2_helpers.h
\author		Korotkov Andrey aka DRON
\version	Beta 2
\date		17.03.2011 (c)Korotkov Andrey

\brief		Additional engine defines and templates.

This header is a part of DGLE2_SDK.
*/

#ifndef _DGLE2_HELPERS_H
#define _DGLE2_HELPERS_H

#include "DGLE2.h"
#include <assert.h>

namespace DGLE2
{

//Macroses//

/** Macros checks HRESULT value and throws exception of HRESULT type if value is failed.
	\param[in] hr HRESULT value to be checked.
	\see FAILED
*/
#define CHECK_HR(hr)\
{HRESULT hr_ = hr; if(FAILED(hr_)) throw hr_;}

/** \def PARANOIC_CHECK_HR(hr) Macros checks HRESULT value and drop assertion on any value except S_OK.
	Useful for debugging. In release macros do nothing. Always returns S_OK.
	\param[in] hr HRESULT value to be checked.
	\code
	PARANOIC_CHECK_HR(pEngineCore->StartEngine());
	\endcode
*/
#ifdef _DEBUG
#	define PARANOIC_CHECK_HR(hr) assert(hr == S_OK), S_OK
#else
#	define PARANOIC_CHECK_HR(hr) hr
#endif

	/** Contains templates of function to make it easy to retrieve engine subsystem or resource. */
	namespace get_helpers
	{
		template<typename Enum, Enum enumeration, class IBase, class IObject, class IProvider, HRESULT (CALLBACK IProvider::*function)(Enum, IBase *&)>
		inline void Get(IProvider *provider, IObject *&object)
		{
			PARANOIC_CHECK_HR((provider->*function)(enumeration, reinterpret_cast<IBase *&>(object)));
			object = static_cast<IObject *>(reinterpret_cast<IBase *>(object));
		}

		//GetSubsystem helpers//
		
		template<E_ENGINE_SUB_SYSTEM enumeration, class IObject>
		inline void GetSubsystem(IEngineCore *pEngineCore, IObject *&object)
		{
			Get<E_ENGINE_SUB_SYSTEM, enumeration, IEngineSubSystem, IObject, IEngineCore, &IEngineCore::GetSubSystem>(pEngineCore, object);
		}

		template<class IObject>
		inline void Get(IEngineCore *pEngineCore, IObject *&object);

		template<>
		inline void Get(IEngineCore *pEngineCore, IRender *&render)
		{
			GetSubsystem<ESS_RENDER>(pEngineCore, render);
		}

		template<>
		inline void Get(IEngineCore *pEngineCore, IInput *&input)
		{
			GetSubsystem<ESS_INPUT>(pEngineCore, input);
		}

		template<>
		inline void Get(IEngineCore *pEngineCore, ISound *&sound)
		{
			GetSubsystem<ESS_SOUND>(pEngineCore, sound);
		}

		template<>
		inline void Get(IEngineCore *pEngineCore, IResourceManager *&resMan)
		{
			GetSubsystem<ESS_RESOURCE_MANAGER>(pEngineCore, resMan);
		}

		template<>
		inline void Get(IEngineCore *pEngineCore, IMainFileSystem *&mainFS)
		{
			GetSubsystem<ESS_FILE_SYSTEM>(pEngineCore, mainFS);
		}

		//GetDefaultResource helpers//

		template<E_ENG_OBJ_TYPE enumeration, class IObject>
		inline void GetDefaultResource(IResourceManager *pResMan, IObject *&object)
		{
			Get<E_ENG_OBJ_TYPE, enumeration, IEngBaseObj, IObject, IResourceManager, &IResourceManager::GetDefaultResource>(pResMan, object);
		}

		template<class IObject>
		inline void Get(IResourceManager *pResMan, IObject *&object);

		template<>
		inline void Get(IResourceManager *pResMan, ITexture *&texture)
		{
			GetDefaultResource<EOT_TEXTURE>(pResMan, texture);
		}

		template<>
		inline void Get(IResourceManager *pResMan, IMesh *&mesh)
		{
			GetDefaultResource<EOT_MESH>(pResMan, mesh);
		}

		template<>
		inline void Get(IResourceManager *pResMan, IBitmapFont *&bitmapFont)
		{
			GetDefaultResource<EOT_BITMAP_FONT>(pResMan, bitmapFont);
		}
 
	}

/** \def IDGLE2_BASE_IMPLEMENTATION(interface_name) Macros inserts realisation of IDGLE2_Base interface into class body.
	Can be used with interfaces inherited from IDGLE2_Base.
	\param[in] interface_name Name of the interface inheritance from IDGLE2_Base.
	\note It also inserts IUnknown implementation for Windows builds.
	\see IUNKNOWN_IMPLEMENTATION
*/

/** \def IDGLE2_BASE_IMPLEMENTATION1(interface1_name, interface2_name) Same is IDGLE2_BASE_IMPLEMENTATION but for inheritance chain with two interfaces.
	Can be used with interfaces inherited from IDGLE2_Base and some other interface.
	\param[in] interface1_name Name of the last interface in the inheritance chain.
	\param[in] interface2_name Name of the second interface in the inheritance chain.
	\see IDGLE2_BASE_IMPLEMENTATION
*/

/** \def IUNKNOWN_IMPLEMENTATION(interface_name) Macros inserts realisation of IUnknown interface into class body.
	\param[in] interface_name Name of the interface inheritance from IUnknown.
	\note For non Windows builds inserts nothing.
*/

//Implementation macroses//

#ifndef DGLE2_USE_COM

#define IDGLE2_BASE_IMPLEMENTATION(interface_name) HRESULT CALLBACK GetGUID(GUID &guid) {guid = IID_##interface_name;return S_OK;}
#define IDGLE2_BASE_IMPLEMENTATION1(interface1_name, interface2_name) IDGLE2_BASE_IMPLEMENTATION(interface1_name)
#define IUNKNOWN_IMPLEMENTATION(interface_name)

#else//DGLE2_USE_COM

#define IDGLE2_BASE_IMPLEMENTATION(interface_name) \
	HRESULT CALLBACK GetGUID(GUID &guid)\
	{\
		guid = IID_##interface_name;\
		return S_OK;\
	}\
	HRESULT CALLBACK QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject)\
	{\
		*ppvObject = NULL;\
		if(::memcmp(&riid,&__uuidof(IUnknown),sizeof(GUID)) == 0) \
		*ppvObject = static_cast<IUnknown *>(this);\
		else if(::memcmp(&riid,&IID_##interface_name,sizeof(GUID)) == 0) \
		*ppvObject = static_cast<interface_name *>(this);\
		else return E_NOINTERFACE;\
		return S_OK;\
	}\
	ULONG CALLBACK AddRef(){return 1;}\
	ULONG CALLBACK Release(){return 1;}

#define IDGLE2_BASE_IMPLEMENTATION1(interface1_name, interface2_name) \
	HRESULT CALLBACK GetGUID(GUID &guid)\
	{\
		guid = IID_##interface1_name;\
		return S_OK;\
	}\
	HRESULT CALLBACK QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject)\
	{\
		*ppvObject = NULL;\
		if(::memcmp(&riid,&__uuidof(IUnknown),sizeof(GUID)) == 0) \
		*ppvObject = static_cast<IUnknown *>(this);\
		else if(::memcmp(&riid,&IID_##interface1_name,sizeof(GUID)) == 0) \
		*ppvObject = static_cast<interface1_name *>(this);\
		else if(::memcmp(&riid,&IID_##interface2_name,sizeof(GUID)) == 0) \
		*ppvObject = static_cast<interface2_name *>(this);\
		else return E_NOINTERFACE;\
		return S_OK;\
	}\
	ULONG CALLBACK AddRef(){return 1;}\
	ULONG CALLBACK Release(){return 1;}

#define IUNKNOWN_IMPLEMENTATION(interface_name) \
	HRESULT CALLBACK QueryInterface(REFIID riid, void __RPC_FAR *__RPC_FAR *ppvObject)\
	{\
		*ppvObject = NULL;\
		if(::memcmp(&riid,&__uuidof(IUnknown),sizeof(GUID)) == 0)\
		*ppvObject = static_cast<IUnknown *>(this);\
		else if(::memcmp(&riid,&__uuidof(interface_name),sizeof(GUID)) == 0)\
		{*ppvObject = static_cast<interface_name *>(this); AddRef();}\
		else return E_NOINTERFACE;\
		return S_OK;\
	}\
	ULONG CALLBACK AddRef() { return 1; }\
	ULONG CALLBACK Release() { return 1; }

#endif
}

#endif//_DGLE2_HELPERS_H