// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"


void parachuteLaunch()
{
    static fl_vector origin;
    vm_vector fvec, rvec;

    if (human_parachute_is_open(player_local_player()) || human_is_freefalling(player_local_player()) || human_is_skydiving(player_local_player()))
    {
        vm_vector loc;
        get_head_pos(player_local_player(), &loc, 0);

        camera_get_xz_orient(&fvec, &rvec);
        origin = loc;

        human_set_pos_frame(player_local_player(), &origin);

        origin = AnglesToForward(loc, rvec, 200);
    }
}

void hud_render()
{
    if (game_is_paused())
        goto stub;

    if (bParachute)
        parachuteLaunch();

    renderESP();

    drawOptions();

    cheat_effects::Singleton()->flags.golden_gun = bGoldenGun;
    cheat_effects::Singleton()->flags.god_mode = bGodMode;
    cheat_effects::Singleton()->flags.infinite_sprint = bGodMode;
    cheat_effects::Singleton()->flags.evil_cars = bEvilCars;
    cheat_effects::Singleton()->flags.evil_cars_2 = bEvilCars2;

    switch (pedIndex)
    {
    case 0: cheat_effects::Singleton()->ped_type_override = cheat_ped_type_override::CHEAT_PED_TYPE_NONE; break;
    case 1: cheat_effects::Singleton()->ped_type_override = cheat_ped_type_override::CHEAT_PED_TYPE_MASCOT; break;
    case 2: cheat_effects::Singleton()->ped_type_override = cheat_ped_type_override::CHEAT_PED_TYPE_ZOMBIE; break;
    default: cheat_effects::Singleton()->ped_type_override = cheat_ped_type_override::CHEAT_PED_TYPE_NONE; break;
    } 
    
stub:
    game_hud_renderer();
}

FILE* f;
BOOL APIENTRY DllMain( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    DetourUpdateThread(GetCurrentThread());
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:

#ifdef _DEBUG
        if (AllocConsole())
        {
            freopen_s(&f, "CONOUT$", "w", stdout);
            freopen_s(&f, "CONOUT$", "w", stderr);
        }

        system("cls");
        printf("SR3R Base: 0x%llX\n", ResolveImport());
        printf("Window size: %i:%i", game_render_screen_width(), game_render_screen_height());
#endif

        DetourTransactionBegin();
        DetourAttach(&(PVOID&)game_hud_renderer, hud_render);
        DetourTransactionCommit();

        break;
    case DLL_PROCESS_DETACH:

        Opt.clear();

#ifdef _DEBUG
        if (FreeConsole())
        {
            fclose(stdout);
            fclose(stderr);
        }
#endif
        DetourTransactionBegin();
        DetourDetach(&(PVOID&)game_hud_renderer, hud_render);
        DetourTransactionCommit();

        break;
    }
    return TRUE;
}

