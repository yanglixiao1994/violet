#pragma once
#include "auxiliary.h"
namespace violet {
	typedef unique_ptr<class Texture>		TexPtr;
	typedef vector<TexPtr>					TexVec;

	class Texture {
		friend class glRenderSystem;
		friend class Mesh;
		enum class TEX_TYPE {
			TextureType_DIFFUSE,
			TextureType_SPECULAR,

			/** The texture is combined with the result of the ambient
			*  lighting equation.
			*/
			TextureType_AMBIENT = 0x3,

			/** The texture is added to the result of the lighting
			*  calculation. It isn't influenced by incoming light.
			*/
			TextureType_EMISSIVE = 0x4,

			/** The texture is a height map.
			*
			*  By convention, higher gray-scale values stand for
			*  higher elevations from the base height.
			*/
			TextureType_HEIGHT = 0x5,

			/** The texture is a (tangent space) normal-map.
			*
			*  Again, there are several conventions for tangent-space
			*  normal maps. Assimp does (intentionally) not
			*  distinguish here.
			*/
			TextureType_NORMALS = 0x6,

			/** The texture defines the glossiness of the material.
			*
			*  The glossiness is in fact the exponent of the specular
			*  (phong) lighting equation. Usually there is a conversion
			*  function defined to map the linear color values in the
			*  texture to a suitable exponent. Have fun.
			*/
			TextureType_SHININESS = 0x7,

			/** The texture defines per-pixel opacity.
			*
			*  Usually 'white' means opaque and 'black' means
			*  'transparency'. Or quite the opposite. Have fun.
			*/
			TextureType_OPACITY = 0x8,

			/** Displacement texture
			*
			*  The exact purpose and format is application-dependent.
			*  Higher color values stand for higher vertex displacements.
			*/
			TextureType_DISPLACEMENT = 0x9,

			/** Lightmap texture (aka Ambient Occlusion)
			*
			*  Both 'Lightmaps' and dedicated 'ambient occlusion maps' are
			*  covered by this material property. The texture contains a
			*  scaling value for the final color value of a pixel. Its
			*  intensity is not affected by incoming light.
			*/
			TextureType_LIGHTMAP = 0xA,

			/** Reflection texture
			*
			* Contains the color of a perfect mirror reflection.
			* Rarely used, almost never for real-time applications.
			*/
			TextureType_REFLECTION = 0xB,

			/** Unknown texture
			*
			*  A texture reference that does not match any of the definitions
			*  above is considered to be 'unknown'. It is still imported,
			*  but is excluded from any further postprocessing.
			*/
			TextureType_UNKNOWN = 0xC,

		};
		enum class TEX_FILTER_METHOD {
			Nearest,
			Linear,
		};
		enum class TEX_DATA_TYPE {
			Float,
			Uint8,
		};
		enum class TEX_WARPING_TYPE {
			Repeat,
			MirroredRepeat,
			ClampEdge,
			ClampBorder,
		};
		enum class TEX_FORMAT {
			DepthComponet,
			DepthStencil,
			R,
			RG,
			RGB,
			RGBA
		};
	public:
		Texture(const string&file);
		void loadFile(const string&file);
		bool isInGpu() { return _inGpu; }
	private:
		uint8		*		_dataUint8;
		float		*		_dataFloat;
		int					_width;
		int					_height;
		int					_channels;
		string				_file;
		TEX_DATA_TYPE		_dataType;
		TEX_TYPE			_type;
		TEX_WARPING_TYPE	_warping;
		TEX_FILTER_METHOD	_filter;
		TEX_FORMAT			_format;
		uint32				_texId;
		bool				_inGpu;
	};
}