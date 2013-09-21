#pragma once

#include "BsPrerequisites.h"
#include "BsGUIElement.h"
#include "BsImageSprite.h"
#include "BsGUIContent.h"
#include "boost/signal.hpp"

namespace BansheeEngine
{
	class BS_EXPORT GUIButton : public GUIElement
	{
	public:
		static const CM::String& getGUITypeName();

		static GUIButton* create(GUIWidget& parent, const CM::WString& text, const GUIElementStyle* style = nullptr);
		static GUIButton* create(GUIWidget& parent, const CM::WString& text, const GUILayoutOptions& layoutOptions, const GUIElementStyle* style = nullptr);

		static GUIButton* create(GUIWidget& parent, const GUIContent& content, const GUIElementStyle* style = nullptr);
		static GUIButton* create(GUIWidget& parent, const GUIContent& content, const GUILayoutOptions& layoutOptions, const GUIElementStyle* style = nullptr);
	
		void setContent(const GUIContent& content);

		boost::signal<void()> onClick;
		boost::signal<void()> onHover;
		boost::signal<void()> onOut;
	protected:
		~GUIButton();

		/**
		 * @copydoc GUIElement::getNumRenderElements()
		 */
		virtual CM::UINT32 getNumRenderElements() const;

		/**
		 * @copydoc GUIElement::getMaterial()
		 */
		virtual const CM::HMaterial& getMaterial(CM::UINT32 renderElementIdx) const;

		/**
		 * @copydoc GUIElement::getNumQuads()
		 */
		virtual CM::UINT32 getNumQuads(CM::UINT32 renderElementIdx) const;

		/**
		 * @copydoc GUIElement::fillBuffer()
		 */
		virtual void fillBuffer(CM::UINT8* vertices, CM::UINT8* uv, CM::UINT32* indices, CM::UINT32 startingQuad, 
			CM::UINT32 maxNumQuads, CM::UINT32 vertexStride, CM::UINT32 indexStride, CM::UINT32 renderElementIdx) const;

		/**
		 * @copydoc GUIElement::updateRenderElementsInternal()
		 */
		virtual void updateRenderElementsInternal();

		/**
		 * @copydoc GUIElement::updateBounds()
		 */
		virtual void updateClippedBounds();

		virtual CM::UINT32 _getOptimalWidth() const;
		virtual CM::UINT32 _getOptimalHeight() const;

		virtual CM::UINT32 _getRenderElementDepth(CM::UINT32 renderElementIdx) const;
	private:
		ImageSprite* mImageSprite;
		ImageSprite* mContentImageSprite;
		TextSprite* mTextSprite;

		IMAGE_SPRITE_DESC mImageDesc;
		GUIContent mContent;

		GUIButton(GUIWidget& parent, const GUIElementStyle* style, const GUIContent& content, const GUILayoutOptions& layoutOptions);

		virtual bool mouseEvent(const GUIMouseEvent& ev);
	};
}