#include "button.h"

namespace button
{
	void assignWidthAndHeight(createButton& btn)
	{
		btn.width = static_cast<float>(btn.buttonText->width);
		btn.height = static_cast<float>(btn.buttonText->height);
	}
}
