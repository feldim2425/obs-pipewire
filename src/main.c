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

#include <obs-module.h>
#include "source_info.h"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("obs-pipewire", "en-US")
OBS_MODULE_AUTHOR("feldim2425")


bool obs_module_load(void) {
    struct obs_source_info info = {};
    pwsrc_get_sourceinfo(&info);
    obs_register_source(&info);
    
    return true;
}

void obs_module_unload(void){
    
}