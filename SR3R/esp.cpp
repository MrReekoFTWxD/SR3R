#include "pch.h"
#include "esp.h"


ctg_object* getObjectInstance()
{
	ctg_object* object = 0;
	if (ctg_world::s_out_world()->m_object_type_buckets[32].num > 0)
		object = ctg_world::s_out_world()->m_all_objects.elt[*ctg_world::s_out_world()->m_object_type_buckets[32].elt];

	return object;
}

void renderESP()
{
	ctg_object* object = getObjectInstance();

	if (!object)
		return;

	for (auto i = 0; i < ctg_world::s_out_world()->m_object_type_buckets[32].num; i++)
	{
		human* humanEntity = (human*)ctg_world::s_out_world()->m_all_objects.elt[ctg_world::s_out_world()->m_object_type_buckets[32].elt[i]];

		if (human_is_dead(humanEntity))
			continue;
		if (humanEntity == player_local_player())
			continue;

		vm_vector headOrigin = vm_vector();
		get_head_pos(humanEntity, &headOrigin, 0);

		fl_vector rootPos = humanEntity->m_pos,
			headPos = headOrigin,
			rootScreen,
			headScreen,
			localOrigin;


		if (!rl_get_screen_coords_from_world_coords(&rootPos, &rootScreen))
			continue;
		if(!rl_get_screen_coords_from_world_coords(&headPos, &headScreen))
			continue;
		if (!rl_get_screen_coords_from_world_coords(&player_local_player()->m_pos, &localOrigin))
			continue;

		float flWidth = fabs((headScreen.y - rootScreen.y) / 4.0f);
		//Box around human entities
		//Not perfect needs work based on self camera angle for sizing box
		if(bBox)
		BoundingBox(rootScreen.x - flWidth - 6.0f, headScreen.y - 8.0f, flWidth * 2.0f + 12.0f, rootScreen.y - headScreen.y + 12.0f, vec4_t(1, 1, 1, 1), 1.f);

		//Simple Snapline to human entities
		if(bSnap)
		drawLine(rootScreen, localOrigin, vec4_t(1, 1, 1, 1));

		if (bName)
		{
			std::string name = humanEntity->char_info->name;
			size_t pos = name.find("e_") + 2;
			name.erase(0, pos);

			drawText(to_upper(name).c_str(), rootScreen.x - (fontStringSize(name.c_str(), .065).x / 2), rootScreen.y, .065, vec4_t(1, 1, 1, 1));
		}
	}
}