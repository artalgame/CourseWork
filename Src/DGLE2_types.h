/**
\file		DGLE2_types.h
\author		Korotkov Andrey aka DRON
\version	Beta 2
\date		17.03.2011 (c)Korotkov Andrey

\brief		Engine types definition header.

This header is a part of DGLE2_SDK.

\warning	Don't include this header directly, include "DGLE2.h" instead.
\see		DGLE2.h
*/

#ifndef DGLE2_TYPES
#define DGLE2_TYPES

#ifndef DGLE2_HEADER
#error Don't include this header directly, include "DGLE2.h" instead.
#endif

#include <Math.h>
#include <stack>
#include <assert.h>

namespace DGLE2
{

//Some standart types redifinition//

	//signed//
	typedef short int			int16;
	typedef long int			int32;
	typedef char				byte;
	typedef wchar_t				wchar;
	
	//unsigned//
	typedef unsigned int		uint;
	typedef unsigned short int	uint16;
	typedef unsigned long int	uint32;
	typedef unsigned char		ubyte;
	typedef ubyte				uchar;

	//int64//
#if defined(PLATFORM_WINDOWS)

	typedef __int64				int64;
	typedef unsigned __int64	uint64;

#else//PLATFORM_WINDOWS

	typedef signed long long	int64;
	typedef unsigned long long	uint64;

#endif

	//HRESULT//
#ifndef PLATFORM_WINDOWS

	/** Engine interface unique identifier. 
		Every engine interface must have it's own GUID.
	*/
	struct GUID
	{
		ui32	Data1;
		ui16	Data2;
		ui16	Data3;
		ubyte	Data4[8];
	};

	/** Default return type for all DGLE2 methods. 
		Every engine interface method returnes HRESULT as result.
		HRESULT must be one of these types S_OK, S_FALSE, E_FAIL, E_INVALIDARG or E_ABORT.
		\note Engine suppresses a lot of errors and keeps all things stable, so it is not necessary to check every methods result.
		\see SUCCEEDED, FAILED, CHECK_HR, PARANOIC_CHECK_HR, S_OK, S_FALSE, E_FAIL, E_INVALIDARG, E_ABORT
	*/
	typedef int32 HRESULT;

//HRESULT return values//

/** Return value of HRESULT type. Method returns S_OK when all of its routines were done succesfully. */
#define S_OK			0

/** Return value of HRESULT type. Method returns S_FALSE when most of its routines were done succesfully but some minor errors occured. */
#define S_FALSE			1

/** Return value of HRESULT type. Method returns E_FAIL when unspecified error occured. */
#define E_FAIL			0x80004005

/** Return value of HRESULT type. Method returns E_INVALIDARG when one or more arguments are invalid. */
#define E_INVALIDARG	0x80070057

/** Return value of HRESULT type. Method returns E_ABORT when operation aborted due to errors of some other function. */
#define E_ABORT			0x80004004

/** Macros to check HRESULT value. Returns true if value is S_OK or S_FALSE and false otherwise.
	\param[in] hr HRESULT value to be checked.
	\code
	if(SUCCEEDED(pEngineCore->InitializeEngine(NULL,"Test"))) pEngineCore->StartEngine();
	\endcode
*/
#define SUCCEEDED(hr) (((HRESULT)(hr)) >= 0)

/** Macros to check HRESULT value. Returns true for any value except S_OK and S_FALSE.
	\param[in] hr HRESULT value to be checked.
	\code
	if(FAILED(pEngineCore->InitializeEngine(NULL,"Test"))) Exit(1);
	\endcode
*/
#define FAILED(hr) (((HRESULT)(hr)) < 0)

#endif

#if defined(STRUCT_ALIGNMENT_1) && defined(PLATFORM_WINDOWS)
#pragma pack( push, 1 )
#endif

//Platform depended types//

#ifdef PLATFORM_WINDOWS

	typedef HWND TWinHandle;

	/** Structure with WinAPI based message information. 
		\see IEvWinMessage
	 */
	struct TWinMessage
	{
		UINT	message;	/**< WinAPI message identifier. */
		WPARAM	wParam;		/**< Message first parametr. */
		LPARAM	lParam;		/**< Message second parametr. */
		
		TWinMessage():message(0),wParam(0),lParam(0){}

		TWinMessage(UINT msg, WPARAM wpm, LPARAM lpm)
		{
			message = msg;
			wParam	= wpm;
			lParam	= lpm;
		}
	};

#endif

//Engine types definition//

	/** Flags of TEngWindow structure that determines the behavior of main engine window. */
	enum E_ENGINE_WINDOW_FLAGS
	{
		EWF_DEFAULT				= 0x00000000,/**< This flag is suitable in most cases. */
		EWF_ALLOW_SIZEING		= 0x00000001,/**< User can resize engine window arbitrarily */
		EWF_TOPMOST				= 0x00000002,/**< Engine window will be always on top. */
		EWF_DONT_HOOK_MLOOP		= 0x00000004,/**< If flag set and engine doesn't owns window, host applications main loop will not be hooked. User must call window repaint manually. */
		EWF_DONT_HOOK_ROOT_WIN	= 0x00000008,/**< If flag set and engine doesn't owns window, main host application window will not be hooked. User must redirect windows messages manually.*/
		EWF_RESTRICT_ALT_ENTER	= 0x00000010,/**< Switching between fullscreen and windowed modes by pressing "Alt-Enter" will be restricted. */
		EWF_RESTRICT_CONSOLE	= 0x00000020 /**< Restricts calling engine console window by pressing "~" key. */
	};

	/** Describes the parameters of the main engine window and its behavior. 
		\see IEngineCore::InitializeEngine
	 */
	struct TEngWindow
	{	
		uint	uiWidth;			/**< Resolution width of client area. */
		uint	uiHeight;			/**< Resolution height of client area. */
		bool	bFullScreen;		/**< Switch to fullscreen mode or not. */
		bool	bVSync;				/**< Enable or not vertical synchronization(triple buffering). */
		uint	uiSamplesCount;		/**< Fullscreen Anti-Aliasing samples count. The value must be a power of two (1, 2, 4, 8 or 16). \note 1 - disabled. */
		E_ENGINE_WINDOW_FLAGS
				stFlags;			/**< Additional settings. */

		TEngWindow()
		{
			uiWidth			= 800;
			uiHeight		= 600;
			bFullScreen		= false;
			bVSync			= false;
			uiSamplesCount	= 1;
			stFlags			= EWF_DEFAULT;
		}

		TEngWindow(uint width, uint height, bool fscreen, bool vsync = false, int samples = 1, E_ENGINE_WINDOW_FLAGS flags = EWF_DEFAULT)
		{
			uiWidth			= width;
			uiHeight		= height;
			bFullScreen		= fscreen;
			bVSync			= vsync;
			uiSamplesCount	= samples;
			stFlags			= flags;
		}
	};

	/** Describes user hardware and operating system. 
		\see IEngineCore::GetSystemInfo
	 */
	struct TSystemInfo
	{	
		char cOSName[128];			/**< String with operating system discription. */
		char cCPUName[128];			/**< String with CPU discription. */
		uint uiCPUCount;			/**< Number of CPUs on host system. */
		uint uiCPUFreq;				/**< Real CPU frequency in MHz. */
		uint uiRAMTotal;			/**< Ammount of RAM in system. */
		uint uiRAMAvailable;		/**< Ammount of free RAM in system on engine start. */
		char cVideocardName[128];	/**< String with primary videocard discription. */
		uint uiVideocardCount;		/**< Number of videocards in system. */
		uint uiVideocardRAM;		/**< Ammount of video RAM in system. */
	};

	/** Describes engine plugin information. 
		\see IPlugin
	 */
	struct TPluginInfo
	{
		ubyte btPluginSDKVersion;	/**< Version of SDK with wich plugin was build. \warning This value MUST BE set to "_DGLE2_PLUGIN_SDK_VER_"! */
		char  cName[128];		 	/**< String with plugin name. */
		char  cVersion[64];		 	/**< String with plugin version. */
		char  cVendor[128];		 	/**< String with name of vendor(developer). */
		char  cDiscription[256]; 	/**< String with plugin discription. */
		
		TPluginInfo()
		{
			btPluginSDKVersion = _DGLE2_PLUGIN_SDK_VER_;
		}

	};

	/** Describes color in engine. Color is four component based. Each component is float, value can vary from 0.0 to 1.0.*/
	struct TColor4
	{
		union
		{
			struct
			{
				float	r, g, b, a;
			};
			float rgba[4];
		};

		typedef float (&ref)[4];
		typedef const float (&cref)[4];

		inline TColor4():r(1.f), g(1.f), b(1.f), a(1.f){}
		inline TColor4(int color, ubyte alpha):
			r(GetRValue(color)/255.f),
			g(GetGValue(color)/255.f),
			b(GetBValue(color)/255.f),
			a((float)(alpha/255.f))
		{}
		inline TColor4(uint uiRGBA):
			r((float)((uiRGBA >> 24) & 0xff)/0xff),
			g((float)((uiRGBA >> 16) & 0xff)/0xff),
			b((float)((uiRGBA >> 8) & 0xff)/0xff),
			a((float)(uiRGBA & 0xff)/0xff)
		{}
		inline TColor4(ubyte ubR, ubyte ubG, ubyte ubB, ubyte ubA)
		{
			SetColorB(ubR, ubG, ubB, ubA);
		}
		inline TColor4(cref rgba)
		{
			memcpy(TColor4::rgba, rgba, sizeof rgba);
		}

		inline void SetColorF(float fR, float fG, float fB, float fA)
		{
			r = fR; g = fG; b = fB; a = fA;
		}
		
		inline void SetColorB(ubyte ubR, ubyte ubG, ubyte ubB, ubyte ubA)
		{
			r = ubR/255.f; g = ubG/255.f; b = ubB/255.f; a = ubA/255.f;
		}
		
		inline uint32 ColorRGB()
		{
			return RGB(255*r, 255*g, 255*b);
		}

		inline operator uint32()
		{
			return RGB(255*r, 255*g, 255*b);
		}

		inline operator ref()
		{
			return rgba;
		}

		inline operator cref() const
		{
			return rgba;
		}
	};

	/** Describes point coordinates in 2D space. */
	struct TPoint2
	{
		float x, y;

		inline TPoint2():x(0.f), y(0.f){}
		inline TPoint2(const float *pfArray):x(pfArray[0]), y(pfArray[1]){}
		inline TPoint2(float fX, float fY):x(fX), y(fY){}
	};

	/** Describes point coordinates in 3D space. */
	struct TPoint3
	{
		union
		{
			struct
			{
				float x, y, z;
			};
			float coords[3];
		};

		typedef float (&ref)[3];
		typedef const float (&cref)[3];

		inline operator ref()
		{
			return coords;
		}
		inline operator cref() const
		{
			return coords;
		}

		inline TPoint3():x(0.f), y(0.f), z(0.f){}
		inline TPoint3(const float *pfArray):x(pfArray[0]), y(pfArray[1]), z(pfArray[2]){}
		inline TPoint3(float fX, float fY, float fZ):x(fX), y(fY), z(fZ){}

#ifdef PHYSX
		inline TPoint3(const NxVec3 &physxVec) : x(physxVec.x), y(physxVec.y), z(physxVec.z) {}
		inline TPoint3(const NxExtendedVec3 &physxVec) : x(physxVec.x), y(physxVec.y), z(physxVec.z) {}
		inline operator NxVec3()
		{
			return NxVec3(x, y, z);
		}
		inline operator NxExtendedVec3()
		{
			return NxExtendedVec3(x, y, z);
		}
#endif
	};

	/** Describes graphical point coordinates, color and its texture coordinates in 2D space. */
	struct TVertex2
	{
		float x, y, u, w, r, g, b, a;
		
		inline TVertex2():x(0.f), y(0.f), u(0.f), w(0.f), r(1.f), g(1.f), b(1.f), a(1.f){}
		inline TVertex2(float fX, float fY, float fU, float fW, float fR, float fG, float fB, float fA):
		x(fX), y(fY), u(fU), w(fW), r(fR), g(fG), b(fB), a(fA){}
	};

	/** Describes graphical point coordinates, color and its texture coordinates in 3D space. */
	struct TVertex3
	{
		float x, y, z, u, w, r, g, b, a;

		inline TVertex3():x(0.f), y(0.f), z(0.f), u(0.f), w(0.f), r(1.f), g(1.f), b(1.f), a(1.f){}
		inline TVertex3(float fX, float fY, float fZ, float fU, float fW, float fR, float fG, float fB, float fA):
		x(fX), y(fY), z(fZ), u(fU), w(fW), r(fR), g(fG), b(fB), a(fA){}
	};

	/** Describes 2D rectangle by float values. */
	struct TRectF
	{
		float x, y, width, height;

		inline TRectF(): x(0.f), y(0.f), width(0.f), height(0.f){}
		inline TRectF(float fX, float fY, float fWidth, float fHeight): x(fX), y(fY), width(fWidth), height(fHeight){}
		inline bool IntersectRect(const TRectF &stRect)
		{
			return	(x < stRect.x + stRect.width && x + width > stRect.x && y < stRect.y + stRect.height && y + height > stRect.y)||
					(stRect.x + stRect.width < x && stRect.x > x + width && stRect.y + stRect.height < y && stRect.y > y + height);
		}
		inline bool PointInRect(const TPoint2 &stPoint){return stPoint.x > x && stPoint.x < x + width && stPoint.y > y && stPoint.y < y + height;}
	};

	/** Describes 4x4 matrix and some math routines used in 3D graphics computes. */
	struct TMatrix
	{
		union
		{
			float _1D[16];
			float _2D[4][4];
		};

		inline TMatrix()
		{
			memset(_1D, 0, sizeof(_1D));
		}

		inline TMatrix(
			float _00, float _01, float _02, float _03,
			float _10, float _11, float _12, float _13,
			float _20, float _21, float _22, float _23,
			float _30, float _31, float _32, float _33)
		{
			_2D[0][0] = _00; _2D[0][1] = _01; _2D[0][2] = _02; _2D[0][3] = _03;
			_2D[1][0] = _10; _2D[1][1] = _11; _2D[1][2] = _12; _2D[1][3] = _13;
			_2D[2][0] = _20; _2D[2][1] = _21; _2D[2][2] = _22; _2D[2][3] = _23;
			_2D[3][0] = _30; _2D[3][1] = _31; _2D[3][2] = _32; _2D[3][3] = _33;
		}
		
#ifdef PHYSX
		inline TMatrix(const NxMat33 &physxMat)
		{
			physxMat.getColumnMajorStride4(_2D);
		}

		inline TMatrix(const NxMat34 &physxMat)
		{
			physxMat.getColumnMajor44(_2D);
		}

		inline operator NxMat33() const
		{
			NxMat33 physxMat;
			physxMat.setColumnMajorStride4(_2D);
			return physxMat;
		}

		inline operator NxMat34() const
		{
			NxMat34 physxMat;
			physxMat.setColumnMajor44(_2D);
			return physxMat;
		}
#endif

		inline TMatrix operator -()
		{
			TMatrix m;
			for(ubyte i = 0; i < 16; i++)
				m._1D[i] = - _1D[i];
			return m;
		}

		inline TMatrix &operator +=(float right)
		{
			for(ubyte i = 0; i < 16; i++)
				_1D[i] += right;
			return *this;
		}

		inline TMatrix &operator -=(float right)
		{
			for(ubyte i = 0; i < 16; i++)
				_1D[i] -= right;
			return *this;
		}

		inline TMatrix &operator *=(float right)
		{
			for(ubyte i = 0; i < 16; i++)
				_1D[i] *= right;
			return *this;
		}

		inline TMatrix &operator /=(float right)
		{
			for(ubyte i = 0; i < 16; i++)
				_1D[i] /= right;
			return *this;
		}

		TMatrix &operator +=(const TMatrix &right)
		{
			for(ubyte i = 0; i < 16; i++)
				_1D[i] += right._1D[i];
			return *this;
		}

		TMatrix &operator -=(const TMatrix &right)
		{
			for(ubyte i = 0; i < 16; i++)
				_1D[i] -= right._1D[i];
			return *this;
		}

		TMatrix &operator *=(const TMatrix &right)
		{
			return *this = *this * right;
		}

		TMatrix operator +(float right) const
		{
			return TMatrix(*this) += right;
		}

		TMatrix operator -(float right) const
		{
			return TMatrix(*this) -= right;
		}

		TMatrix operator *(float right) const
		{
			return TMatrix(*this) *= right;
		}

		TMatrix operator /(float right) const
		{
			return TMatrix(*this) /= right;
		}

		TMatrix operator +(const TMatrix &right) const
		{
			return TMatrix(*this) += right;
		}

		TMatrix operator -(const TMatrix &right) const
		{
			return TMatrix(*this) -= right;
		}

		TMatrix operator *(const TMatrix &right) const
		{
			TMatrix product;
			for(ubyte i = 0; i < 4; i++)
				for(ubyte j = 0; j < 4; j++)
					for(ubyte k = 0; k < 4; k++)
						product._2D[i][j] += this->_2D[i][k] * right._2D[k][j];
			return product;
		}
	};

	// Matrix helper functions //

	/** Returns identity matrx. */
	inline TMatrix MatrixIdentity()
	{
		return TMatrix(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
	}

	/** Returns inverce matrx. */
	inline TMatrix MatrixInverce(const TMatrix &stMatrix)
	{
		float mat[4][8] =
		{
			stMatrix._2D[0][0], stMatrix._2D[0][1], stMatrix._2D[0][2], stMatrix._2D[0][3], 1, 0, 0, 0,
			stMatrix._2D[1][0], stMatrix._2D[1][1], stMatrix._2D[1][2], stMatrix._2D[1][3], 0, 1, 0, 0,
			stMatrix._2D[2][0], stMatrix._2D[2][1], stMatrix._2D[2][2], stMatrix._2D[2][3], 0, 0, 1, 0,
			stMatrix._2D[3][0], stMatrix._2D[3][1], stMatrix._2D[3][2], stMatrix._2D[3][3], 0, 0, 0, 1
		};
		float *rows[4] = { mat[0], mat[1], mat[2], mat[3] };
		ubyte i, r;
		for(i = 0; i < 4; i++)
		{
			ubyte row_num = i;
			float major = fabs(rows[i][i]);
			for(r = i+1; r < 4; r++)
			{
				float cur_ABS = fabs(rows[r][i]);
				if(cur_ABS > major)
				{
					major=cur_ABS;
					row_num=r;
				}
			}
			if(row_num != i)
			{
				(int &)rows[i]			^= (int)rows[row_num];
				(int &)rows[row_num]	^= (int)rows[i];
				(int &)rows[i]			^= (int)rows[row_num];
			}
			for(r = i+1; r < 4; r++)
			{
				float factor=rows[r][i] / rows[i][i];
				for(ubyte c = i; c < 8; c++)
					rows[r][c] -= factor * rows[i][c];
			}
		}
		for(i = 3; i > 0; i--)
			for(r = 0; r < i; r++) {
				float factor=rows[r][i] / rows[i][i];
				for(ubyte c = 4; c < 8; c++)
					rows[r][c] -= factor * rows[i][c];
			}
		return TMatrix(
			rows[0][4] / rows[0][0], rows[0][5] / rows[0][0], rows[0][6] / rows[0][0], rows[0][7] / rows[0][0],
			rows[1][4] / rows[1][1], rows[1][5] / rows[1][1], rows[1][6] / rows[1][1], rows[1][7] / rows[1][1],
			rows[2][4] / rows[2][2], rows[2][5] / rows[2][2], rows[2][6] / rows[2][2], rows[2][7] / rows[2][2],
			rows[3][4] / rows[3][3], rows[3][5] / rows[3][3], rows[3][6] / rows[3][3], rows[3][7] / rows[3][3]);
	}

	/** Returns transpose matrx. */
	inline TMatrix MatrixTranspose(const TMatrix &stMatrix)
	{
		return TMatrix(
			stMatrix._2D[0][0], stMatrix._2D[1][0], stMatrix._2D[2][0], stMatrix._2D[3][0],
			stMatrix._2D[0][1], stMatrix._2D[1][1], stMatrix._2D[2][1], stMatrix._2D[3][1],
			stMatrix._2D[0][2], stMatrix._2D[1][2], stMatrix._2D[2][2], stMatrix._2D[3][2],
			stMatrix._2D[0][3], stMatrix._2D[1][3], stMatrix._2D[2][3], stMatrix._2D[3][3]);
	}
	
	/** Returns scaled matrix by given vector. */
	inline TMatrix MatrixScale(const TPoint3 &stVec)
	{
		return TMatrix(
			stVec.x, 0.f, 0.f, 0.f,
			0.f, stVec.y, 0.f, 0.f,
			0.f, 0.f, stVec.z, 0.f,
			0.f, 0.f, 0.f, 1.f);
	}

	/** Returns translated matrix by given vector. */
	inline TMatrix MatrixTranslate(const TPoint3 &stVec)
	{
		return TMatrix(
			1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			stVec.x, stVec.y, stVec.z, 1.f);
	}

	/** Returns rotated matrix by given axes vector and angle. */
	inline TMatrix MatrixRotate(float fAngle, TPoint3 &stAxes)
	{
		const float
			axis_norm = sqrt(stAxes.x*stAxes.x + stAxes.y*stAxes.y + stAxes.z*stAxes.z),
			x = stAxes.x / axis_norm,
			y = stAxes.y / axis_norm,
			z = stAxes.z / axis_norm,
			sin_angle = (float)sin(fAngle*3.1415926535897932/180.f),
			cos_angle = (float)cos(fAngle*3.1415926535897932/180.f);
		return TMatrix(
			(1.f - x * x) * cos_angle + x * x,			z * sin_angle + x * y * (1.f - cos_angle),	x * z * (1.f - cos_angle) - y * sin_angle,	0.f,
			x * y * (1.f - cos_angle) - z * sin_angle,	(1.f - y * y) * cos_angle + y * y,			y * z * (1.f - cos_angle) + x * sin_angle,	0.f,
			x * z * (1.f - cos_angle) + y * sin_angle,	y * z * (1.f - cos_angle) - x * sin_angle,	(1.f - z * z) * cos_angle + z * z,			0.f,
			0.f,										0.f,										0.f,										1.f);
	}

	/** Returns billboarded matrix. Removes rotation information from the matrix. */
	inline TMatrix MatrixBillboard(const TMatrix &stMatrix)
	{
		return TMatrix(
			1.f,				0.f,				0.f,				stMatrix._2D[0][3],
			0.f,				1.f,				0.f,				stMatrix._2D[1][3],
			0.f,				0.f,				1.f,				stMatrix._2D[2][3],
			stMatrix._2D[3][0],	stMatrix._2D[3][1],	stMatrix._2D[3][2],	stMatrix._2D[3][3]);
	}

#pragma warning(push)
#pragma warning(disable: 4290)

	/** Template for multiplication stacks. */
	template<class TTransform>
	class TTransformStack: private std::stack<TTransform>
	{
	public:
		TTransformStack(const TTransform &base_transform = TTransform());
		/** Saves current stack state. */
		void Push();
		/** Restores previously saved stack state. */
		void Pop();
		/** Returns current stack state. */
		const TTransform &Top() const;
		/** Returns current stack state. */
		TTransform &Top();
		/** Multiplicates current stack state on transform. */
		void Mult1(const TTransform &transform);
		/** Multiplicates transform on current stack state and saves result as current stack state. */
		void Mult2(const TTransform &transform);
	};

	template<class TTransform>
	inline TTransformStack<TTransform>::TTransformStack(const TTransform &base_transform)
	{
		push(base_transform);
	}

	template<class TTransform>
	inline void TTransformStack<TTransform>::Push()
	{
		push(top());
	}

	template<class TTransform>
	inline void TTransformStack<TTransform>::Pop()
	{
		assert(size() > 1);
		pop();
	}

	template<class TTransform>
	inline const TTransform &TTransformStack<TTransform>::Top() const
	{
		return top();
	}

	template<class TTransform>
	inline TTransform &TTransformStack<TTransform>::Top()
	{
		return top();
	}

	template<class TTransform>
	inline void TTransformStack<TTransform>::Mult1(const TTransform &transform)
	{
		top() *= transform;
	}

	template<class TTransform>
	inline void TTransformStack<TTransform>::Mult2(const TTransform &transform)
	{
		top() = transform * top();
	}

	/** Stack of matrix 4x4 multiplication operations. */
	typedef TTransformStack<TMatrix> TMatrixStack;

#pragma warning(pop)

	/** Describes the state of the mouse. 
		\see IInput
	*/
	struct TMouseStates
	{
		int	 iX;			/**< X coordinate of mouse pointer. */ 
		int	 iY;			/**< Y coordinate of mouse pointer. */
		int	 iDeltaX;		/**< The difference between the current and previous X coordinate value. */
		int	 iDeltaY;		/**< The difference between the current and previous Y coordinate value. */
		int	 iDeltaWheel;	/**< Mouse wheel offset. */
		bool bLeftButton;	/**< Is mouse left button pressed. */
		bool bRightButton;	/**< Is mouse right button pressed. */
		bool bMiddleButton; /**< Is mouse middle button pressed. */
	};

	/** Describes the state of the keyboard. 
		\see IInput
	*/
	struct TKeyboardStates 
	{
		bool bCapsLock; 	/**< Is CapsLock pressed. */
		bool bShiftL;		/**< Is left Shift pressed. */
		bool bShiftR;		/**< Is right Shift pressed. */
		bool bCtrlL;		/**< Is left Control pressed. */
		bool bCtrlR;		/**< Is right Control pressed. */
		bool bAltL;			/**< Is left Alt pressed. */
		bool bAltR;			/**< Is right Alt pressed. */
	};

	/** Describes the state of the joystick or gamepad. 
		\see IInput
	*/
	struct TJoystickStates
	{
		int iXAxes;		    /**< X-axis position. */
		int iYAxes;		    /**< Y-axis position. */
		int iZAxes;		    /**< Z-axis position. */
		int iXRotate;		/**< X-axis rotation. */
		int iYRotate;		/**< Y-axis rotation. */
		int iZRotate;		/**< Z-axis rotation. */
		int iVX;			/**< X-axis velocity. */
		int iVY;			/**< Y-axis velocity. */
		int iVZ;			/**< Z-axis velocity. */
		int iVXRotate;		/**< X-axis angular velocity. */
		int iVYRotate;		/**< Y-axis angular velocity. */
		int iVZRotate;		/**< Z-axis angular velocity. */
		int iAX;			/**< X-axis acceleration. */
		int iAY;			/**< Y-axis acceleration. */
		int iAZ;			/**< Z-axis acceleration. */
		int iAXRotate;		/**< X-axis angular acceleration. */
		int iAYRotate;		/**< Y-axis angular acceleration. */
		int iAZRotate;		/**< Z-axis angular acceleration. */
		int iFX;			/**< X-axis force. */
		int iFY;			/**< Y-axis force. */
		int iFZ;			/**< Z-axis force. */
		int iFXRotate;		/**< X-axis torque. */
		int iFYRotate;		/**< y-axis torque. */
		int iFZRotate;		/**< Z-axis torque. */
		int iSlider0;		/**< Extra axis position 0. */
		int iSlider1;		/**< Extra axis position 1.*/
		int iVSlider0;		/**< Extra axis velocity 0. */
		int iVSlider1;		/**< Extra axis velocity 0.*/
		int iASlider0;		/**< Extra axis acceleration 0. */
		int iASlider1;		/**< Extra axis acceleration 1. */
		int iFSlider0;		/**< Extra axis force 0. */
		int iFSlider1;		/**< Extra axis force 1. */
		int iPOV0;			/**< POV direction 0. */
		int iPOV1;			/**< POV direction 1. */
		int iPOV2;			/**< POV direction 2. */
		int iPOV3;			/**< POV direction 3. */
	};

#if defined(STRUCT_ALIGNMENT_1) && defined(PLATFORM_WINDOWS)
#pragma pack(pop)
#endif

	/** Describes all keyboard key codes. 
		\see IInput
	*/
	enum E_KEYBOARD_KEY_CODES
	{
		KEY_ESCAPE			= 0x01,
		KEY_TAB				= 0x0F,
		KEY_GRAVE			= 0x29,
		KEY_CAPSLOCK		= 0x3A,
		KEY_BACKSPACE		= 0x0E,
		KEY_RETURN			= 0x1C,
		KEY_SPACE			= 0x39,
		KEY_SLASH			= 0x35,
		KEY_BACKSLASH		= 0x2B,

		KEY_SYSRQ			= 0xB7,
		KEY_SCROLL			= 0x46,
		KEY_PAUSE			= 0xC5,

		KEY_INSERT			= 0xD2,
		KEY_DELETE			= 0xD3,
		KEY_HOME			= 0xC7,
		KEY_END				= 0xCF,
		KEY_PGUP			= 0xC9,
		KEY_PGDN			= 0xD1,

		KEY_LSHIFT			= 0x2A,
		KEY_RSHIFT			= 0x36,
		KEY_LALT			= 0x38,
		KEY_RALT			= 0xB8,
		KEY_LWIN			= 0xDB,
		KEY_RWIN			= 0xDC,
		KEY_LCONTROL		= 0x1D,
		KEY_RCONTROL		= 0x9D,

		KEY_UP				= 0xC8,
		KEY_RIGHT			= 0xCD,
		KEY_LEFT			= 0xCB,
		KEY_DOWN			= 0xD0,

		KEY_1				= 0x02,
		KEY_2				= 0x03,
		KEY_3				= 0x04,
		KEY_4				= 0x05,
		KEY_5				= 0x06,
		KEY_6				= 0x07,
		KEY_7				= 0x08,
		KEY_8				= 0x09,
		KEY_9				= 0x0A,
		KEY_0				= 0x0B,

		KEY_F1				= 0x3B,
		KEY_F2				= 0x3C,
		KEY_F3				= 0x3D,
		KEY_F4				= 0x3E,
		KEY_F5				= 0x3F,
		KEY_F6				= 0x40,
		KEY_F7				= 0x41,
		KEY_F8				= 0x42,
		KEY_F9				= 0x43,
		KEY_F10				= 0x44,
		KEY_F11				= 0x57,
		KEY_F12				= 0x58,

		KEY_Q				= 0x10,
		KEY_W				= 0x11,
		KEY_E				= 0x12,
		KEY_R				= 0x13,
		KEY_T				= 0x14,
		KEY_Y				= 0x15,
		KEY_U				= 0x16,
		KEY_I				= 0x17,
		KEY_O				= 0x18,
		KEY_P				= 0x19,
		KEY_A				= 0x1E,
		KEY_S				= 0x1F,
		KEY_D				= 0x20,
		KEY_F				= 0x21,
		KEY_G				= 0x22,
		KEY_H				= 0x23,
		KEY_J				= 0x24,
		KEY_K				= 0x25,
		KEY_L				= 0x26,
		KEY_Z				= 0x2C,
		KEY_X				= 0x2D,
		KEY_C				= 0x2E,
		KEY_V				= 0x2F,
		KEY_B				= 0x30,
		KEY_N				= 0x31,
		KEY_M				= 0x32,

		KEY_MINUS			= 0x0C,
		KEY_PLUS			= 0x0D,
		KEY_LBRACKET		= 0x1A,
		KEY_RBRACKET		= 0x1B,

		KEY_SEMICOLON		= 0x27,
		KEY_APOSTROPHE		= 0x28,

		KEY_COMMA			= 0x33,
		KEY_PERIOD			= 0x34,

		KEY_NUMPAD0			= 0x52,
		KEY_NUMPAD1			= 0x4F,
		KEY_NUMPAD2			= 0x50,
		KEY_NUMPAD3			= 0x51,
		KEY_NUMPAD4			= 0x4B,
		KEY_NUMPAD5			= 0x4C,
		KEY_NUMPAD6			= 0x4D,
		KEY_NUMPAD7			= 0x47,
		KEY_NUMPAD8			= 0x48,
		KEY_NUMPAD9			= 0x49,
		KEY_NUMPADPERIOD	= 0x53,
		KEY_NUMPADENTER		= 0x9C,
		KEY_NUMPADSTAR		= 0x37,
		KEY_NUMPADPLUS		= 0x4E,
		KEY_NUMPADMINUS		= 0x4A,
		KEY_NUMPADSLASH		= 0xB5,
		KEY_NUMLOCK			= 0x45,
	};

}

#endif//DGLE2_TYPES
