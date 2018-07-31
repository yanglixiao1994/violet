#pragma once
#include "RenderSystem.h"
#define MAX_LIGHT_NUM 8
namespace violet {
	class glRenderSystem :public RenderSystem {
	public:
		glRenderSystem(const windowInfo&);
		void setGpuProgram()final override;
		void bindGlobalEnvironmentInfo(const globalEnvironmentInfo&)final override;
		void bindMaterial(const MatlPtr&)final override;
		void uploadSubMesh2Gpu(SubMesh&)final override;
		void bindSubMesh(SubMesh&)final override;
		GpuBufferPtr createGpuBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE, uint32 size, void* pSource)final override;
		void draw(SubMesh&)final override;
		void swapBuffer()final override;
		void setColor(float r, float g, float b);
		void loadGpuProgram();
	private:
		uint				_width;
		uint				_height;
		bool				_fullscreen;
		std::string			_title;

		GLuint				_cur_gpu_program;
		std::map<std::string, GLuint> _gpu_program_cache;
		MatlPtr				_cur_matl;
	};
}