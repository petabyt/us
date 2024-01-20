# Smallest Android APK Attempt
Back in 2016, you could make a [6kb Hello World](https://ajinasokan.com/posts/smallest-app/#import-to-android-studio) Android app. Since then, Google has
added more Material Design (Material You), adaptive icons, and most importantly, breaking API changes. The hello world app from 2016 doesn't even install on the latest Android.

You could easily skip past appcompat and get an even smaller (50kb?) Hello World working on a bare opengl/framebuffer - but nobody does that. This is an attempt to make a *real world* app as small as possible.

Rules:
- Must work on almost all versions (Android 5 to 14)
- Must have icon
- Includes JNI shared object for all required platforms (x86, ARM)
- UI is written with C (LibUI)
- App content is a US Constitution reader
