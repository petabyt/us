PKG=dev.danielc.us

install:
	bash gradlew installDebug -Pandroid.optional.compilation=INSTANT_DEV -Pandroid.injected.build.api=24
	#bash gradlew installDebug -Pandroid.optional.compilation=INSTANT_DEV -Pandroid.injected.build.api=24
	adb shell monkey -p $(PKG) -c android.intent.category.LAUNCHER 1

# JNI DETECTED ERROR IN APPLICATION
log:
	adb logcat | grep -F "`adb shell ps | grep $(PKG) | tr -s [:space:] ' ' | cut -d' ' -f2`"

ln:
	rm -f src/main/java/LibUI*.java
	cd src/main/java/ && ln ../../../../libui-android/*.java .

	cd lib && rm -f libui.c ui.h ui_android.h
	cd lib && ln ../../libui-android/*.c ../../libui-android/*.h .
