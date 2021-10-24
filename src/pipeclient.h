// Copyright (C) 2021 feldim2425
// 
// This file is part of obs-pipewire.
// 
// obs-pipewire is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
// 
// obs-pipewire is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with obs-pipewire.  If not, see <http://www.gnu.org/licenses/>.

#pragma once

#include <obs-module.h>
#include <pipewire/pipewire.h>
#include <spa/param/video/format-utils.h>

struct pwc_data_st
{
    obs_data_t* settings;
    obs_source_t* source;

    struct pw_thread_loop *thread_loop;
	struct pw_context *context;

	struct pw_core *core;
	struct spa_hook core_listener;

	struct pw_stream *stream;
	struct spa_hook stream_listener;
	struct spa_video_info format;

};

typedef struct pwc_data_st pwc_data_t;
typedef void (*pw_vframe_cb)();

pwc_data_t* pwc_create(const char* name);

void pwc_destroy(pwc_data_t* data);

void pwc_deactivate(pwc_data_t* data);

void pwc_activate(pwc_data_t* data);

void pwc_set_framecallback();

