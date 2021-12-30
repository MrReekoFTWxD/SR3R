#include "pch.h"
#include "esp.h"

bool tagTest;

ctg_object* getObjectInstance()
{
	ctg_object* object = 0;
	if (ctg_world::s_out_world()->m_object_type_buckets[32].num > 0)
		object = ctg_world::s_out_world()->m_all_objects.elt[*ctg_world::s_out_world()->m_object_type_buckets[32].elt];

	return object;
}

vec4_t getHumanAffiliation(const human* humanEntity)
{
	vec4_t espColor(1, 1, 1, 1);

	if (human_is_gang_member(humanEntity))
		espColor = human_is_enemy_gang(humanEntity) ? vec4_t(219, 82, 61, 255) : human_is_ally(player_local_player(), humanEntity) ? vec4_t(126, 66, 245, 1) : vec4_t(61, 219, 114, 1);
	else if (human_is_law_enforcement(humanEntity))
		espColor = vec4_t(52, 125, 235, 1);
	else if (human_is_civilian(humanEntity))
		espColor = vec4_t(162, 163, 162, 155);
	else if (human_is_ally(player_local_player(), humanEntity))
		espColor = vec4_t(126, 66, 245, 1);

	return espColor;
}


void nearestTarget()
{
	float nearest_dist;
	fl_vector nearest,
		chestOrigin,
		outChest;
	vm_vector targetChest;

	auto target = find_nearest_human_to_reticule(&nearest_dist, &nearest);
	fl_vector centerScreen(game_render_screen_width() / 2, game_render_screen_height() / 2);

	if (target == player_local_player())
		return;

	get_chest_pos(target, &targetChest, 0);
	chestOrigin = targetChest;
	if (!rl_get_screen_coords_from_world_coords(&chestOrigin, &outChest))
		return;

	drawLine(centerScreen, outChest, getHumanAffiliation(target));

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
		if (!rl_get_screen_coords_from_world_coords(&headPos, &headScreen))
			continue;
		if (!rl_get_screen_coords_from_world_coords(&player_local_player()->m_pos, &localOrigin))
			continue;

		float flWidth = fabs((headScreen.y - rootScreen.y) / 4.0f);
		//Box around human entities
		//Not perfect needs work based on self camera angle for sizing box
		if (bBox)
			BoundingBox(rootScreen.x - flWidth - 6.0f, headScreen.y - 8.0f, flWidth * 2.0f + 12.0f, rootScreen.y - headScreen.y + 12.0f, getHumanAffiliation(humanEntity), 1.f);

		//Simple Snapline to human entities
		if (bSnap)
			drawLine(rootScreen, localOrigin, getHumanAffiliation(humanEntity));

		if (bName)
		{
			std::string name = humanEntity->char_info->name;
			size_t pos = name.find("e_") + 2;
			name.erase(0, pos);

			drawText(to_upper(name).c_str(), rootScreen.x - (fontStringSize(name.c_str(), .065).x / 2), rootScreen.y, .065, vec4_t(1, 1, 1, 1));
		}
	}

	if (bNearestReticle)
		nearestTarget();
}