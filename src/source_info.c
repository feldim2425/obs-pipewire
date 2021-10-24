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
#include "pipeclient.h"

static const char* pwsrc_get_name(void *unused){
    UNUSED_PARAMETER(unused);
    return obs_module_text("Pipewire Video Source");
}

static void* pwsrc_create(obs_data_t *settings, obs_source_t *source){
    return pwc_create("test");
}

static void pwsrc_destroy(void* ptr){
    pwc_destroy(ptr);
}

static unsigned int pwsrc_get_width(void* ptr){
    return 0;
}

static unsigned int pwsrc_get_height(void* ptr){
    return 0;
}

static obs_properties_t* pwsrc_get_properties(void* ptr){
    obs_properties_t* props = obs_properties_create();
    return props;
}

static void pwsrc_default_properties(obs_data_t* settings){

}

static void pwsrc_tick(void* ptr, float seconds){

}

static void pwsrc_src_activate(void* ptr){

}

static void pwsrc_src_deactivate(void* ptr){

}

static void pwsrc_src_show(void* ptr){

}

static void pwsrc_src_hide(void* ptr){

}

void pwsrc_get_sourceinfo(struct obs_source_info *info){
    info->id = "pipewire-video-source",
    info->type = OBS_SOURCE_TYPE_INPUT,
    info->output_flags = OBS_SOURCE_ASYNC_VIDEO,

    info->get_name = pwsrc_get_name;
    info->create = pwsrc_create;
    info->destroy = pwsrc_destroy;

    info->video_tick = pwsrc_tick;
    info->get_height = pwsrc_get_height;
    info->get_width = pwsrc_get_width;

    //info->get_defaults = pwsrc_default_properties;
    //info->get_properties = pwsrc_get_properties;

    info->activate = pwsrc_src_activate;
    info->deactivate = pwsrc_src_deactivate;
    info->show = pwsrc_src_show;
    info->hide = pwsrc_src_hide;
}