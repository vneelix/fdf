#include "fdf.h"

static void	correct_queue(void)
{
	SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);
	SDL_EventState(SDL_KEYDOWN, SDL_ENABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
}

void	mouse_hook(SDL_Event *evt, t_figure *f) {
	if (evt->motion.xrel)
		f->delta.y += evt->motion.xrel;
	else if (evt->motion.yrel)
		f->delta.x += evt->motion.yrel;
	transform_manager(f);
	draw(f);
}

int	SDL_Loop(t_figure *f) {
	SDL_Event	evt;
	SDL_bool	left_click = SDL_FALSE;

	if (!f)
		return (-1);
	while (SDL_WaitEvent(&evt)) {
		if (evt.type == SDL_QUIT)
			return (0);
		else if (evt.type == SDL_KEYDOWN)
			key_press(evt.key.keysym.sym, f);
		else if (left_click == SDL_TRUE
			&& evt.type == SDL_MOUSEMOTION)
			mouse_hook(&evt, f);
		else if (evt.type == SDL_MOUSEBUTTONDOWN
			&& evt.button.button == SDL_BUTTON_LEFT)
			left_click = SDL_TRUE;
		else if (evt.type == SDL_MOUSEBUTTONUP
			&& evt.button.button == SDL_BUTTON_LEFT)
			left_click = SDL_FALSE;
		correct_queue();
	}
	return (0);
}
