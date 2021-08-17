![3dtris](android_ar/app/src/main/res/mipmap-xxhdpi/ic_launcher_foreground.png)

# 3D-tris

A game and an experiment on using WebGL, Emscripten and ARCore. Available in two flavors:

* [WebGL-based browser version](https://oseiskar.github.io/3dtris/)
* Android ARCore version (available on [Google Play](https://play.google.com/store/apps/details?id=xyz.osei.tris))

<a href='https://play.google.com/store/apps/details?id=xyz.osei.tris&pcampaignid=MKT-Other-global-all-co-prtnr-py-PartBadge-Mar2515-1'><img alt='Get it on Google Play' src='https://play.google.com/intl/en_us/badges/images/generic/en_badge_web_generic.png' width='200px'/></a>

## Building the browser version

The browser version can be built like this

1. Install [Emscripten](https://kripken.github.io/emscripten-site/docs/getting_started/downloads.html)
1. locate `emsdk_env.sh` and set that in the root `Makefile`
1. Run `make browser` (also try `make test`)
1. `cd browser`
1. `python -m SimpleHTTPServer`
1. Go to http://localhost:8000/ (and http://localhost:8000/test/)

There is also an old [JavaScript-only version](https://github.com/oseiskar/3dtris/releases/tag/js-only), hosted
in https://oseiskar.github.io/3dtris/ which works without this complicated build process.

## ARCore version for Android

Import `android_ar/build.gradle` to Android Studio 3+ and run.

## Copyright & License info

See `COPYRIGHT.md` for the licences of the included JS libraries.
