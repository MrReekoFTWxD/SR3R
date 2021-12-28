#include "pch.h"

std::vector<Option*> Opt;
void changeBoolState(bool* b) { *b = !*b; }

void Option::Render()
{
	if (this->state)
		drawRect(this->x + this->w, this->y + 4, 12, 12, *this->state ? vec4_t(126, 66, 245, 1) : vec4_t(0, 0, 0, .55));


	drawText(to_upper(this->option).c_str(), this->x, this->y, this->scale, vec4_t(1, 1, 1, 1));

	if(this->comboIndex)
		drawText(to_upper(this->comboArray[*this->comboIndex]).c_str(), (this->x + this->w) - 45, this->y + 2, .065f, vec4_t(1, 1, 1, 1));
}
