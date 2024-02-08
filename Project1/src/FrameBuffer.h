#pragma once
#include "Renderer.h"

struct FrameBufferSpecification
{

	uint32_t  width;
	uint32_t  height;
	uint32_t  samples = 1;

	bool swapChainTarget = false;
};
class FrameBuffer
{
public:

	FrameBuffer(const FrameBufferSpecification& specs);
	~FrameBuffer();

	void Bind();
	void Unbind();
	void Invalidate();
	void Resize(unsigned int width, unsigned int height);

	unsigned int& GetColorAttachmentID();
	unsigned int& GetRendererID();
	unsigned int& GetDepthAttachementID();

private:

	unsigned int rendererID = 0;
	unsigned int colorAttachmentID = 0;
	unsigned int depthAttachmentID = 0;
	FrameBufferSpecification specification;


};

