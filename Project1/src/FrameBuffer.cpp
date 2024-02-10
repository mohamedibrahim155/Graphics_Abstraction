#include "FrameBuffer.h"

FrameBuffer::FrameBuffer(const FrameBufferSpecification& specs)
{
	this->specification = specs;
	Invalidate();
}

FrameBuffer::~FrameBuffer()
{
	GLCALL(glDeleteFramebuffers(1, &rendererID));
	GLCALL(glDeleteTextures(1, &colorAttachmentID));
	GLCALL(glDeleteTextures(1, &depthAttachmentID));
}

void FrameBuffer::Bind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));
}

void FrameBuffer::Unbind()
{
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

}

unsigned int& FrameBuffer::GetColorAttachmentID()
{
	return colorAttachmentID;
}

unsigned int& FrameBuffer::GetRendererID()
{
	return rendererID;
}

unsigned int& FrameBuffer::GetDepthAttachementID()
{
	return depthAttachmentID;
}

void FrameBuffer::Invalidate()
{
	if (rendererID != 0)
	{
		GLCALL(glDeleteFramebuffers(1, &rendererID));
		GLCALL(glDeleteTextures(1, &colorAttachmentID));
		GLCALL(glDeleteTextures(1, &depthAttachmentID));
	}

	GLCALL(glCreateFramebuffers(1, &rendererID));
	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, rendererID));

	GLCALL(glCreateTextures(GL_TEXTURE_2D,1, &colorAttachmentID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, colorAttachmentID));
	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, specification.width, specification.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));
	
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorAttachmentID,0));

	GLCALL(glCreateTextures(GL_TEXTURE_2D, 1, &depthAttachmentID));
	GLCALL(glBindTexture(GL_TEXTURE_2D, depthAttachmentID));
	//GLCALL(glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, specification.width, specification.height));

	GLCALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, specification.width, specification.height, 0,
		GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL));

	GLCALL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, depthAttachmentID, 0));

	GLCALL(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

	GLCALL(glBindFramebuffer(GL_FRAMEBUFFER, 0));

}

void FrameBuffer::Resize(unsigned int width, unsigned int height)
{
	this->specification.width = width;
	this->specification.height = height;

	Invalidate();
}
