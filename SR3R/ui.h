#ifndef UI_H
#define UI_H

void changeBoolState(bool* b);

class Option
{
private:
	float x, y, w, h, scale;
	int index;
	const char* option;


public:

	bool* state;
	int* comboIndex;
	std::vector<std::string> comboArray;
	std::function<void()> action;

	Option(const char* option, int index, std::function<void()> action) : option(option), index(index), action(action)
	{
		this->x = 25;
		this->y = 20 + (index * 20);
		this->w = 190;
		this->h = 20;
		this->scale = .085f;
	}

	Option(const char* option, int index, std::function<void()> action, bool* state) : option(option), index(index), action(action), state(state)
	{
		this->x = 25;
		this->y = 20 + (index * 20);
		this->w = 190;
		this->h = 20;
		this->scale = .085f;
	}

	Option(const char* option, int index, bool* state) : option(option), index(index), state(state)
	{
		this->x = 25;
		this->y = 20 + (index * 20);
		this->w = 190;
		this->h = 20;
		this->scale = .085f;
		this->action = std::bind(changeBoolState, state);
	}

	Option(const char* option, int index, std::vector<std::string> comboArray, int* comboIndex) : option(option), index(index), comboArray(comboArray), comboIndex(comboIndex)
	{
		this->x = 25;
		this->y = 20 + (index * 20);
		this->w = 190;
		this->h = 20;
		this->scale = .085f;
	}

	void Render();
};
extern std::vector<Option*> Opt;

#endif