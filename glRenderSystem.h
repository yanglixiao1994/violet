#pragma once
#include "RenderSystem.h"
#define MAX_LIGHT_NUM 8
namespace violet {
	class glRenderSystem :public RenderSystem {
	public:
		glRenderSystem(const WindowInfo&);
		void setGpuProgram(const string&)final override;
		void bindGlobalEnvironmentInfo(const GlobalEnvironmentInfo&)final override;
		void bindMaterial(const MatlPtr&)final override;
		void uploadSubMesh2Gpu(const SubMeshPtr&)final override;
		void bindSubMesh(const SubMeshPtr&)final override;
		void bindObject(const ObjPtr&)final override;
		GpuBufferPtr createGpuBuffer(BUFFER_USAGE, ATTRIBUTE_TYPE, uint32 size, void* pSource)final override;
		void draw(const SubMeshPtr&)final override;
		void swapBuffer()final override;
		void setColor(float r, float g, float b);
		void clear();
		bool isInGpu(const SubMeshPtr&);
		void loadGpuProgram();
	private:
		uint							_width;
		uint							_height;
		bool							_fullScreen;
		std::string						_title;

		GLuint							_curGpuProgram;
		std::map<std::string, GLuint>	_gpuProgramCache;
		MatlPtr							_curMatl;
	};
}