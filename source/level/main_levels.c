#include "main_levels.h"

MainLevelDefinition main_levels[] = {
    {
        .level_name = "Stereo Madness",
        .gmd_path = "romfs:/main_levels/StereoMadness.gmd",
        .song_path = "romfs:/songs/StereoMadness.mp3",
        .difficulty = MAIN_DIFF_EASY,
        .stars = 1
    },
    {
        .level_name = "Back On Track",
        .gmd_path = "romfs:/main_levels/BackOnTrack.gmd",
        .song_path = "romfs:/songs/BackOnTrack.mp3",
        .difficulty = MAIN_DIFF_EASY,
        .stars = 2
    },
    {
        .level_name = "Polargeist",
        .gmd_path = "romfs:/main_levels/Polargeist.gmd",
        .song_path = "romfs:/songs/Polargeist.mp3",
        .difficulty = MAIN_DIFF_NORMAL,
        .stars = 3
    },
    {
        .level_name = "Dry Out",
        .gmd_path = "romfs:/main_levels/DryOut.gmd",
        .song_path = "romfs:/songs/DryOut.mp3",
        .difficulty = MAIN_DIFF_NORMAL,
        .stars = 4
    },
    {
        .level_name = "Base After Base",
        .gmd_path = "romfs:/main_levels/BaseAfterBase.gmd",
        .song_path = "romfs:/songs/BaseAfterBase.mp3",
        .difficulty = MAIN_DIFF_HARD,
        .stars = 5
    },
    {
        .level_name = "Cant Let Go",
        .gmd_path = "romfs:/main_levels/CantLetGo.gmd",
        .song_path = "romfs:/songs/CantLetGo.mp3",
        .difficulty = MAIN_DIFF_HARD,
        .stars = 6
    },
};