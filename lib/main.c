#include <stdio.h>
#include "myjni.h"

#include "ui.h"
#include "ui_android.h"

#ifndef JNI_FUNC
#define JNI_FUNC(ret, name) JNIEXPORT ret JNICALL Java_dev_danielc_us_MainActivity_##name
#endif

void uiAndroidSetContent(uiControl *c);

JNI_FUNC(void, StartUI)(JNIEnv *env, jobject thiz, jobject ctx) {
	uiAndroidInit(env, ctx);

	uiButton *btn = uiNewButton("Helo, World");

	uiAndroidSetContent(btn);
}
