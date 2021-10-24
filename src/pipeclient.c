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

#include "pipeclient.h"

pwc_data_t* pwc_create(const char* name){
    const struct spa_pod *param;
    struct spa_pod_builder pod_builder;
    uint8_t params_buffer[1024];
    struct obs_video_info ovi;

    pwc_data_t* data = bzalloc(sizeof(pwc_data_t));
    
    data->thread_loop = pw_thread_loop_new("Pipewire source thread", NULL);
    data->context = pw_context_new(pw_thread_loop_get_loop(data->thread_loop), NULL, 0);

    if(pw_thread_loop_start(data->thread_loop) != 0){
        blog(LOG_WARNING, "[OBS Pipewire source] Error while starting pipewire thread loop");
        return NULL;
    }

    pw_thread_loop_lock(data->thread_loop);

    data->core = pw_context_connect(data->context, NULL, 0);

    if(data->core == NULL){
        blog(LOG_WARNING, "[OBS Pipewire source] Error connecting pipewire core: %m");
        pw_thread_loop_unlock(data->thread_loop);
        return NULL;
    }

    data->stream = pw_stream_new(data->core, name,
        pw_properties_new(
            PW_KEY_MEDIA_TYPE, "Video",
            PW_KEY_MEDIA_CATEGORY, "Capture",
            PW_KEY_MEDIA_ROLE, "Camera",
            NULL
        ));

    pod_builder = SPA_POD_BUILDER_INIT(params_buffer, sizeof(params_buffer));
    obs_get_video_info(&ovi);
    param = spa_pod_builder_add_object(
		&pod_builder, SPA_TYPE_OBJECT_Format, SPA_PARAM_EnumFormat,
		SPA_FORMAT_mediaType, SPA_POD_Id(SPA_MEDIA_TYPE_video),
		SPA_FORMAT_mediaSubtype, SPA_POD_Id(SPA_MEDIA_SUBTYPE_raw),
		SPA_FORMAT_VIDEO_format,
		SPA_POD_CHOICE_ENUM_Id(
			4, SPA_VIDEO_FORMAT_BGRA, SPA_VIDEO_FORMAT_RGBA,
			SPA_VIDEO_FORMAT_BGRx, SPA_VIDEO_FORMAT_RGBx),
		SPA_FORMAT_VIDEO_size,
		SPA_POD_CHOICE_RANGE_Rectangle(
			&SPA_RECTANGLE(320, 240), // Arbitrary
			&SPA_RECTANGLE(1, 1), &SPA_RECTANGLE(8192, 4320)),
		SPA_FORMAT_VIDEO_framerate,
		SPA_POD_CHOICE_RANGE_Fraction(
			&SPA_FRACTION(ovi.fps_num, ovi.fps_den),
			&SPA_FRACTION(0, 1), &SPA_FRACTION(360, 1)));

    int res = pw_stream_connect(data -> stream,
                          PW_DIRECTION_INPUT,
                          PW_ID_ANY,
                          PW_STREAM_FLAG_INACTIVE | PW_STREAM_FLAG_MAP_BUFFERS,  
                          &param, 1);
    
    if (res < 0) {
        blog(LOG_WARNING, "[OBS Pipewire source] Error can't connect: %s\n", spa_strerror(res));
        pw_thread_loop(data->thread_loop);
        return NULL;
    }

    blog(LOG_INFO, "[OBS Pipewire source] Pipewire started %s", name);
    pw_thread_loop_unlock(data->thread_loop);
    return data;
}

void pwc_destroy(pwc_data_t* data){
    if(data->thread_loop){
        pw_thread_loop_wait(data->thread_loop);
        pw_thread_loop_stop(data->thread_loop);
    }

    if(data->stream){
        pw_stream_disconnect(data->stream);
        pw_stream_destroy(data->stream);
    }

    if(data->core){
        pw_core_disconnect(data->core);
    }

    if(data->context){
        pw_context_destroy(data->context);
    }

    if(data->thread_loop){
        pw_thread_loop_destroy(data->thread_loop);
    }
    bfree(data);
}

void pwc_deactivate(pwc_data_t* data);

void pwc_activate(pwc_data_t* data);

void pwc_set_framecallback();

