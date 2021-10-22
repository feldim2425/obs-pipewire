/**
 * Copyright (C) 2021 feldim2425
 * 
 * This file is part of obs-pipewire.
 * 
 * obs-pipewire is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * obs-pipewire is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with obs-pipewire.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "source_info.h"

static const char* pwsrc_get_name(void *unused){
    UNUSED_PARAMETER(unused);
    return obs_module_text("Pipewire Video Source");
}

static void* pwsrc_create(obs_data_t *settings, obs_source_t *source){
    
}

void pwsrc_get_sourceinfo(struct obs_source_info *info){
    info->id = "pipewire-video-source",
    info->type = OBS_SOURCE_TYPE_INPUT,
    info->output_flags = OBS_SOURCE_ASYNC_VIDEO,

    info->get_name = pwsrc_get_name;
    info->create = pwsrc_create;
}