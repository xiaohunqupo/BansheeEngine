//********************************** Banshee Engine (www.banshee3d.com) **************************************************//
//**************** Copyright (c) 2016 Marko Pintera (marko.pintera@gmail.com). All rights reserved. **********************//
#pragma once

#include "BsPrerequisites.h"
#include "BsGUIElement.h"
#include "BsImageSprite.h"
#include "BsEvent.h"

namespace BansheeEngine
{
	/** @cond INTERNAL */
	/** @addtogroup GUI
	 *  @{
	 */

	/** A handle that can be dragged from its predefined minimum and maximum position, either horizontally or vertically. */
	class BS_EXPORT GUISliderHandle : public GUIElement
	{
		/**	Visual state of the handle. */
		enum class State
		{
			Normal, Hover, Active
		};

	public:
		/** Returns type name of the GUI element used for finding GUI element styles.  */
		static const String& getGUITypeName();

		/**
		 * Creates a new handle.
		 *
		 * @param[in]	horizontal		Should the handle be movable vertically or horizontally.
		 * @param[in]	jumpOnClick		If true clicking on a specific position on the slider will cause the slider handle
		 *								to jump to that position. Otherwise the slider will just slightly move towards that
		 *								direction.
		 * @param[in]	styleName		Optional style to use for the element. Style will be retrieved from GUISkin of the
		 *								GUIWidget the element is used on. If not specified default style is used.
		 */
		static GUISliderHandle* create(bool horizontal, bool jumpOnClick, const String& styleName = StringUtil::BLANK);

		/**
		 * Creates a new handle.
		 *
		 * @param[in]	horizontal		Should the handle be movable vertically or horizontally.
		 * @param[in]	jumpOnClick		If true clicking on a specific position on the slider will cause the slider handle
		 *								to jump to that position. Otherwise the slider will just slightly move towards that
		 *								direction.
		 * @param[in]	options			Options that allow you to control how is the element positioned and sized.
		 *								This will override any similar options set by style.
		 * @param[in]	styleName		Optional style to use for the element. Style will be retrieved from GUISkin of the
		 *								GUIWidget the element is used on. If not specified default style is used.
		 */
		static GUISliderHandle* create(bool horizontal, bool jumpOnClick, const GUIOptions& options,
			const String& styleName = StringUtil::BLANK);

		/**	Gets the current position of the handle, in percent ranging [0.0f, 1.0f]. */
		float getHandlePos() const;

		/**	Returns the position of the slider handle, in pixels. Relative to this object. */
		INT32 getHandlePosPx() const;

		/**	Returns remaining length of the scrollable area not covered by the handle, in pixels. */
		UINT32 getScrollableSize() const;

		/**	Returns the total length of the area the handle can move in, in pixels. */
		UINT32 getMaxSize() const;

		/**	
		 * Sets a step that defines the minimal increment the value can be increased/decreased by. Set to zero	to have no
		 * step.
		 */
		void setStep(float step);

		/** Triggered when the user drags the handle. */
		Event<void(float newPosition)> onHandleMoved;

	public: // ***** INTERNAL ******
		/** @cond INTERNAL */

		/**
		 * Size of the handle in pixels, along the handle drag direction.
		 *
		 * @note	Internal method. Does not trigger layout update.
		 */
		void _setHandleSize(UINT32 size);

		/**
		 * Moves the handle the the specified position in the handle area.
		 *
		 * @param[in]	pct	Position to move the handle to, in percent ranging [0.0f, 1.0f]
		 *
		 * @note	Internal method. Does not trigger layout update.
		 */
		void _setHandlePos(float pct);

		/** @copydoc GUIElement::_getOptimalSize */
		virtual Vector2I _getOptimalSize() const override;

		/** @endcond */
	protected:
		~GUISliderHandle();

		/** @copydoc GUIElement::_getNumRenderElements() */
		virtual UINT32 _getNumRenderElements() const override;

		/** @copydoc GUIElement::_getMaterial() */
		virtual const SpriteMaterialInfo& _getMaterial(UINT32 renderElementIdx) const override;

		/** @copydoc GUIElement::_getNumQuads() */
		virtual UINT32 _getNumQuads(UINT32 renderElementIdx) const override;

		/** @copydoc GUIElement::_fillBuffer() */
		virtual void _fillBuffer(UINT8* vertices, UINT8* uv, UINT32* indices, UINT32 startingQuad, 
			UINT32 maxNumQuads, UINT32 vertexStride, UINT32 indexStride, UINT32 renderElementIdx) const override;

		/** @copydoc GUIElement::updateRenderElementsInternal() */
		virtual void updateRenderElementsInternal() override;

		/** @copydoc GUIElement::updateBounds() */
		virtual void updateClippedBounds() override;
	private:
		GUISliderHandle(bool horizontal, bool jumpOnClick, const String& styleName, const GUIDimensions& dimensions);

		/** @copydoc GUIElement::mouseEvent */
		virtual bool _mouseEvent(const GUIMouseEvent& ev) override;

		/** Checks are the specified over the scroll handle. Coordinates are relative to the parent widget. */
		bool isOnHandle(const Vector2I& pos) const;

		/**	Sets the position of the slider handle, in pixels. Relative to this object. For internal use only. */
		void setHandlePosPx(INT32 pos);

		/**	Gets the currently active texture, depending on handle state. */
		const HSpriteTexture& getActiveTexture() const;

		ImageSprite* mImageSprite;
		UINT32 mHandleSize;

		bool mHorizontal; // Otherwise its vertical
		bool mJumpOnClick;
		float mPctHandlePos;
		float mStep;
		INT32 mDragStartPos;
		bool mMouseOverHandle;
		bool mHandleDragged;
		State mState;
	};

	/** @} */
	/** @endcond */
}