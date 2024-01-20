#ifndef LIBUI_FW
#define LIBUI_FW

int uiAndroidInit(JNIEnv *env, jobject context);
uiBox *uiAndroidBox(JNIEnv *env, jobject context, jobject parent);

void uiAndroidSetContent(uiControl *c);

typedef struct uiScroll uiScroll;
struct uiScroll *uiNewScroll();

#endif