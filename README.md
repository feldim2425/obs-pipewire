# OBS Pipewire video source (WIP)

Adds the ability to OBS to receive video trough pipewire.


While OBS has the ability to receive Window and Screen capture trough pipewire this is only enabled on Wayland and is specifically made for Window and Screen share and not for general video input. 

## Usecase
While Pipewire hasn't a ton of usecases in Video currently outside of Screen casting on Wayland, the goal is to make Pipewire video a more viable option than V4L2-Loopbacks on future applications.

## Connecting
This plugin will not automatically connect the video source. I recommend using [helvum](https://gitlab.freedesktop.org/ryuukyu/helvum) for this purpose or create a script if you are using [WirePlumber](https://pipewire.pages.freedesktop.org/wireplumber/) 

